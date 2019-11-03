#include <iostream>
#include <math.h>
#include "Vecteur.h"
#include "Matrice.h"
#include "Maillage.h"
#include "Quadrature.h"
using namespace std;

enum schema_type {Euler_implicite, Cranck_Nicolson};
Matrice Ksi(2,2);

const double r=0.05;

double (*tau_P1[3])(const Vecteur &)={tau1_P1, tau2_P1, tau3_P1}; // Tableau des fonctions de base P1 pour le triangle de référence
Vecteur (*Dtau_P1[3])(const Vecteur &)={Dtau1_P1, Dtau2_P1, Dtau3_P1}; // Tableau des gradients des fonctions de base P1 pour le triangle de référence

double (*tau_P2[6])(const Vecteur &)={tau1_P2, tau2_P2, tau3_P2, tau12_P2, tau23_P2, tau31_P2}; // Tableau des fonctions de base P2 pour le triangle de référence
Vecteur (*Dtau_P2[6])(const Vecteur &)={Dtau1_P2, Dtau2_P2, Dtau3_P2, Dtau12_P2, Dtau23_P2, Dtau31_P2};



Matrice A(const Vecteur & U)
{
//    Matrice res(Ksi);
//    res(1,1)*=U(1)*U(1);
//    res(1,2)*=U(1)*U(2);
//    res(2,1)*=U(2)*U(1);
//    res(2,2)*=U(2)*U(2);
//    res=0.5*res;
    Matrice res(2,2); res(1,1)=res(2,2)=1.;
    return res;
}

Vecteur V(const Vecteur & U)
{
    Vecteur res(2);
    res(1)=(Ksi(1,1)+0.5*Ksi(2,1)-r)*U(1);
    res(2)=(Ksi(2,2)+0.5*Ksi(1,2)-r)*U(2);
    return res;
}

Matrice matM_elem(const elmt_type P, const Quadrature & Q)
{
    Matrice Mel;
    if(P==P1_)
    {
        Mel=Matrice(3,3,1./24.);
        Mel(1,1)=Mel(2,2)=Mel(3,3)=1./12.;
    }
    else
    {
        Mel=Matrice(6,6);
        double (**tau)(const Vecteur &)=tau_P2;
        for(int i=1; i<=6; ++i)
        {
            for(int j=1; j<=i; ++j)
            {
                for(int k=0; k<Q.n; ++k)
                {
                    Mel(j,i)=Mel(i,j)+=Q.omega[k]*(*tau[i-1])(Q.M[k])*(*tau[j-1])(Q.M[k]); // Formule de quadrature pour approcher l'intégrale obtenue par changement de variable
                }
            }
        }
    }
    return Mel;
}

Matrice matK_elem(const Matrice & B, const Matrice & B_inv_t, const Vecteur & S1, const elmt_type P, const Quadrature & Q)
{
    const int m=(P==P1_ ? 3 : 6); // m est le nombre de degrés de liberté dans un triangle
    Vecteur (**Dtau)(const Vecteur &)=(P==P1_ ? Dtau_P1 : Dtau_P2); // Dtau est un tableu de pointeur vers les fonctions calculant les gradients des fonctons de base pour le triangle de référence
    const Matrice Kel(m,m);

    for(int i=1; i<=m; ++i)
    {
        for(int j=1; j<=i; ++j)
        {
            for(int k=0; k<Q.n; ++k)
            {
                Vecteur Current_point(B*Q.M[k]+S1); //Transforme le point de Quadrature numero k du triangle de référence vers le triangle courant
                Kel(j,i)=Kel(i,j)+=Q.omega[k]*dot(A(Current_point)*(B_inv_t*(*Dtau[i-1])(Q.M[k])),B_inv_t*(*Dtau[j-1])(Q.M[k])); // Formule de quadrature pour approcher l'intégrale obtenue par changement de variable
            }
        }
    }
    return Kel;
}

Matrice matB_elem(const Matrice & B, const Matrice & B_inv_t, const Vecteur & S1, const elmt_type P, const Quadrature & Q)
{
    const int m=(P==P1_ ? 3 : 6);
    double (**tau)(const Vecteur &)=(P==P1_ ? tau_P1 : tau_P2);
    Vecteur (**Dtau)(const Vecteur &)=(P==P1_ ? Dtau_P1 : Dtau_P2);

    Matrice B_inv(B_inv_t);
    B_inv(1,2)=B_inv_t(2,1);
    B_inv(2,1)=B_inv_t(1,2);

    Matrice Bel(m,m);

    for(int i=1; i<=m; ++i)
    {
        for(int j=1; j<=m; ++j)
        {
            for(int k=0; k<Q.n; ++k)
            {
                Vecteur Current_point(B*Q.M[k]+S1);
                Bel(i,j)+=Q.omega[k]*dot(V(Current_point),B_inv_t*((*Dtau[j-1])(Q.M[k])))*((*tau[i-1])(Q.M[k]));
            }
        }
    }
    return Bel;
}

void matrice_elem(const Maillage & msh, const Triangle & tri, Matrice & Mel, Matrice & Kel, Matrice & Bel, const Quadrature & Q)
{ // Calcul les matrices élémentaires pour le triangle tri
    const elmt_type P=msh.get_type();

    const Vecteur S1(msh.som(tri(1))); //Sommets du triangle tri
    const Vecteur S2(msh.som(tri(2)));
    const Vecteur S3(msh.som(tri(3)));

    Matrice B(2,2); //Matrice B_l pour la transformation affine du triangle de référence vers le triangle tri
    B(1,1)=S2(1)-S1(1);
    B(1,2)=S3(1)-S1(1);
    B(2,1)=S2(2)-S1(2);
    B(2,2)=S3(2)-S1(2);
    double Det_B=B(1,1)*B(2,2)-B(2,1)*B(1,2);
    double ADet_B=fabs(Det_B);

    Matrice B_inv_t(2,2); //B_inv_t=(B^-1)^T
    B_inv_t(1,1)=B(2,2);
    B_inv_t(1,2)=-B(2,1);
    B_inv_t(2,1)=-B(1,2);
    B_inv_t(2,2)=B(1,1);
    B_inv_t=(1./Det_B)*B_inv_t;
    Mel=ADet_B*matM_elem(P,Q); //Calcul des matrices elementaires
    Kel=ADet_B*matK_elem(B,B_inv_t,S1,P,Q);
    Bel=ADet_B*matB_elem(B,B_inv_t,S1,P,Q);
}

void build(const Maillage & msh, Matrice & MM, Matrice & KK, Matrice & BB, Matrice & DD, const Quadrature & Q)
{
    // Construit les matrices globales

    const elmt_type P=msh.get_type();
    const int m=(P==P1_ ? 3 : 6);

    const int nb_tri=msh.nb_tri();
    Triangle tri;

    for(int l=1;l<=nb_tri;++l) // On se place dans le triangle l
    {
        tri=msh.tri(l);

        Matrice Mel(m,m);
        Matrice Kel(m,m);
        Matrice Bel(m,m);
        matrice_elem(msh, tri, Mel, Kel, Bel, Q); // Calcul des matrices élémentaires pour le triangle l

        for(int i=1;i<=m;++i) // Assemblage des matrices globales
        {
            int I=tri(i);
            for(int j=1;j<=m;++j)
            {
                int J=tri(j);
                MM(I,J)+=Mel(i,j);
                KK(I,J)+=Kel(i,j);
                BB(I,J)+=Bel(i,j);
            }
        }
    }
    DD=KK+BB+r*MM;
}

void validation_matrices_globales(int nb_noeuds, const Matrice & MM, const Matrice & KK, const Matrice & BB)
{
    Vecteur V(nb_noeuds,1.);
    cout << "Validation des matrices globales\n";
    // Test de MM
    const double mes_omega=dot(MM*V,V);
    cout << "<MM*V,V> = " << mes_omega << '\n';

    // Test de KK
    Vecteur zero=KK*V;
    cout << "||KK*V||^2 = " << dot(zero,zero) << '\n';

    // Test de BB
    Vecteur x=BB*V;
    cout << "||BB*V||^2 = " << dot(x,x) << "\n\n";
}

void schema_iteratif(const schema_type st, const Matrice & MM, const Matrice & DD, double Delta_t, double T, double K, const Maillage & msh, const string & file)
{ // Calcul les valeurs de P_k pour lorsque k décrit l'intervalle [0,T] avec un pas Delta_t
    // puis enregistre les vecteurs obtenus dans le fichier "file"
    ofstream f_out(file.c_str());
    if(!f_out)
        cout << "Impossible d'ouvrir le fichier " << file << '\n';
    else
    {
        int N=msh.nb_noeuds();
        int k_max=static_cast<int>(T/Delta_t);
        Vecteur P(N); // Vecteur qui va contenir les valeurs P_k

        cout << "Calcul des iteres avec le schema : " << (st==Euler_implicite ? "Euler implicite\n" : "Cranck-Nicolson ordre 2\n");
        cout << "Temps final T = " << T << '\n';
        cout << "Pas de temps Delta_t = " << Delta_t << '\n';
        cout << "Nombre d'iteres k_max = " << k_max << '\n';
        for(int k=1; k<=N; ++k)
        {
            P(k)=max((msh.som(k))(1)+(msh.som(k))(2)-K,0.); // P=Q_0
        }
        f_out << k_max << '\n'; // On écrit le nombre de vecteurs P_k calculés
        f_out << Delta_t << '\n'; // puis le pas de temps
        f_out << P << '\n';

        Matrice EE,FF;
        if(st==Euler_implicite) {EE=MM+Delta_t*DD; FF=MM;}
        else {EE=MM+Delta_t/2.*DD; FF=MM-Delta_t/2.*DD;}
        Matrice L, U;
        LU_factor(EE,L,U);
        for(int k=1; k<=k_max; ++k)
        {
            P=FF*P;
            P=LU_solve(L,U,P); // Calcul du nouvel itéré
            f_out << P << '\n'; // On enregistre le vecteur P_k dans le fichier
        }
        f_out.flush();
        f_out.close();
    }

}

void run_FE(elmt_type P, int m, int n, const schema_type st)
{
    const int noeuds_tri=(P==P1_ ? 3 : 6); // noeuds_tri est le nombre de noeuds dans un triangle pour le maillage courant
    const Maillage msh(P,m,n);
    const int nb_noeuds=msh.nb_noeuds(); // Nombre de noeuds dans tous le maillage
	msh.save_to_file("msh.txt");
	cout << "Maillage de type " << (P==P1_ ? "P1" : "P2") << '\n';
	cout << "Decoupage : " << m << 'x' << n << '\n';
	cout << "Nombre de noeuds : " << nb_noeuds << "\n\n";

    Matrice MM(nb_noeuds,nb_noeuds);
    Matrice KK(nb_noeuds,nb_noeuds);
    Matrice BB(nb_noeuds,nb_noeuds);
    Matrice DD(nb_noeuds,nb_noeuds);
	const Quadrature * Q=(P==P1_ ? Gauss_Legendre_3pt() : Gauss_Lobatto_7pt());

// On détermine la position des trois sommets du triangle de référence
	Vecteur T1(2), T2(2), T3(2);
	T2(1)=T3(2)=1.;
	int T1_corr, T2_corr, T3_corr;

	for(int k=1; k<=nb_noeuds; ++k)
    {
        if(msh.som(k)==T1) T1_corr=k;
        else if(msh.som(k)==T2) T2_corr=k;
        else if(msh.som(k)==T3) {T3_corr=k; break;}
    }

// Validation des matrices élémentaire
    cout << "Validation des matrices elementaires\n";
    Matrice Mel_ref(noeuds_tri,noeuds_tri), Kel_ref(noeuds_tri,noeuds_tri), Bel_ref(noeuds_tri,noeuds_tri);
    Triangle tri_ref(T1_corr,T2_corr,T3_corr);
    matrice_elem(msh,tri_ref,Mel_ref,Kel_ref,Bel_ref,*Q);
    cout << "Mel_ref = " << Mel_ref << '\n';
    cout << "Kel_ref = " << Kel_ref << '\n';
    cout << "Bel_ref = " << Bel_ref << '\n';

    build(msh, MM, KK, BB, DD, *Q);
    validation_matrices_globales(nb_noeuds,MM,KK,BB);

    schema_iteratif(st,MM,DD,1.,2.*365.,1.,msh,"results.txt");

    delete Q;
}

int main()
{
    Ksi(1,1)=Ksi(2,2)=0.04;
    Ksi(1,2)=Ksi(2,1)=-0.024;

    //test de factorisation LU
	Matrice A(3,3);
	A(1,1)=A(2,2)=A(3,3)=2.;
	A(1,2)=A(2,1)=A(2,3)=A(3,2)=-1.;

	Matrice L,U;
	LU_factor(A,L,U);
	Vecteur Y(3,4.);
	cout << "Validation de la factorisation LU\n";
	(LU_solve(L,U,Y)).print();
	cout << '\n';

    run_FE(P1_,10,10,Euler_implicite);

    return 0;
}

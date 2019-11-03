#ifndef QUADRATURE_H
#define QUADRATURE_H

#include <iostream>
#include "Vecteur.h"

using namespace std;

class Quadrature // Classe définissant une quadrature à n points avec les poids associés
{
public:
    int n; // Taille de la quadrature
    double * omega; // Poids de quadrature
    Vecteur * M; // Points de quadrature

    Quadrature() : n(0), omega(nullptr), M(nullptr){} // Constructeur par défaut
    Quadrature(int taille=0) : n(taille) // Constructeur avec paramètre de taille
    {
        if(n)
        {
            omega=new double[n];
            M=new Vecteur[n];
            for(int k=0; k<n; ++k)
                M[k]=Vecteur(2);
        }
    }
    ~Quadrature() // Destructeur
    {
        if(omega) {delete [] omega;}
        if(M) {delete [] M;}
    }
};

Quadrature * Gauss_Legendre_3pt() // Génère une quadrature de Gauss-Legendre à 3 points et retourne le pointeur correspondant
{
    double s0=1./6.;
    double s1=2./3.;

    Quadrature * Q=new Quadrature(3);

    Q->M[0]=Q->M[1]=Q->M[2]=Vecteur(2,s0);
    (Q->M[1])(1)=(Q->M[2])(2)=s1;
    Q->omega[0]=Q->omega[1]=Q->omega[2]=s0;
    return Q;
}

Quadrature * Gauss_Lobatto_7pt() // Génère une quadrature de Gauss-Lobatto à 7 points et retourne le pointeur correspondant
{
    double s0=1./3.;
    double s1=(6.-sqrt(15.))/21.;
    double s2=(6.+sqrt(15.))/21.;
    double s3=(9.+2.*sqrt(15.))/21.;
    double s4=(9.-2.*sqrt(15.))/21.;
    double eta0=9./80.;
    double eta1=(155.-sqrt(15.))/2400.;
    double eta2=(155.+sqrt(15.))/2400.;

    Quadrature * Q=new Quadrature(7);
    for(int i=0; i<7; i++)
    Q->M[0]=Vecteur(2,s0);
    Q->M[1]=Vecteur(2,s1);
    (Q->M[2])(1)=s1; (Q->M[2])(2)=s3;
    (Q->M[3])(1)=s3; (Q->M[3])(2)=s1;
    Q->M[4]=Vecteur(2,s2);
    (Q->M[5])(1)=s2; (Q->M[5])(2)=s4;
    (Q->M[6])(1)=s4; (Q->M[6])(2)=s2;

    Q->omega[0]=eta0;
    Q->omega[1]=Q->omega[2]=Q->omega[3]=eta1;
    Q->omega[4]=Q->omega[5]=Q->omega[6]=eta2;
    return Q;
}

#endif // QUADRATURE_H

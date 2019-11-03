#include "Maillage.h"

//
//Point::Point() //constructeur par defaut
//{
//    dim=0;
//    pCor=0;
//}
//
//Point::Point(double x, double y) //constructeur prenant deux coordonnees, ne net pas cont & ds les constructeurs sauf dans le constructeur par copie
//{
//    dim=2;
//    pCor= new double[dim];
//    pCor[0]=x;
//    pCor[1]=y;
//}
//
//Point::Point(const  Point& P) //constructeur par copie
//{
//    dim=P.dim;
//    pCor=new double[dim];
//    for(int i=0; i<dim; i++)
//        pCor[i]=P.pCor[i];
//}
//
//Point & Point::operator=(const Point & P)//copie de P ds l'objet courant
//{
//    if(this==&P)//this est un pointeur donc c'est mormal de le comparer a un pointeur
//        return *this;
//    if(dim!=P.dim)
//    {
//        delete[] pCor;
//        pCor=new double [P.dim];
//    }
//    dim=P.dim;
//    for (int i=0; i<dim; i++)
//        pCor[i]=P.pCor[i];
//
//    return *this;
//}
//
////Operateurs algebriques internes
////////////////////////////////////////
//Point & Point::operator+=(const Point & P)// PC=PC+P
//{
//    if (dim!=P.dim)
//        exit(-1);
//    for (int i=0; i<dim; i++)
//        pCor[i]+=P.pCor[i];
//    return *this;
//}
//
//Point & Point::operator-=(const Point & P) //PC=PC-P
//{
//    if (dim!=P.dim)
//        exit(-1);
//    for (int i=0; i<dim; i++)
//        pCor[i]-=P.pCor[i];
//    return *this;
//}
//
//Point & Point::operator+=(const double & c)//P=P+c
//{
//    for (int i=0; i<dim; i++)
//        pCor[i]=c+pCor[i];
//    return *this;
//}
//Point & Point::operator-=(const double & c)//P=P-c
//{
//    for (int i=0; i<dim; i++)
//        pCor[i]=pCor[i]-c;
//    return *this;
//}
//Point & Point::operator*=(const double & c) //PC=PC*c
//{
//    for (int i=0; i<dim; i++)
//        pCor[i]=c*pCor[i];
//    return *this;
//}
//Point & Point::operator/=(const double & c) //PC=CP/c
//{
//    if(c==0)
//        exit(-1);
//    for (int i=0; i<dim; i++)
//        pCor[i]=pCor[i]/c;
//    return *this;
//}
//
//
////Operateurs Booleens
//bool operator==(const Point & P1, const Point & P2) //P1=P2?
//{
//    if (P1.dim!=P2.dim)
//        return false;
//    for (int i=0; i<P1.dim; i++)
//    {
//        if(P1.pCor[i]!=P2.pCor[i])
//        {
//
//            return false;
//            break;
//        }
//    }
//    return true;
//}
//
//bool operator!=(const Point & P1, const Point & P2) //P1=P2?
//{
//    if (P1.dim!=P2.dim)
//        return true;
//    for (int i=0; i<P1.dim; i++)
//    {
//        if(P1.pCor[i]!=P2.pCor[i])
//        {
//            return true;
//            break;
//        }
//    }
//    return false;
//}
//
//
////Operateurs externes a la classe
//////////////////////////////////////////////
//Point operator+(const Point & P)
//{
//    return P;
//}
//
//Point operator-(const Point & P) //-P
//{
//    Point Q;
//    Q.dim=P.dim;
//    Q.pCor=new double[Q.dim];
//    for (int i=0; i<Q.dim; i++)
//        Q.pCor[i]=-P.pCor[i];
//    return Q;
//}
//Point operator+(const double & c,const Point & P) //c+P
//{
//    Point Q;
//    Q.dim=P.dim;
//    Q.pCor=new double[Q.dim];
//    for (int i=0; i<Q.dim; i++)
//        Q.pCor[i]=c+P.pCor[i];
//    return Q;
//}
//
//Point operator+(const Point & P,const double & c) //P+c
//{
//    Point Q;
//    Q.dim=P.dim;
//    Q.pCor=new double[Q.dim];
//    for (int i=0; i<Q.dim; i++)
//        Q.pCor[i]=c+P.pCor[i];
//    return Q;
//}
//
//Point operator-(const double & c,const Point & P) //c-P
//{
//    Point Q;
//    Q.dim=P.dim;
//    Q.pCor=new double[Q.dim];
//    for (int i=0; i<Q.dim; i++)
//        Q.pCor[i]=c-P.pCor[i];
//    return Q;
//}
//
//Point operator-(const Point & P,const double & c) //P-c
//{
//    Point Q;
//    Q.dim=P.dim;
//    Q.pCor=new double[Q.dim];
//    for (int i=0; i<Q.dim; i++)
//        Q.pCor[i]=P.pCor[i]-c;
//    return Q;
//}
//
//Point operator*(const double & c,const Point & P) //c*P
//{
//    Point Q;
//    Q.dim=P.dim;
//    Q.pCor=new double[Q.dim];
//    for (int i=0; i<Q.dim; i++)
//        Q.pCor[i]=c*P.pCor[i];
//    return Q;
//}
//
//Point operator*(const Point & P,const double & c) //P*c
//{
//    Point Q;
//    Q.dim=P.dim;
//    Q.pCor=new double[Q.dim];
//    for (int i=0; i<Q.dim; i++)
//        Q.pCor[i]=c*P.pCor[i];
//    return Q;
//}
//
//Point operator/(const Point & P,const double & c) //P/c
//{
//Point Q;
//Q.dim=P.dim;
//Q.pCor=new double[Q.dim];
//for (int i=0; i<Q.dim; i++)
//Q.pCor[i]=P.pCor[i]/c;
//return Q;
//}
//    Point Point::operator-(const double & c,const Point & P) //c-P
//    {Point Q;
//    Q.dim=P.dim;
//    Q.pCor=new double[Q.dim];
//    for (int i=0; i<dim; i++) pCor[i]=c+P.pCor[i];
//    return Q;
//    }

//Point operator+(const Point & P1, const Point & P2)//P1+P2
//{
//if (P1.dim!=P2.dim)
//exit(-1);
//Point Q;
//Q.dim=P1.dim;
//Q.pCor=new double[Q.dim];
//for (int i=0; i<Q.dim; i++)
//Q.pCor[i]=P1.pCor[i]+P2.pCor[i];
//return Q;
//}
//Point operator-(const Point & P1, const Point &P2)//P1-P2
//{
//if (P1.dim!=P2.dim)
//exit(-1);
//Point Q;
//Q.dim=P1.dim;
//Q.pCor=new double[Q.dim];
//for (int i=0; i<Q.dim; i++)
//Q.pCor[i]=P1.pCor[i]-P2.pCor[i];
//return Q;
//}

////impression
////////////////////
//ostream & operator<<(ostream & out, const Point & P)
//{
//cout<<"vecteur de dimension "<<P.dim<<" : "<<endl;
//for(int i=0; i<P.dim; i++)
//{
//cout<<P.pCor[i] <<", ";
//cout<<endl;
//}
//cout<<")"<<endl;
//return out;
//}

////////////////////////////////
//classe Triangle
///////////////////////////////////

Triangle::Triangle()
{
    // ?
}

Triangle::Triangle(const Triangle & tri)
{
    reserve(tri.size());
    for(vector<int>::const_iterator it=tri.begin(); it!=tri.end(); ++it)
    {
        push_back(*it);
    }
}

Triangle::Triangle(int i, int j, int k)//ici i, j,et k sont les numeros globaux des sommets de mon triangle( i est le numero global du sommet de numero local 1,
//j est le numero global du numero de sommet local 2 et k est le numero global du sommet de numero global 3)
// attention t'as pas le droit d'ecrire un constructeur avec un nom autre que le nom de la classe, ie que comme tu voulais faire TriangleP1(coe constructeur d'un elmt P1)
//et faire TriangleP2(coe constructeur des elmts P2) , tu n'as pas le droit. Rappelle toi que si tu as des constructeurs avec  des nbre d'arg d'entree diff, alors le compilateur sait ce qu'il doit utiliser
{
    reserve(3);
    push_back(i);
    push_back(j);
    push_back(k);
}

int Triangle::operator()(int i) const// on rentre le numero local i du sommet dont on veut obtemir le numero global
{
    return at(i-1);
}

Triangle::Triangle(int i, int j, int k, int l, int m, int n)//de i a j ce sont les numeros globaux de mes triangles que je rentrerais
{
    reserve(6);
    push_back(i);
    push_back(j);
    push_back(k);
    push_back(l);
    push_back(m);
    push_back(n);
}

ostream & operator<<(ostream & out, const Triangle & Ns) //permet d'afficher les numeros globaux du triangle Ns
{
    for(vector<int>::const_iterator i=Ns.begin(); i!=Ns.end(); ++i)
    {
        out << (*i) << ((i==Ns.end()-1) ? "" : " ");
    }
    return out;
}


Triangle Triangle::shift(int s) const// ajoute s a chacun des numeros globaux du triangle concerne, le but etant d'utiliser cette fonction pour ...
{
    Triangle R=*this;
    for(vector<int>::iterator i=R.begin(); i!=R.end(); ++i)
    {
        *i+=s;
    }
    return R;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//                             Classe Maillage
////////////////////////////////////////////////////////////////////////////////////////////////////////////////



/////////////////////////////////////////////   Maillage P1    /////////////////////////////////////////////////

void Maillage::maille_carre_uniteP1(int m, int n)//maillage avec des elements P1
{
    //////////////liste de sommets ////////////////////

    liste_som.reserve((m+1)*(n+1));//(m+1)*(n+1) etant le nbre de noeuds(en faisant un'reserve' on evite au systeme de devoir faire une reallocation de memoire a chaque fois que l;on fait un 'pushback'
    for(int i=1; i<n+2; ++i)
    {
        for(int j=1; j<m+2; ++j)
        {
            Vecteur V(2);
            V(1)=static_cast<double>(j-1)/static_cast<double>(m);
            V(2)=static_cast<double>(i-1)/static_cast<double>(n);
            liste_som.push_back(V);//coord du sommet de numero global du sommet Pij(et ce nuero est j+(m+1)*(i-1), meme coe on n'a pas besoin puisque le pushback fais le travail

        }
    }


    liste_tri.reserve(2*n*m);// avec 2*n*m qui designe le nombre de triangles

    bool b=true;//on introduit le booleen pour avoir un maillage qui change de sens d'un rectangle du maillage au suivant
    for (int i=1; i<n+1; i++)//i designe la ieme ligne de mon maillage (ça voir ton dessin papier)
    {
        for (int j=1; j<m+1; j++)// j designe la jeme colonne de mon maillage
        {
            int Pij=j+(m+1)*(i-1);
            if (b==true)
            {
                //le constructeur triangle prend en entree les numeros globaux pas les coord des noeuds
                liste_tri.push_back(Triangle(Pij+1, Pij+m+2, Pij));
                liste_tri.push_back(Triangle(Pij+m+1, Pij, Pij+m+2));
                b=false; // on change la valeur du booleen pour que a la prochaine iteration du for( donc au prochain carre on divise differemment
            }
            else
            {
                liste_tri.push_back(Triangle(Pij+m+2, Pij+m+1, Pij+1));
                liste_tri.push_back(Triangle(Pij, Pij+1, Pij+m+1));
                b=true;
            }
        }
    }
    type_maillage=P1_;
}


///////////////////////////////////////////////      Maillage P2     ///////////////////////////////////////////////////////


void Maillage::maille_carre_uniteP2(int m, int n)//maillage avec des elements P2
{
    ///////////////liste des sommets du maillage, on peut utiliser 2 methodes: soit on utilise un 'reserve' et apres on fait un push_back
    ///////////////ce qui est moins couteux; soit on utilise un resize (attention on ne cree pas le vecteur car comme notre classe vecteur herite de la classe vecteur de la STL qui a un constructeur par defaut qui cree un vecteur vide, et donc tout ce que tu as a faire c'est de le 'resizer' puis d'utiliser le crochert pour acceder a ses elements
    liste_som.reserve((2*m+1)*(2*n+1));
    for (int i=1; i<2*n+2; i++)
    {
        for(int j=1; j<2*m+2; j++)
        {
            Vecteur V(2);
            V(1)=static_cast<double>(j-1)/static_cast<double>(2*m);
            V(2)=static_cast<double>(i-1)/static_cast<double>(2*n);
            liste_som.push_back(V);
        }
    }
    ////////////////liste des triangles du maillage(pour chaque triangle, on cite les 6 numeros globaux des 6 points constituant l'elmt P2, qui apparaissent ds l'ordre croissant des numeroslocaux du triangle)
    ////////////////!!!l'emplacement ou apparait chaque triangle dans la liste correspond a son numero global, donc pour acceder a un triangle il suffira du'utiliser'at(numero de triangle)'

    //for (int k=1; k<2*m*n+1, k+2)//numero du triangle pas besoin d'avoir explicitement le numero du triangle puisque tu remplis par push_back, et que tu peux remplir successivement
    liste_tri.reserve(2*n*m);
    bool b=true;//on introduit le booleen pour avoir un maillage qui change de sens d'un rectangle du maillage au suivant
    for(int i=1; i<2*n+1; i=i+2)
    {
        for (int j=1; j<2*m+1; j=j+2)
        {
            int Pij=(j-1)*2*m+j+i-1;
            if (b==true)
            {
                liste_tri.push_back(Triangle(Pij+2, Pij+2*(2*m+1)+2, Pij, Pij+2*m+3, Pij+(2*m+2), Pij+1));// triangle n 1 du triangle considere
                liste_tri.push_back(Triangle(Pij+2*(2*m+1), Pij, Pij+2*(2*m+1)+2, Pij+(2*m+1), Pij+(2*m+2), Pij+2*(2*m+1)+1));
                b=false; // on change la valeur du booleen pour que a la prochaine iteration du for( donc au prochain carre on divise differemment
            }
            else
            {
                liste_tri.push_back(Triangle(Pij, Pij+2, Pij+2*(2*m+1), Pij+1, Pij+(2*m+2), Pij+(2*m+1)));
                liste_tri.push_back(Triangle(Pij+2*(2*m+1)+2, Pij+2*(2*m+1), Pij+2, Pij+2*(2*m+1)+1, Pij+(2*m+2), Pij+(2*m+3)));
                b=true;
            }
        }
    }

    liste_tri2.reserve(8*n*m);
    int i=1;
    for(vector<Triangle>::const_iterator it = liste_tri.begin(); it != liste_tri.end(); ++it, ++i)
    {
        switch(i%4)
        {
        case 1 :
            liste_tri2.push_back(Triangle((*it)(6),(*it)(5),(*it)(3)));
            liste_tri2.push_back(Triangle((*it)(5),(*it)(6),(*it)(4)));
            liste_tri2.push_back(Triangle((*it)(1),(*it)(4),(*it)(6)));
            liste_tri2.push_back(Triangle((*it)(4),(*it)(2),(*it)(5)));
            break;
        case 2 :
            liste_tri2.push_back(Triangle((*it)(4),(*it)(2),(*it)(5)));
            liste_tri2.push_back(Triangle((*it)(6),(*it)(5),(*it)(3)));
            liste_tri2.push_back(Triangle((*it)(5),(*it)(6),(*it)(4)));
            liste_tri2.push_back(Triangle((*it)(1),(*it)(4),(*it)(6)));
            break;
        case 3 :
            liste_tri2.push_back(Triangle((*it)(1),(*it)(4),(*it)(6)));
            liste_tri2.push_back(Triangle((*it)(5),(*it)(6),(*it)(4)));
            liste_tri2.push_back(Triangle((*it)(4),(*it)(2),(*it)(5)));
            liste_tri2.push_back(Triangle((*it)(6),(*it)(5),(*it)(3)));
            break;
        case 0 :
            liste_tri2.push_back(Triangle((*it)(6),(*it)(5),(*it)(3)));
            liste_tri2.push_back(Triangle((*it)(1),(*it)(4),(*it)(6)));
            liste_tri2.push_back(Triangle((*it)(5),(*it)(6),(*it)(4)));
            liste_tri2.push_back(Triangle((*it)(4),(*it)(2),(*it)(5)));
            break;
        }
    }
    type_maillage=P2_;
}

///////////////////////////////////////////      Fonctions communes aux deux types de maillages     /////////////////////////////////////////////




ostream & operator <<(ostream & out, const Maillage & M)
{
    return M.Print(out, true);//en mettant l'argument 'with_comments' a true , cela me permet d'afficher les donnees avec des commentaires    return out;
}

void Maillage::save_to_file(const string & View) const//View c'est le nom de la variable chaine de caracteres dans laquelle tu mets le nom du fichier dans lequel tu veux ecrire, dc apres ds ton main tu mettras pour ton maillage M1 par ex. M1.save_to_file("affichage_matlab", false);  pour enregistrer ton maillage M1 dans le fichier affichage_matlab
{
    ofstream f_out(View.c_str());//j'ouvre le fichier dont le nom est contenu dans le string 'View' et j'obtiens un flux d'ecriture 'f_out'
    if(!f_out)
        cout << "Impossible d'ouvrir le fichier " << View << '\n';
    else
    {
        Print(f_out, false);//pas besoin de M. au debut car je suis dans la classe Maillage, dc j'agis implicitement sur un maillage
    }
    f_out.flush();
    f_out.close(); //fermeture du flux d'ecriture 'f_out'
}
ostream & Maillage::Print(ostream & out, bool with_comments) const
{
    if (with_comments)
    {
        out << "nbre de sommets, nbre de triangles\n";//'endl' permet de passer a la ligne
        out << liste_som.size() << " " << liste_tri.size() << '\n';
    }
    else
    {
        out << "$MeshFormat\n" << "2.2 0 8\n" << "$EndMeshFormat\n";
        out << "$MaillageType\n" << (type_maillage==P1_ ? 1 : 2) << "\n$EndMaillageType\n";
        out << "$Nodes\n" << liste_som.size() << '\n';
    }

    int k=1;
    for(vector<Vecteur>::const_iterator i=liste_som.begin(); i!=liste_som.end(); ++i, ++k)
        out << k << ' ' << (*i) << " 0\n"; //Affiche les coordonnées des sommets, 0 est la coordonnée z

    out << "$EndNodes\n";
    out << "$Elements\n" << liste_tri.size() << '\n';

    k=1;
    for(vector<Triangle>::const_iterator j=liste_tri.begin(); j!=liste_tri.end(); ++j, ++k)
        out << k << " 2 2 1 1 " << (*j) << '\n';//mettre les parentheses sur *i, car il ya un probleme de priorite, j est un triangle, donc contient les 3 numeraux globaux des sommets du triangle

    out << "$EndElements\n";

    out << "$Elements2\n" << liste_tri2.size() << '\n';

    k=1;
    for(vector<Triangle>::const_iterator j=liste_tri2.begin(); j!=liste_tri2.end(); ++j, ++k)
        out << k << " 2 2 1 1 " << (*j) << '\n';//mettre les parentheses sur *i, car il ya un probleme de priorite, j est un triangle, donc contient les 3 numeraux globaux des sommets du triangle

    out << "$EndElements2\n";
    return out;
}

Triangle Maillage::tri(int i) const
{
    return liste_tri.at(i-1);
}

Vecteur Maillage::som(int i) const
{
    return liste_som.at(i-1);
}

int Maillage::nb_tri() const
{
    return liste_tri.size();//taille du vecteur de triangles
}

int Maillage::nb_noeuds() const
{
    return liste_som.size();//nbre de sommets du nmaillage
}

Maillage & Maillage::tf_affine(const Matrice & A, const Vecteur & t) // A=matrice representant l'homothetie, et t la transltion
{
    //donc coe liste_som est un vecteur de Points, alors *it est un Point
    for (vector<Vecteur>::iterator itP=liste_som.begin(); itP!=liste_som.end(); ++itP)
    {
        *itP=A*(*itP)+t;
    }
    return *this;
}//faut eviter d'utiliser for pour parcourir des listes ou des vecteurs de la classe STL, mieux vaut utiliser des iterateurs, tu vois

Maillage & Maillage::maille_rectangle(elmt_type t, double a, double b, double c, double d, int m, int n)//considere que ta fonction
{
    if (t==P1_)
        maille_carre_uniteP1(m,n);
    else
        maille_carre_uniteP2(m,n);
    //tf_affine()
    return (*this);
}


// Fonctions de base P1

double tau1_P1(const Vecteur & V)
{
    return (1-V(1)-V(2));
}

double tau2_P1(const Vecteur & V)
{
    return V(1);
}

double tau3_P1(const Vecteur & V)
{
    return V(2);
}

Vecteur Dtau1_P1(const Vecteur & V)
{
    return Vecteur(2,-1.);
}

Vecteur Dtau2_P1(const Vecteur & V)
{
    Vecteur W(2);
    W(1)=1.;
    return W;
}

Vecteur Dtau3_P1(const Vecteur & V)
{
    Vecteur W(2);
    W(2)=1.;
    return W;
}

// Fonctions de base P2

double tau1_P2(const Vecteur & V)
{
    return (1.-V(1)-V(2))*(1.-2.*V(1)-2.*V(2));
}

double tau2_P2(const Vecteur & V)
{
    return V(1)*(2.*V(1)-1.);
}

double tau3_P2(const Vecteur & V)
{
    return V(2)*(2.*V(2)-1.);
}

double tau12_P2(const Vecteur & V)
{
    return 4.*V(1)*(1.-V(1)-V(2));
}

double tau23_P2(const Vecteur & V)
{
    return 4.*V(1)*V(2);
}

double tau31_P2(const Vecteur & V)
{
    return 4.*V(2)*(1.-V(1)-V(2));
}

Vecteur Dtau1_P2(const Vecteur & V)
{
    return Vecteur(2,4.*V(1)-3.+4.*V(2));
}

Vecteur Dtau2_P2(const Vecteur & V)
{
    Vecteur W(2);
    W(1)=4.*V(1)-1.;
    return W;
}

Vecteur Dtau3_P2(const Vecteur & V)
{
    Vecteur W(2);
    W(2)=4.*V(2)-1.;
    return W;
}

Vecteur Dtau12_P2(const Vecteur & V)
{
    Vecteur W(2);
    W(1)=-8.*V(1)+4.-4.*V(2);
    W(2)=-4.*V(1);
    return W;
}

Vecteur Dtau23_P2(const Vecteur & V)
{
    Vecteur W(2);
    W(1)=4.*V(2);;
    W(2)=4.*V(1);
    return W;
}

Vecteur Dtau31_P2(const Vecteur & V)
{
    Vecteur W(2);
    W(1)=-4.*V(2);
    W(2)=-8.*V(2)+4.-4.*V(1);
    return W;
}



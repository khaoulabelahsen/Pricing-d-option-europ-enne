#ifndef MAILLAGE_H_INCLUDED
#define MAILLAGE_H_INCLUDED

#include <iostream>
#include <cstdlib>
#include <complex>
#include <iterator>
#include <list>
#include <vector>
#include <fstream>

#include "Matrice.h"
#include "Vecteur.h"

using namespace std;

////////////////////////////////
//classe Triangle
////////////////////////////////////////

class Triangle: public vector<int>//gere un Triangle ie un vecteur de 3 numeros
{
public:
	Triangle();
	Triangle(const Triangle &);
    Triangle(int, int, int);//constructeur (d'un triangle P1)prenant 3 entiers
    Triangle(int, int, int, int, int, int);//constructeur (d'un triangle P2) prenant 6 entiers
    int operator()(int) const;//fontion d'acces au ieme numero du triangle
    Triangle shift(int) const;//fonction operant une translation des Triangle du prototype
    friend ostream & operator<<(ostream &, const Triangle &);//fonction d'impression des Triangle
};


/////////////////////////////////////             Classe Maillage            /////////////////////////////////////////

enum elmt_type {P1_, P2_}; //permet de choisir quel maillage utilise
class Maillage
{
private:
    vector<Vecteur> liste_som;//la difference entre une liste et un vecteur reste l'acces aux elmts: direct pour un vecteur(grace au crochet) alors que sequentiel pour les listes
    vector<Triangle> liste_tri;
    vector<Triangle> liste_tri2;
    elmt_type type_maillage;
public:

    void maille_carre_uniteP1(int, int);//generateur de maillage: c'est 1 fonction permettant de generer un maillage du carre a partir du couple (m,n), donnant la longueur des segments resp sur l'axe des abscisses et sur l'axe des ordonnees
    void maille_carre_uniteP2(int, int);
    Maillage & maille_rectangle(elmt_type, double, double, double, double, int, int);

    Maillage(elmt_type t, int m, int n)   //constructeur appelant le generateur de maillage
    {
        if (t==P1_)
            maille_carre_uniteP1(m,n);
        else
            maille_carre_uniteP2(m,n);
    }
    Maillage(elmt_type t, double a, double b, double c, double d, int m, int n)
    {
        maille_rectangle(t, a, b, c, d, m, n);
    }

    elmt_type get_type() const {return type_maillage;}

    void save_to_file(const string &) const;
    ostream & Print (ostream &, bool) const ;
    Maillage & tf_affine(const Matrice &, const Vecteur &);

    Triangle tri(int) const;
    Vecteur som(int) const;

    int nb_tri() const;
    int nb_noeuds() const;

    friend ostream& operator<<(ostream &, const Maillage &); //fonction d'impression de la liste des sommets et des Triangle des triangles
};

double tau1_P1(const Vecteur &);
double tau2_P1(const Vecteur &);
double tau3_P1(const Vecteur &);
Vecteur Dtau1_P1(const Vecteur &);
Vecteur Dtau2_P1(const Vecteur &);
Vecteur Dtau3_P1(const Vecteur &);


double tau1_P2(const Vecteur &);
double tau2_P2(const Vecteur &);
double tau3_P2(const Vecteur &);
double tau12_P2(const Vecteur &);
double tau23_P2(const Vecteur &);
double tau31_P2(const Vecteur &);
Vecteur Dtau1_P2(const Vecteur &);
Vecteur Dtau2_P2(const Vecteur &);
Vecteur Dtau3_P2(const Vecteur &);
Vecteur Dtau12_P2(const Vecteur &);
Vecteur Dtau23_P2(const Vecteur &);
Vecteur Dtau31_P2(const Vecteur &);

#endif // MAILLAGE_H_INCLUDED

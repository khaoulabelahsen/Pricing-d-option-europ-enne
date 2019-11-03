#ifndef MATRICE_H
#define MATRICE_H

#include "Vecteur.h"
#include <iostream>

using namespace std;

class Matrice
{
private:
    int dim_l_, dim_c_;
    double * val_;
public:
    Matrice(){dim_l_=0; dim_c_=0; val_=nullptr;}
    Matrice(int, int, double=0);
    Matrice(const Matrice &);
    ~Matrice();


    Matrice & operator =(const Matrice &);
    double & operator()(int, int) const;
    int dim_l() const;
    int dim_c() const;

    Matrice & operator +=(double);
    Matrice & operator -=(double);
    Matrice & operator *=(double);
    Matrice & operator /=(double);

    Matrice & operator +=(const Matrice &);
    Matrice & operator -=(const Matrice &);

    bool operator ==(const Matrice &);
    bool operator !=(const Matrice &);

    void print() const;
    friend ostream & operator <<(ostream &, const Matrice &);
};

Matrice operator +(const Matrice &);
Matrice operator -(const Matrice &);
Matrice operator +(const Matrice &, double);
Matrice operator -(const Matrice &, double);
Matrice operator *(const Matrice &, double);
Matrice operator /(const Matrice &, double);
Matrice operator +(double, const Matrice &);
Matrice operator -(double, const Matrice &);
Matrice operator *(double, const Matrice &);
Matrice operator /(double, const Matrice &);
Matrice operator +(const Matrice &, const Matrice &);
Matrice operator -(const Matrice &, const Matrice &);
ostream & operator <<(ostream &, const Matrice &);
istream & operator >>(istream &, Matrice &);

Vecteur operator *(const Matrice &, const Vecteur &);

void LU_factor(const Matrice &, Matrice &, Matrice &);
Vecteur LU_solve(const Matrice &, const Matrice &, const Vecteur &);

#endif // MATRICE_H

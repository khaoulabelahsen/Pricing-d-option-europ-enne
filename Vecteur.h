#ifndef Vecteur_H
#define Vecteur_H

#include <iostream>

using namespace std;

class Vecteur
{
private :
    int dim_;
    double *val_;
public :
    Vecteur(const int, double=0);
    Vecteur();
    Vecteur(const Vecteur &);
    ~Vecteur();

    bool operator ==(const Vecteur &);
    bool operator !=(const Vecteur &);

    Vecteur & operator =(const Vecteur &);

    Vecteur & operator +=(double);
    Vecteur & operator -=(double);
    Vecteur & operator *=(double);
    Vecteur & operator /=(double);

    Vecteur & operator +=(const Vecteur &);
    Vecteur & operator -=(const Vecteur &);

    friend ostream & operator <<(ostream &, const Vecteur &);
    //friend istream & operator >>(istream &, Vecteur &);

    double operator ()(int) const;
    double & operator ()(int);

    int dim() const;
    double val(int) const;
    double & val(int);
    void print() const;
};

Vecteur operator +(const Vecteur &);
Vecteur operator -(const Vecteur &);
Vecteur operator +(const Vecteur &, double);
Vecteur operator -(const Vecteur &, double);
Vecteur operator *(const Vecteur &, double);
Vecteur operator /(const Vecteur &, double);
Vecteur operator +(double, const Vecteur &);
Vecteur operator -(double, const Vecteur &);
Vecteur operator *(double, const Vecteur &);
Vecteur operator /(double, const Vecteur &);
Vecteur operator +(const Vecteur &, const Vecteur &);
Vecteur operator -(const Vecteur &, const Vecteur &);

double dot(const Vecteur &, const Vecteur &);
#endif // Vecteur_H

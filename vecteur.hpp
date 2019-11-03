#ifndef VECTEUR_HPP
#define VECTEUR_HPP

#include <vector>
#include <string>
#include <iostream>
#include <cmath>

using namespace std;

typedef vector<double>::iterator itv;
typedef vector<double>::const_iterator citv;

// classe vecteur dérivée de vector de la STL avec un itérateur

class vecteur : public vector<double>
{
  public:
    // constructeurs
    vecteur(int d = 0, double v0 = 0) : vector<double>(d, v0){}; //  dimension et valeur initiale constantes
    ~vecteur() { ((vector) * this).~vector(); }
    vecteur(const vecteur &v) : vector<double>(v){};          // constructeur par copie
    double operator()(int i) const { return (*this)[i - 1]; } // accès à la valeur de l'élément i
    double &operator()(int i) { return (*this)[i - 1]; }

    // taille et redimensionnement
    int dim() const
    {
        return vector<double>::size();
    }

    void redim(int d, double v0 = 0)
    {
        resize(d, v0); // redimensionnement avec v0 comme valeur
    }

    void add(double val)
    {
        resize(dim() + 1, val);
    }

    void print()
    {
        cout << this;
    }

    void put(int index, double value=0.){
        if(index > 0 && index <= dim()+1){
            resize(dim()+1);
            for(int i = dim(); i >= index; i--){
                (*this)(i) = (*this)(i-1); 
            }
            (*this)(index) = value;
        }
        else{
            throw std::invalid_argument("index invalid");
        }
    }

    void remove(int index){
        if(index > 0 && index <= dim()){
            for(int i = index; i < dim(); i++){
                (*this)(i) = (*this)(i+1); 
            }
            resize(dim()-1);
        }else{
            throw std::invalid_argument("index invalid");
        }
    }
    //opérateurs algébriques
    vecteur &operator=(const vecteur &v);
    vecteur &operator+=(const vecteur &v);
    vecteur &operator-=(const vecteur &v);
    vecteur &operator+=(const double &x);
    vecteur &operator-=(const double &x);
    vecteur &operator*=(const double &x);
    vecteur &operator/=(const double &x);

}; // fin de la définition de la classe vecteur

// définition du constructeur par copie

vecteur &vecteur::operator=(const vecteur &v)
{
    resize(v.dim(), 0);

    itv it_end = vector<double>::end(); // this.end()
    citv jt = v.begin();
    for (itv it = vector<double>::begin(); it != it_end; ++it, ++jt)
        *it = *jt;
    return *this;
}
// définition des opérateurs internes

vecteur &vecteur::operator+=(const vecteur &v)
{
    itv it_end = vector<double>::end();
    citv jt = v.begin();
    for (itv it = vector<double>::begin(); it != it_end; ++it, ++jt)
        *it += *jt;
    return *this;
}

vecteur &vecteur::operator-=(const vecteur &v)
{
    itv it_end = vector<double>::end();
    citv jt = v.begin();
    for (itv it = vector<double>::begin(); it != it_end; ++it, ++jt)
        *it -= *jt;
    return *this;
}

vecteur &vecteur::operator+=(const double &x)
{
    itv it_end = vector<double>::end();
    for (itv it = vector<double>::begin(); it != it_end; ++it)
        *it += x;
    return *this;
}

vecteur &vecteur::operator-=(const double &x)
{
    itv it_end = vector<double>::end();
    for (itv it = vector<double>::begin(); it != it_end; ++it)
        *it -= x;
    return *this;
}

vecteur &vecteur::operator*=(const double &x)
{
    itv it_end = vector<double>::end();
    for (itv it = vector<double>::begin(); it != it_end; ++it)
        *it *= x;
    return *this;
}

vecteur &vecteur::operator/=(const double &x)
{
    itv it_end = vector<double>::end();
    for (itv it = vector<double>::begin(); it != it_end; ++it)
        *it /= x;
    return *this;
}

// Opérateurs externes

ostream &operator<<(ostream &os, const vecteur &u)
{
    typedef vector<double>::const_iterator citv;
    citv it_end = u.end();
    for (citv it = u.begin(); it != it_end; ++it)
        os << *it << " ";
    return os;
}

//istream & operator<<(istream & is,const vecteur &u)
//{
//    typedef vector<double>::const_iterator citv;
//    citv it_end=u.end();
//    for (citv it=u.begin(); it!=it_end; ++it) is>>*it;
//    return is;
//}

vecteur operator+(const vecteur &u)
{
    return u;
}

vecteur operator+(const vecteur &u, const vecteur &v)
{
    vecteur w(u);
    return w += v;
}

vecteur operator-(const vecteur &u, const vecteur &v)
{
    vecteur w(u);
    return w -= v;
}

vecteur operator+(const vecteur &u, double x) //v+2
{
    vecteur w(u);
    return w += x;
}

vecteur operator-(const vecteur &u, double x) // v-2
{
    vecteur w(u);
    return w -= x;
}

vecteur operator*(const vecteur &u, double x) // v*2
{
    vecteur w(u);
    return w *= x;
}

vecteur operator/(const vecteur &u, double x)
{
    vecteur w(u);
    return w /= x;
}

vecteur operator+(double x, const vecteur &u) // 2+v
{
    vecteur w(u);
    return w += x;
}

vecteur operator-(double x, const vecteur &u) // 2-v
{
    vecteur w(u);
    return w -= x;
}

vecteur operator*(double x, const vecteur &u) // 2*v
{
    vecteur w(u);
    return w *= x;
}

#endif

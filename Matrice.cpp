#include "Matrice.h"
#include <iostream>

Matrice::Matrice(int dl, int dc, double v)
{
    dim_l_=dl;
    dim_c_=dc;
    val_=nullptr;
    int d=dl*dc;
    if(d<=0)
        return;
    val_=new double[d];
    for(int k=0; k<d; ++k)
        val_[k]=v;
}

Matrice::Matrice(const Matrice & V)
{
    dim_l_=V.dim_l_;
    dim_c_=V.dim_c_;
    val_=nullptr;
    int d=dim_c_*dim_l_;
    if(d<=0)
        return;
    val_=new double[d];
    for(int k=0; k<d; ++k)
        val_[k]=V.val_[k];
}

Matrice::~Matrice()
{
    if(val_!=nullptr)
        delete [] val_;
}

Matrice & Matrice::operator =(const Matrice & B)
{
    if(this==&B)
        return *this;
    int s=B.dim_c_*B.dim_l_;
    if(s<=0)
    {
        if(val_!=nullptr)
            delete [] val_;
        dim_c_=dim_l_=0;
        return *this;
    }
    if(dim_c_*dim_l_!=s)
    {
        if(val_!=nullptr)
            delete [] val_;
        val_=new double[s];
    }
    dim_c_=B.dim_c_;
    dim_l_=B.dim_l_;
    for(int k=0; k<s; ++k)
        val_[k]=B.val_[k];
    return *this;
}

double & Matrice::operator ()(int i, int j) const
{
    return val_[(i-1)*dim_l_+j-1];
}

int Matrice::dim_l() const
{
    return dim_l_;
}

int Matrice::dim_c() const
{
    return dim_c_;
}

Matrice & Matrice::operator +=(double x)
{
    int d=dim_c_*dim_l_;
    for(int k=0; k<d; ++k)
        val_[k]+=x;
    return *this;
}

Matrice & Matrice::operator -=(double x)
{
    int d=dim_c_*dim_l_;
    for(int k=0; k<d; ++k)
        val_[k]-=x;
    return *this;
}

Matrice & Matrice::operator *=(double x)
{
    int d=dim_c_*dim_l_;
    for(int k=0; k<d; ++k)
        val_[k]*=x;
    return *this;
}

Matrice & Matrice::operator /=(double x)
{
    if(x==0)
    {
        cout << "Division par 0 dans A/=\n";
        exit(-1);
    }
    int d=dim_c_*dim_l_;
    for(int k=0; k<d; ++k)
        val_[k]/=x;
    return *this;
}

Matrice & Matrice::operator +=(const Matrice & B)
{
    if(dim_c_ !=B.dim_c_ || dim_l_!=B.dim_l_)
    {
        cout << "Matrices incompatibles dans A+=\n";
        exit(-1);
    }
    int d=dim_l_*dim_c_;
    for(int k=0; k<d; ++k)
        val_[k]+=B.val_[k];
    return (*this);
}

Matrice & Matrice::operator -=(const Matrice & B)
{
    if(dim_c_!=B.dim_c_ || dim_l_!=B.dim_l_)
    {
        cout << "Matrices incompatibles dans A+=\n";
        exit(-1);
    }
    int d=dim_l_*dim_c_;
    for(int k=0; k<d; ++k)
        val_[k]-=B.val_[k];
    return (*this);
}

bool Matrice::operator ==(const Matrice &B)
{
    if(dim_c_!=B.dim_c_ || dim_l_!=B.dim_l_)
        return false;
    int d=dim_l_*dim_c_;
    for(int k=0; k<d; ++k)
    {
        if(val_[k]!=B.val_[k])
            return false;
    }
    return true;
}

bool Matrice::operator !=(const Matrice &B)
{
    return !((*this)==B);
}

ostream & operator <<(ostream & out, const Matrice & M)
{
    out << "Matrice de taille " << M.dim_l_ << 'x' << M.dim_c_ << '\n';
    for(int i=1; i<=M.dim_l_; ++i)
    {
        for(int j=1; j<=M.dim_c_; ++j)
        {
            out << M(i,j) << ' ';
        }
        out << '\n';
    }
    return out;
}

void Matrice::print() const
{
    cout << (*this);
}

Matrice operator +(const Matrice & A, double x)
{
    Matrice B(A);
    return (B+=x);
}

Matrice operator -(const Matrice & A, double x)
{
    Matrice B(A);
    return (B-=x);
}

Matrice operator *(const Matrice & A, double x)
{
    Matrice B(A);
    return (B*=x);
}

Matrice operator /(const Matrice & A, double x)
{
    Matrice B(A);
    return (B/=x);
}

Matrice operator +(double x, const Matrice & A)
{
    return (A+x);
}

Matrice operator -(double x, const Matrice & A)
{
    return (A-x);
}

Matrice operator *(double x, const Matrice & A)
{
    return (A*x);
}

Matrice operator +(const Matrice & A, const Matrice & B)
{
    Matrice C(A);
    return (C+=B);
}

Matrice operator -(const Matrice & A, const Matrice & B)
{
    Matrice C(A);
    return (C-=B);
}

Vecteur operator *(const Matrice & A, const Vecteur & V)
{
    if(A.dim_c()!=V.dim())
    {
        cout << "Produit matrice vecteur incompatible\n";
        exit(-1);
    }
    Vecteur W(A.dim_l());
    for(int k=1; k<=A.dim_l(); ++k)
    {
        for(int i=1; i<=V.dim(); ++i)
        {
            W(k)+=A(k,i)*V(i);
        }
    }
    return W;
}

void LU_factor(const Matrice & A, Matrice & L, Matrice & U)
{
    if(A.dim_c()!=A.dim_l())
    {
        cout << "Matrice A non carrée\n";
        exit(-1);
    }
    U=A;
    int N{A.dim_c()};
    L=Matrice(N,N);
    for(int k=1; k<=N; ++k) L(k,k)=1.;

    for(int n=1; n<=N; ++n)
    {
        for(int i=n+1; i<=N; ++i)
        {
            if(U(n,n)==0.) {cout << "divide by 0\n"; exit(-1);}
            double lin=-(L(i,n)=U(i,n)/U(n,n));
            for(int k=1; k<=N; ++k)
            {
                U(i,k)+=lin*U(n,k);
            }
        }
    }
}

Vecteur LU_solve(const Matrice & L, const Matrice & U, const Vecteur & Y)
{
    if(!(L.dim_c()==L.dim_l() && L.dim_l()==U.dim_c() && U.dim_c()==U.dim_l() && U.dim_l()==Y.dim()))
    {
        cout << "Erreur sur les dimensions\n";
        exit(-1);
    }

    Vecteur X(Y);
    int N{X.dim()};
    for(int i=1; i<=N; ++i) // On résout LX=Y par déscente
    {
        for(int k=1; k<i; ++k)
        {
            X(i)-=L(i,k)*X(k);
        }
    }

    for(int i=N; i>=1; --i) // On résout UZ=X par remontée
    {
        for(int k=N; k>i; --k)
        {
            X(i)-=U(i,k)*X(k);
        }
        X(i)/=U(i,i);
    }
    return X;
}


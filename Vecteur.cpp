#include "Vecteur.h"

Vecteur::Vecteur()
{
    dim_=0;
    val_=nullptr;
}

Vecteur::Vecteur(const int d, double x)
{
    dim_=d;
    val_=new double[dim_];
    for(int i=0; i<dim_; ++i)
    {
        val_[i]=x;
    }
}

Vecteur::Vecteur(const Vecteur& v2)
{
    dim_=v2.dim_;
    val_=new double[dim_];
    for(int i=0; i<dim_; ++i)
    {
        val_[i]=v2.val_[i];
    }
}
Vecteur::~Vecteur()
{
    if(val_!=nullptr)
        delete [] val_;
}

bool Vecteur::operator ==(const Vecteur & v)
{
    if(dim_==v.dim())
    {
        int k=0;
        for(k=0; k<dim_; k++)
        {
            if(val_[k]!=v.val(k))
                return false;
        }
        return true;
    }
    return false;
}

bool Vecteur::operator !=(const Vecteur & v)
{
    return !((*this)==v);
}



Vecteur& Vecteur::operator =(const Vecteur & v)
{
    if(&v==this)
        return *this;

    if(dim_!=v.dim_)
    {
        delete [] val_;
        val_=new double[v.dim_];
    }
    dim_=v.dim_;
    for(int i=0; i<dim_; ++i)
    {
        val_[i]=v.val_[i];
    }
    return *this;
}

Vecteur & Vecteur::operator +=(const Vecteur & v)
{
    if(dim_!=v.dim_)
    {
        exit(-1);
    }
    else
    {
        for(int i=0; i<dim_; ++i)
        {
            val_[i]+=v.val_[i];
        }
    }
    return *this;
}
Vecteur & Vecteur::operator +=(double x)
{
    for(int i=0; i<dim_; ++i)
    {
        val_[i]+=x;
    }
    return *this;
}

Vecteur& Vecteur::operator -=(const Vecteur & v)
{
    if(dim_!=v.dim_)
    {
        exit(-1);
    }
    else
    {
        for(int i=0; i<dim_; ++i)
        {
            val_[i]-=v.val_[i];
        }
        return *this;
    }
}
Vecteur& Vecteur::operator -=(double x)
{
    for(int i=0; i<dim_; ++i)
    {
        val_[i]-=x;
    }
    return *this;
}

Vecteur& Vecteur::operator *=(const double x)
{
    for(int i=0; i<dim_; ++i)
    {
        val_[i]*=x;
    }
    return *this;
}

Vecteur& Vecteur::operator /=(double x)
{
    if(x==0)
    {
        return *this;
    }
    for(int i=0; i<dim_; ++i)
    {
        val_[i]/=x;
    }
    return *this;
}

double Vecteur::operator ()(int i) const
{
    return val(i-1);
}

double & Vecteur::operator ()(int i)
{
    return val(i-1);
}

double Vecteur::val(int i) const
{
    if(val_!=nullptr && i<dim_)
        return val_[i];
    else
    {
        if(val_==nullptr)
            cout << "Vecteur::val=nullptr\n";
        else
            cout << "i<Vecteur::dim_\n";
        exit(-1);
    }
}

double & Vecteur::val(int i)
{
    if(val_!=0 && i<dim_)
        return val_[i];
    else
    {
        if(val_==nullptr)
            cout << "Vecteur::val=nullptr\n";
        else
            cout << "i<Vecteur::dim_\n";
        exit(-1);
    }
}

int Vecteur::dim() const
{
    return dim_;
}

void Vecteur::print() const
{
    if(val_==0)
        return;
    for(int i=0; i<dim_; ++i)
    {
        cout << val_[i] << '\n';
    }
}

Vecteur operator +(const Vecteur & V, double x)
{
    Vecteur W(V);
    return (W+=x);
}

Vecteur operator -(const Vecteur & V, double x)
{
    Vecteur W(V);
    return (W-=x);
}

Vecteur operator *(const Vecteur & V, double x)
{
    Vecteur W(V);
    return (W*=x);
}

Vecteur operator /(const Vecteur & V, double x)
{
    Vecteur W(V);
    return (W/=x);
}

Vecteur operator +(double x, const Vecteur & V)
{
    return (V+x);
}

Vecteur operator -(double x, const Vecteur & V)
{
    return (V-x);
}

Vecteur operator *(double x, const Vecteur & V)
{
    return (V*x);
}

Vecteur operator +(const Vecteur & U, const Vecteur & V)
{
    Vecteur W(U);
    return (W+=V);
}

Vecteur operator -(const Vecteur & U, const Vecteur & V)
{
    Vecteur W(U);
    return (W-=V);
}

ostream & operator <<(ostream  & out, const Vecteur & V)
{
	if(V.val_!=nullptr)
	{
		for(int k=0; k<V.dim_; ++k)
		{
			out << V.val_[k] << ((k==V.dim_-1) ? "" : " ");
		}
	}
	return out;
}

double dot(const Vecteur & V1, const Vecteur & V2)
{
    double d=0.0;
    if(V1.dim()!=V2.dim())
    {
        cout << "Produit scalaire entre vecteurs incompatibles\n";
        exit(-1);
    }
    for(int k=1; k<=V1.dim(); ++k)
    {
        d+=V1(k)*V2(k);
    }
    return d;
}

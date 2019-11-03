#ifndef MATRICE_HPP
#define MATRICE_HPP

#include "vecteur.hpp"
#include <vector>
#include <string>
#include <iostream>
#include <cmath>

using namespace std;

// On crée une classe matrice avec un stockage de type profil

class matrice //(profil)
{
  protected:
    int dim_m;
    vecteur *valL; // la partie triangulaire inférieure de la matrice
    vecteur *valU; // la partie triangulaire supérieure de la matrice
    vecteur *pl;   // vecteur de l'indice de l'élément non nul dans la ligne
    vecteur *pu;   // vecteur de l'indice de l'élément non nul dans la colonne
    vecteur *q;    // vecteur de l'indice de l'élément de la diagonale dans L
    double _get(int i, int j) const;

  public:
    matrice() : dim_m(0), valL(nullptr), valU(nullptr), pl(nullptr), pu(nullptr), q(nullptr) {} // constructeur par défaut
    matrice(int, double v);                                                                     // constructeur avec un élément
    matrice(const matrice &M);                                                                  // constructeur par copie
    virtual ~matrice()
    {
        delete pu;
        delete pl;
        delete q;
        delete valL;
        delete valU;
    } // desctructeur

    //Accesseurs
    int dim() const
    {
        return dim_m;
    }
    vecteur L_() const
    {
        return *valL;
    }
    vecteur q_() const
    {
        return *q;
    }
    vecteur U_() const
    {
        return *valU;
    }
    vecteur pu_() const
    {
        return *pu;
    }

    vecteur pl_() const
    {
        return *pl;
    }

    //Accès à l'élément (i,j)

    double val(int i, int j) const;

    //Fonction d'impression

    void print(ostream &o);

    // La fonction qui modifie l'élément i,j selon s'il est stocké ou non

    void modifier(int i, int j, double a);

    // Opérateurs
    void operator=(const matrice &);
    matrice &operator+(const matrice &);
    matrice &operator-(const matrice &);
    matrice &operator+=(const matrice &);
    matrice &operator-=(const matrice &);
    matrice &operator*(double a);

    // Produit matrice vecteur

    friend vecteur produit(const matrice &, const vecteur &);
};

// Le constructeur par un int et une valeur

matrice::matrice(int n, double v) // OK
{
    if (v == 0.) // Cas de v nul : on ne stocke que la diagonale de zéros
    {
        dim_m = n;

        valL = new vecteur(dim_m, v);

        valU = new vecteur(dim_m, v);

        pu = new vecteur(dim_m, 0);

        pl = new vecteur(dim_m, 0);
        for (int _ = 1; _ < dim_m + 1; _++)
        {
            (*pl)(_) = _;
        }
        q = new vecteur(*pl);
    }
    if (v != 0.) // Cas v non nul : on stocke tous les éléments
    {
        dim_m = n;

        int dim_L = n * (n + 1) / 2;

        valL = new vecteur(dim_L, v);
        valU = new vecteur(dim_L, v);

        pl = new vecteur(dim_m, 1);
        pu = new vecteur(dim_m, 1);

        q = new vecteur(dim_m, 0);

        for (int _ = 1; _ < dim_m + 1; _++)
        {
            (*q)(_) = _ * (_ + 1) / 2;
        }
    }
}

// Le constructeur par copie

matrice::matrice(const matrice &M) // OK
{
    dim_m = M.dim();

    pu = new vecteur(*M.pu);
    pl = new vecteur(*M.pl);

    q = new vecteur(*M.q);

    valL = new vecteur(*M.valL);

    valU = new vecteur(*M.valU);
}

// La fonction _get(i,j) d'accès à un élément (privée dans la classe, on utilisera val(i,j) pour les classes héritées)

double matrice::_get(int i, int j) const // OK
{
    if (i > dim_m || j > dim_m || i < 1 || j < 1)
    {
        throw new std::invalid_argument("indexes invalides");
    }
    else
    {
        if (j <= i) // On est dans la triangulaire inférieure
        {
            if (j < (*pl)(i)) // l'élement i,j n'est pas stocké et donc c'est un zéro
            {
                return 0.;
            }
            else
            {
                return (*valL)((*q)(i)-i + j); //l'élément est bien stocké et on y accéde dans valL
            }
        }
        else // On est dans la triangulaire supérieure maintenant
        {
            if (i < (*pu)(j)) // l'élement i,j n'est pas stocké donc c'est un zéro
            {
                return 0.;
            }
            else
            {
                return (*valU)((*q)(j)-j + i); // l'élément est stocké et on y accéde dans valU
            }
        }
    }
}

// L'accès à un élément i,j par fonction val(i,j)

double matrice::val(int i, int j) const
{
    return _get(i, j);
}

// La fonction d'impression

void matrice::print(ostream &o) // OK
{
    for (int i = 1; i <= dim_m; i++)
    {
        for (int j = 1; j <= dim_m; j++)
        {
            o << val(i, j) << " ";
        }
        o << endl;
    }
}

// La fonction modifier qui prend les indices i,j ainsi que la nouvelle valeur a et qui modifie l'élément i,j

void matrice::modifier(int i, int j, double a)
{
    // Partie triangulaire inférieure
    if (i > j)
    {
        //i, j est stocké
        if (j >= (*pl)(i))
        {
            cout << "here" << endl; // Juste pour vérifier que tout ce passe bien
            // Si on vous mettre l'élément i,j à 0
            if (a == 0)
            {
                //premier élément stocké de la ligne
                if (j == (*pl)(i))
                {
                    //calcul de l'offset
                    int offset = 0; //<- nombre d'éléments à enlever de valL s'il y avait des zéros après l'élément M(i,p(i))
                    for (int k = (*q)(i - 1) + 2; k < (*q)(i); k++)
                    {
                        if ((*valL)(k) == 0)
                        {
                            offset += 1;
                        }
                        else
                        {
                            break; // On s'arrête dès qu'on arrive à un élément non nul
                        }
                    }
                    //update valL
                    for (int _ = 0; _ < offset + 1; _++)
                    {
                        valL->remove((*q)(i - 1) + 1); //valL -> pop at (*q)(i-1) + 1,
                        // valU->remove((*q)(i - 1) + 1); //valU -> pop at (*q)(i-1) + 1,
                    }
                    //update q
                    for (int line = i; line <= dim_m; line++)
                    {
                        (*q)(line) -= (offset + 1); // Car ils seront décalés du nombre d'éléments qui ne sont plus stockés
                    }
                    //update p
                    (*pl)(i) += (offset + 1);
                    return;
                }
                // Si l'élément est déjà stocké
                else
                {
                    (*valL)((*q)(i)-i + j) = a;
                    return;
                }
            }
            //seting une valeur non nulle
            else
            {
                (*valL)((*q)(i)-i + j) = a;
                //TODO: do something about symmetric module ? => but do we care since it's already stored ?
                return;
            }
        }
        //i, j non stockée
        else
        {
            if (a != 0)
            {
                //calcul de l'offset
                int offset = (*pl)(i)-j; //<- nombre d'éléments à rajouter dans valL
                //update valL
                for (int _ = 0; _ < offset - 1; _++)
                {
                    valL->put((*q)(i - 1) + 1); //valL -> add value 0 at (*q)(i-1) + 1 (after)
                    // valU->put((*q)(i - 1) + 1); //valU -> add value 0 at (*q)(i-1) + 1 (after)
                }
                valL->put((*q)(i - 1) + 1, a); //valL -> add value 'a' at (*q)(i-1) + 1 (after)
                // valU->put((*q)(i - 1) + 1, a); //valU -> add value 'a' at (*q)(i-1) + 1 (after) /// mmm ?
                //update p
                (*pl)(i) = j;
                //update q
                for (int line = i; line <= dim_m; line++)
                {
                    (*q)(line) += (offset);
                }
                return;
            }
            //in case a = 0, exit without doing anthing
            else
            {
                return;
            }
        }
    }
    //upper
    else if (i < j)
    {
        //i, j stored
        if (i >= (*pu)(j))
        {
            cout << "here" << endl;
            //setting to zero
            if (a == 0)
            {
                //setting the first stored element in line
                if (i == (*pu)(j))
                {
                    //calclulate offset
                    int offset = 0; //<- number of elements to remove from valU
                    for (int k = (*q)(j - 1) + 2; k < (*q)(j); k++)
                    {
                        if ((*valU)(k) == 0)
                        {
                            offset += 1;
                        }
                        else
                        {
                            break;
                        }
                    }
                    //update valU
                    for (int _ = 0; _ < offset + 1; _++)
                    {
                        valU->remove((*q)(j - 1) + 1); //valU -> pop at (*q)(j-1) + 1,
                        // valL->remove((*q)(j - 1) + 1); //valL -> pop at (*q)(j-1) + 1,
                    }
                    // //update q
                    // for (int line = j; line <= dim_m; line++)
                    // {
                    //     (*q)(line) -= (offset + 1);
                    // }
                    //update p
                    (*pu)(j) += (offset + 1);
                    return;
                }
                //setting other element
                else
                {
                    (*valU)((*q)(j)-j + i) = a;
                    return;
                }
            }
            //seting to non-zero valLe
            else
            {
                (*valU)((*q)(j)-j + i) = a;
                //TODO: do something about symmetric module ? => but do we care since it's already stored ?
                return;
            }
        }
        //i, i not stored
        else
        {
            if (a != 0)
            {
                //calculating offset
                int offset = (*pu)(j)-i; //<- number of elements to add to valU
                //update valU
                for (int _ = 0; _ < offset - 1; _++)
                {
                    valU->put((*q)(j - 1) + 1); //valU -> add valLe 0 at (*q)(j-1) + 1 (after)
                    // valL->put((*q)(j - 1) + 1); //valL -> add valLe 0 at (*q)(j-1) + 1 (after)
                }
                valU->put((*q)(j - 1) + 1, a); //valU -> add valLe 'a' at (*q)(j-1) + 1 (after)
                // valL->put((*q)(j - 1) + 1, a); //valL -> add valLe 'a' at (*q)(j-1) + 1 (after) /// mmm ?
                //update p
                (*pu)(j) = i;
                //update q
                for (int line = j; line <= dim_m; line++)
                {
                    (*q)(line) += (offset);
                }
                return;
            }
            //in case a = 0, exit without doing anthing
            else
            {
                return;
            }
        }
    }
    //diagonal as special case
    else
    {

        //diagonal is always stored
        (*valL)((*q)(i)) = a;
        return;
    }
}

// Opérateur égalité

void matrice::operator=(const matrice &M) // Normalement OK si modifier marche
{
    // bool pWasSet;
    // double a, b; //variables de passage
    // int n;
    // matrice_sym nm;

    if (dim_m == M.dim())
    {
        if ((*pu == M.pu_()) && (*q == M.q_()) && (*pl == M.pl_()))
        {
            *valL = M.L_();
            *valU = M.U_();
        }
        else
        {
            int n = M.dim();
            for (int i = 1; i <= n; i++)
            {
                for (int j = 1; j <= n; j++)
                {
                    modifier(i, j, M._get(i, j));
                }
            }
        }
    }
    else
    {
        throw new std::invalid_argument("dimensions non égales");
    }
}

// Somme

matrice &matrice::operator+=(const matrice &M)
{
    vecteur *Ln = valL;
    vecteur *Un = valU;
    vecteur *un = pu;
    vecteur *ln = pl;
    vecteur *qn = q;

    vecteur LM = (M.L_());
    vecteur UM = (M.U_());
    vecteur uM = (M.pu_());
    vecteur lM = (M.pl_());
    vecteur qM = (M.q_());

    *Ln += LM;
    *Un += UM;
    *un += uM;
    *ln += lM;
    *qn += qM;

    return *this;
}

// Différence

matrice &matrice::operator-=(const matrice &M)
{
    vecteur *Ln = valL;
    vecteur *Un = valU;
    vecteur *un = pu;
    vecteur *ln = pl;
    vecteur *qn = q;

    vecteur LM = (M.L_());
    vecteur UM = (M.U_());
    vecteur uM = (M.pu_());
    vecteur lM = (M.pl_());
    vecteur qM = (M.q_());

    *Ln -= LM;
    *Un -= UM;
    *un -= uM;
    *ln -= lM;
    *qn -= qM;

    return *this;
}

// Multiplication par une scalaire

matrice &matrice::operator*(double a)
{
    for (int i = 1; i < dim_m + 1; i++)
    {
        for (int j = 1; j < dim_m + 1; j++)
        {
            (*this).modifier(i, j, (*this).val(i, j) * a);
        }
    }
    return *this;
}

// Produit matrice vecteur

vecteur produit(matrice &M, vecteur &X) // OK
{
    if (M.dim() == X.dim())
    {
        int n = M.dim();
        vecteur *b;
        b = new vecteur(n, 0);

        for (int i = 1; i <= n; i++)
        {
            for (int j = (M.pl_())(i); j <= n; j++)
            {
                (*b)(i) += M.val(i, j) * X(j);
            }
        }
        return *b;
    }
    else
        throw std::invalid_argument("On ne peut pas faire le produit");
}

class matrice_sym : public matrice
{
  public:
    matrice_sym() : matrice() {}
    matrice_sym(int n, double v = 0.) : matrice(n, v) {}
    matrice_sym(const matrice &M) : matrice(M)
    {
        verifier_symetrique();
    }

    void verifier_symetrique()
    {
        bool is_symetric = true;
        for (int i = 1; i < dim_m + 1; i++)
        {
            for (int j = 1; j <= i; j++)
            {
                if (_get(i, j) != _get(j, i))
                {
                    is_symetric = false;
                }
            }
        }
        if (!is_symetric)
        {
            throw new std::invalid_argument("this matrix is not symetric");
        }
    }
    virtual ~matrice_sym()
    {
    }

    double val(int i, int j) const;
    void print(ostream &o);

    // Opérateurs
    matrice_sym &operator=(const matrice_sym &);
    matrice_sym &operator+(const matrice_sym &);

    matrice_sym &operator+=(const matrice_sym &);
    matrice_sym &operator-=(const matrice_sym &);
};

double matrice_sym::val(int i, int j) const
{
    if (i >= j)
    {
        return _get(i, j);
    }
    else
    {
        return _get(j, i);
    }
}
void &matrice_sym::operator=(const matrice_sym &M)
{
    bool pWasSet;
    double a, b; //variables de passage
    int n;
    matrice_sym nm;
    if (dim_m == M.dim())
    {
        n = M.dim();
        vecteur *pOut = p; //valeur par défaut de p
        vecteur *qOut = q;
        vecteur *LOut = valL;

        for (int i = 1; i <= n; i++)
        {
            pWasSet = false;
            for (int j = 1; j <= i; j++)
            {
                a = val(i, j);
                b = M.val(i, j);
                if (a + b != 0)
                {
                    if (!pWasSet)
                    {
                        pWasSet = true;
                        (*pOut)(i) = j;
                    }
                    (*LOut)((*q)(i)-i + j) = b;
                    (*qOut)(i) = (*LOut).dim();
                }
                if (!pWasSet)
                {
                    (*LOut)((*q)(i)-i + j) = 0;
                    (*qOut)(i) = (*LOut).dim();
                }
            }
        }
        nm.p = pOut;
        nm.q = qOut;
        nm.valL = LOut;
        nm.valU = LOut;
        return nm;
    }
    else
    {
        throw new std::invalid_argument("dimensions non égales");
    }
}
matrice_sym &matrice_sym::operator+(const matrice_sym &M)
{
    bool pWasSet;
    double a, b; //variables de passage
    int n;
    static matrice_sym nm;
    if (dim_m == M.dim())
    {
        n = M.dim();
        vecteur *pOut = p; //valeur par défaut de p
        vecteur *qOut = q;
        vecteur *LOut = new vecteur;

        for (int i = 1; i <= n; i++)
        {
            pWasSet = false;
            for (int j = 1; j <= i; j++)
            {
                a = val(i, j);
                b = M.val(i, j);
                if (a + b != 0)
                {
                    if (!pWasSet)
                    {
                        pWasSet = true;
                        (*pOut)(i) = j;
                    }
                    (*LOut).add(a + b);
                    (*qOut)(i) = (*LOut).dim();
                }
                if (!pWasSet)
                {
                    (*LOut).add(0);
                    (*qOut)(i) = (*LOut).dim();
                }
            }
        }
        nm.p = pOut;
        nm.q = qOut;
        nm.valL = LOut;
        nm.valU = LOut;
        return nm;
    }
    else
    {
        throw new std::invalid_argument("dimensions non égales");
    }
}
void matrice_sym::print(ostream &o)
{
    for (int i = 1; i < dim_m + 1; i++)
    {
        int j = 1;
        for (j = 1; j <= i; j++)
        {
            if (j < (*p)(i))
            {
                o << 0 << " ";
            }
            else
            {
                o << (*valL)((int)((*q)(i)-i + j)) << " ";
            }
        }
        for (j = i + 1; j <= dim_m; j++)
        {
            if (i < (*p)(j))
            {
                o << 0 << " ";
            }
            else
            {
                o << (*valL)((int)((*q)(j)-j + i)) << " ";
            }
        }
        o << endl;
    }
}

class matrice_nonsym : public matrice
{
};
#endif
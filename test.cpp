#include <iostream>
#include "vecteur.hpp"
#include "matrice.hpp"

int main()

{
    vecteur X(5, 1);
    matrice M(5, 0);
    // cout << M.q_() << endl;
    // cout << M.pu_() << endl;
    // cout << M.pl_() << endl;
    // cout << M.L_() << endl;
    // cout << M.U_() << endl;
    matrice N(5, 0);
    M.modifier(4, 1, 1);
    M.modifier(1, 4, 2);
    cout << M.q_() << endl;
    cout << M.pu_() << endl;
    cout << M.pl_() << endl;
    cout << M.L_() << endl;
    cout << M.U_() << endl;
    // M.modifier(3, 1, 1);
    // M.print(cout);
    // N.print(cout);
    // vecteur Y(5, 0);
    // cout << produit(M, X) << endl;
    // b = produit(M, X);
    // cout << "b=" << b << endl;
}

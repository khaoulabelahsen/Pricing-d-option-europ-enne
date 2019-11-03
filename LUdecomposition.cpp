#include "matrice.hpp"

using namespace std;

const int MAX = 100;

void luDecomposition(matrice mat(MAX), int n)
{
    matrice lower(n), upper(n);

    // Decomposition de la matrice en L et U
    // Matrice triangulaire
    for (int i = 0; i < n; i++)
    {

        // Triangle Supérieur
        for (int k = i; k < n; k++)
        {

            // Somme des L(i, j) * U(j, k)
            int sum = 0;
            for (int j = 0; j < i; j++)
                sum += (lower.val(i, j) * upper.val(i, j));

            // Evaluation U(i, k)
            upper.val(i, j) = mat.val(i, j) - sum;
        }

        // Triangle Inférieur
        for (int k = i; k < n; k++)
        {
            if (i == k)

                lower.val(i, i) = 1; // Diagonal as 1
            else
            {

                // SOmme des L(k, j) * U(j, i)
                int sum = 0;
                for (int j = 0; j < i; j++)
                    sum += (lower.val(k, j) * upper.val(j, i));

                // Evaluation L(k, i)
                lower.val(k, i) = (mat.val(k, i) - sum) / upper.val(i, i);
            }
        }
    }

    // Résultat de la décomposition
    for (int i = 0; i < n; i++)
    {
        Lower for (int j = 0; j < n; j++)
                cout
            << lower.val(i, j) << " ";
        cout << " ";

        Upper for (int j = 0; j < n; j++)
                cout
            << upper.val(i, j) << " ";
        cout << endl;
    }
    // resolution

    for (i = 1; i <= n; i++)
    {
        int s = 0;
        vecteur x(n, 0);
        vecteur y0(n, 0);

        for (j = 1; j <= i; j++)
        {
            s = s + lower.val(i, j) * y(j);
        }
        y(i) = (b(i) - s) / lower.val(i, j);
    }

    for (i = n; i >= 1; i--)
    {
        s = 0;
        for (j = i + 1; j < n; j++)
        {
            s = s + upper.val(i, j) * x(j);
        }
        x(i) = (y(i) - s) / upper.val(i, j);
    }
}

// int main()
// {
//     int mat[][MAX] = { { 2, -1, -2 },
//         { -4, 6, 3 },
//         { -4, -2, 8 }
//     };
//   luDecomposition(mat, 3);
//     return 0;
// }
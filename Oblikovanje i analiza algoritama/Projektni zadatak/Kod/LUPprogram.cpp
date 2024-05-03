#include <iostream>
#include <random>
#include <cstdlib> //stdlib.h
#include <ctime>  //time.h
#include <chrono>
#include <iomanip>
#include <cmath>

using namespace std;

/****************************************** LUP SOLVE S L I U *************************************************/

void LUP_SOLVE(double** L, double** U, int* P, double* b, const int n, double* x)
{
    double sum;

    for(int i = 0; i < n; i++)
    {
        sum = 0.0;
        for(int j = 0; j < i-1; j++)
            sum = sum + L[i][j] * x[j];

        x[i] = b[P[i]] - sum;
    }

    for(int i = n - 1; i >= 0; i--)
    {
        sum = 0.0;
        for(int j = i + 1; j < n; j++)
            sum = sum + U[i][j] * x[j];

        x[i] = (x[i] - sum) / U[i][i];
    }
}

/***************************************** LUP SOLVE SAMO S A ******************************************************/

void LUP_SOLVE(double** A, int* P, double* b, const int n, double* x)
{
    double sum;

    for(int i = 0; i < n; i++)
    {
        sum = 0.0;
        for(int j = 0; j < i-1; j++)
            sum = sum + A[i][j] * x[j];

        x[i] = b[P[i]] - sum;
    }

    for(int i = n - 1; i >= 0; i--)
    {
        sum = 0.0;
        for(int j = i + 1; j < n; j++)
            sum = sum + A[i][j] * x[j];

        x[i] = (x[i] - sum) / A[i][i];
    }
}

void LU_DECOMPOSITION_REK(double** A, double** L,
                          double** U,
                          const int n, const int k)
{
    if(k < n)
        U[k][k] = A[k][k];
    for(int i = k + 1; i < n; i++)
    {
        L[i][k] = A[i][k] / A[k][k];

        U[k][i] = A[k][i];
    }
    for(int i = k + 1; i < n; i++)
        for(int j = k + 1; j < n; j++)
        {
            A[i][j] = A[i][j] - L[i][k] * U[k][j];
        }
    if(k < n - 1)
        LU_DECOMPOSITION_REK(A, L, U, n, k + 1);
}

void LU_DECOMPOSITION(double** A, double** L, double** U, const int n)
{
    for(int k = 0; k < n; k++)
    {
        U[k][k] = A[k][k];

        for(int i = k + 1; i < n; i++)
        {
            L[i][k] = A[i][k] / A[k][k];

            U[k][i] = A[k][i];
        }

        for(int i = k + 1; i < n; i++)
            for(int j = k + 1; j < n; j++)
            {
                A[i][j] = A[i][j] - L[i][k] * U[k][j];
            }
    }
}

/********************** LUP REKURZIVNI S L i U ******************************************************************/

void LUP_DECOMPOSITION_REK(double** A, double** L, double** U, int* P, const int n, const int k)
{
    if(k < n - 1)
    {
        double max = 0.0;
        int max_ind;
        for(int i = k; i < n; i++)
        {
            if(abs(A[i][k]) > max)
            {
                max = abs(A[i][k]);
                max_ind = i;
            }
        }

        if(max == 0)
        {
            cout << "Matrica sustava je singularna!" << endl;
            exit(-1);
        }

        if(max_ind != k)
        {
            int temp = P[k];
            P[k] = P[max_ind];
            P[max_ind] = temp;

            double pom;
            for(int j = k; j < n; j++)
            {
                pom = A[k][j];
                A[k][j] = A[max_ind][j];
                A[max_ind][j] = pom;
            }

            for(int j = 0; j < k; j++)
            {
                pom = L[k][j];
                L[k][j] = L[max_ind][j];
                L[max_ind][j] = pom;
            }
        }
    }

    if(k < n)
        U[k][k] = A[k][k];

    for(int i = k + 1; i < n; i++)
    {
        L[i][k] = A[i][k] / A[k][k];

        U[k][i] = A[k][i];
    }

    for(int i = k + 1; i < n; i++)
        for(int j = k + 1; j < n; j++)
        {
            A[i][j] = A[i][j] - L[i][k] * U[k][j];
        }

    if(k < n - 1)
        LUP_DECOMPOSITION_REK(A, L, U, P, n, k + 1);
}

/********************** LUP S PETLJOM S L i U *****************************************************************/

void LUP_DECOMPOSITION(double** A, double** L, double** U, int* P, const int n)
{
    for(int k = 0; k < n; k++)
    {
        double max = 0;
        int max_ind;
        for(int i = k; i < n; i++)
        {
            if(abs(A[i][k]) > max)
            {
                max = abs(A[i][k]);
                max_ind = i;
            }
        }

        if(max == 0)
        {
            cout << "Matrica sustava je singularna!" << endl;
            exit(-1);
        }

        if(max_ind != k)
        {
            int temp = P[k];
            P[k] = P[max_ind];
            P[max_ind] = temp;

            double pom;
            for(int j = k; j < n; j++)
            {
                pom = A[k][j];
                A[k][j] = A[max_ind][j];
                A[max_ind][j] = pom;
            }

            for(int j = 0; j < k; j++)
            {
                pom = L[k][j];
                L[k][j] = L[max_ind][j];
                L[max_ind][j] = pom;
            }
        }

        U[k][k] = A[k][k];

        for(int i = k + 1; i < n; i++)
        {
            L[i][k] = A[i][k] / A[k][k];

            U[k][i] = A[k][i];
        }

        for(int i = k + 1; i < n; i++)
            for(int j = k + 1; j < n; j++)
            {
                A[i][j] = A[i][j] - L[i][k] * U[k][j];
            }
    }
}

/********************** LUP REKURZIVNI SAMO S A ***********************************************/

void LUP_DECOMPOSITION_REK(double** A, int* P, const int n, const int k)
{
    if(k < n - 1)
    {
        double max = 0.0;
        int max_ind;
        for(int i = k; i < n; i++)
        {
            if(abs(A[i][k]) > max)
            {
                max = abs(A[i][k]);
                max_ind = i;
            }
        }

        if(max == 0)
        {
            cout << "Matrica sustava je singularna!" << endl;
            exit(-1);
        }

        if(max_ind != k)
        {
            int temp = P[k];
            P[k] = P[max_ind];
            P[max_ind] = temp;

            double pom;
            for(int j = 0; j < n; j++)
            {
                pom = A[k][j];
                A[k][j] = A[max_ind][j];
                A[max_ind][j] = pom;
            }
        }
    }

    for(int i = k + 1; i < n; i++)
    {
        A[i][k] = A[i][k] / A[k][k];

        for(int j = k + 1; j < n; j++)
        {
            A[i][j] = A[i][j] - A[i][k] * A[k][j];
        }
    }

    if(k < n - 1)
        LUP_DECOMPOSITION_REK(A, P, n, k + 1);
}


/********************** LUP S PETLJOM SAMO S A ********************************************************/

void LUP_DECOMPOSITION(double** A, int* P, const int n)
{
    for(int k = 0; k < n; k++)
    {
        double max = 0;
        int max_ind;
        for(int i = k; i < n; i++)
        {
            if(abs(A[i][k]) > max)
            {
                max = abs(A[i][k]);
                max_ind = i;
            }
        }

        if(max == 0.0)
        {
            cout << "Matrica sustava je singularna!" << endl;
            exit(-1);
        }

        if(max_ind != k)
        {
            int temp = P[k];
            P[k] = P[max_ind];
            P[max_ind] = temp;

            double pom;
            for(int j = 0; j < n; j++)
            {
                pom = A[k][j];
                A[k][j] = A[max_ind][j];
                A[max_ind][j] = pom;
            }
        }

        for(int i = k + 1; i < n; i++)
        {
            A[i][k] = A[i][k] / A[k][k];

            for(int j = k + 1; j < n; j++)
            {
                A[i][j] = A[i][j] - A[i][k] * A[k][j];
            }
        }
    }
}

/***************************** GLAVNI PROGRAM ***************************************************************/

int main()
{
    /// dimenzija matrice sustava
    const int n = 2000;

    /// matrica sustava A
    double** A = new double*[n];
    for(int i = 0; i < n; i++)
    {
        A[i] = new double[n];
    }

    /// vektor desne strane sustava b
    double* b = new double[n];


    /// matrica L
    double** L = new double*[n];
    for(int i = 0; i < n; i++)
    {
        L[i] = new double[n];
    }

    /// matrica U
    double** U = new double*[n];
    for(int i = 0; i < n; i++)
    {
        U[i] = new double[n];
    }

    ///matrica permutacije reprezentirana kao vektor
    int* P = new int[n];
/*
    /// inicijalizacija matrice permutacije kao identitete
    for(int i = 0; i < n; i++)
        P[i] = i;
*/


    double suma = 0.0;
    int broj_ponavljanja = 20;
    for(int i = 0; i < broj_ponavljanja; i++) /// ponovi npr. 50 puta i svaki put izmjeri vrijeme
    {
        /// seed za rand()
        srand((unsigned)time(NULL));

        /// generiranje nove matrice A, za novi sustav
        for(int i = 0; i < n; i++)
            for(int j = 0; j < n; j++)
                A[i][j] = rand();


        auto begin = std::chrono::high_resolution_clock::now();

        ///inicijalizacija gornjeg trokuta i dijagonale matrice L, te donjeg trokuta matrice U
        ///zakomentirati po potrebi
        for(int i = 0; i < n; i++)
        {
            L[i][i] = 1;
            for(int j = i + 1; j < n; j++)
            {
            L[i][j] = 0;
            U[j][i] = 0;
            }
        }

        ///inicijalizacija permutacije kao identitete
        for(int i = 0; i < n; i++)
            P[i] = i;


        LUP_DECOMPOSITION(A, L, U, P, n);

        auto end = std::chrono::high_resolution_clock::now();

        auto dt = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);

        suma += dt.count();
    }

    auto avg_time = suma / broj_ponavljanja;
    std::cout << "LUP dekompozicija - prosjecno vrijeme za " << broj_ponavljanja << " ponavljanja: " << std::fixed << setprecision(8) << avg_time << " ms. " << endl;



/* MOGUCI POZIVI:
 LUP_DECOMPOSITION_REK(A, L, U, P, n, 0);
 LUP_DECOMPOSITION_REK(A, P, n, 0);
 LUP_DECOMPOSITION_(A, L, U, P, n);
 LUP_DECOMPOSITION(A, P, n);
 */


    ///vektor za rjesenje sustava x
    double* x = new double[n];

    double suma2 = 0.0;
    int broj_ponavljanja2 = 50;
    for(int i = 0; i < broj_ponavljanja2; i++) /// ponovi npr. 50 puta i svaki put izmjeri vrijeme
    {
        /// seed za rand()
        srand((unsigned)time(NULL));

        /// generiranje novog vektora b, za istu matricu A
        for(int i = 0; i < n; i++)
            b[i] = rand();

        auto begin2 = std::chrono::high_resolution_clock::now();

        /// rad cije se vrijeme mjeri
        LUP_SOLVE(L, U, P, b, n, x);

        auto end2 = std::chrono::high_resolution_clock::now();

        auto dt2 = std::chrono::duration_cast<std::chrono::seconds>(end2 - begin2);

        suma2 += dt2.count();
    }

    auto avg_time2 = suma2 / broj_ponavljanja2;
    std::cout << "LUP solve - prosjecno vrijeme za " << broj_ponavljanja2 << " ponavljanja: " << std::fixed << setprecision(8) << avg_time2 << " s. \n";


    for(int i = 0; i < n; i++)
        delete[] A[i];
    delete[] A;

    delete[] b;
    delete[] x;

    for(int i = 0; i < n; i++)
        delete[] L[i];
    delete[] L;

    for(int i = 0; i < n; i++)
        delete[] U[i];
    delete[] U;

    delete[] P;

    return 0;
}

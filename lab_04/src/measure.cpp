#ifndef MEASURE_CPP
#define MEASURE_CPP

#include <time.h>
#include <fstream>
#include <windows.h>

#include "matrix.cpp"
#include "multiply_matrices.cpp"

#define MAX_THREADS 32

using std::ofstream;

typedef void (*multiplicationLinearAlgorithm)(int **m1, int m, int n, int **m2, int q, int **r);
typedef void (*multiplicationParAlgorithm)(int **m1, int m, int n, int **m2, int q, int **r, int nThreads);

double PCFreq = 0.0;
__int64 CounterStart = 0;

void StartCounter()
{
    LARGE_INTEGER li;
    if (!QueryPerformanceFrequency(&li))
        cout << "QueryPerformanceFrequency failed!\n";

    PCFreq = double(li.QuadPart);

    QueryPerformanceCounter(&li);
    CounterStart = li.QuadPart;
}

double GetCounter()
{
    LARGE_INTEGER li;
    QueryPerformanceCounter(&li);
    return double(li.QuadPart - CounterStart) / PCFreq;
}

void measureLinear(int repeats, multiplicationLinearAlgorithm algortihm, char *name)
{
    srand(time(0));
    ofstream file;
    char fileName[30];
    matrix_t matr1, matr2, res;

    sprintf(fileName, "%s", name);
    file.open(fileName);
    for (int i = 100; i < 1001; i += 100)
    {
        initMatrix(&matr1, i, i);
        initMatrix(&matr2, i, i);
        initMatrix(&res, i, i);
        fillMatrixRandom(matr1);
        fillMatrixRandom(matr2);

        StartCounter();
        for (int j = 0; j < repeats; j++)
            algortihm(matr1.matrix, i, i, matr2.matrix, i, res.matrix);
        file << i << " " << GetCounter() / repeats << "\n";

        deleteMatrix(matr1);
        deleteMatrix(matr2);
        deleteMatrix(res);
    }
    file.close();
}

void measureParallel(int repeats, multiplicationParAlgorithm algortihm, char *name)
{
    srand(time(0));
    ofstream file;
    char fileName[30];
    matrix_t matr1, matr2, res;

    for (int t = 1; t <= 32; t *= 2)
    {
        sprintf(fileName, "%s%d", name, t);
        file.open(fileName);
        for (int i = 100; i < 1001; i += 100)
        {
            initMatrix(&matr1, i, i);
            initMatrix(&matr2, i, i);
            initMatrix(&res, i, i);
            fillMatrixRandom(matr1);
            fillMatrixRandom(matr2);

            StartCounter();
            for (int j = 0; j < repeats; j++)
                algortihm(matr1.matrix, i, i, matr2.matrix, i, res.matrix, t);
            file << i << " " << GetCounter() / repeats << "\n";

            deleteMatrix(matr1);
            deleteMatrix(matr2);
            deleteMatrix(res);
        }
        file.close();
    }
}

void randomTest()
{
    bool passed = true;
    matrix_t matrix1, matrix2, result1, result2;
    for (int rows = 1; rows < 10; rows++)
    {
        for (int m = 1; m < 10; m++)
        {
            initMatrix(&matrix1, rows, m);
            for (int cols = 1; cols < 10; cols++)
            {
                initMatrix(&matrix2, m, cols);
                initMatrix(&result1, rows, cols);
                initMatrix(&result2, rows, cols);

                fillMatrixRandom(matrix1);
                fillMatrixRandom(matrix2);

                multiplyMatricesWinograd(matrix1.matrix, matrix1.rows, matrix1.cols, matrix2.matrix, matrix2.cols, result1.matrix);

                multiplyMatricesWinogradP1(matrix1.matrix, matrix1.rows, matrix1.cols, matrix2.matrix, matrix2.cols, result2.matrix, 2);
                if (!compareMatrices(result1, result2))
                {
                    cout << "Incorrect multiplication using Winograd P1 with rows=" << rows << "; m=" << m << "; cols=" << cols << "\n";
                    passed = false;
                }

                multiplyMatricesWinogradP2(matrix1.matrix, matrix1.rows, matrix1.cols, matrix2.matrix, matrix2.cols, result2.matrix, 2);
                if (!compareMatrices(result1, result2))
                {
                    cout << "Incorrect multiplication using Winograd P2 with rows=" << rows << "; m=" << m << "; cols=" << cols << "\n";
                    passed = false;
                }

                deleteMatrix(matrix2);
                deleteMatrix(result1);
                deleteMatrix(result2);
            }
            deleteMatrix(matrix1);
        }
    }
    if (passed)
        cout << "All tests are passed!\n\n";
}


#endif

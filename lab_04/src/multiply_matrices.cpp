#ifndef MULTIPLY_MATRICES_CPP
#define MULTIPLY_MATRICES_CPP

#include <thread>

using std::thread;

void multiplyMatricesWinograd(int **matrix1, int m, int n, int **matrix2, int q, int **result)
{
    int buf;
    const int isOdd = n % 2;
    const int t = n - 1;
    if (isOdd)
        n -= 1;

    int *mulH = new int[m];
    for (int i = 0; i < m; i++)
    {
        buf = 0;
        for (int k = 0; k < n; k += 2)
            buf -= matrix1[i][k] * matrix1[i][k + 1];
        mulH[i] = buf;
    }

    int *mulV = new int[q];
    for (int i = 0; i < q; i++)
    {
        buf = 0;
        for (int k = 0; k < n; k += 2)
            buf -= matrix2[k][i] * matrix2[k + 1][i];
        mulV[i] = buf;
    }

    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < q; j++)
        {
            buf = mulH[i] + mulV[j];
            for (int k = 0; k < n; k += 2)
                buf += (matrix1[i][k] + matrix2[k + 1][j]) * (matrix1[i][k + 1] + matrix2[k][j]);
            result[i][j] = buf;
        }
    }

    if (isOdd)
    {
        for (int i = 0; i < m; i++)
            for (int j = 0; j < q; j++)
                result[i][j] += matrix1[i][t] * matrix2[t][j];
    }

    delete[] mulH;
    delete[] mulV;
}

void parallelMainCycle(int **matrix1, int **matrix2, int *mulH, int *mulV, int rs, int re, int columns, int rows, int **result)
{
    int buf;
    for (int i = rs; i < re; i++)
    {
        for (int j = 0; j < rows; j++)
        {
            buf = mulH[i] + mulV[j];
            for (int k = 0; k < columns; k += 2)
                buf += (matrix1[i][k] + matrix2[k + 1][j]) * (matrix1[i][k + 1] + matrix2[k][j]);
            result[i][j] = buf;
        }
    }
}

void multiplyMatricesWinogradP1(int **matrix1, int m, int n, int **matrix2, int q, int **result, int nThreads)
{
    int buf;
    const int isOdd = n % 2;
    const int t = n - 1;
    if (isOdd)
        n -= 1;

    int *mulH = new int[m];
    for (int i = 0; i < m; i++)
    {
        buf = 0;
        for (int k = 0; k < n; k += 2)
            buf -= matrix1[i][k] * matrix1[i][k + 1];
        mulH[i] = buf;
    }

    int *mulV = new int[q];
    for (int i = 0; i < q; i++)
    {
        buf = 0;
        for (int k = 0; k < n; k += 2)
            buf -= matrix2[k][i] * matrix2[k + 1][i];
        mulV[i] = buf;
    }

    thread *threads = new thread[nThreads];
    int rows = m / nThreads;
    int rs = 0;
    for (int t = 0; t < nThreads; t++)
    {
        int re = t == nThreads - 1 ? m : (rs + rows);
        threads[t] = thread(parallelMainCycle, matrix1, matrix2, mulH, mulV, rs, re, n, q, result);
        rs = re;
    }

    for (int i = 0; i < nThreads; i++)
        threads[i].join();

    if (isOdd)
    {
        for (int i = 0; i < m; i++)
            for (int j = 0; j < q; j++)
                result[i][j] += matrix1[i][t] * matrix2[t][j];
    }

    delete[] threads;
    delete[] mulH;
    delete[] mulV;
}

void parallelMul(int **matrix1, int vs, int ve, int n, int **matrix2, int hs, int he, int *mulV, int *mulH)
{
    int buf;
    for (int i = vs; i < ve; i++)
    {
        buf = 0;
        for (int k = 0; k < n; k += 2)
            buf -= matrix1[i][k] * matrix1[i][k + 1];
        mulH[i] = buf;
    }

    for (int i = hs; i < he; i++)
    {
        buf = 0;
        for (int k = 0; k < n; k += 2)
            buf -= matrix2[k][i] * matrix2[k + 1][i];
        mulV[i] = buf;
    }
}

void multiplyMatricesWinogradP2(int **matrix1, int m, int n, int **matrix2, int q, int **result, int nThreads)
{
    int buf;
    const int isOdd = n % 2;
    const int t = n - 1;
    if (isOdd)
        n -= 1;

    int *mulH = new int[m];
    int *mulV = new int[q];

    thread *threads = new thread[nThreads];
    int vs = 0;
    int vt = m / nThreads;
    int hs = 0;
    int ht = q / nThreads;
    for (int t = 0; t < nThreads; t++)
    {
        int ve = t == nThreads - 1 ? m : (vs + vt);
        int he = t == nThreads - 1 ? q : (hs + ht);
        threads[t] = thread(parallelMul, matrix1, vs, ve, n, matrix2, hs, he, mulV, mulH);

        vs = ve;
        hs = he;
    }

    for (int i = 0; i < nThreads; i++)
        threads[i].join();

    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < q; j++)
        {
            buf = mulH[i] + mulV[j];
            for (int k = 0; k < n; k += 2)
                buf += (matrix1[i][k] + matrix2[k + 1][j]) * (matrix1[i][k + 1] + matrix2[k][j]);
            result[i][j] = buf;
        }
    }

    if (isOdd)
    {
        for (int i = 0; i < m; i++)
            for (int j = 0; j < q; j++)
                result[i][j] += matrix1[i][t] * matrix2[t][j];
    }

    delete[] mulH;
    delete[] mulV;
}

#endif

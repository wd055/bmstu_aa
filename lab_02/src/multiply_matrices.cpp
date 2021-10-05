#ifndef MULTIPLY_MATRICES_CPP
#define MULTIPLY_MATRICES_CPP

void multiplyMatricesStandard(int **matrix1, int m, int n, int **matrix2, int q, int **result)
{
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < q; j++)
        {
            result[i][j] = 0;
            for (int k = 0; k < n; k++)
            {
                result[i][j] = result[i][j] + matrix1[i][k] * matrix2[k][j];
            }
        }
    }
}

void multiplyMatricesWinograd(int **matrix1, int m, int n, int **matrix2, int q, int **result)
{
    int *mulH = new int[m];
    for (int i = 0; i < m; i++)
    {
        mulH[i] = 0;
        for (int k = 0; k < n / 2; k++)
        {
            mulH[i] = mulH[i] + matrix1[i][2 * k] * matrix1[i][2 * k + 1];
        }
    }

    int *mulV = new int[q];
    for (int i = 0; i < q; i++)
    {
        mulV[i] = 0;
        for (int k = 0; k < n / 2; k++)
            mulV[i] = mulV[i] + matrix2[2 * k][i] * matrix2[2 * k + 1][i];
    }

    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < q; j++)
        {
            result[i][j] = -mulH[i] - mulV[j];
            for (int k = 0; k < n / 2; k++)
                result[i][j] = result[i][j] + (matrix1[i][2 * k] + matrix2[2 * k + 1][j]) * (matrix1[i][2 * k + 1] + matrix2[2 * k][j]);
        }
    }

    if (n % 2 == 1)
    {
        for (int i = 0; i < m; i++)
            for (int j = 0; j < q; j++)
                result[i][j] = result[i][j] + matrix1[i][n - 1] * matrix2[n - 1][j];
    }
    delete[] mulH;
    delete[] mulV;
}

// +=
// заранее выч. конст.
// k < n/2; k++ -> k < n; k += 2
// объединил 3 и 4
// mulh mulv уже негативные
// Ввёл buf
void multiplyMatricesWinogradOptimized(int **matrix1, int m, int n, int **matrix2, int q, int **result)
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
            if (isOdd == 1)
                buf += matrix1[i][t] * matrix2[t][j];
            result[i][j] = buf;
        }
    }
    delete[] mulH;
    delete[] mulV;
}

#endif

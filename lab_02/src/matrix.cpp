#ifndef MATRIX_CPP
#define MATRIX_CPP

#include <iostream>

using std::cin;
using std::cout;
using std::endl;

typedef struct
{
    int **matrix;
    int rows;
    int cols;
} matrix_t;

void initMatrix(matrix_t *matr, int rows, int cols)
{
    matr->rows = rows;
    matr->cols = cols;
    matr->matrix = new int *[matr->rows];
    for (int i = 0; i < matr->rows; i++)
        matr->matrix[i] = new int[matr->cols]{0};
}

void fillMatrix(matrix_t matr, int value)
{
    for (int i = 0; i < matr.rows; i++)
        for (int j = 0; j < matr.cols; j++)
            matr.matrix[i][j] = value;
}

void fillMatrixRandom(matrix_t matr)
{
    for (int i = 0; i < matr.rows; i++)
        for (int j = 0; j < matr.cols; j++)
            matr.matrix[i][j] = rand();
}

void deleteMatrix(matrix_t matr)
{
    for (int i = 0; i < matr.rows; i++)
        delete[] matr.matrix[i];
    delete[] matr.matrix;
}

void inputMatrix(matrix_t matr)
{
    for (int i = 0; i < matr.rows; i++)
        for (int j = 0; j < matr.cols; j++)
            cin >> matr.matrix[i][j];
}

void outputMatrix(matrix_t matr)
{
    for (int i = 0; i < matr.rows; i++)
    {
        for (int j = 0; j < matr.cols; j++)
            cout << matr.matrix[i][j];
        cout << endl;
    }
}

bool compareMatrices(matrix_t matr1, matrix_t matr2) // ПЛОХОЕ НАЗВАНИЕ
{
    bool similar = true;
    for (int i = 0; i < matr1.rows; i++)
        for (int j = 0; j < matr1.cols; j++)
            if (matr1.matrix[i][j] != matr2.matrix[i][j])
            {
                similar = false;
                break;
            }
    return similar;
}

#endif

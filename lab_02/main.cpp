#include "./src/matrix.cpp"
#include "./src/multiply_matrices.cpp"
#include "./src/measure.cpp"

using std::cout;
using std::endl;
using std::cin;

int main()
{
    while (1)
    {
        int choice = 3;
        cout << "Menu:\n";
        cout << "1. Multiply matrices\n";
        cout << "2. Measure time\n";
        cout << "3. Check work\n";
        cout << "4. Exit\n";
        cout << "Input your choice: ";
        cin >> choice;

        if (choice == 1)
        {
            matrix_t matr1, matr2, res;
            int rows1, rows2;
            int cols1, cols2;
            cout << "Number of rows for first matrix: ";
            cin >> rows1;
            cout << "Number of columns for first matrix: ";
            cin >> cols1;
            cout << "Number of columns for second matrix: ";
            cin >> cols2;
            initMatrix(&matr1, rows1, cols1);
            initMatrix(&matr2, cols1, cols2);
            initMatrix(&res, rows1, cols2);

            cout << "Matrix 1:\n";
            inputMatrix(matr1);

            cout << "Matrix 2:\n";
            inputMatrix(matr2);

            multiplyMatricesStandard(matr1.matrix, matr1.rows, matr1.cols, matr2.matrix, matr2.cols, res.matrix);
            cout << "Standart:\n";
            outputMatrix(res);

            multiplyMatricesWinograd(matr1.matrix, matr1.rows, matr1.cols, matr2.matrix, matr2.cols, res.matrix);
            cout << "Winograd:\n";
            outputMatrix(res);

            multiplyMatricesWinogradOptimized(matr1.matrix, matr1.rows, matr1.cols, matr2.matrix, matr2.cols, res.matrix);
            cout << "Winograd optimized:\n";
            outputMatrix(res);

            deleteMatrix(matr1);
            deleteMatrix(matr2);
            deleteMatrix(res);
        }
        else if (choice == 2)
        {
            int repeats;
            cout << "Input number of repeats: ";
            cin >> repeats;

            char name[9] = "standard";

            measureMatricesMultiplication(repeats, multiplyMatricesStandard, name);
            cout << "Measured standard\n";
            strcpy(name, "winograd");
            measureMatricesMultiplication(repeats, multiplyMatricesWinograd, name);
            cout << "Measured Winograd\n";
            strcpy(name, "winoptim");
            measureMatricesMultiplication(repeats, multiplyMatricesWinogradOptimized, name);
            cout << "Measured Winograd optimized\n\n";
        }
        else if (choice == 3)
        {
            randomTest();
        }
        else
        {
            break;
        }
    }
    return 0;
}
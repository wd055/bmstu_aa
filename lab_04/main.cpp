#include "./src/array.cpp"
#include "./src/search.cpp"
#include "./src/measure.cpp"

using std::cin;
using std::cout;
using std::endl;

int main()
{
    while (1)
    {
        int choice = 3;
        cout << "Menu:\n";
        cout << "1. Seacrh in array\n";
        cout << "2. Measure time\n";
        cout << "3. Exit\n";
        cout << "Input your choice: ";
        cin >> choice;

        if (choice == 1)
        {
            array_t arr;
            int length;
            int searchInt;

            cout << "Number of length for array: ";
            cin >> length;
            initArray(&arr, length);

            cout << "Array:";
            inputArray(arr);

            cout << "Search: ";
            cin >> searchInt;

            int res = -1;
            searchInArray(arr.array, arr.length, 0, arr.length, searchInt, res);
            cout << "Index:" << res << endl;

            deleteArray(arr);
        }
        else if (choice == 2)
        {
            int repeats;
            cout << "Input number of repeats: ";
            cin >> repeats;

            char name[20] = "tempRes/linear";

            measureLinear(repeats, name);
            cout << "Measured linear\n";

            strcpy(name, "tempRes/parallel_");
            measureParallel(repeats, name);
            cout << "Measured parallel\n";
        }
        else
        {
            break;
        }
    }
    return 0;
}
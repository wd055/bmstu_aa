#include "./src/array.cpp"
#include "./src/sort.cpp"
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
        cout << "1. Sort array\n";
        cout << "2. Measure time\n";
        cout << "3. Check work\n";
        cout << "4. Exit\n";
        cout << "Input your choice: ";
        cin >> choice;

        if (choice == 1)
        {
            array_t array, res;
            int length;
            cout << "Length of array: ";
            cin >> length;
            if (length <= 0)
            {
                cout << "Length of array is not positive!\n\n";
                continue;
            }
            initArray(&array, length);
            initArray(&res, length);

            cout << "Input array:\n";
            inputArray(array);

            copyArray(res, array);

            bubbleSort(res);
            cout << "Bubble sort:\n";
            outputArray(res);

            copyArray(res, array);

            heapSort(res);
            cout << "Heap sort:\n";
            outputArray(res);

            copyArray(res, array);

            selectionSort(res);
            cout << "Selection sort:\n";
            outputArray(res);

            deleteArray(array);
            deleteArray(res);
        }
        else if (choice == 2)
        {
            int repeats;
            cout << "Input number of repeats: ";
            cin >> repeats;

            char name[30] = "tempRes\\bubbleSort";

            measureSortingTime(repeats, 50000, bubbleSort, name);
            cout << "Measured bubble sort\n";
            strcpy(name, "tempRes\\selectionSort");
            measureSortingTime(repeats, 50000, selectionSort, name);
            cout << "Measured selection sort\n";
            strcpy(name, "tempRes\\heapSort");
            measureSortingTime(repeats, 50000, heapSort, name);
            cout << "Measured heap sort\n\n";
        }
        else if (choice == 3)
        {
            randomTest();
            sortedTest();
        }
        else
        {
            break;
        }
    }
    return 0;
}
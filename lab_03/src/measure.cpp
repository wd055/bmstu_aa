#ifndef MEASURE_CPP
#define MEASURE_CPP

#include <iostream>
#include <time.h>
#include <fstream>
#include <windows.h>
#include "array.cpp"
#include "sort.cpp"

using namespace std;

typedef void (*sortingAlgorithm)(array_t array);

double PCFreq = 0.0;
__int64 CounterStart = 0;

void StartCounter()
{
    LARGE_INTEGER li;
    if (!QueryPerformanceFrequency(&li))
        cout << "QueryPerformanceFrequency failed!\n";

    PCFreq = double(li.QuadPart) / 1000.;

    QueryPerformanceCounter(&li);
    CounterStart = li.QuadPart;
}

double GetCounter()
{
    LARGE_INTEGER li;
    QueryPerformanceCounter(&li);
    return double(li.QuadPart - CounterStart) / PCFreq;
}

void measureSortingTime(int repeats, int max, sortingAlgorithm algortihm, char *name)
{
    srand(time(0));
    ofstream file;
    char fileName[50];
    array_t array;

    strcpy(fileName, name);
    strcat(fileName, "Random.txt");
    file.open(fileName);
    for (int i = max / 10; i <= max; i += max / 10)
    {
        initArray(&array, i);
        fillArrayRandom(array);

        StartCounter();
        for (int j = 0; j < repeats; j++)
            algortihm(array);
        file << i << " " << GetCounter() / repeats << "\n";

        deleteArray(array);
    }
    file.close();

    strcpy(fileName, name);
    strcat(fileName, "SortedA.txt");
    file.open(fileName);
    for (int i = max / 10; i <= max; i += max / 10)
    {
        initArray(&array, i);
        fillArraySorted(array);

        StartCounter();
        for (int j = 0; j < repeats; j++)
            algortihm(array);
        file << i << " " << GetCounter() / repeats << "\n";

        deleteArray(array);
    }
    file.close();

    strcpy(fileName, name);
    strcat(fileName, "SortedD.txt");
    file.open(fileName);
    for (int i = max / 10; i <= max; i += max / 10)
    {
        initArray(&array, i);
        fillArraySorted(array, false);

        StartCounter();
        for (int j = 0; j < repeats; j++)
            algortihm(array);
        file << i << " " << GetCounter() / repeats << "\n";

        deleteArray(array);
    }
    file.close();
}

void randomTest()
{
    bool passed = true;
    array_t array1, array2, arrayConst;
    for (int length = 1; length < 10; length++)
    {
        initArray(&array1, length);
        initArray(&array2, length);
        initArray(&arrayConst, length);

        fillArrayRandom(arrayConst);
        copyArray(array1, arrayConst);
        copyArray(array2, arrayConst);

        bubbleSort(array1);
        selectionSort(array2);

        if (!compareArrays(array1, array2))
        {
            cout << "Incorrect sorting using selection sort with length=" << length << ";\n";
            passed = false;
        }

        copyArray(array2, arrayConst);

        heapSort(array2);

        if (!compareArrays(array1, array2))
        {
            cout << "Incorrect sorting using heap sort with length=" << length << ";\n";
            passed = false;
        }

        deleteArray(array1);
        deleteArray(array2);
        deleteArray(arrayConst);
    }
    if (passed)
        cout << "All tests are passed!\n\n";
}

void sortedTest()
{
    bool passed = true;
    array_t array1, array2, arrayConst;
    for (int length = 1; length < 10; length++)
    {
        initArray(&array1, length);
        initArray(&array2, length);
        initArray(&arrayConst, length);

        fillArraySorted(arrayConst);
        copyArray(array1, arrayConst);
        copyArray(array2, arrayConst);

        bubbleSort(array1);
        selectionSort(array2);

        if (!compareArrays(array1, array2))
        {
            cout << "Incorrect sorting using selection sort with length=" << length << ";\n";
            passed = false;
        }

        copyArray(array2, arrayConst);

        heapSort(array2);

        if (!compareArrays(array1, array2))
        {
            cout << "Incorrect sorting using heap sort with length=" << length << ";\n";
            passed = false;
        }

        deleteArray(array1);
        deleteArray(array2);
        deleteArray(arrayConst);
    }
    if (passed)
        cout << "All tests are passed!\n\n";
}

#endif
#ifndef ARRAY_CPP
#define ARRAY_CPP

#include <iostream>

using std::cin;
using std::cout;
using std::endl;

typedef struct
{
    int *array;
    int length;
} array_t;

void initArray(array_t *arr, int length)
{
    arr->length = length;
    arr->array = new int[arr->length];
}

void fillArray(array_t arr, int value)
{
    for (int i = 0; i < arr.length; i++)
        arr.array[i] = value;
}

void fillArrayRandom(array_t arr)
{
    for (int i = 0; i < arr.length; i++)
        arr.array[i] = rand();
}

void deleteArray(array_t arr)
{
    delete[] arr.array;
}

void inputArray(array_t arr)
{
    for (int i = 0; i < arr.length; i++)
        cin >> arr.array[i];
}

void outputArray(array_t arr)
{
    for (int i = 0; i < arr.length; i++)
    {
        cout << arr.array[i];
    }
    cout << endl;
}

bool compareMatrices(array_t arr1, array_t arr2)
{
    bool similar = true;
    for (int i = 0; i < arr1.length; i++)
        if (arr1.array[i] != arr2.array[i])
        {
            similar = false;
            break;
        }
    return similar;
}

#endif

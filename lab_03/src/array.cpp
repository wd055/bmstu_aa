#ifndef ARRAY_CPP
#define ARRAY_CPP

#include <iostream>

using std::cout;
using std::endl;
using std::cin;

typedef struct
{
    int *array;
    int length;
} array_t;

void copyArray(array_t to, array_t from)
{
    for (int i = 0; i < from.length; i++)
        to.array[i] = from.array[i];
}

void deleteArray(array_t array)
{
    delete[] array.array;
}

void initArray(array_t *array, int length)
{
    array->length = length;
    array->array = new int[length]{0};
}

void inputArray(array_t array)
{
    for (int i = 0; i < array.length; i++)
        cin >> array.array[i];
}

void outputArray(array_t array)
{
    for (int i = 0; i < array.length; i++)
        cout << array.array[i];
    cout << endl;
}

bool compareArrays(array_t array1, array_t array2)
{
    bool similar = true;
    for (int i = 0; i < array1.length; i++)
        if (array1.array[i] != array2.array[i])
        {
            similar = false;
            break;
        }
    return similar;
}

void fillArrayRandom(array_t array)
{
    for (int i = 0; i < array.length; i++)
        array.array[i] = rand();
}

void fillArraySorted(array_t array, bool ascending = true)
{
    if (ascending)
        for (int i = 0; i < array.length; i++)
            array.array[i] = i;
    else
        for (int i = 0; i < array.length; i++)
            array.array[i] = array.length - i;
}

void fillMatrix(array_t array, int value)
{
    for (int i = 0; i < array.length; i++)
        array.array[i] = value;
}

#endif

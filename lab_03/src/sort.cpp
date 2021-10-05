#ifndef SORT_CPP
#define SORT_CPP
#include "array.cpp"

void bubbleSort(array_t array)
{
    bool changed = false;
    for (int i = 1; i < array.length; i++)
    {
        for (int j = 0; j < array.length - i; j++)
            if (array.array[j + 1] < array.array[j])
            {
                const int temp = array.array[j];
                array.array[j] = array.array[j + 1];
                array.array[j + 1] = temp;
                changed = true;
            }
        if (!changed)
            break;
    }
}

void selectionSort(array_t array)
{
    for(int i=0; i<array.length-1; i++)
    {
        int min_i = i;
        for(int j=i+1;j<array.length;j++)
        {
            if (array.array[j] < array.array[min_i])
                min_i = j;
        }
        if (min_i != i)
        {
            int tmp = array.array[i];
            array.array[i] = array.array[min_i];
            array.array[min_i] = tmp;
        }        
    }
}

void siftDown(array_t array, int i)
{
    int nMax = i;
    int value = array.array[i];
    while (true)
    {
        i = nMax;
        int childN = i*2 + 1;
        if ((childN < array.length) && (array.array[childN] > value))
            nMax = childN;
        childN++;
        if ((childN < array.length) && (array.array[childN] > array.array[nMax]))
            nMax = childN;
        if (nMax == i)
            break;
        array.array[i] = array.array[nMax];
        array.array[nMax] = value;
    }
}

void heapSort(array_t array)
{
    for (int i = array.length / 2 - 1; i >= 0; --i)
        siftDown(array, i);
    while (array.length > 1)
    {
        array.length--;

        int firstElement = array.array[0];
        array.array[0] = array.array[array.length];
        array.array[array.length] = firstElement;

        siftDown(array, 0);
    }
}

#endif

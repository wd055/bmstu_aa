#ifndef MEASURE_CPP
#define MEASURE_CPP

#include <time.h>
#include <fstream>
#include <windows.h>

#include "array.cpp"
#include "time.cpp"
#include "search.cpp"

#define MAX_THREADS 32
#define MIN_COUNT 10000
#define MAX_COUNT 10000001

using std::ofstream;

void measureLinear(int repeats, char *name)
{
    srand(time(0));
    ofstream file;
    char fileName[30];
    array_t arr;
    int res;

    sprintf(fileName, "%s", name);
    file.open(fileName);
    for (int i = MIN_COUNT; i < MAX_COUNT; i *= 10)
    {
        initArray(&arr, i);
        fillArrayRandom(arr);

        StartCounter();
        for (int j = 0; j < repeats; j++)
            searchInArray(arr.array, i, 0, i, rand(), res);
        file << i << " " << GetCounter() / repeats << endl;

        deleteArray(arr);
    }
    file.close();
}

void measureParallel(int repeats, char *name)
{
    srand(time(0));
    ofstream file;
    char fileName[30];
    array_t arr;
    int res;

    for (int t = 1; t <= MAX_THREADS; t *= 2)
    {
        sprintf(fileName, "%s%d", name, t);
        file.open(fileName);
        for (int i = MIN_COUNT; i < MAX_COUNT; i *= 10)
        {
            initArray(&arr, i);
            fillArrayRandom(arr);

            StartCounter();
            for (int j = 0; j < repeats; j++)
                parallelSearch(arr.array, i, rand(), t);
            file << i << " " << GetCounter() / repeats << "\n";

            deleteArray(arr);
        }
        file.close();
    }
}

#endif

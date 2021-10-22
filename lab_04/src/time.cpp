#ifndef TIME_CPP
#define TIME_CPP

#include <time.h>
#include <fstream>
#include <windows.h>
#include <iostream>

double PCFreq = 0.0;
__int64 CounterStart = 0;

using std::cout;

void StartCounter()
{
    LARGE_INTEGER li;
    if (!QueryPerformanceFrequency(&li))
        cout << "QueryPerformanceFrequency failed!\n";

    PCFreq = double(li.QuadPart);

    QueryPerformanceCounter(&li);
    CounterStart = li.QuadPart;
}

double GetCounter()
{
    LARGE_INTEGER li;
    QueryPerformanceCounter(&li);
    return double(li.QuadPart - CounterStart) / PCFreq;
}

#endif
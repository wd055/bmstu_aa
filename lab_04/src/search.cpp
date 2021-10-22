#ifndef SEARCH_CPP
#define SEARCH_CPP

#include <thread>

using std::ref;
using std::thread;

void searchInArray(int *array, int length, int start, int end, int search, int &result)
{
    for (int i = start; i < end; i++)
        if (array[i] == search)
            result = i;
}

int parallelSearch(int *array, int length, int search, int nThreads)
{
    int result = -1;
    thread *threads = new thread[nThreads];
    int step = length / nThreads;
    int start = 0;
    for (int t = 0; t < nThreads; t++)
    {
        int end = t == nThreads - 1 ? length : (start + step);
        threads[t] = thread(searchInArray, array, length, start, end, search, ref(result));
        start = end;
    }

    for (int i = 0; i < nThreads; i++)
        threads[i].join();

    delete[] threads;
    return result;
}

#endif

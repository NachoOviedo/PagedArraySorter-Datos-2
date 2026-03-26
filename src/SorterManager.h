//
// Created by nacho on 26/3/2026.
//

#ifndef PAGEDSORT_SORTERMANAGER_H
#define PAGEDSORT_SORTERMANAGER_H

#include <cstring>
#include <iostream>
#include "PagedArray.h"
#include "BUBBLESORT.h"
#include "HEAPSORT.h"
#include "MERGESORT.h"
#include "QUICKSORT.h"
#include "SHELLSORT.h"

//inline indicador de que esta bien que aparezca en mas de un archivo.

inline void SortManager (PagedArray& arr, int n, const char* algoritmo )
{
    if ( strcmp(algoritmo, "BUBBLESORT") == 0)
    {
        bubbleSort(arr, n);
    } else if ( strcmp(algoritmo, "QUICKSORT") == 0)
    {
        quickSort(arr, 0, n - 1);
    } else if ( strcmp(algoritmo, "SHELLSORT") == 0)
    {
        shellSort(arr, n);
    } else if ( strcmp(algoritmo, "MERGESORT") == 0)
    {
        mergeSort(arr, 0, n - 1);
    } else if ( strcmp(algoritmo, "HEAPSORT") == 0)
    {
        heapSort(arr, n);
    } else {
        std::cout << "Algoritmo invalido" << "\n";
    }
}
#endif //PAGEDSORT_SORTERMANAGER_H
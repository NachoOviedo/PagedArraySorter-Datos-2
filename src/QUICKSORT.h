//
// Created by nacho on 26/3/2026.
//

#ifndef PAGEDSORT_QUICKSORT_H
#define PAGEDSORT_QUICKSORT_H

#include "PagedArray.h"
#include <iostream>

int partition(PagedArray& arr, long long low, long long high) {
    int pivot = arr[high];
    int i = (low - 1);

    for (int j = low; j <= high - 1; j++) {
        if (arr[j] <= pivot) {
            i++;
            mySwap(arr, i, j);
        }
    }
    mySwap(arr, i + 1, high);
    return (i + 1);
}

void quickSort(PagedArray& arr, int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

#endif //PAGEDSORT_QUICKSORT_H
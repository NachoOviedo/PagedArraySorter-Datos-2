//
// Created by nacho on 26/3/2026.
//

#ifndef PAGEDSORT_HEAPSORT_H
#define PAGEDSORT_HEAPSORT_H

#include <algorithm>
#include "PagedArray.h"
using namespace std;

void heapify(PagedArray& arr, int n, int i) {
    int largest = i, l = 2*i + 1, r = 2*i + 2;
    if (l < n && arr[l] > arr[largest]) largest = l;
    if (r < n && arr[r] > arr[largest]) largest = r;
    if (largest != i) {
        swap(arr[i], arr[largest]);
        heapify(arr, n, largest);
    }
}

void heapSort(PagedArray& arr, int n) {
    for (int i = n / 2 - 1; i >= 0; i--) heapify(arr, n, i);
    for (int i = n - 1; i > 0; i--) {
        swap(arr[0], arr[i]);
        heapify(arr, i, 0);
    }
}

#endif //PAGEDSORT_HEAPSORT_H
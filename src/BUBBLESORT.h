//
// Created by nacho on 26/3/2026.
//

#ifndef PAGEDSORT_BUBBLESORT_H
#define PAGEDSORT_BUBBLESORT_H
#include "PagedArray.h"

#include <iostream>

void bubbleSort(PagedArray& arr, int n) {
    for (int i = 0; i < n - 1; i++) {
        bool swapped = false;
        for (int j = 0; j < n - i - 1; j++) {
            // Compare adjacent elements and swap if they are in the wrong order
            if (arr[j] > arr[j + 1]) {
                std::swap(arr[j], arr[j + 1]);
                swapped = true;
            }
        }
        // If no two elements were swapped by inner loop, then break
        if (!swapped)
            break;
    }
}


#endif //PAGEDSORT_BUBBLESORT_H
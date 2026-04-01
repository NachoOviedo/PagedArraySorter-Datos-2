//
// Created by nacho on 26/3/2026.
//

#ifndef PAGEDSORT_SHELLSORT_H
#define PAGEDSORT_SHELLSORT_H
#include "PagedArray.h"

// Function to perform Shell Sort
void shellSort(PagedArray& arr, long long n) {

    // Start with a large gap, then reduce the gap
    for (int gap = n / 2; gap > 0; gap /= 2) {
        // Perform a gapped insertion sort for this gap size
        // The inner loop sorts elements spaced by 'gap'
        for (int i = gap; i < n; i++) {
            // Store the current element to be inserted
            int temp = arr[i];

            // Shift earlier gap-sorted elements up until the correct position for arr[i] is found
            int j;
            for (j = i; j >= gap && arr[j - gap] > temp; j -= gap) {
                arr[j] = arr[j - gap];
            }

            // Place the stored element in its correct location
            arr[j] = temp;
        }
    }
}

#endif //PAGEDSORT_SHELLSORT_H
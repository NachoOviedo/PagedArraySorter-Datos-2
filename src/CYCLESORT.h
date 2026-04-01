//
// Created by nacho on 29/3/2026.
//

#ifndef PAGEDSORT_CYCLESORT_H
#define PAGEDSORT_CYCLESORT_H

#include <iostream>
#include <algorithm> // Required for std::swap

#include "PagedArray.h"

void cycleSort(PagedArray& arr, int n) {
    // Traverse the array to find cycles to rotate
    for (int cycle_start = 0; cycle_start <= n - 2; cycle_start++) {
        int item = arr[cycle_start];
        // Find the correct position for the current item
        int pos = cycle_start;
        for (int i = cycle_start + 1; i < n; i++) {
            if (arr[i] < item) {
                pos++;
            }
        }

        // If the item is already in its correct position, continue to the next cycle
        if (pos == cycle_start) {
            continue;
        }

        // Ignore any duplicate elements
        while (item == arr[pos]) {
            pos++;
        }

        // Put the item in its correct position
        if (pos != cycle_start) {
            std::swap(item, arr[pos]);
        }

        // Rotate the rest of the cycle
        while (pos != cycle_start) {
            pos = cycle_start;

            // Find the correct position for the swapped item
            for (int i = cycle_start + 1; i < n; i++) {
                if (arr[i] < item) {
                    pos++;
                }
            }

            // Ignore any duplicate elements
            while (item == arr[pos]) {
                pos++;
            }

            // Put the item in its correct position
            if (item != arr[pos]) {
                std::swap(item, arr[pos]);
            }
        }
    }
}

#endif //PAGEDSORT_CYCLESORT_H
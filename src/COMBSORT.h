//
// Created by nacho on 28/3/2026.
//

#ifndef PAGEDSORT_COMBSORT_H
#define PAGEDSORT_COMBSORT_H
#include "PagedArray.h"

// Function to update the gap size using a shrink factor (commonly 1.3)
int get_next_gap(int gap) {
    // Shrink gap by the shrink factor 1.3
    gap = (gap * 10) / 13;
    if (gap < 1) {
        return 1;
    }
    return gap;
}

// Function to implement the Comb Sort algorithm
void combSort(PagedArray& arr, int n) {
    int gap = n;
    bool swapped = true;

    // Keep going while the gap is not 1 or a swap occurred in the previous pass
    while (gap != 1 || swapped == true) {
        // Update the gap
        gap = get_next_gap(gap);

        // Reset swapped flag for this pass
        swapped = false;

        // A single pass through the array with the current gap
        for (int i = 0; i < n - gap; i++) {
            if (arr[i] > arr[i + gap]) {
                std::swap(arr[i], arr[i + gap]);
                swapped = true;
            }
        }
    }
}

#endif //PAGEDSORT_COMBSORT_H
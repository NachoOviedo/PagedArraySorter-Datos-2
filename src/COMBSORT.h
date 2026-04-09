//
// Created by nacho on 28/3/2026.
//

#ifndef PAGEDSORT_COMBSORT_H
#define PAGEDSORT_COMBSORT_H
#include "PagedArray.h"

int get_next_gap(int gap) {
    gap = (gap * 10) / 13;
    if (gap < 1) {
        return 1;
    }
    return gap;
}

void combSort(PagedArray& arr, int n) {
    int gap = n;
    bool swapped = true;

    while (gap != 1 || swapped == true) {
        gap = get_next_gap(gap);
        swapped = false;

        for (int i = 0; i < n - gap; i++) {
            if (arr[i] > arr[i + gap]) {
                mySwap(arr, i, i + gap);
                swapped = true;
            }
        }
    }
}

#endif //PAGEDSORT_COMBSORT_H
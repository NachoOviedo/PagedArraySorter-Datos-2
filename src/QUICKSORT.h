//
// Created by nacho on 26/3/2026.
//

#ifndef PAGEDSORT_QUICKSORT_H
#define PAGEDSORT_QUICKSORT_H

#include "PagedArray.h"
#include <iostream>

/*
 * This function takes the last element as the pivot, places the pivot
 * element at its correct position in a sorted array, and places all
 * smaller elements to the left of the pivot and all greater elements
 * to the right of the pivot.
 */
int partition(PagedArray& arr, int low, int high) {
    int pivot = arr[high]; // Choose the last element as the pivot
    int i = (low - 1); // Index of smaller element

    for (int j = low; j <= high - 1; j++) {
        // If current element is smaller than or equal to pivot
        if (arr[j] <= pivot) {
            i++; // Increment index of smaller element
            std::swap(arr[i], arr[j]);
        }
    }
    std::swap(arr[i + 1], arr[high]);
    return (i + 1);
}

/*
 * The main function that implements QuickSort()
 * arr[] --> Array to be sorted, low --> Starting index, high --> Ending index
 */
void quickSort(PagedArray& arr, int low, int high) {
    if (low < high) {
        /* pi is partitioning index, arr[pi] is now at right place */
        int pi = partition(arr, low, high);

        // Recursively sort elements before partition and after partition
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

#endif //PAGEDSORT_QUICKSORT_H
//
// Created by jwill on 2018-03-16.
//

#include <math.h>
#include <exception>
#include "Sorter.h"

void Sorter::bubbleSort(int *array, int arraySize) {
    int i, j, tmp;
    for(i = arraySize - 1; i >= 0; --i) {
        for(j = 0; j < i; j++) {
            if(array[j] > array[j+1]) {
                tmp = array[j];
                array[j] = array[j+1];
                array[j+1] = tmp;
            }
        }
    }
}

void Sorter::selectionSort(int *array, int arraySize) {
    int index, i, j, tmp;
    for(i = 0; i < arraySize; i++) {
        index = i;
        for(j = i; j < arraySize; j++) {
            if(array[j] < array[index]) {
                index = j;
            }
        }
        tmp = array[i];
        array[i] = array[index];
        array[index] = tmp;
    }
}

void Sorter::insertionSort(int* array, int arraySize) {
    int i, j, tmp;
    for(i = 1; i < arraySize; i++) {
        j = i;
        while(j > 0 && array[j - 1] > array[j]) {
            tmp = array[j];
            array[j] = array[j - 1];
            array[j - 1] = tmp;
            j--;
        }
    }
}

void Sorter::shellSort(int *array, int arraySize) {
    int i, j, tmp, increment;
    for(increment = arraySize/2; increment > 0; increment /= 2) {
        for(i = increment; i < arraySize; i++) {
            tmp = array[i];
            for(j = i; j >= increment; j -= increment) {
                if(tmp < array[j - increment]) {
                    array[j] = array[j - increment];
                } else {
                    break;
                }
            }
            array[j] = tmp;
        }
    }
}

void Sorter::mergeSort(int *array, int arraySize) {
    int tempArray [arraySize];
    mergeSort(array, 0, arraySize, tempArray);
}

void Sorter::mergeSort(int *array, int first, int last, int *tempArray) {
    if(last - first > 1) {
        int middle = (first + last) / 2;
        mergeSort(array, first, middle, tempArray);
        mergeSort(array, middle, last, tempArray);
        merge(array, first, middle, last, tempArray);
    }
}

void Sorter::merge(int *array, int first, int middle, int last, int *tempArray) {
    int i = first, j = middle, k;
    for(k = 0; i < middle && j < last; k++) {
        if(array[i] <= array[j]) {
            tempArray[k] = array[i++];
        } else {
            tempArray[k] = array[j++];
        }
    }
    for(; i < middle; k++) {
        tempArray[k] = array[i++];
    }
    for(; j < last; k++) {
        tempArray[k] = array[j++];
    }
    for(int index = 0; index < last - first; index++) {
        array[first + index] = tempArray[index];
    }
}

void Sorter::quickSort(int *array, int arraySize) {
    quickSort(array, 0, arraySize - 1);
}

void Sorter::quickSort(int *array, int left, int right) {
    if(left < right) {
        int middle = partition(array, left, right);
        quickSort(array, left, middle - 1);
        quickSort(array, middle+1, right);
    }
}

int Sorter::partition(int *array, int left, int right) {
    int i = left, pivot = array[left], j;
    for(j = left + 1; j <= right; j++) {
        if(pivot > array[j]) {
            array[i] = array[j];
            array[j] = array[i + 1];
            array[i + 1] = pivot;

            i++;
        }
    }
    return i;
}

void Sorter::sort(int *array, int arraySize, sortType type) {
    switch (type) {
        case bubble_sort:
            bubbleSort(array, arraySize);
            break;
        case selection_sort:
            selectionSort(array, arraySize);
            break;
        case insertion_sort:
            insertionSort(array, arraySize);
            break;
        case shell_sort:
            shellSort(array, arraySize);
            break;
        case merge_sort:
            mergeSort(array, arraySize);
            break;
        case quick_sort:
            quickSort(array, arraySize);
            break;
    }
}
//
// Created by jwill on 2018-03-16.
//

#ifndef ASSIGNMENT_3_BUBBLESORT_H
#define ASSIGNMENT_3_BUBBLESORT_H


class Sorter {
private:
    void merge(int* array, int first, int middle, int last, int* tempArray);
    void mergeSort(int* array, int first, int last, int* tempArray);
    void quickSort(int* array, int left, int right);
    int partition(int* array, int left, int right);
public:
    enum sortType {bubble_sort, selection_sort, insertion_sort, shell_sort, merge_sort, quick_sort};
    void bubbleSort(int *array, int arraySize);
    void selectionSort(int *array, int arraySize);
    void insertionSort(int* array, int arraySize);
    void shellSort(int* array, int arraySize);
    void mergeSort(int* array, int arraySize);
    void quickSort(int* array, int arraySize);
    void sort(int* array, int arraySize, sortType type);
};


#endif //ASSIGNMENT_3_BUBBLESORT_H

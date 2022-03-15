#include "sortsAndGenerates.h"
#include "stdlib.h"

#define FI 1.24733

void swap(int *a, int *b) {
    if (a != b) {
        *a ^= *b;
        *b ^= *a;
        *a ^= *b;
    }
}

// Функции сортировки

void bubbleSort(int *a, size_t n) {
    for (int i = 0; i < n - 1; i++)
        for (int j = 0; j < (n - 1) - i; j++)
            if (a[j] > a[j + 1])
                swap(a + j, a + j + 1);
}

void selectionSort(int *a, size_t n) {
    for (int i = 0; i < n - 1; i++) {
        int minPos = i;
        for (int j = i + 1; j < n; j++)
            if (a[j] < a[minPos])
                minPos = j;
        swap(a + i, a + minPos);
    }
}

void insertionSort(int *a, size_t n) {
    for (int currentElementIndex = 1; currentElementIndex < n; currentElementIndex++) {
        int currentElement = a[currentElementIndex];
        int vacantPlaceIndex = currentElementIndex;
        while (vacantPlaceIndex > 0 && a[vacantPlaceIndex - 1] >
        currentElement) {
            a[vacantPlaceIndex] = a[vacantPlaceIndex - 1];
            vacantPlaceIndex--;
        }
        a[vacantPlaceIndex] = currentElement;
    }
}

void combSort(int *a, size_t n) {
    size_t step = n;
    bool swapped = true;
    while (step > 1 || swapped) {
        if (step > 1)
            step /= FI;
        swapped = 0;
        for (size_t i = 0, j = i + step; j < n; ++i, ++j)
            if (a[i] > a[j]) {
                swap(a + i, a + j);
                swapped = 1;
            }
    }
}

void shellSort(int *a, size_t n) {

}

void digitalSort(int *a, size_t n) {

}


// Генерация тестовых последовательностей

void generateRandomArray(int *a, size_t n) {
    srand(42);
    for (int i = 0; i < n; i++)
        a[i] = rand() % n;
}

void generateOrderedArray(int *a, size_t n) {
    for (int i = 0; i < n; i++)
        a[i] = i;
}

void generateOrderedBackwards(int *a, size_t n) {
    for (int i = 0; i < n; i++)
        a[i] = (int) (n - 1) - i;
}
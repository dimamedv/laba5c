#include "sortsAndGenerates.h"
#include "stdlib.h"

void swap(int *a, int *b) {
    *a ^= *b;
    *b ^= *a;
    *a ^= *b;
}

// Функции сортировки

void bubbleSort(int *a, size_t n) {
    for (int i = 0; i < n - 1; i++)
        for (int j = 0; j < n - i - 1; j++)
            if (a[j] > a[j + 1])
                swap(a + j, a + j + 1);
}

void selectionSort(int *a, size_t n) {

}

void insertionSort(int *a, size_t n) {

}

void combSort(int *a, size_t n) {

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
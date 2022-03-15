#ifndef LABA5C_SORTSANDGENERATES_H
#define LABA5C_SORTSANDGENERATES_H

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <time.h>

// Функции сортировки

void bubbleSort(int *a, size_t n);

void selectionSort(int *a, size_t n);

void insertionSort(int *a, size_t n);

void combSort(int *a, size_t n);

void shellSort(int *a, size_t n);

void digitalSort(int *a, size_t n);



// Генерация тестовых последовательностей

void generateRandomArray(int *a, size_t n);

void generateOrderedArray(int *a, size_t n);

void generateOrderedBackwards(int *a, size_t n);


#endif //LABA5C_SORTSANDGENERATES_H

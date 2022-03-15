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
    for (int currentElementIndex = 1;
         currentElementIndex < n; currentElementIndex++) {
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
    for (size_t gap = n / 2; gap > 0; gap /= 2) {
        for (int i = (int) gap; i < n; i++) {
            for (int j = i - gap; j >= 0 && a[j] > a[j + gap]; j -= gap) {
                swap(a + j, a + j + gap);
            }
        }
    }
}

typedef struct number {
    int number;
    int key;
} number;

#define BYTE_SIZE 8
#define SCAN_ONE_BYTE 255
#define VARIANTS_FOR_ONE_BYTE 256

void digitalSort(int *a, size_t size) {
    number numbers[size];
    size_t *countKeys = calloc(VARIANTS_FOR_ONE_BYTE, sizeof(size_t));

    for (int currentShift = 0;
         currentShift < sizeof(int) * 8; currentShift += BYTE_SIZE) {
        for (int j = 0; j < size; ++j) {
            int key = (a[j] >> currentShift) & SCAN_ONE_BYTE;
            numbers[j].number = a[j];
            numbers[j].key = key;
            countKeys[key]++;
        }

        size_t keyStartIndex[VARIANTS_FOR_ONE_BYTE];
        keyStartIndex[0] = 0;

        for (int j = 1; j < VARIANTS_FOR_ONE_BYTE; ++j)
            keyStartIndex[j] = keyStartIndex[j - 1] + countKeys[j - 1];

        for (int j = 0; j < size; ++j) {
            size_t iWrite = keyStartIndex[numbers[j].key]++;
            a[iWrite] = numbers[j].number;
        }

        for (int j = 0; j < VARIANTS_FOR_ONE_BYTE; ++j)
            countKeys[j] = 0;
    }

    free(countKeys);
}


long long bubbleSortCountCompares(int *a, size_t n) {
    long long comparesTotal = 0;

    for (int i = 0; ++comparesTotal && i < n - 1; i++)
        for (int j = 0; ++comparesTotal && j < (n - 1) - i; j++)
            if (++comparesTotal && a[j] > a[j + 1])
                swap(a + j, a + j + 1);

    return comparesTotal;
}


long long selectionSortCountCompares(int *a, size_t n) {
    long long comparesTotal = 0;

    for (int i = 0; ++comparesTotal && i < n - 1; i++) {
        int minPos = i;

        for (int j = i + 1; ++comparesTotal && j < n; j++)
            if (++comparesTotal && a[j] < a[minPos])
                minPos = j;

        swap(a + i, a + minPos);
    }

    return comparesTotal;
}


long long insertionSortCountCompares(int *a, size_t n) {
    long long comparesTotal = 0;

    for (int currentElementIndex = 1;
         ++comparesTotal && currentElementIndex < n; currentElementIndex++) {
        int currentElement = a[currentElementIndex];
        int vacantPlaceIndex = currentElementIndex;

        while (++comparesTotal && vacantPlaceIndex > 0 &&
               ++comparesTotal && a[vacantPlaceIndex - 1] > currentElement) {
            a[vacantPlaceIndex] = a[vacantPlaceIndex - 1];
            vacantPlaceIndex--;
        }

        a[vacantPlaceIndex] = currentElement;
    }

    return comparesTotal;
}


long long combSortCountCompares(int *a, size_t n) {
    long long comparesTotal = 0;

    size_t step = n;
    bool swapped = true;

    while (step > 1 || swapped) {
        if (step > 1)
            step /= FI;
        swapped = 0;

        for (size_t i = 0, j = i + step; ++comparesTotal && j < n; ++i, ++j)
            if (++comparesTotal && a[i] > a[j]) {
                swap(a + i, a + j);
                swapped = 1;
            }
    }

    return comparesTotal;
}


long long shellSortCountCompares(int *a, size_t n) {
    long long comparesTotal = 0;

    for (size_t gap = n / 2; ++comparesTotal && gap > 0; gap /= 2)
        for (int i = (int) gap; ++comparesTotal && i < n; i++)
            for (int j = i - gap; ++comparesTotal && j >= 0 &&
                                  ++comparesTotal && a[j] > a[j + gap];
                 j -= gap)
                swap(a + j, a + j + gap);

    return comparesTotal;
}


long long digitalSortCountCompares(int *a, size_t size) {
    long long comparesTotal = 0;

    number numbers[size];
    size_t *countKeys = calloc(VARIANTS_FOR_ONE_BYTE, sizeof(size_t));

    for (int currentShift = 0;
         ++comparesTotal && currentShift < sizeof(int) * 8; currentShift +=
                 BYTE_SIZE) {
        for (int j = 0; ++comparesTotal && j < size; ++j) {
            int key = (a[j] >> currentShift) & SCAN_ONE_BYTE;
            numbers[j].number = a[j];
            numbers[j].key = key;
            countKeys[key]++;
        }

        size_t keyStartIndex[VARIANTS_FOR_ONE_BYTE];
        keyStartIndex[0] = 0;

        for (int j = 1; ++comparesTotal && j < VARIANTS_FOR_ONE_BYTE; ++j)
            keyStartIndex[j] = keyStartIndex[j - 1] + countKeys[j - 1];

        for (int j = 0; ++comparesTotal && j < size; ++j) {
            size_t iWrite = keyStartIndex[numbers[j].key]++;
            a[iWrite] = numbers[j].number;
        }

        for (int j = 0; ++comparesTotal && j < VARIANTS_FOR_ONE_BYTE; ++j)
            countKeys[j] = 0;
    }

    free(countKeys);

    return comparesTotal;
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
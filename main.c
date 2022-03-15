#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <time.h>

#define TIME_TEST(testCode, time) { \
    clock_t start_time = clock();   \
    testCode                        \
    clock_t end_time = clock();     \
    clock_t sort_time = end_time - start_time; \
    time = (double) sort_time / CLOCKS_PER_SEC;\
    }

#define ARRAY_SIZE(a) sizeof(a) / sizeof(a[0])

typedef struct SortFunc {
    void (*sort)(int *a, size_t n);

    char name[64];
} SortFunc;

typedef struct GeneratingFunc {
    void (*generate)(int *a, size_t n);

    char name[64];
} GeneratingFunc;

void outputArray_(int *a, size_t n) {
    for (int i = 0; i < n; i++)
        printf("%d ", a[i]);
}

bool isOrdered(const int *a, size_t n) {
    for (int i = 1; i < n; i++)
        if (a[i - 1] > a[i])
            return false;
    return true;
}

void checkTime(void(*sortFunc)(int *, size_t),
               void(*generateFunc)(int *, size_t),
               size_t size, char *experimentName) {
    static size_t runCounter = 1;

    static int innerBuffer[100000];
    generateFunc(innerBuffer, size);
    printf("Run #%zu| ", runCounter++);
    printf("Name: %s\n", experimentName);

    double time;
    TIME_TEST({
        sortFunc(innerBuffer, size);
    }, time);

    printf("Status: ");
    if (isOrdered(innerBuffer, size)) {
        printf("OK! Time: %.3f s.\n", time);

        char filename[256];
        sprintf(filename, "./data/%s.csv", experimentName);
        FILE *f = fopen(filename, "a");
        if (f == NULL) {
            printf("FileOpenError %s", filename);
            exit(1);
        }
        fprintf(f, "%zu; %.3f\n", size, time);
        fclose(f);
    } else {
        printf("Wrong!\n");

        outputArray_(innerBuffer, size);

        exit(1);
    }
}


// Функции сортировки

void selectionSort(int *a, size_t n) {

}

void insertionSort(int *a, size_t n) {

}


// Генерация тестовых последовательностей

void generateRandomArray(int *a, size_t n) {

}

void generateOrderedArray(int *a, size_t n) {

}

void generateOrderedBackwards(int *a, size_t n) {

}

void timeExperiment() {
    SortFunc sorts[] = {
            {selectionSort, "selectionSort"},
            {insertionSort, "insertionSort"},

    };
    const unsigned FUNCS_N = ARRAY_SIZE(sorts);

    GeneratingFunc generatingFuncs[] = {
            {generateRandomArray, "random"},
            {generateOrderedArray, "ordered"},
            {generateOrderedBackwards, "orderedBackwards"}
    };
    const unsigned  CASES_N = ARRAY_SIZE(generatingFuncs);

    for (size_t size = 10000; size <= 100000; size += 10000) {
        printf("------------------------------\n");
        printf("Size: %zul\n", size);
        for (int i = 0; i < FUNCS_N; i++) {
            for (int j = 0; j < CASES_N; j++) {
                static char filename[128];
                sprintf(filename, "%s_%s_time",
                        sorts[i].name, generatingFuncs[j].name);
                checkTime(sorts[i].sort,
                          generatingFuncs[j].generate,
                          size, filename);
            }
        }
        printf("\n");
    }
}


int main() {
    timeExperiment();

    return 0;
}

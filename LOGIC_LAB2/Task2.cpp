#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <locale.h>

#define N 50000

// 1. Сортировка Шелла (из методического указания)
void shell(int* items, int count) {
    int i, j, gap, k;
    int x, a[5];
    a[0] = 9; a[1] = 5; a[2] = 3; a[3] = 2; a[4] = 1;

    for (k = 0; k < 5; k++) {
        gap = a[k];
        for (i = gap; i < count; ++i) {
            x = items[i];
            for (j = i - gap; (j >= 0) && (x < items[j]); j = j - gap) {
                items[j + gap] = items[j];
            }
            items[j + gap] = x;
        }
    }
}

// 2. Быстрая сортировка с оптимизацией глубины стека O(log N)
void qs(int* items, int left, int right) {
    while (left < right) {
        int i = left, j = right;
        int x = items[left + (right - left) / 2];

        do {
            while ((items[i] < x) && (i < right)) i++;
            while ((x < items[j]) && (j > left)) j--;

            if (i <= j) {
                int y = items[i];
                items[i] = items[j];
                items[j] = y;
                i++;
                j--;
            }
        } while (i <= j);

        
        if ((j - left) < (right - i)) {
            if (left < j) qs(items, left, j);
            left = i; 
        }
        else {
            if (i < right) qs(items, i, right);
            right = j;
        }
    }
}

// Компаратор для qsort
int compare_ints(const void* a, const void* b) {
    int arg1 = *(const int*)a;
    int arg2 = *(const int*)b;
    if (arg1 < arg2) return -1;
    if (arg1 > arg2) return 1;
    return 0;
}

// Генерация наборов данных
void generate_random(int* arr, int n) {
    for (int i = 0; i < n; i++) arr[i] = rand() % 100000;
}

void generate_ascending(int* arr, int n) {
    for (int i = 0; i < n; i++) arr[i] = i;
}

void generate_descending(int* arr, int n) {
    for (int i = 0; i < n; i++) arr[i] = n - i;
}

void generate_half_asc_half_desc(int* arr, int n) {
    int mid = n / 2;
    for (int i = 0; i < mid; i++) arr[i] = i;
    for (int i = mid; i < n; i++) arr[i] = n - i;
}

void run_test(const char* test_name, void (*gen_func)(int*, int)) {
    int* orig = (int*)malloc(N * sizeof(int));
    int* work = (int*)malloc(N * sizeof(int));

    if (!orig || !work) {
        printf("Ошибка выделения памяти!\n");
        return;
    }

    gen_func(orig, N);

    printf("\n=== Набор данных: %s (N = %d) ===\n", test_name, N);

    // 1. Тест Сортировки Шелла
    memcpy(work, orig, N * sizeof(int));
    clock_t start = clock();
    shell(work, N);
    clock_t end = clock();
    printf("1. Сортировка Шелла:    %10.4f сек.\n", (double)(end - start) / CLOCKS_PER_SEC);

    // 2. Тест Быстрой сортировки (qs)
    memcpy(work, orig, N * sizeof(int));
    start = clock();
    qs(work, 0, N - 1);
    end = clock();
    printf("2. Своя QuickSort (qs): %10.4f сек.\n", (double)(end - start) / CLOCKS_PER_SEC);

    // 3. Тест Стандартной qsort
    memcpy(work, orig, N * sizeof(int));
    start = clock();
    qsort(work, N, sizeof(int), compare_ints);
    end = clock();
    printf("3. Стандартная qsort:   %10.4f сек.\n", (double)(end - start) / CLOCKS_PER_SEC);

    free(orig);
    free(work);
}

int main(void) {
    setlocale(LC_ALL, "rus");
    setvbuf(stdin, NULL, _IONBF, 0);
    setvbuf(stdout, NULL, _IONBF, 0);
    srand((unsigned int)time(NULL));

    run_test("Случайный массив", generate_random);
    run_test("Возрастающая последовательность", generate_ascending);
    run_test("Убывающая последовательность", generate_descending);
    run_test("1/2 возрастающая, 1/2 убывающая", generate_half_asc_half_desc);

    return 0;
}
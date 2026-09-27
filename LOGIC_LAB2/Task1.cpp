#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>

void measure_matrix_multiply_fast(int N) {
    // 1. Выделяем память ОДНИМ непрерывным блоком
    // Используем size_t, чтобы избежать переполнения при N = 10000 (10000 * 10000 = 100 000 000)
    int* a = (int*)malloc((size_t)N * N * sizeof(int));
    int* b = (int*)malloc((size_t)N * N * sizeof(int));
    int* c = (int*)calloc((size_t)N * N, sizeof(int)); // calloc зануляет матрицу C

    if (!a || !b || !c) {
        printf("Ошибка выделения памяти для N = %d!\n", N);
        free(a); free(b); free(c);
        return;
    }

    srand((unsigned int)time(NULL));

    // Заполнение случайными числами
    for (size_t i = 0; i < (size_t)N * N; i++) {
        a[i] = rand() % 100 + 1;
        b[i] = rand() % 100 + 1;
    }

    clock_t start = clock();

    // 2. Кэш-эффективный порядок циклов (i-r-j)
    for (int i = 0; i < N; i++) {
        for (int r = 0; r < N; r++) {
            int a_ir = a[i * N + r];
            for (int j = 0; j < N; j++) {
                c[i * N + j] += a_ir * b[r * N + j];
            }
        }
    }

    clock_t end = clock();
    double time_spent = (double)(end - start) / CLOCKS_PER_SEC;

    printf("Размер N = %5d | Время вычисления: %10.4f сек.\n", N, time_spent);

    free(a);
    free(b);
    free(c);
}

int main(void) {
    setlocale(LC_ALL, "rus");
    setvbuf(stdin, NULL, _IONBF, 0);
    setvbuf(stdout, NULL, _IONBF, 0);

    int sizes[] = {100, 200, 400, 1000, 2000, 4000, 10000 };
    int num_sizes = sizeof(sizes) / sizeof(sizes[0]);

    printf("=== Быстрый замер времени перемножения матриц ===\n");
    for (int i = 0; i < num_sizes; i++) {
        measure_matrix_multiply_fast(sizes[i]);
    }

    return 0;
}
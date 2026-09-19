#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <locale>

void measure_matrix_multiply(int N) {
    
    int** a = (int**)malloc(N * sizeof(int*));
    int** b = (int**)malloc(N * sizeof(int*));
    int** c = (int**)malloc(N * sizeof(int*));
    for (int i = 0; i < N; i++) {
        a[i] = (int*)malloc(N * sizeof(int));
        b[i] = (int*)malloc(N * sizeof(int));
        c[i] = (int*)malloc(N * sizeof(int));
    }

    srand((unsigned int)time(NULL));

    
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            a[i][j] = rand() % 100 + 1;
            b[i][j] = rand() % 100 + 1;
        }
    }

    
    clock_t start = clock();

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            int elem_c = 0;
            for (int r = 0; r < N; r++) {
                elem_c += a[i][r] * b[r][j];
            }
            c[i][j] = elem_c;
        }
    }

    clock_t end = clock();
    double time_spent = (double)(end - start) / CLOCKS_PER_SEC;

    printf("Размер N = %5d | Время вычисления: %10.4f сек.\n", N, time_spent);

    
    for (int i = 0; i < N; i++) {
        free(a[i]); free(b[i]); free(c[i]);
    }
    free(a); free(b); free(c);
}

int main2(void) {
    setlocale(LC_ALL, "rus");
    setvbuf(stdin, NULL, _IONBF, 0);
    setvbuf(stdout, NULL, _IONBF, 0);

    int sizes[] = { 100, 200, 400, 1000, 2000, 4000 };
    int num_sizes = sizeof(sizes) / sizeof(sizes[0]);

    printf("=== Замер времени перемножения матриц ===\n");
    for (int i = 0; i < num_sizes; i++) {
        measure_matrix_multiply(sizes[i]);
    }

    
    return 0;
}
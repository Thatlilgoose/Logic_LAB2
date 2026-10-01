#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>

void measure_matrix_multiply_fast(int N) {
   
    int* a = (int*)malloc((size_t)N * N * sizeof(int));
    int* b = (int*)malloc((size_t)N * N * sizeof(int));
    int* c = (int*)calloc((size_t)N * N, sizeof(int));

    if (!a || !b || !c) {
        printf("N = %d!\n", N);
        free(a); free(b); free(c);
        return;
    }

    srand((unsigned int)time(NULL));

   
    for (size_t i = 0; i < (size_t)N * N; i++) {
        a[i] = rand() % 100 + 1;
        b[i] = rand() % 100 + 1;
    }

    clock_t start = clock();

    
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

    printf("N = %5d %10.4f сек.\n", N, time_spent);

    free(a);
    free(b);
    free(c);
}

int main2(void) {
    setlocale(LC_ALL, "rus");
    setvbuf(stdin, NULL, _IONBF, 0);
    setvbuf(stdout, NULL, _IONBF, 0);

    int sizes[] = {100, 200, 400, 1000, 2000, 4000, 10000};
    int num_sizes = sizeof(sizes) / sizeof(sizes[0]);

    
    for (int i = 0; i < num_sizes; i++) {
        measure_matrix_multiply_fast(sizes[i]);
    }

    return 0;
}
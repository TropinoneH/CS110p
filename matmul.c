#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <emmintrin.h> /* header file for the SSE intrinsics */
#include <math.h>

#define MATRIX_SIZE 1024

void matmul_naive(const double *a, const double *b, double *c) {
    for (int i = 0; i < MATRIX_SIZE; i++) {
        for (int j = 0; j < MATRIX_SIZE; j++) {
            for (int k = 0; k < MATRIX_SIZE; k++) {
                c[i * MATRIX_SIZE + j] += a[i * MATRIX_SIZE + k] * b[k * MATRIX_SIZE + j];
            }
        }
    }
}

void matmul_optimized_slices(const double *a, const double *b, double *c) {
    int num_threads = omp_get_max_threads();
#pragma omp parallel
    {
        int tid = omp_get_thread_num();
        for (int i = tid; i < MATRIX_SIZE; i += num_threads) {
            for (int j = 0; j < MATRIX_SIZE; j++) {
                c[i * MATRIX_SIZE + j] = 0;
                for (int k = 0; k < MATRIX_SIZE; k++) {
                    c[i * MATRIX_SIZE + j] += a[i * MATRIX_SIZE + k] * b[k * MATRIX_SIZE + j];
                }
            }
        }
    }
}

void matmul_optimized_chunks(const double *a, const double *bT, double *c) {
    int num_threads = omp_get_max_threads();
    int block_size = MATRIX_SIZE / num_threads;
#pragma omp parallel
    {
        int thread_ID = omp_get_thread_num();
        int start = thread_ID * block_size;
        int end = (thread_ID == num_threads - 1) ? MATRIX_SIZE : start + block_size;

        for (int i = start; i < end; i++) {
            for (int j = 0; j < MATRIX_SIZE; j++) {
                __m128d tmp = _mm_setzero_pd();
                for (int k = 0; k < MATRIX_SIZE; k += 2) {
                    __m128d A0 = _mm_loadu_pd(&a[i * MATRIX_SIZE + k]);
                    __m128d B0 = _mm_loadu_pd(&bT[j * MATRIX_SIZE + k]);
                    __m128d C0 = _mm_mul_pd(A0, B0);
                    tmp = _mm_add_pd(tmp, C0);
                }
                c[i * MATRIX_SIZE + j] = tmp[0] + tmp[1];
            }
        }
    }
}

void check_correctness(char *msg, const double *c, const double *c1) {
    for (int i = 0; i < MATRIX_SIZE; ++i) {
        for (int j = 0; j < MATRIX_SIZE; ++j) {
            if (fabs(c[i * MATRIX_SIZE + j] - c1[i * MATRIX_SIZE + j]) > 1e-6) {
                printf("%d, %d; c=%f, c2=%f\n", i, j, c[i * MATRIX_SIZE + j], c1[i * MATRIX_SIZE + j]);
                printf("%s incorrect!\n", msg);
                return;
            }
        }
    }
}

int main() {
    double *a = (double *) malloc(MATRIX_SIZE * MATRIX_SIZE * sizeof(double));
    double *b = (double *) malloc(MATRIX_SIZE * MATRIX_SIZE * sizeof(double));
    double *c = (double *) calloc(MATRIX_SIZE * MATRIX_SIZE, sizeof(double));
    double *c1 = (double *) calloc(MATRIX_SIZE * MATRIX_SIZE, sizeof(double));
    double *c2 = (double *) calloc(MATRIX_SIZE * MATRIX_SIZE, sizeof(double));
    double *bT = (double *) malloc(MATRIX_SIZE * MATRIX_SIZE * sizeof(double));

    if (!a || !b || !c || !c1 || !c2) {
        printf("Error: could not allocate memory.\n");
        return 1;
    }

    for (int i = 0; i < MATRIX_SIZE; i++) {
        for (int j = 0; j < MATRIX_SIZE; j++) {
            a[i * MATRIX_SIZE + j] = (double) rand() / RAND_MAX;
            b[i * MATRIX_SIZE + j] = (double) rand() / RAND_MAX;
        }
    }

    for (int i = 0; i < MATRIX_SIZE; ++i)
        for (int j = 0; j < MATRIX_SIZE; ++j)
            bT[i * MATRIX_SIZE + j] = b[j * MATRIX_SIZE + i];

    double start_time = omp_get_wtime();
    matmul_naive(a, b, c);
    double end_time = omp_get_wtime();
    printf("Naive: %.5f seconds\n", end_time - start_time);

    start_time = omp_get_wtime();
    matmul_optimized_slices(a, b, c1);
    end_time = omp_get_wtime();
    check_correctness("slices", c, c1);
    printf("Optimized (slices): %.5f seconds\n", end_time - start_time);

    start_time = omp_get_wtime();
    matmul_optimized_chunks(a, bT, c2);
    end_time = omp_get_wtime();
    check_correctness("chunks", c, c2);
    printf("Optimized (chunks): %.5f seconds\n", end_time - start_time);

    free(a);
    free(b);
    free(c);
    free(c1);
    free(c2);
    free(bT);

    return 0;
}

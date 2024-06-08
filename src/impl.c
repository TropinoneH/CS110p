#include <memory.h>
#include <omp.h>
#include <emmintrin.h>
#include <immintrin.h>

void impl(int N, int step, double *p) {
    /* Your code here */
    double *p_next = calloc(N * N, sizeof(double));
    for (int k = 0; k < step / 2; k++) {
        for (int i = 1; i < N - 1; i++) {
            for (int j = 1; j < N - 1; j++) {
                p_next[i * N + j] = (p[(i - 1) * N + j] + p[(i + 1) * N + j] + p[i * N + j + 1] + p[i * N + j - 1]) / 4.0f;
            }
        }

        for (int i = 1; i < N - 1; i++) {
            for (int j = 1; j < N - 1; j++) {
                p[i * N + j] = (p_next[(i - 1) * N + j] + p_next[(i + 1) * N + j] + p_next[i * N + j + 1] + p_next[i * N + j - 1]) / 4.0f;
            }
        }
    }

    free(p_next);
}
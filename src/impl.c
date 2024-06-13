#include <emmintrin.h>
#include <immintrin.h>
#include <memory.h>
#include <omp.h>
#include <string.h>

void impl(int N, int step, double *p) {
    /* Your code here */
    double *temp;
    double *p_next = malloc(N * N * sizeof(double));
    memcpy(p_next, p, N * N * sizeof(double));

    int i, j, k;
    for (k = 0; k < step / 4; k++) {
        for (i = 4; i < N - 4; i++) {
            for (j = 4; j < N - 4; j++) {
                p_next[i * N + j] = (1.0 / 256) * (p[(i - 4) * N + (j)] + p[(i) *N + (j - 4)] + p[(i) *N + (j + 4)] + p[(i + 4) * N + (j)]) +
                                    (1.0 / 64) * (p[(i - 3) * N + (j - 1)] + p[(i - 3) * N + (j + 1)] + p[(i - 1) * N + (j - 3)] + p[(i - 1) * N + (j + 3)] +
                                                  p[(i + 1) * N + (j - 3)] + p[(i + 1) * N + (j + 3)] + p[(i + 3) * N + (j - 1)] + p[(i + 3) * N + (j + 1)]) +
                                    (3.0 / 128) * (p[(i - 2) * N + (j - 2)] + p[(i - 2) * N + (j + 2)] + p[(i + 2) * N + (j - 2)] + p[(i + 2) * N + (j + 2)]) +
                                    (1.0 / 16) * (p[(i - 2) * N + (j)] + p[(i) *N + (j - 2)] + p[(i) *N + (j + 2)] + p[(i + 2) * N + (j)]) +
                                    (3.0 / 32) * (p[(i - 1) * N + (j - 1)] + p[(i - 1) * N + (j + 1)] + p[(i + 1) * N + (j - 1)] + p[(i + 1) * N + (j + 1)]) +
                                    (9.0 / 64) * (p[(i) *N + (j)]);
            }
        }
        // corner 3
        // p_next[3 * N + 3] = (1.0/256)*(p[7*N+])

        temp = p;
        p = p_next;
        p_next = temp;
    }


    free(p_next);
}

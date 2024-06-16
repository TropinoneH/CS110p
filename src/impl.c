#include <immintrin.h>
#include <malloc.h>
#include <memory.h>
#include <omp.h>

void impl(int N, int step, double *p) {
    double *check_p = p;
    double *p_next = malloc(N * N * sizeof(double));
    memcpy(p_next, p, N * N * sizeof(double));
    if (step % 2 == 1) { step--; }

    // Set the number of threads to 14
    for (int k = 0; k < step; k += 2) {
#pragma omp parallel for
        for (int i = 2; i < N - 2; i++) {
            for (int j = 2; j < N - 2; j++) {
                p_next[i * N + j] = 0.0625 * (p[(i - 2) * N + j] + p[(i + 2) * N + j] + p[i * N + j - 2] + p[i * N + j + 2]) +
                                    0.125 * (p[(i - 1) * N + j - 1] + p[(i + 1) * N + j - 1] + p[(i - 1) * N + j + 1] + p[(i + 1) * N + j + 1]) +
                                    0.25 * p[i * N + j];
            }
        }
#pragma omp parallel for
        for (int i = 2; i < N - 2; i++) {
            p_next[N + i] = (p[N + i - 2] + p[N + i + 2] + p[3 * N + i] + p[i - 1] + p[i + 1]) / 16.0f + (p[2 * N + i - 1] + p[2 * N + i + 1]) / 8.0f +
                            p[i] / 4.0f + 3.0f * p[N + i] / 16.0f;
            p_next[N * i + 1] = (p[N * (i - 2) + 1] + p[N * (i + 2) + 1] + p[3 + N * i] + p[N * (i - 1)] + p[N * (i + 1)]) / 16.0f +
                                (p[2 + N * (i - 1)] + p[2 + N * (i + 1)]) / 8.0f + p[N * i] / 4.0f + 3.0f * p[N * i + 1] / 16.0f;
            p_next[N * (i + 1) - 2] = (p[N * (i - 2) + N - 2] + p[N * (i + 2) + N - 2] + p[N * i + N - 4] + p[N * i - 1] + p[N * i + 2 * N - 1]) / 16.0f +
                                      (p[N * i - 3] + p[2 * N - 3 + N * i]) / 8.0f + p[N * i + N - 1] / 4.0f + 3.0f * p[N * i + N - 2] / 16.0f;
            p_next[N * (N - 2) + i] =
                    (p[N * (N - 2) + i - 2] + p[N * (N - 2) + i + 2] + p[N * (N - 4) + i] + p[N * (N - 1) + i - 1] + p[N * (N - 1) + i + 1]) / 16.0f +
                    (p[i - 1 + N * (N - 3)] + p[i + 1 + N * (N - 3)]) / 8.0f + p[N * (N - 1) + i] / 4.0f + 3.0f * p[N * (N - 2) + i] / 16.0f;
        }
        p_next[N + 1] = (p[1] + p[N]) / 4.0f + (p[2 * N] + p[2] + p[N + 3] + p[3 * N + 1]) / 16.0f + (p[2 * N + 2] + p[N + 1]) / 8.0f;

        p_next[N * (N - 2) + 1] = (p[(N - 2) * N] + p[N * (N - 1) + 1]) / 4.0f +
                                  (p[N * (N - 3)] + p[N * (N - 4) + 1] + p[N * (N - 2) + 3] + p[N * (N - 1) + 2]) / 16.0f +
                                  (p[N * (N - 2) + 1] + p[N * (N - 3) + 2]) / 8.0f;
        p_next[2 * N - 2] =
                (p[N - 2] + p[2 * N - 1]) / 4.0f + (p[N - 3] + p[2 * N - 4] + p[4 * N - 2] + p[3 * N - 1]) / 16.0f + (p[2 * N - 2] + p[3 * N - 3]) / 8.0f;

        p_next[N * (N - 2) + N - 2] = (p[N * (N - 4) + N - 2] + p[N * (N - 3) + N - 1] + p[N * (N - 2) + N - 4] + p[N * (N - 1) + N - 3]) / 16.0f +
                                      (p[N * (N - 3) + N - 3] + p[N * (N - 2) + N - 2]) / 8.0f + (p[N * (N - 2) + N - 1] + p[N * (N - 1) + N - 2]) / 4.0f;

        double *temp = p;
        p = p_next;
        p_next = temp;
    }
    if (p != check_p) {
        memcpy(p_next, p, N * N * sizeof(double));
        double *temp = p;
        p = p_next;
        p_next = temp;
    }

    free(p_next);
}

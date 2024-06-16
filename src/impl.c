#include <immintrin.h>
#include <omp.h>
#include <memory.h>

void impl(int N, int step, double *p) {
    /* Your code here */
    double *temp;
    int half = (N - 1) / 2 + 2;
    double *odd = calloc(N * half, sizeof(double));
    double *odd_next = malloc(N * half * sizeof(double));

    int i, j, k;

    for (i = 0; i < N; i++) {
        for (j = 1; j < half; ++j) {
            odd[i * half + j] = p[i * N + 2 * j - (i & 1)];
        }
        odd[i * half] = p[i * N];
        odd[i * half + half - 1] = p[i * N + N - 1];
    }
    memcpy(odd_next, odd, N * half * sizeof(double));

    int stp = step / 2 - 1;
    for (k = 0; k < stp; ++k) {
#pragma omp parallel for
        for (i = 2; i < N - 2; ++i) {
            for (j = 1 + (i & 1); j < half - 2 + (i & 1); ++j) {
                odd_next[i * half + j] = 0.0625 * (odd[(i - 2) * half + j] + odd[i * half + j - 1] + odd[i * half + j + 1] + odd[(i + 2) * half + j]) +
                                         0.125 * (odd[(i - 1) * half + j - (i & 1)] + odd[(i - 1) * half + j + 1 - (i & 1)] +
                                                  odd[(i + 1) * half + j - (i & 1)] + odd[(i + 1) * half + j + 1 - (i & 1)]) +
                                         0.25 * odd[i * half + j];
            }
        }
        // edge
#pragma omp parallel for
        for (i = 2; i < N - 3; i += 2) {
            // same column, walk row
            // if N is odd, then rightmost column should walk by i += 2
            odd_next[(i + 1) * half + 1] = 0.0625 * (odd[(i - 1) * half + 1] + p[i * N] + odd[(i + 1) * half + 2] + p[(i + 2) * N] + odd[(i + 3) * half + 1]) +
                                           0.125 * (odd[i * half + 1] + odd[(i + 2) * half + 1]) + 0.1875 * (odd[(i + 1) * half + 1]) + 0.25 * p[(i + 1) * N];
            odd_next[i * half + half - 2] = 0.0625 *
                                            (odd[(i - 2) * half + half - 2] + p[(i - 1) * N + N - 1] + odd[i * half + half - 3] + p[(i + 1) * N + N - 1] +
                                             odd[(i + 2) * half + half - 2]) + 0.125 * (odd[(i - 1) * half + half - 2] + odd[(i + 1) * half + half - 2]) +
                                            0.1875 * odd[i * half + half - 2] + 0.25 * p[i * N + N - 1];
        }
#pragma omp parallel for
        for (j = 2; j < half - 1; ++j) {
            odd_next[half + j] = 0.25 * p[2 * j - 1] + 0.0625 * (p[(j - 1) * 2] + p[j * 2] + odd[half + j - 1] + odd[half + j + 1] + odd[3 * half + j]) +
                                 0.125 * (odd[2 * half + j - 1] + odd[2 * half + j]) + 0.1875 * odd[half + j];
            odd_next[(N - 2) * half + j - 1] = 0.0625 * (odd[(N - 4) * half + j - 1] + odd[(N - 2) * half + j - 2] + odd[(N - 2) * half + j] +
                                                         p[(N - 1) * N + (j - 2) * 2 - 1] + p[(N - 1) * N + 2 * j - 1]) +
                                               0.125 * (odd[(N - 3) * half + j - 1] + odd[(N - 3) * half + j]) + 0.1875 * odd[(N - 2) * half + j - 1] +
                                               0.25 * p[(N - 1) * N + 2 * (j - 1) - 1];
        }


        odd_next[half + 1] =
                0.0625 * (p[2] + odd[half + 3] + p[2 * N] + odd[3 * half + 1]) + 0.125 * (odd[half + 1] + odd[2 * half + 1]) + 0.25 * (p[1] + p[N]);
        // only for N is even
        odd_next[(N - 2) * half + half - 2] =
                0.0625 * (odd[(N - 4) * half + half - 2] + p[(N - 3) * N + N - 1] + odd[(N - 2) * half + half - 3] + p[(N - 1) * N + N - 3]) +
                0.125 * (odd[(N - 3) * half + half - 2] + odd[(N - 2) * half + half - 2]) + 0.25 * (p[(N - 2) * N + N - 1] + p[(N - 1) * N + N - 2]);
        // only for N is odd
//            odd_next[half + half - 2] = 0.0625 * (p[N - 3] + odd[half + half - 3] + p[2 * N + N - 1] + odd[3 * half + half - 2]) +
//                                        0.125 * (odd[half + half - 2] + odd[2 * half + half - 3]) + 0.25 * (p[N - 2] + p[N + N - 1]);
//            odd_next[(N - 2) * half + 1] = 0.0625 * (odd[(N - 4) * half + 1] + p[(N - 3) * N] + odd[(N - 2) * half + 2] + p[(N - 1) * N + 2]) +
//                                           0.125 * (odd[(N - 3) * half + 1] + odd[(N - 2) * half + 1]) + 0.25 * (p[(N - 2) * N] + p[(N - 1) * N + 1]);

        temp = odd;
        odd = odd_next;
        odd_next = temp;
    }

    if (stp % 2 == 0) {
        for (i = 1; i < N - 1; i++) {
            for (j = 1; j < half; ++j) {
                p[i * N + 2 * j - (i & 1)] = odd[i * half + j];
            }
        }
    } else {
        for (i = 1; i < N - 1; i++) {
            for (j = 1; j < half - 1; ++j) {
                p[i * N + 2 * j - (i & 1)] = odd_next[i * half + j];
            }
        }

        for (k = stp * 2; k < step + 2; ++k) {
#pragma omp parallel for
            for (i = 1; i < N - 1; ++i) {
                for (j = 1 + ((k & 1) ^ (i & 1)); j < N - 1; j += 2) {
                    p[i * N + j] = (p[(i - 1) * N + j] + p[i * N + j - 1] + p[i * N + j + 1] + p[(i + 1) * N + j]) * 0.25;
                }
            }
        }
    }

    free(odd);
    free(odd_next);
}

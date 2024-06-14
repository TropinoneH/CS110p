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
#pragma omp parallel for
        for (i = 4; i < N - 4; i++) {
            for (j = 4; j < N - 4; j++) {
                p_next[i * N + j] = (1.0 / 256) * (p[(i - 4) * N + j] + p[(i + 4) * N + j] + p[i * N + j - 4] + p[i * N + j + 4]) +
                                    (2.0 / 32) * (p[(i - 1) * N + j - 1] + p[(i - 1) * N + j + 1] + p[(i + 1) * N + j - 1] + p[(i + 1) * N + j + 1]) +
                                    (3.0 / 128) * (p[(i - 2) * N + j - 2] + p[(i - 2) * N + j + 2] + p[(i + 2) * N + j - 2] + p[(i + 2) * N + j + 2]) +
                                    (1.0 / 64) * (p[(i - 3) * N + j - 1] + p[(i - 3) * N + j + 1] + p[(i - 1) * N + j - 3] + p[(i - 1) * N + j + 3] +
                                                  p[(i + 1) * N + j - 3] + p[(i + 1) * N + j + 3] + p[(i + 3) * N + j - 1] + p[(i + 3) * N + j + 1]) +
                                    (1.0 / 16) * (p[(i - 2) * N + j] + p[i * N + j - 2] + p[i * N + j + 2] + p[(i + 2) * N + j]) + (9.0 / 64) * p[i * N + j];
            }
        }
        // 1, 1
        p_next[N + 1] = (9.0 / 32) * (p[(0) * N + (1)] + p[(1) * N + (0)]) + (21.0 / 256) * (p[(0) * N + (2)] + p[(2) * N + (0)]) +
                        (1.0 / 64) * (p[(0) * N + (3)] + p[(2) * N + (4)] + p[(3) * N + (0)] + p[(4) * N + (2)]) +
                        (1.0 / 256) * (p[(0) * N + (4)] + p[(1) * N + (5)] + p[(4) * N + (0)] + p[(5) * N + (1)]) + (5.0 / 128) * (p[(1) * N + (1)]) +
                        (9.0 / 256) * (p[(1) * N + (3)] + p[(3) * N + (1)]) + (1.0 / 16) * (p[(2) * N + (2)]) + (3.0 / 128) * (p[(3) * N + (3)]);
        p_next[N + 2] = (21.0 / 256) * (p[(0) * N + (1)] + p[(1) * N + (0)]) + (19.0 / 64) * (p[(0) * N + (2)]) + (11.0 / 128) * (p[(0) * N + (3)]) +
                        (1.0 / 64) * (p[(0) * N + (4)] + p[(2) * N + (5)] + p[(4) * N + (1)] + p[(4) * N + (3)]) +
                        (1.0 / 256) * (p[(0) * N + (5)] + p[(1) * N + (6)] + p[(5) * N + (2)]) + (19.0 / 256) * (p[(1) * N + (2)]) +
                        (5.0 / 128) * (p[(1) * N + (4)]) + (1.0 / 32) * (p[(2) * N + (0)]) + (1.0 / 16) * (p[(2) * N + (1)]) + (5.0 / 64) * (p[(2) * N + (3)]) +
                        (3.0 / 256) * (p[(3) * N + (0)]) + (15.0 / 256) * (p[(3) * N + (2)]) + (3.0 / 128) * (p[(3) * N + (4)]);
        p_next[N + 3] = (1.0 / 64) * (p[(0) * N + (1)] + p[(0) * N + (5)] + p[(1) * N + (0)] + p[(2) * N + (6)] + p[(4) * N + (2)] + p[(4) * N + (4)]) +
                        (11.0 / 128) * (p[(0) * N + (2)] + p[(0) * N + (4)]) + (19.0 / 64) * (p[(0) * N + (3)]) +
                        (1.0 / 256) * (p[(0) * N + (6)] + p[(1) * N + (7)] + p[(5) * N + (3)]) + (9.0 / 256) * (p[(1) * N + (1)]) +
                        (5.0 / 64) * (p[(1) * N + (3)] + p[(2) * N + (2)] + p[(2) * N + (4)]) + (5.0 / 128) * (p[(1) * N + (5)]) +
                        (3.0 / 256) * (p[(2) * N + (0)]) + (3.0 / 128) * (p[(3) * N + (1)] + p[(3) * N + (5)]) + (15.0 / 256) * (p[(3) * N + (3)]);
        p_next[N + N - 4] = (1 / 256) * (p[(1 - 1) * N + (N - 4 - 3)] + p[(1) * N + (N - 4 - 4)] + p[(1 + 4) * N + (N - 4)]) +
                            (1 / 64) * (p[(1 - 1) * N + (N - 4 - 2)] + p[(1 - 1) * N + (N - 4 + 2)] + p[(1) * N + (N - 4 + 3)] + p[(1 + 1) * N + (N - 4 - 3)] +
                                        p[(1 + 3) * N + (N - 4 - 1)] + p[(1 + 3) * N + (N - 4 + 1)]) +
                            (11 / 128) * (p[(1 - 1) * N + (N - 4 - 1)] + p[(1 - 1) * N + (N - 4 + 1)]) + (19 / 64) * (p[(1 - 1) * N + (N - 4)]) +
                            (5 / 128) * (p[(1) * N + (N - 4 - 2)]) +
                            (5 / 64) * (p[(1) * N + (N - 4)] + p[(1 + 1) * N + (N - 4 - 1)] + p[(1 + 1) * N + (N - 4 + 1)]) +
                            (9 / 256) * (p[(1) * N + (N - 4 + 2)]) + (3 / 256) * (p[(1 + 1) * N + (N - 4 + 3)]) +
                            (3 / 128) * (p[(1 + 2) * N + (N - 4 - 2)] + p[(1 + 2) * N + (N - 4 + 2)]) + (15 / 256) * (p[(1 + 2) * N + (N - 4)]);
        p_next[N + N - 3] =
                (1 / 256) * (p[(1 - 1) * N + (N - 3 - 3)] + p[(1) * N + (N - 3 - 4)] + p[(1 + 4) * N + (N - 3)]) +
                (1 / 64) * (p[(1 - 1) * N + (N - 3 - 2)] + p[(1 + 1) * N + (N - 3 - 3)] + p[(1 + 3) * N + (N - 3 - 1)] + p[(1 + 3) * N + (N - 3 + 1)]) +
                (11 / 128) * (p[(1 - 1) * N + (N - 3 - 1)]) + (19 / 64) * (p[(1 - 1) * N + (N - 3)]) +
                (21 / 256) * (p[(1 - 1) * N + (N - 3 + 1)] + p[(1) * N + (N - 3 + 2)]) + (5 / 128) * (p[(1) * N + (N - 3 - 2)]) +
                (19 / 256) * (p[(1) * N + (N - 3)]) + (5 / 64) * (p[(1 + 1) * N + (N - 3 - 1)]) + (1 / 16) * (p[(1 + 1) * N + (N - 3 + 1)]) +
                (1 / 32) * (p[(1 + 1) * N + (N - 3 + 2)]) + (3 / 128) * (p[(1 + 2) * N + (N - 3 - 2)]) + (15 / 256) * (p[(1 + 2) * N + (N - 3)]) +
                (3 / 256) * (p[(1 + 2) * N + (N - 3 + 2)]);
        p_next[N + N - 2] =
                (1 / 256) * (p[(1 - 1) * N + (N - 2 - 3)] + p[(1) * N + (N - 2 - 4)] + p[(1 + 3) * N + (N - 2 + 1)] + p[(1 + 4) * N + (N - 2)]) +
                (1 / 64) * (p[(1 - 1) * N + (N - 2 - 2)] + p[(1 + 1) * N + (N - 2 - 3)] + p[(1 + 2) * N + (N - 2 + 1)] + p[(1 + 3) * N + (N - 2 - 1)]) +
                (21 / 256) * (p[(1 - 1) * N + (N - 2 - 1)] + p[(1 + 1) * N + (N - 2 + 1)]) + (9 / 32) * (p[(1 - 1) * N + (N - 2)] + p[(1) * N + (N - 2 + 1)]) +
                (9 / 256) * (p[(1) * N + (N - 2 - 2)] + p[(1 + 2) * N + (N - 2)]) + (5 / 128) * (p[(1) * N + (N - 2)]) +
                (1 / 16) * (p[(1 + 1) * N + (N - 2 - 1)]) + (3 / 128) * (p[(1 + 2) * N + (N - 2 - 2)]);

        // corner 3
        p_next[3 * N + 3] = (1.0 / 256) * (p[7 * N + 3] + p[3 * N + 7]) +
                            (1.0 / 64) * (p[3] + p[2 * N + 6] + p[3 * N] + p[4 * N + 6] + p[6 * N + 2] + p[6 * N + 4]) +
                            (3.0 / 32) * (p[2 * N + 2] + p[2 * N + 4] + p[4 * N + 2] + p[4 * N + 4]) + (3.0 / 256) * (p[4 * N] + p[2 * N] + p[2] + p[4]) +
                            (15.0 / 256) * (p[3 * N + 1] + p[N + 3]) + (3.0 / 128) * (p[N + 1] + p[N + 5] + p[5 * N + 1] + p[5 * N + 5]) +
                            (1.0 / 16) * (p[5 * N + 3] + p[3 * N + 5]) + (9.0 / 64) * p[3 * N + 3];
        p_next[3 * N + N - 4] = (1.0 / 256) * (p[7 * N + N - 4] + p[3 * N + N - 8]) +
                                (1.0 / 64) * (p[6 * N + N - 3] + p[6 * N + N - 5] + p[4 * N + N - 7] + p[3 * N + N - 1] + p[3 * N + N - 7] + p[N - 4]) +
                                (3.0 / 32) * (p[2 * N + N - 3] + p[2 * N + N - 5] + p[(N - 3) * N + 4] + p[(N - 5) * N + 4]) +
                                (3.0 / 256) * (p[N - 3] + p[N - 5] + p[2 * N + N - 1] + p[4 * N + N - 1]) +
                                (15.0 / 256) * (p[(N - 4) * N + 1] + p[(N - 2) * N + 3]) +
                                (3.0 / 128) * (p[(N - 2) * N + 5] + p[(N - 6) * N + 5] + p[(N - 2) * N + 1] + p[(N - 6) * N + 1]) +
                                (1.0 / 16) * (p[(N - 4) * N + 5] + p[(N - 6) * N + 3]) + (9.0 / 64) * p[(N - 4) * N + 3];
        p_next[(N - 4) * N + 3] =
                (1.0 / 256) * (p[(N - 4) * N + 7] + p[(N - 8) * N + 3]) +
                (1.0 / 64) * (p[(N - 3) * N + 6] + p[(N - 5) * N + 6] + p[(N - 7) * N + 4] + p[(N - 1) * N + 3] + p[(N - 7) * N + 3] + p[(N - 4) * N]) +
                (3.0 / 32) * (p[(N - 3) * N + 2] + p[(N - 5) * N + 2] + p[4 * N + N - 3] + p[4 * N + N - 5]) +
                (3.0 / 256) * (p[(N - 3) * N] + p[(N - 5) * N] + p[(N - 1) * N + 2] + p[(N - 1) * N + 4]) + (15.0 / 256) * (p[N + N - 4] + p[3 * N + N - 2]) +
                (3.0 / 128) * (p[5 * N + N - 2] + p[5 * N + N - 6] + p[N + N - 2] + p[N + N - 6]) + (1.0 / 16) * (p[5 * N + N - 4] + p[3 * N + N - 6]) +
                (9.0 / 64) * p[3 * N + N - 4];
        p_next[(N - 4) * N + N - 4] = (1.0 / 256) * (p[(N - 8) * N + N - 4] + p[(N - 4) * N + N - 8]) +
                                      (1.0 / 64) * (p[(N - 7) * N + N - 3] + p[(N - 7) * N + N - 5] + p[(N - 5) * N + N - 7] + p[(N - 3) * N + N - 7] +
                                                    p[(N - 4) * N + N - 1] + p[(N - 1) * N + N - 4]) +
                                      (3.0 / 32) * (p[(N - 3) * N + N - 3] + p[(N - 3) * N + N - 5] + p[(N - 5) * N + N - 3] + p[(N - 5) * N + N - 3]) +
                                      (3.0 / 256) * (p[(N - 5) * N + N - 1] + p[(N - 3) * N + N - 1] + p[(N - 1) * N + N - 3] + p[(N - 1) * N + N - 5]) +
                                      (15.0 / 256) * (p[(N - 4) * N + N - 2] + p[(N - 2) * N + N - 4]) +
                                      (3.0 / 128) * (p[(N - 6) * N + N - 2] + p[(N - 6) * N + N - 6] + p[(N - 2) * N + N - 6] + p[(N - 6) * N + N - 2]) +
                                      (1.0 / 16) * (p[(N - 6) * N + N - 4] + p[(N - 4) * N + N - 6]) + (9.0 / 64) * p[(N - 4) * N + N - 4];

        // edge
        for (j = 4; j < N - 4; ++j) {
            p_next[3 * N + j] = (3.0 / 256) * (p[(3 - 3) * N + (j - 1)] + p[(3 - 3) * N + (j + 1)]) +
                                (1.0 / 64) * (p[(3 - 3) * N + (j)] + p[(3 - 1) * N + (j - 3)] + p[(3 - 1) * N + (j + 3)] + p[(3 + 1) * N + (j - 3)] +
                                              p[(3 + 1) * N + (j + 3)] + p[(3 + 3) * N + (j - 1)] + p[(3 + 3) * N + (j + 1)]) +
                                (3.0 / 128) * (p[(3 - 2) * N + (j - 2)] + p[(3 - 2) * N + (j + 2)] + p[(3 + 2) * N + (j - 2)] + p[(3 + 2) * N + (j + 2)]) +
                                (1.0 / 16) * (p[(3 - 2) * N + (j)] + p[(3) * N + (j - 2)] + p[(3) * N + (j + 2)]) +
                                (3.0 / 32) * (p[(3 - 1) * N + (j - 1)] + p[(3 - 1) * N + (j + 1)] + p[(3 + 1) * N + (j - 1)] + p[(3 + 1) * N + (j + 1)]) +
                                (1.0 / 256) * (p[(3) * N + (j - 4)] + p[(3) * N + (j + 4)] + p[(3 + 4) * N + (j)]) + (9.0 / 64) * (p[(3) * N + (j)]) +
                                (15.0 / 256) * (p[(3 + 2) * N + (j)]);
            p_next[(N - 4) * N + j] =
                    (1.0 / 256) * (p[(N - 4 - 4) * N + (j)] + p[(N - 4) * N + (j - 4)] + p[(N - 4) * N + (j + 4)]) +
                    (1.0 / 64) * (p[(N - 4 - 3) * N + (j - 1)] + p[(N - 4 - 3) * N + (j + 1)] + p[(N - 4 - 1) * N + (j - 3)] + p[(N - 4 - 1) * N + (j + 3)] +
                                  p[(N - 4 + 1) * N + (j - 3)] + p[(N - 4 + 1) * N + (j + 3)] + p[(N - 4 + 3) * N + (j)]) +
                    (3.0 / 128) * (p[(N - 4 - 2) * N + (j - 2)] + p[(N - 4 - 2) * N + (j + 2)] + p[(N - 4 + 2) * N + (j - 2)] + p[(N - 4 + 2) * N + (j + 2)]) +
                    (1.0 / 16) * (p[(N - 4 - 2) * N + (j)] + p[(N - 4) * N + (j - 2)] + p[(N - 4) * N + (j + 2)]) +
                    (3.0 / 32) * (p[(N - 4 - 1) * N + (j - 1)] + p[(N - 4 - 1) * N + (j + 1)] + p[(N - 4 + 1) * N + (j - 1)] + p[(N - 4 + 1) * N + (j + 1)]) +
                    (9.0 / 64) * (p[(N - 4) * N + (j)]) + (15.0 / 256) * (p[(N - 4 + 2) * N + (j)]) +
                    (3.0 / 256) * (p[(N - 4 + 3) * N + (j - 1)] + p[(N - 4 + 3) * N + (j + 1)]);

            // i = 2
            p_next[2 * N + j] = (3.0 / 256) * (p[(2 - 2) * N + (j - 2)] + p[(2 - 2) * N + (j + 2)]) + (1.0 / 32) * (p[(2 - 2) * N + (j - 1)]) +
                                (3.0 / 32) * (p[(2 - 2) * N + (j)] + p[(2 + 1) * N + (j - 1)] + p[(2 + 1) * N + (j + 1)]) +
                                (1.0 / 64) * (p[(2 - 1) * N + (j - 3)] + p[(2 - 1) * N + (j + 3)] + p[(2 + 1) * N + (j - 3)] + p[(2 + 1) * N + (j + 3)] +
                                              p[(2 + 3) * N + (j - 1)] + p[(2 + 3) * N + (j + 1)]) +
                                (5.0 / 64) * (p[(2 - 1) * N + (j - 1)] + p[(2 - 1) * N + (j + 1)]) +
                                (1.0 / 256) * (p[(2) * N + (j - 4)] + p[(2) * N + (j + 4)] + p[(2 + 4) * N + (j)]) +
                                (1.0 / 16) * (p[(2) * N + (j - 2)] + p[(2) * N + (j + 2)]) + (35.0 / 256) * (p[(2) * N + (j)]) +
                                (3.0 / 128) * (p[(2 + 2) * N + (j - 2)] + p[(2 + 2) * N + (j + 2)]) + (15.0 / 256) * (p[(2 + 2) * N + (j)]);
            p_next[(N - 3) * N + j] = (1.0 / 256) * (p[(N - 3 - 4) * N + (j)] + p[(N - 3) * N + (j - 4)] + p[(N - 3) * N + (j + 4)]) +
                                      (1.0 / 64) * (p[(N - 3 - 3) * N + (j - 1)] + p[(N - 3 - 3) * N + (j + 1)] + p[(N - 3 - 1) * N + (j - 3)] +
                                                    p[(N - 3 - 1) * N + (j + 3)] + p[(N - 3 + 1) * N + (j - 3)] + p[(N - 3 + 1) * N + (j + 3)]) +
                                      (3.0 / 128) * (p[(N - 3 - 2) * N + (j - 2)] + p[(N - 3 - 2) * N + (j + 2)]) + (15.0 / 256) * (p[(N - 3 - 2) * N + (j)]) +
                                      (5.0 / 64) * (p[(N - 3 - 1) * N + (j - 1)] + p[(N - 3 - 1) * N + (j + 1)]) +
                                      (1.0 / 16) * (p[(N - 3) * N + (j - 2)] + p[(N - 3) * N + (j + 2)]) + (35.0 / 256) * (p[(N - 3) * N + (j)]) +
                                      (3.0 / 32) * (p[(N - 3 + 1) * N + (j - 1)] + p[(N - 3 + 1) * N + (j + 1)] + p[(N - 3 + 2) * N + (j)]) +
                                      (3.0 / 256) * (p[(N - 3 + 2) * N + (j - 2)] + p[(N - 3 + 2) * N + (j + 2)]) + (1.0 / 32) * (p[(N - 3 + 2) * N + (j - 1)]);

            // i = 1
            p_next[N + j] =
                    (1.0 / 256) * (p[(1 - 1) * N + (j - 3)] + p[(1 - 1) * N + (j + 3)] + p[(1) * N + (j - 4)] + p[(1) * N + (j + 4)] + p[(1 + 4) * N + (j)]) +
                    (1.0 / 64) * (p[(1 - 1) * N + (j - 2)] + p[(1 - 1) * N + (j + 2)] + p[(1 + 1) * N + (j - 3)] + p[(1 + 1) * N + (j + 3)] +
                                  p[(1 + 3) * N + (j - 1)] + p[(1 + 3) * N + (j + 1)]) +
                    (11.0 / 128) * (p[(1 - 1) * N + (j - 1)] + p[(1 - 1) * N + (j + 1)]) + (19.0 / 64) * (p[(1 - 1) * N + (j)]) +
                    (1.0 / 16) * (p[(1) * N + (j - 2)] + p[(1) * N + (j + 2)]) + (35.0 / 256) * (p[(1) * N + (j)]) +
                    (5.0 / 64) * (p[(1 + 1) * N + (j - 1)] + p[(1 + 1) * N + (j + 1)]) + (3.0 / 128) * (p[(1 + 2) * N + (j - 2)] + p[(1 + 2) * N + (j + 2)]) +
                    (15.0 / 256) * (p[(1 + 2) * N + (j)]);
            p_next[(N - 2) * N + j] = (1.0 / 256) * (p[(N - 2 - 4) * N + (j)] + p[(N - 2) * N + (j - 4)] + p[(N - 2) * N + (j + 4)] +
                                                     p[(N - 2 + 1) * N + (j - 3)] + p[(N - 2 + 1) * N + (j + 3)]) +
                                      (1.0 / 64) * (p[(N - 2 - 3) * N + (j - 1)] + p[(N - 2 - 3) * N + (j + 1)] + p[(N - 2 - 1) * N + (j - 3)] +
                                                    p[(N - 2 - 1) * N + (j + 3)] + p[(N - 2 + 1) * N + (j - 2)] + p[(N - 2 + 1) * N + (j + 2)]) +
                                      (3.0 / 128) * (p[(N - 2 - 2) * N + (j - 2)] + p[(N - 2 - 2) * N + (j + 2)]) + (15.0 / 256) * (p[(N - 2 - 2) * N + (j)]) +
                                      (5.0 / 64) * (p[(N - 2 - 1) * N + (j - 1)] + p[(N - 2 - 1) * N + (j + 1)]) +
                                      (1.0 / 16) * (p[(N - 2) * N + (j - 2)] + p[(N - 2) * N + (j + 2)]) + (35.0 / 256) * (p[(N - 2) * N + (j)]) +
                                      (11.0 / 128) * (p[(N - 2 + 1) * N + (j - 1)] + p[(N - 2 + 1) * N + (j + 1)]) + (19.0 / 64) * (p[(N - 2 + 1) * N + (j)]);
        }
        for (i = 4; i < N - 4; ++i) {
            p_next[i * N + 3] = (1.0 / 256) * (p[(i - 4) * N + (3)] + p[(i) *N + (3 + 4)] + p[(i + 4) * N + (3)]) +
                                (1.0 / 64) * (p[(i - 3) * N + (3 - 1)] + p[(i - 3) * N + (3 + 1)] + p[(i - 1) * N + (3 + 3)] + p[(i) *N + (3 - 3)] +
                                              p[(i + 1) * N + (3 + 3)] + p[(i + 3) * N + (3 - 1)] + p[(i + 3) * N + (3 + 1)]) +
                                (3.0 / 128) * (p[(i - 2) * N + (3 - 2)] + p[(i - 2) * N + (3 + 2)] + p[(i + 2) * N + (3 - 2)] + p[(i + 2) * N + (3 + 2)]) +
                                (1.0 / 16) * (p[(i - 2) * N + (3)] + p[(i) *N + (3 - 2)] + p[(i + 2) * N + (3)]) +
                                (3.0 / 256) * (p[(i - 1) * N + (3 - 3)] + p[(i + 1) * N + (3 - 3)]) +
                                (3.0 / 32) * (p[(i - 1) * N + (3 - 1)] + p[(i - 1) * N + (3 + 1)] + p[(i + 1) * N + (3 - 1)] + p[(i + 1) * N + (3 + 1)]) +
                                (9.0 / 64) * (p[(i) *N + (3)]) + (15.0 / 256) * (p[(i) *N + (3 + 2)]);
            p_next[i * N + N - 4] =
                    (1.0 / 256) * (p[(i - 4) * N + (N - 4)] + p[(i) *N + (N - 4 - 4)] + p[(i + 4) * N + (N - 4)]) +
                    (1.0 / 64) * (p[(i - 3) * N + (N - 4 - 1)] + p[(i - 3) * N + (N - 4 + 1)] + p[(i - 1) * N + (N - 4 - 3)] + p[(i) *N + (N - 4 + 3)] +
                                  p[(i + 1) * N + (N - 4 - 3)] + p[(i + 3) * N + (N - 4 - 1)] + p[(i + 3) * N + (N - 4 + 1)]) +
                    (3.0 / 128) * (p[(i - 2) * N + (N - 4 - 2)] + p[(i - 2) * N + (N - 4 + 2)] + p[(i + 2) * N + (N - 4 - 2)] + p[(i + 2) * N + (N - 4 + 2)]) +
                    (1.0 / 16) * (p[(i - 2) * N + (N - 4)] + p[(i) *N + (N - 4 + 2)] + p[(i + 2) * N + (N - 4)]) +
                    (3.0 / 32) * (p[(i - 1) * N + (N - 4 - 1)] + p[(i - 1) * N + (N - 4 + 1)] + p[(i + 1) * N + (N - 4 - 1)] + p[(i + 1) * N + (N - 4 + 1)]) +
                    (3.0 / 256) * (p[(i - 1) * N + (N - 4 + 3)] + p[(i + 1) * N + (N - 4 + 3)]) + (15.0 / 256) * (p[(i) *N + (N - 4 - 2)]) +
                    (9.0 / 64) * (p[(i) *N + (N - 4)]);

            // j = 2
            p_next[i * N + 2] = (1.0 / 256) * (p[(i - 4) * N + (2)] + p[(i) *N + (2 + 4)] + p[(i + 4) * N + (2)]) +
                                (1.0 / 64) * (p[(i - 3) * N + (2 - 1)] + p[(i - 3) * N + (2 + 1)] + p[(i - 1) * N + (2 + 3)] + p[(i + 1) * N + (2 + 3)] +
                                              p[(i + 3) * N + (2 - 1)] + p[(i + 3) * N + (2 + 1)]) +
                                (3.0 / 256) * (p[(i - 2) * N + (2 - 2)] + p[(i + 2) * N + (2 - 2)]) +
                                (1.0 / 16) * (p[(i - 2) * N + (2)] + p[(i + 2) * N + (2)]) +
                                (3.0 / 128) * (p[(i - 2) * N + (2 + 2)] + p[(i + 2) * N + (2 + 2)]) + (1.0 / 32) * (p[(i - 1) * N + (2 - 2)]) +
                                (5.0 / 64) * (p[(i - 1) * N + (2 - 1)] + p[(i + 1) * N + (2 - 1)]) +
                                (3.0 / 32) * (p[(i - 1) * N + (2 + 1)] + p[(i) *N + (2 - 2)] + p[(i + 1) * N + (2 + 1)]) + (35.0 / 256) * (p[(i) *N + (2)]) +
                                (15.0 / 256) * (p[(i) *N + (2 + 2)]);
            p_next[i * N + N - 3] = (1.0 / 256) * (p[(i - 4) * N + (N - 3)] + p[(i) *N + (N - 3 - 4)] + p[(i + 4) * N + (N - 3)]) +
                                    (1.0 / 64) * (p[(i - 3) * N + (N - 3 - 1)] + p[(i - 3) * N + (N - 3 + 1)] + p[(i - 1) * N + (N - 3 - 3)] +
                                                  p[(i + 1) * N + (N - 3 - 3)] + p[(i + 3) * N + (N - 3 - 1)] + p[(i + 3) * N + (N - 3 + 1)]) +
                                    (3.0 / 128) * (p[(i - 2) * N + (N - 3 - 2)] + p[(i + 2) * N + (N - 3 - 2)]) +
                                    (1.0 / 16) * (p[(i - 2) * N + (N - 3)] + p[(i + 2) * N + (N - 3)]) +
                                    (3.0 / 256) * (p[(i - 2) * N + (N - 3 + 2)] + p[(i + 2) * N + (N - 3 + 2)]) +
                                    (5.0 / 64) * (p[(i - 1) * N + (N - 3 - 1)] + p[(i + 1) * N + (N - 3 - 1)]) +
                                    (3.0 / 32) * (p[(i - 1) * N + (N - 3 + 1)] + p[(i) *N + (N - 3 + 2)] + p[(i + 1) * N + (N - 3 + 1)]) +
                                    (1.0 / 32) * (p[(i - 1) * N + (N - 3 + 2)]) + (15.0 / 256) * (p[(i) *N + (N - 3 - 2)]) +
                                    (35.0 / 256) * (p[(i) *N + (N - 3)]);

            // j = 1
            p_next[i * N + 1] =
                    (1.0 / 256) * (p[(i - 4) * N + (1)] + p[(i - 3) * N + (1 - 1)] + p[(i) *N + (1 + 4)] + p[(i + 3) * N + (1 - 1)] + p[(i + 4) * N + (1)]) +
                    (1.0 / 64) * (p[(i - 3) * N + (1 + 1)] + p[(i - 2) * N + (1 - 1)] + p[(i - 1) * N + (1 + 3)] + p[(i + 1) * N + (1 + 3)] +
                                  p[(i + 2) * N + (1 - 1)] + p[(i + 3) * N + (1 + 1)]) +
                    (1.0 / 16) * (p[(i - 2) * N + (1)] + p[(i + 2) * N + (1)]) + (3.0 / 128) * (p[(i - 2) * N + (1 + 2)] + p[(i + 2) * N + (1 + 2)]) +
                    (11.0 / 128) * (p[(i - 1) * N + (1 - 1)] + p[(i + 1) * N + (1 - 1)]) + (5.0 / 64) * (p[(i - 1) * N + (1 + 1)] + p[(i + 1) * N + (1 + 1)]) +
                    (19.0 / 64) * (p[(i) *N + (1 - 1)]) + (35.0 / 256) * (p[(i) *N + (1)]) + (15.0 / 256) * (p[(i) *N + (1 + 2)]);
            p_next[i * N + N - 2] = (1.0 / 256) * (p[(i - 4) * N + (N - 2)] + p[(i - 3) * N + (N - 2 + 1)] + p[(i) *N + (N - 2 - 4)] +
                                                   p[(i + 3) * N + (N - 2 + 1)] + p[(i + 4) * N + (N - 2)]) +
                                    (1.0 / 64) * (p[(i - 3) * N + (N - 2 - 1)] + p[(i - 2) * N + (N - 2 + 1)] + p[(i - 1) * N + (N - 2 - 3)] +
                                                  p[(i + 1) * N + (N - 2 - 3)] + p[(i + 2) * N + (N - 2 + 1)] + p[(i + 3) * N + (N - 2 - 1)]) +
                                    (3.0 / 128) * (p[(i - 2) * N + (N - 2 - 2)] + p[(i + 2) * N + (N - 2 - 2)]) +
                                    (1.0 / 16) * (p[(i - 2) * N + (N - 2)] + p[(i + 2) * N + (N - 2)]) +
                                    (5.0 / 64) * (p[(i - 1) * N + (N - 2 - 1)] + p[(i + 1) * N + (N - 2 - 1)]) +
                                    (11.0 / 128) * (p[(i - 1) * N + (N - 2 + 1)] + p[(i + 1) * N + (N - 2 + 1)]) + (15.0 / 256) * (p[(i) *N + (N - 2 - 2)]) +
                                    (35.0 / 256) * (p[(i) *N + (N - 2)]) + (19.0 / 64) * (p[(i) *N + (N - 2 + 1)]);
        }

        temp = p;
        p = p_next;
        p_next = temp;
    }


    free(p_next);
}

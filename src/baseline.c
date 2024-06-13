#include <omp.h>

void baseline(int N, int step, double *p, double *p_next) {
    for (int k = 0; k < step; k++) {
#pragma omp parallel for
        for (int i = 4; i < N - 4; i++) {
            for (int j = 4; j < N - 4; j++) {
                p_next[i * N + j] = (p[(i - 1) * N + j] + p[(i + 1) * N + j] + p[i * N + j + 1] + p[i * N + j - 1]) / 4.0f;
            }
        }
        double *temp = p;
        p = p_next;
        p_next = temp;
    }
}

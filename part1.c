#include <emmintrin.h> /* header file for the SSE intrinsics */
#include <assert.h>

int **a;
int **b;
int **c;

void naive_add(void) {
    for (int i = 0; i < 1000; ++i) {
        for (int j = 0; j < 40; ++j) {
            c[i][j] = a[i][j] + b[i][j];
        }
    }
}

void simd_add(void) {
    // TODO: implement me!
    for (int i = 0; i < 1000; ++i) {
        for (int j = 0; j < 40; j += 4) {
            // Load 4 integers from each matrix a and b
            __m128i vec_a = _mm_loadu_si128((__m128i*)&a[i][j]);
            __m128i vec_b = _mm_loadu_si128((__m128i*)&b[i][j]);

            // Perform vector addition
            __m128i vec_c = _mm_add_epi32(vec_a, vec_b);

            // Store the result back into matrix c
            _mm_storeu_si128((__m128i*)&c[i][j], vec_c);
        }
    }
}

int main(void) {
    a = malloc(1000 * sizeof(int *));
    b = malloc(1000 * sizeof(int *));
    c = malloc(1000 * sizeof(int *));
    for (int i = 0; i < 1000; ++i) {
        a[i] = malloc(40 * sizeof(int));
        b[i] = malloc(40 * sizeof(int));
        c[i] = malloc(40 * sizeof(int));
    }

    for (int i = 0; i < 1000; ++i) {
        for (int j = 0; j < 40; ++j) {
            a[i][j] = i * 40 + j;
            b[i][j] = 2 * (i * 40 - j);
        }
    }

    simd_add();

    for (int i = 0; i < 1000; ++i) {
        for (int j = 0; j < 40; ++j) {
            assert(c[i][j] == (i * 40 + j + 2 * (i * 40 - j)));
        }
    }
    return 0;
}

#include "FloatCalculate.h"
#include <assert.h>
#include <fenv.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

float random_float(void) {
    static const float min = 1e-39f;
    static const float max = 1e38f;
    float scale = (float) rand() / (float) RAND_MAX;
    float result = min + scale * (max - min);

    int sign = rand() % 2;
    return sign == 0 ? result : -result;
}

void float2bitstring(float f, char *bitstring) {
    uint32_t intRepresentation;
    memcpy(&intRepresentation, &f, sizeof(float));

    for (int i = 31; i >= 0; --i) {
        bitstring[31 - i] = (intRepresentation & (1u << i)) ? '1' : '0';
    }
    bitstring[32] = '\0';
}

int main(void) {
    // This is for your test, you should never call this function in your
    // submissions.
    fesetround(FE_TOWARDZERO);
    // Note that valgrind does not support fesetround,
    // so test will report incorrect if you are using valgrind.

    //    srand(0x5eed);

    int count = 10000000;
    while (count--) {
        char a[33], b[33];
        char result[33] = {0};
        float fa = random_float(), fb = random_float();
//        float fa = 1.1754944E-38f, fb = -1.1754945E-38f;
//        float fa = -4.77396912e+37f, fb = -2.77774648e+37f;
        float2bitstring(fa, a);
        float2bitstring(fb, b);
        float_add(a, b, result);
        char solution[33];
        float fsolution = fa + fb;
        float2bitstring(fsolution, solution);
        if (memcmp(result, solution, 32) != 0) {
            printf("-------------------------------------count:%d\n", count);
            printf("a:        %s\n", a);
            printf("b:        %s\n", b);
            printf("result:   %s\n", result);
            printf("solution: %s\n", solution);
            printf("------------------------------------------\n");
            fflush(stdout);
            assert(0);
        }
    }

    //    char a[33] = "00000000100000000000000000000001", b[33] =
    //    "10000000011111111111111111111111"; char a[33] =
    //    "01111111000000000011111111100001", b[33] =
    //    "01111111011111111111111111111111"; char a[33] =
    //    "00000000000000000000000000000000", b[33] =
    //    "00000000000000000000000000000000";
    // char a[33] = "11111101100011111010100101010100", b[33] =
    // "11111110001001110010110111110111"; char solution[33]; float_add(a, b,
    // solution); printf("%s\n", solution);

    return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "FloatCalculate.h"

const size_t SIGN_BIT = 1;
const size_t EXPONENT_BITS = 8;
const size_t MANTISSA_BITS = 23;

static void build_bitstring(Float input, char *output) {
    output[0] = input.sign == 1 ? '1' : '0';
    if (input.type == INFINITY_T) {
        for (size_t i = 0; i < EXPONENT_BITS; ++i) {
            output[i + 1] = '1';
        }
        for (size_t i = 0; i < MANTISSA_BITS; ++i) {
            output[i + 1 + EXPONENT_BITS] = '0';
        }
        output[32] = '\0';
        return;
    } else if (input.type == NAN_T) {
        for (size_t i = 0; i < EXPONENT_BITS; ++i) {
            output[i + 1] = '1';
        }
        for (size_t i = 0; i < MANTISSA_BITS; ++i) {
            output[i + 1 + EXPONENT_BITS] = (i == 0) ? '1' : '0';
        }
        output[32] = '\0';
        return;
    } else if (input.type == ZERO_T) {
        for (size_t i = 0; i < EXPONENT_BITS + MANTISSA_BITS; ++i) {
            output[i + 1] = '0';
        }
        output[32] = '\0';
        return;
    } else if (input.type == DENORMALIZED_T) {
        for (size_t i = 0; i < EXPONENT_BITS; ++i) {
            output[i + 1] = '0';
        }
        for (size_t i = 0; i < MANTISSA_BITS; ++i) {
            output[i + 1 + EXPONENT_BITS] = (input.mantissa & (1u << (MANTISSA_BITS - 1 - i))) ? '1' : '0';
        }
        output[32] = '\0';
        return;
    } else {
        for (size_t i = 0; i < EXPONENT_BITS; ++i) {
            output[i + 1] = (input.exponent & (1u << (EXPONENT_BITS - 1 - i))) ? '1' : '0';
        }
        for (size_t i = 0; i < MANTISSA_BITS; ++i) {
            output[i + 1 + EXPONENT_BITS] = (input.mantissa & (1u << (MANTISSA_BITS - 1 - i))) ? '1' : '0';
        }
        output[32] = '\0';
        return;
    }
}

static bool test_rightmost_all_zeros(uint32_t number, size_t bits) {
    uint32_t mask = (1ull << bits) - 1;
    return (number & mask) == 0;
}

static bool test_rightmost_all_ones(uint32_t number, size_t bits) {
    uint32_t mask = (1ull << bits) - 1;
    return (number & mask) == mask;
}

static Float parse_bitstring(const char *input) {
    Float f_input;
    f_input.sign = input[0] == '1' ? 1 : 0;

    char exp_char[9];
    strncpy(exp_char, input + SIGN_BIT, EXPONENT_BITS);
    exp_char[8] = '\0';
    f_input.exponent = (uint32_t) strtol(exp_char, NULL, 2);

    char man_char[24];
    strncpy(man_char, input + SIGN_BIT + EXPONENT_BITS, MANTISSA_BITS);
    man_char[23] = '\0';
    f_input.mantissa = (uint32_t) strtol(man_char, NULL, 2);

    if (test_rightmost_all_ones(f_input.exponent, EXPONENT_BITS) &&
        test_rightmost_all_zeros(f_input.mantissa, MANTISSA_BITS)) {
        f_input.type = INFINITY_T;
    } else if (test_rightmost_all_ones(f_input.exponent, EXPONENT_BITS) &&
               !test_rightmost_all_zeros(f_input.mantissa, MANTISSA_BITS)) {
        f_input.type = NAN_T;
    } else if (test_rightmost_all_zeros(f_input.exponent, EXPONENT_BITS) &&
               test_rightmost_all_zeros(f_input.mantissa, MANTISSA_BITS)) {
        f_input.type = ZERO_T;
    } else if (test_rightmost_all_zeros(f_input.exponent, EXPONENT_BITS)) {
        f_input.type = DENORMALIZED_T;
    } else {
        f_input.type = NORMALIZED_T;
    }

    return f_input;
}



int main(void) {
    Float a;
    a.type = NAN_T;
    a.sign = 0; // positive for 0, negative for 1
    a.mantissa = 838860;
    a.exponent = 120;
    char out[33];
    build_bitstring(a, out);
    out[32] = '\0';
    printf("%s\n", out);
    Float b = parse_bitstring(out);
    printf("%d %d %d %d\n", b.type, b.sign, b.mantissa, b.exponent);
    char out2[33];
    build_bitstring(b, out2);
    out2[32] = '\0';
    printf("%s\n", out2);
    return 0;
}

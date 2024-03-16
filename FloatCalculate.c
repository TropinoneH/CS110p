#include "FloatCalculate.h"
#include <malloc.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

const size_t SIGN_BIT = 1;
const size_t EXPONENT_BITS = 8;
const size_t MANTISSA_BITS = 23;

static int32_t get_norm_bias(void) { return 1 - (1 << (EXPONENT_BITS - 1)); }

static int32_t get_denorm_bias(void) { return 1 + get_norm_bias(); }

static bool test_rightmost_all_zeros(uint32_t number, size_t bits) {
    uint32_t mask = (1ull << bits) - 1;
    return (number & mask) == 0;
}

static bool test_rightmost_all_ones(uint32_t number, size_t bits) {
    uint32_t mask = (1ull << bits) - 1;
    return (number & mask) == mask;
}

// You can also design a function of your own.
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

// You can also design a function of your own.
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

// You can also design a function of your own.
static Float float_add_impl(Float a, Float b) {
    Float result;
    return result;
}

// You should not modify the signature of this function
void float_add(const char *a, const char *b, char *result) {
    // TODO: Implement this function
    // A possible implementation of the function:
    Float fa = parse_bitstring(a);
    Float fb = parse_bitstring(b);
    Float fresult = float_add_impl(fa, fb);
    build_bitstring(fresult, result);
}

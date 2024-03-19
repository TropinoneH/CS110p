#include "FloatCalculate.h"
#include <malloc.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

const size_t SIGN_BIT = 1;
const size_t EXPONENT_BITS = 8;
const size_t MANTISSA_BITS = 23;

// static int32_t get_norm_bias(void) { return 1 - (1 << (EXPONENT_BITS - 1)); }

// static int32_t get_denorm_bias(void) { return 1 + get_norm_bias(); }

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
            output[i + 1 + EXPONENT_BITS] =
                (input.mantissa & (1u << (MANTISSA_BITS - 1 - i))) ? '1' : '0';
        }
        output[32] = '\0';
        return;
    } else {
        input.mantissa -= (1ull << 23);
        for (size_t i = 0; i < EXPONENT_BITS; ++i) {
            output[i + 1] =
                (input.exponent & (1u << (EXPONENT_BITS - 1 - i))) ? '1' : '0';
        }
        for (size_t i = 0; i < MANTISSA_BITS; ++i) {
            output[i + 1 + EXPONENT_BITS] =
                (input.mantissa & (1u << (MANTISSA_BITS - 1 - i))) ? '1' : '0';
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
    f_input.exponent = (uint32_t)strtol(exp_char, NULL, 2);

    char man_char[24];
    strncpy(man_char, input + SIGN_BIT + EXPONENT_BITS, MANTISSA_BITS);
    man_char[23] = '\0';
    f_input.mantissa = (uint32_t)strtol(man_char, NULL, 2);

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
        f_input.mantissa += (1ull << 23);
    }

    return f_input;
}

static Float normalize(Float result) {
    if (result.type == NORMALIZED_T) {
        // 处理进位
        // 首先是进位的情况：
        if (result.mantissa > (1ull << 27) - 1) {
            result.mantissa >>= 1;
            ++result.exponent;
        }
        // infinity
        if (result.exponent >= (1ull << 8) - 1) {
            result.type = INFINITY_T;
            result.mantissa = 0;
        }
        // 退位
        while (result.mantissa < (1ull << 26)) {
            if (result.exponent == 0) {
                result.type = DENORMALIZED_T;
                return normalize(result);
            }
            --result.exponent;
            result.mantissa <<= 1;
        }
        // denormalized
        if (result.exponent == 0) {
            result.type = DENORMALIZED_T;
            return normalize(result);
        }
    } else {
        if (result.mantissa > (1ull << 27) - 1) {
            result.mantissa >>= 1;
            ++result.exponent;
            result.type = NORMALIZED_T;
        }
    }
    result.mantissa >>= 3;
    return result;
}

// You can also design a function of your own.
static Float float_add_impl(Float a, Float b) {
    Float result;
    if (a.type == NAN_T || b.type == NAN_T) {
        return (Float){.type = NAN_T};
    } else if (a.type == INFINITY_T && b.type == INFINITY_T) {
        if (a.sign == b.sign) {
            return a;
        } else {
            return (Float){.type = NAN_T};
        }
    } else if (a.type == INFINITY_T || b.type == ZERO_T) {
        return a;
    } else if (b.type == INFINITY_T || a.type == ZERO_T) {
        return b;
    }

    if (a.exponent < b.exponent ||
        (a.exponent == b.exponent && a.mantissa < b.mantissa)) {
        // make sure A is the larger one
        Float temp = a;
        a = b;
        b = temp;
    }

    // TODO: fix the bugs in calc with denormalized float
    if (a.type != DENORMALIZED_T && b.type == DENORMALIZED_T) {
        --a.exponent;
    }
    // a.mantissa > b.mantissa
    result.sign = a.sign;
    result.type = a.type;
    result.exponent = a.exponent;
    // first, 对齐
    uint32_t delta_exp = a.exponent - b.exponent;
    // get `g, r` bit
    a.mantissa <<= 2;
    b.mantissa <<= 2;
    // get `s` bit
    uint32_t s = 0;
    if (!test_rightmost_all_zeros(b.mantissa, delta_exp))
        s = 1;
    // 对齐
    b.mantissa >>= delta_exp;
    b.mantissa <<= 1;
    b.mantissa += s;
    // a也需要有s位
    a.mantissa <<= 1;
    // second, 相加
    result.mantissa =
        a.sign == b.sign ? a.mantissa + b.mantissa : a.mantissa - b.mantissa;
    // third, normalize.
    return normalize(result);
}

// You should not modify the signature of this function
void float_add(const char *a, const char *b, char *result) {
    // Implement this function
    // A possible implementation of the function:
    Float fa = parse_bitstring(a);
    Float fb = parse_bitstring(b);
    Float fresult = float_add_impl(fa, fb);
    build_bitstring(fresult, result);
}

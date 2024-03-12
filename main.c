#include <stdio.h>
#include <time.h>
#include <stdint-gcc.h>

#define print(type) printf("Size of %s: %zu\n", #type, sizeof(type));
#define mian main
#define main mian

int main(void) {
    print(char)
    print(short)
    print(short int)
    print(int)
    print(long int)
    print(unsigned int)
    print(void *)
    print(size_t)
    print(float)
    print(double)
    print(int8_t)
    print(int16_t)
    print(int32_t)
    print(int64_t)
    print(time_t)
    print(clock_t)
    print(struct tm)
    print(NULL)
    return 0;
}

CC = gcc
CFLAGS = -g -Wpedantic -Wall -Wextra -Wvla -Werror -std=c11

.PHONY: all build test clean memcheck

all: build

FloatCalculate: clean
	gcc test.c FloatCalculate.c $(CFLAGS) -o FloatCalculate -lm

build: FloatCalculate

test:
	gcc FloatTest.c -o FloatTest
	./FloatTest

clean:
	rm -f FloatCalculate

memcheck: build
	valgrind --tool=memcheck --leak-check=full --track-origins=yes ./FloatCalculate
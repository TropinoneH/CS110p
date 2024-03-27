CC = gcc
CFLAGS = -g -std=c11 -Wpedantic -Wall -Wextra -Werror -Wvla
MEMCHECK=valgrind --tool=memcheck --leak-check=full --track-origins=yes

all: clean
	$(CC) $(CFLAGS) -o main main.c src/assembler.c src/util.c

memcheck: all
	$(MEMCHECK) ./main ./test/test.S ./test/test.out

test: all
	./main ./test/err_bad_imm_or_off.S ./test/err_bad_imm_or_off.out

clean:
	rm -f ./main

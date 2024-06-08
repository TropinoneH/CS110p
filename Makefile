CC = gcc
CFLAGS = -g -std=c11 -Wpedantic -Wall -Wextra -Werror -Wvla -O0
MEMCHECK=valgrind --tool=memcheck --leak-check=full --track-origins=yes

all: 
	$(CC) $(CFLAGS) -o vm_tlb main.c src/simulator.c src/memory.c src/process.c src/TLB.c

memcheck: all
	$(MEMCHECK) ./vm_tlb ./testcases/10_alloc_to_same.txt

test: all
	./vm_tlb ./testcases/10_alloc_to_same.txt

clean:
	rm -f ./vm_tlb

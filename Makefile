CC = gcc
CFLAGS = -Wall -Werror -O2 -fno-tree-vectorize -fno-tree-loop-vectorize -fno-tree-slp-vectorize -fopenmp -march=native

BUILD_DIR = ./build
BIN = $(BUILD_DIR)/test

$(shell mkdir -p $(BUILD_DIR))

$(BIN): src/test.c src/baseline.c src/impl_pp.c
	@$(CC) $(CFLAGS) $^ -o $@

run: $(BIN)	
	@$^

clean: 
	-@rm -rf $(BUILD_DIR)

.PHONY: run clean

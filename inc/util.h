#ifndef UTIL_H
#define UTIL_H

#include <stdint.h>
#include <stdio.h>

#define ASSEMBLER_ERROR (-1)
#define ASSEMBLER_CORRECT 0

uint32_t R_type(const char *line, size_t cmd_length, uint32_t func3, uint32_t func7);

uint32_t I_type(const char *line, size_t cmd_length, uint32_t func3, uint32_t func7, uint32_t opcode);

uint32_t S_type(const char *line, size_t cmd_length, uint32_t func3);

uint32_t SB_type(const char *line, size_t cmd_length, uint32_t func3);

uint32_t U_type(const char *line, size_t cmd_length, uint32_t opcode);

uint32_t UJ_type(const char *line, size_t cmd_length);

void read_line(FILE *file_, char *line);

uint32_t char2addr(char *reg_name);

void dump_code(FILE *file_, uint32_t code);

void dump_error_information(FILE *file_);

#endif

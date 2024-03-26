#include "../inc/util.h"
#include <stdio.h>
#include <string.h>

/* YOUR CODE HERE */

void read_line(FILE *file_, char *line) {
    char ch = (char) fgetc(file_);
    while (ch != EOF) {
        line[strlen(line)] = ch;
        ch = (char) fgetc(file_);
        if (ch == '\n') {
            line[strlen(line)] = '\0';
            return;
        }
    }
}

uint32_t char2addr(char *reg_name) {
    if (strcmp(reg_name, "zero") == 0 || strcmp(reg_name, "x0") == 0) {
        return 0;
    } else if (strcmp(reg_name, "ra") == 0 || strcmp(reg_name, "x1") == 0) {
        return 1;
    } else if (strcmp(reg_name, "sp") == 0 || strcmp(reg_name, "x2") == 0) {
        return 2;
    } else if (strcmp(reg_name, "gp") == 0 || strcmp(reg_name, "x3") == 0) {
        return 3;
    } else if (strcmp(reg_name, "tp") == 0 || strcmp(reg_name, "x4") == 0) {
        return 4;
    } else if (strcmp(reg_name, "t0") == 0 || strcmp(reg_name, "x5") == 0) {
        return 5;
    } else if (strcmp(reg_name, "t1") == 0 || strcmp(reg_name, "x6") == 0) {
        return 6;
    } else if (strcmp(reg_name, "t2") == 0 || strcmp(reg_name, "x7") == 0) {
        return 7;
    } else if (strcmp(reg_name, "s0") == 0 || strcmp(reg_name, "x8") == 0) {
        return 8;
    } else if (strcmp(reg_name, "s1") == 0 || strcmp(reg_name, "x9") == 0) {
        return 9;
    } else if (strcmp(reg_name, "a0") == 0 || strcmp(reg_name, "x10") == 0) {
        return 10;
    } else if (strcmp(reg_name, "a1") == 0 || strcmp(reg_name, "x11") == 0) {
        return 11;
    } else if (strcmp(reg_name, "a2") == 0 || strcmp(reg_name, "x12") == 0) {
        return 12;
    } else if (strcmp(reg_name, "a3") == 0 || strcmp(reg_name, "x13") == 0) {
        return 13;
    } else if (strcmp(reg_name, "a4") == 0 || strcmp(reg_name, "x14") == 0) {
        return 14;
    } else if (strcmp(reg_name, "a5") == 0 || strcmp(reg_name, "x15") == 0) {
        return 15;
    } else if (strcmp(reg_name, "a6") == 0 || strcmp(reg_name, "x16") == 0) {
        return 16;
    } else if (strcmp(reg_name, "a7") == 0 || strcmp(reg_name, "x17") == 0) {
        return 17;
    } else if (strcmp(reg_name, "s2") == 0 || strcmp(reg_name, "x18") == 0) {
        return 18;
    } else if (strcmp(reg_name, "s3") == 0 || strcmp(reg_name, "x19") == 0) {
        return 19;
    } else if (strcmp(reg_name, "s4") == 0 || strcmp(reg_name, "x20") == 0) {
        return 20;
    } else if (strcmp(reg_name, "s5") == 0 || strcmp(reg_name, "x21") == 0) {
        return 21;
    } else if (strcmp(reg_name, "s6") == 0 || strcmp(reg_name, "x22") == 0) {
        return 22;
    } else if (strcmp(reg_name, "s7") == 0 || strcmp(reg_name, "x23") == 0) {
        return 23;
    } else if (strcmp(reg_name, "s8") == 0 || strcmp(reg_name, "x24") == 0) {
        return 24;
    } else if (strcmp(reg_name, "s9") == 0 || strcmp(reg_name, "x25") == 0) {
        return 25;
    } else if (strcmp(reg_name, "s10") == 0 || strcmp(reg_name, "x26") == 0) {
        return 26;
    } else if (strcmp(reg_name, "s11") == 0 || strcmp(reg_name, "x27") == 0) {
        return 27;
    } else if (strcmp(reg_name, "t3") == 0 || strcmp(reg_name, "x28") == 0) {
        return 28;
    } else if (strcmp(reg_name, "t4") == 0 || strcmp(reg_name, "x29") == 0) {
        return 29;
    } else if (strcmp(reg_name, "t5") == 0 || strcmp(reg_name, "x30") == 0) {
        return 30;
    } else if (strcmp(reg_name, "t6") == 0 || strcmp(reg_name, "x31") == 0) {
        return 31;
    }
    return ASSEMBLER_ERROR;
}

/* DO NOT MODIFY CODES BELOW*/

/* Store code into file_ under fixed format */
void dump_code(FILE *file_, uint32_t code) { fprintf(file_, "0x%.8X\n", code); }

/* Output error information to file_ */
void dump_error_information(FILE *file_) {
    fprintf(file_, "Assembling Error\n");
}

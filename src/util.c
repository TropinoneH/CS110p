#include "../inc/util.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

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

// Error check: check if the register name is valid (char2addr returns ASSEMBLER_ERROR)
// Error check: check if the imm is not a number: if the imm is not a number, then return ASSEMBLER_ERROR
// Error check: check if the imm is out of range: if the imm is out of range, then return ASSEMBLER_ERROR

uint32_t R_type(const char *line, size_t cmd_length, uint32_t func3, uint32_t func7) {
    char c_rd[5] = "", c_rs1[5] = "", c_rs2[5] = "";

    char ch = line[cmd_length + 1];
    while (ch != ' ') {
        c_rd[strlen(c_rd)] = ch;
        ch = line[strlen(c_rd) + cmd_length + 1];
    }
    ch = line[cmd_length + strlen(c_rd) + 2];
    while (ch != ' ') {
        c_rs1[strlen(c_rs1)] = ch;
        ch = line[strlen(c_rs1) + cmd_length + strlen(c_rd) + 2];
    }
    ch = line[cmd_length + strlen(c_rd) + strlen(c_rs1) + 3];
    while (ch != ' ' && ch != '\0') {
        c_rs2[strlen(c_rs2)] = ch;
        ch = line[strlen(c_rs2) + cmd_length + strlen(c_rd) + strlen(c_rs1) + 3];
    }

    uint32_t rd = char2addr(c_rd);
    uint32_t rs1 = char2addr(c_rs1);
    uint32_t rs2 = char2addr(c_rs2);

    if (rd == (uint32_t) ASSEMBLER_ERROR || rs1 == (uint32_t) ASSEMBLER_ERROR || rs2 == (uint32_t) ASSEMBLER_ERROR)
        return ASSEMBLER_ERROR;

    uint32_t opcode = 0x33;

    return func7 << 25 | rs2 << 20 | rs1 << 15 | func3 << 12 | rd << 7 | opcode;
}

uint32_t I_type(const char *line, size_t cmd_length, uint32_t func3, uint32_t func7, uint32_t opcode) {
    int64_t i64_imm;
    uint32_t rs1;
    uint32_t rd;
    char *endptr;

    char c_rs1[5] = "", c_rd[5] = "", c_imm[10] = "";
    char ch = line[cmd_length + 1];
    if (opcode == 0x73) {
        i64_imm = 0x0;
        rs1 = 0x0;
        rd = 0x0;
        endptr = c_rs1;
    } else if (opcode == 0x03) {
        while (ch != ' ') {
            c_rd[strlen(c_rd)] = ch;
            ch = line[cmd_length + strlen(c_rd) + 1];
        }
        ch = line[cmd_length + strlen(c_rd) + 2];
        while (ch != '(') {
            c_imm[strlen(c_imm)] = ch;
            ch = line[cmd_length + strlen(c_rd) + strlen(c_imm) + 2];
        }
        ch = line[cmd_length + strlen(c_rd) + strlen(c_imm) + 3];
        while (ch != ')') {
            c_rs1[strlen(c_rs1)] = ch;
            ch = line[cmd_length + strlen(c_rd) + strlen(c_imm) + strlen(c_rs1) + 3];
        }

        i64_imm = strtol(c_imm, &endptr, 0);
        rs1 = char2addr(c_rs1);
        rd = char2addr(c_rd);
    } else if (opcode == 0x13) {
        while (ch != ' ') {
            c_rd[strlen(c_rd)] = ch;
            ch = line[strlen(c_rd) + cmd_length + 1];
        }
        ch = line[strlen(c_rd) + cmd_length + 2];
        while (ch != ' ') {
            c_rs1[strlen(c_rs1)] = ch;
            ch = line[strlen(c_rs1) + strlen(c_rd) + cmd_length + 2];
        }
        ch = line[strlen(c_rd) + strlen(c_rs1) + cmd_length + 3];
        while (ch != ' ' && ch != '\0') {
            c_imm[strlen(c_imm)] = ch;
            ch = line[strlen(c_imm) + strlen(c_rd) + strlen(c_rs1) + cmd_length + 3];
        }
        rd = char2addr(c_rd);
        rs1 = char2addr(c_rs1);
        i64_imm = strtol(c_imm, &endptr, 0);
        // if func3 is 0x5, then it is srli or srai; if func3 is 0x1, then it is slli
        if (func3 == 0x5 || func3 == 0x1) {
            // judge the range of i64_imm
            if (i64_imm >= (2 << 4) || i64_imm < 0) {
                return ASSEMBLER_ERROR;
            }
        }
        // if func7 is 0x20, then it is srai
        if (func7 == 0x20) i64_imm |= func7 << 5;
    } else if (opcode == 0x67) {
        // jalr
        while (ch != ' ') {
            c_rd[strlen(c_rd)] = ch;
            ch = line[strlen(c_rd) + cmd_length + 1];
        }
        ch = line[strlen(c_rd) + cmd_length + 2];
        while (ch != ' ') {
            c_rs1[strlen(c_rs1)] = ch;
            ch = line[strlen(c_rs1) + strlen(c_rd) + cmd_length + 2];
        }
        ch = line[strlen(c_rd) + strlen(c_rs1) + cmd_length + 3];
        while (ch != ' ' && ch != '\0') {
            c_imm[strlen(c_imm)] = ch;
            ch = line[strlen(c_imm) + strlen(c_rd) + strlen(c_rs1) + cmd_length + 3];
        }
        rd = char2addr(c_rd);
        rs1 = char2addr(c_rs1);
        i64_imm = strtol(c_imm, &endptr, 0);
    } else return ASSEMBLER_ERROR; // the opcode is not valid

    if (rd == (uint32_t) ASSEMBLER_ERROR || rs1 == (uint32_t) ASSEMBLER_ERROR) return ASSEMBLER_ERROR;
    if (*endptr != '\0') return ASSEMBLER_ERROR;
    if (i64_imm > 2047 || i64_imm < -2048) return ASSEMBLER_ERROR;

    uint32_t imm = (uint32_t) i64_imm;
    return imm << 20 | rs1 << 15 | func3 << 12 | rd << 7 | opcode;
}

uint32_t S_type(const char *line, size_t cmd_length, uint32_t func3) {
    uint32_t opcode = 0x23;
    int64_t i64_imm;
    uint32_t rs1, rs2;
    char *endptr;

    char ch = line[cmd_length + 1];
    char c_rs2[5] = "", c_rs1[5] = "", c_imm[10] = "";
    while (ch != ' ') {
        c_rs2[strlen(c_rs2)] = ch;
        ch = line[cmd_length + strlen(c_rs2) + 1];
    }
    ch = line[cmd_length + strlen(c_rs2) + 2];
    while (ch != '(') {
        c_imm[strlen(c_imm)] = ch;
        ch = line[cmd_length + strlen(c_rs2) + strlen(c_imm) + 2];
    }
    ch = line[cmd_length + strlen(c_rs2) + strlen(c_imm) + 3];
    while (ch != ')') {
        c_rs1[strlen(c_rs1)] = ch;
        ch = line[cmd_length + strlen(c_rs2) + strlen(c_imm) + strlen(c_rs1) + 3];
    }

    rs1 = char2addr(c_rs1);
    rs2 = char2addr(c_rs2);
    i64_imm = strtol(c_imm, &endptr, 0);

    if (rs1 == (uint32_t) ASSEMBLER_ERROR || rs2 == (uint32_t) ASSEMBLER_ERROR) return ASSEMBLER_ERROR;
    if (*endptr != '\0') return ASSEMBLER_ERROR;
    if (i64_imm > 2047 || i64_imm < -2048) return ASSEMBLER_ERROR;

    uint32_t imm = (uint32_t) i64_imm;
    return (imm >> 5) << 25 | rs2 << 20 | rs1 << 15 | func3 << 12 | (i64_imm & ((1ull << 5) - 1)) << 7 | opcode;
}

uint32_t SB_type(const char *line, size_t cmd_length, uint32_t func3) {
    char *endptr;

    char c_rs1[5] = "", c_rs2[5] = "", c_imm[15] = "";
    char ch = line[cmd_length + 1];
    while (ch != ' ') {
        c_rs1[strlen(c_rs1)] = ch;
        ch = line[cmd_length + strlen(c_rs1) + 1];
    }
    ch = line[cmd_length + strlen(c_rs1) + 2];
    while (ch != ' ') {
        c_rs2[strlen(c_rs2)] = ch;
        ch = line[cmd_length + strlen(c_rs1) + strlen(c_rs2) + 2];
    }
    ch = line[cmd_length + strlen(c_rs1) + strlen(c_rs2) + 3];
    while (ch != ' ' && ch != '\0') {
        c_imm[strlen(c_imm)] = ch;
        ch = line[cmd_length + strlen(c_rs1) + strlen(c_rs2) + strlen(c_imm) + 3];
    }

    uint32_t rs1 = char2addr(c_rs1);
    uint32_t rs2 = char2addr(c_rs2);
    int64_t i64_imm = strtol(c_imm, &endptr, 0);

    uint32_t opcode = 0x63;

    if (rs1 == (uint32_t) ASSEMBLER_ERROR || rs2 == (uint32_t) ASSEMBLER_ERROR) return ASSEMBLER_ERROR;
    if (*endptr != '\0') return ASSEMBLER_ERROR;
    if (i64_imm > 4095 || i64_imm < -4096) return ASSEMBLER_ERROR;

    uint32_t imm = i64_imm;
    return ((imm & (1ull << 12)) >> 12) << 31 | ((imm & ((1ull << 6) - 1) << 5) >> 5) << 25 | rs2 << 20 | rs1 << 15 |
           func3 << 12 | ((imm & ((1ull << 4) - 1) << 1) >> 1) << 8 | ((imm & (1ull << 11)) >> 11) << 7 | opcode;
}

uint32_t U_type(const char *line, size_t cmd_length, uint32_t opcode) {
    char *endptr;

    char c_rd[5] = "", c_imm[20] = "";
    char ch = line[cmd_length + 1];
    while (ch != ' ') {
        c_rd[strlen(c_rd)] = ch;
        ch = line[cmd_length + strlen(c_rd) + 1];
    }
    ch = line[cmd_length + strlen(c_rd) + 2];
    while (ch != ' ' && ch != '\0') {
        c_imm[strlen(c_imm)] = ch;
        ch = line[cmd_length + strlen(c_rd) + strlen(c_imm) + 2];
    }

    uint32_t rd = char2addr(c_rd);
    uint32_t imm = strtol(c_imm, &endptr, 0);

    if (rd == (uint32_t) ASSEMBLER_ERROR) return ASSEMBLER_ERROR;
    if (*endptr != '\0') return ASSEMBLER_ERROR;
    if (imm > 1048575) return ASSEMBLER_ERROR;

    return imm << 12 | rd << 7 | opcode;
}

uint32_t UJ_type(const char *line, size_t cmd_length) {
    char *endptr;

    char c_rd[5] = "", c_imm[20] = "";
    char ch = line[cmd_length + 1];
    while (ch != ' ') {
        c_rd[strlen(c_rd)] = ch;
        ch = line[cmd_length + strlen(c_rd) + 1];
    }
    ch = line[cmd_length + strlen(c_rd) + 2];
    while (ch != ' ' && ch != '\0') {
        c_imm[strlen(c_imm)] = ch;
        ch = line[cmd_length + strlen(c_rd) + strlen(c_imm) + 2];
    }

    uint32_t rd = char2addr(c_rd);
    int64_t i64_imm = strtoll(c_imm, &endptr, 0);

    uint32_t opcode = 0x6F;

    if (rd == (uint32_t) ASSEMBLER_ERROR) return ASSEMBLER_ERROR;
    if (*endptr != '\0') return ASSEMBLER_ERROR;
    if (i64_imm < -1048576 || i64_imm > 1048575) return ASSEMBLER_ERROR;

    uint32_t imm = i64_imm;
    return ((imm & (1ull << 20)) >> 20) << 31 | ((imm & ((1ull << 10) - 1) << 1) >> 1) << 21 |
           ((imm & (1ull << 11)) >> 11) << 20 | ((imm & ((1ull << 8) - 1) << 12) >> 12) << 12 | rd << 7 | opcode;
}


/* DO NOT MODIFY CODES BELOW*/

/* Store code into file_ under fixed format */
void dump_code(FILE *file_, uint32_t code) { fprintf(file_, "0x%.8X\n", code); }

/* Output error information to file_ */
void dump_error_information(FILE *file_) {
    fprintf(file_, "Assembling Error\n");
}

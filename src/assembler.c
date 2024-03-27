#include "../inc/assembler.h"
#include "../inc/util.h"
#include <stdint.h>
#include <regex.h>

// Fuck CA! proj1.1 never use label?

typedef struct {
    char label[100];
    uint32_t line_number;
} Label;

Label labels[1000];
int label_count = 0;

void find_labels(FILE *input_file) {
    // move file pointer to the end of the file, for getting the size of the file
    fseek(input_file, 0, SEEK_END);
    long file_size = ftell(input_file);
    fseek(input_file, 0, SEEK_SET); // reset point to the beginning of file

    // alloc memory for file size
    char *file_content = (char *) malloc(file_size + 1);
    if (!file_content) {
        fprintf(stderr, "Memory allocation failed\n");
        return;
    }

    fread(file_content, 1, file_size, input_file);
    file_content[file_size] = '\0';

    // use reg to find labels
    regex_t regex;
    regcomp(&regex, "([a-zA-Z0-9_]+):", REG_EXTENDED);

    const char *p = file_content;
    regmatch_t m;
    int line_number = 0;

    while (1) {
        if (regexec(&regex, p, 1, &m, 0)) break; // 没有匹配则退出循环

        // calc line number by '\n'
        for (int i = 0; i < m.rm_so; ++i) {
            if (p[i] == '\n') line_number++;
        }

        // save label name and line number
        strncpy(labels[label_count].label, p + m.rm_so, m.rm_eo - m.rm_so - 1);
        labels[label_count].label[m.rm_eo - m.rm_so - 1] = '\0'; // 确保字符串终止
        labels[label_count].line_number = line_number - 2 * label_count;
        label_count++;

        p += m.rm_eo; // move to next position that matched
        ++line_number; // move to next line
    }

    // test: print all the labels and line number
    for (int i = 0; i < label_count; ++i) {
        printf("Label: %s, Line: %u\n", labels[i].label, labels[i].line_number);
    }

    regfree(&regex); // release reg
    free(file_content); // release memory

    fseek(input_file, 0, SEEK_SET); // reset file pointer to the beginning of the file
    // for the function `int assembler` will read the file again
}

uint32_t R_type(const char *line, size_t cmd_length, uint32_t func3, uint32_t func7);

uint32_t I_type(const char *line, size_t cmd_length, uint32_t func3, uint32_t func7, uint32_t opcode);

uint32_t S_type(const char *line, size_t cmd_length, uint32_t func3);

uint32_t SB_type(const char *line, size_t cmd_length, uint32_t func3);

uint32_t U_type(const char *line, size_t cmd_length, uint32_t opcode);

uint32_t UJ_type(const char *line, size_t cmd_length);

/* DO NOT MODIFY THE GIVEN API*/
int assembler(FILE *input_file, FILE *output_file) {
    /*YOUR CODE HERE*/
    if (output_file == NULL) {
        dump_error_information(output_file);
        return 1;
    }

    find_labels(input_file);

    uint32_t line_number = 0;

    while (!feof(input_file)) {
        char line[100] = "";
        read_line(input_file, line);

        if (strlen(line) == 0) break;
        if (line[strlen(line) - 1] == ':') {
            continue;
        }

        ++line_number;

        char command[10] = "";
        char ch = line[0];
        while (ch != ' ' && ch != '\0') {
            command[strlen(command)] = ch;
            ch = line[strlen(command)];
        }

        uint32_t code = 0;
        if (strcmp(command, "add") == 0)
            code = R_type(line, strlen(command), 0x0, 0x00);
        else if (strcmp(command, "mul") == 0)
            code = R_type(line, strlen(command), 0x0, 0x01);
        else if (strcmp(command, "sub") == 0)
            code = R_type(line, strlen(command), 0x0, 0x20);
        else if (strcmp(command, "sll") == 0)
            code = R_type(line, strlen(command), 0x1, 0x00);
        else if (strcmp(command, "mulh") == 0)
            code = R_type(line, strlen(command), 0x1, 0x01);
        else if (strcmp(command, "slt") == 0)
            code = R_type(line, strlen(command), 0x2, 0x00);
        else if (strcmp(command, "sltu") == 0)
            code = R_type(line, strlen(command), 0x3, 0x00);
        else if (strcmp(command, "xor") == 0)
            code = R_type(line, strlen(command), 0x4, 0x00);
        else if (strcmp(command, "div") == 0)
            code = R_type(line, strlen(command), 0x4, 0x01);
        else if (strcmp(command, "srl") == 0)
            code = R_type(line, strlen(command), 0x5, 0x00);
        else if (strcmp(command, "sra") == 0)
            code = R_type(line, strlen(command), 0x5, 0x20);
        else if (strcmp(command, "or") == 0)
            code = R_type(line, strlen(command), 0x6, 0x00);
        else if (strcmp(command, "rem") == 0)
            code = R_type(line, strlen(command), 0x6, 0x01);
        else if (strcmp(command, "and") == 0)
            code = R_type(line, strlen(command), 0x7, 0x00);
        else if (strcmp(command, "lb") == 0)
            code = I_type(line, strlen(command), 0x0, 0, 0x03);
        else if (strcmp(command, "lh") == 0)
            code = I_type(line, strlen(command), 0x1, 0, 0x03);
        else if (strcmp(command, "lw") == 0)
            code = I_type(line, strlen(command), 0x2, 0, 0x03);
        else if (strcmp(command, "lbu") == 0)
            code = I_type(line, strlen(command), 0x4, 0, 0x03);
        else if (strcmp(command, "lhu") == 0)
            code = I_type(line, strlen(command), 0x5, 0, 0x03);
        else if (strcmp(command, "addi") == 0)
            code = I_type(line, strlen(command), 0x0, 0, 0x13);
        else if (strcmp(command, "slli") == 0)
            code = I_type(line, strlen(command), 0x1, 0, 0x13);
        else if (strcmp(command, "slti") == 0)
            code = I_type(line, strlen(command), 0x2, 0, 0x13);
        else if (strcmp(command, "sltiu") == 0)
            code = I_type(line, strlen(command), 0x3, 0, 0x13);
        else if (strcmp(command, "xori") == 0)
            code = I_type(line, strlen(command), 0x4, 0, 0x13);
        else if (strcmp(command, "srli") == 0)
            code = I_type(line, strlen(command), 0x5, 0, 0x13);
        else if (strcmp(command, "srai") == 0)
            code = I_type(line, strlen(command), 0x5, 0x20, 0x13);
        else if (strcmp(command, "ori") == 0)
            code = I_type(line, strlen(command), 0x6, 0, 0x13);
        else if (strcmp(command, "andi") == 0)
            code = I_type(line, strlen(command), 0x7, 0, 0x13);
        else if (strcmp(command, "jalr") == 0)
            code = I_type(line, strlen(command), 0x0, 0, 0x67);
        else if (strcmp(command, "ecall") == 0)
            code = I_type(line, strlen(command), 0x0, 0, 0x73);
        else if (strcmp(command, "sb") == 0)
            code = S_type(line, strlen(command), 0x0);
        else if (strcmp(command, "sh") == 0)
            code = S_type(line, strlen(command), 0x1);
        else if (strcmp(command, "sw") == 0)
            code = S_type(line, strlen(command), 0x2);
            // find labels globally, for jump command
            // FUCK CA proj1.1: never use label for jump, only imm
        else if (strcmp(command, "beq") == 0)
            code = SB_type(line, strlen(command), 0x0);
        else if (strcmp(command, "bne") == 0)
            code = SB_type(line, strlen(command), 0x1);
        else if (strcmp(command, "blt") == 0)
            code = SB_type(line, strlen(command), 0x4);
        else if (strcmp(command, "bge") == 0)
            code = SB_type(line, strlen(command), 0x5);
        else if (strcmp(command, "bltu") == 0)
            code = SB_type(line, strlen(command), 0x6);
        else if (strcmp(command, "bgeu") == 0)
            code = SB_type(line, strlen(command), 0x7);
        else if (strcmp(command, "auipc") == 0)
            code = U_type(line, strlen(command), 0x17);
        else if (strcmp(command, "lui") == 0)
            code = U_type(line, strlen(command), 0x37);
        else if (strcmp(command, "jal") == 0)
            code = UJ_type(line, strlen(command));
        else if (strcmp(command, "beqz") == 0) {
            uint32_t rs2 = 0;

            char c_rs1[5] = "", c_imm[10] = "";
            ch = line[strlen(command) + 1];
            while (ch != ' ') {
                c_rs1[strlen(c_rs1)] = ch;
                ch = line[strlen(c_rs1) + strlen(command) + 1];
            }
            ch = line[strlen(c_rs1) + strlen(command) + 2];
            while (ch != ' ' && ch != '\0') {
                c_imm[strlen(c_imm)] = ch;
                ch = line[strlen(c_imm) + strlen(c_rs1) + strlen(command) + 2];
            }

            uint32_t imm = strtol(c_imm, NULL, 0), rs1 = char2addr(c_rs1);
            uint32_t opcode = 0x63, func3 = 0x0;
            code = ((imm & (1ull << 12)) >> 12) << 31 | ((imm & ((1ull << 6) - 1) << 5) >> 5) << 25 | rs2 << 20 |
                   rs1 << 15 | func3 << 12 | ((imm & ((1ull << 4) - 1) << 1) >> 1) << 8 |
                   ((imm & (1ull << 11)) >> 11) << 7 | opcode;
        } else if (strcmp(command, "bnez") == 0) {
            uint32_t rs2 = 0;

            char c_rs1[5] = "", c_imm[10] = "";
            ch = line[strlen(command) + 1];
            while (ch != ' ') {
                c_rs1[strlen(c_rs1)] = ch;
                ch = line[strlen(c_rs1) + strlen(command) + 1];
            }
            ch = line[strlen(c_rs1) + strlen(command) + 2];
            while (ch != ' ' && ch != '\0') {
                c_imm[strlen(c_imm)] = ch;
                ch = line[strlen(c_imm) + strlen(c_rs1) + strlen(command) + 2];
            }

            uint32_t imm = strtol(c_imm, NULL, 0), rs1 = char2addr(c_rs1);
            uint32_t opcode = 0x63, func3 = 0x1;
            code = ((imm & (1ull << 12)) >> 12) << 31 | ((imm & ((1ull << 6) - 1) << 5) >> 5) << 25 | rs2 << 20 |
                   rs1 << 15 | func3 << 12 | ((imm & ((1ull << 4) - 1) << 1) >> 1) << 8 |
                   ((imm & (1ull << 11)) >> 11) << 7 | opcode;
        } else if (strcmp(command, "j") == 0) {
            char c_imm[20] = "";
            ch = line[strlen(command) + 1];
            while (ch != ' ' && ch != '\0') {
                c_imm[strlen(c_imm)] = ch;
                ch = line[strlen(command) + strlen(c_imm) + 1];
            }

            uint32_t rd = 0;
            uint32_t imm = strtol(c_imm, NULL, 0);

            uint32_t opcode = 0x6F;

            code = ((imm & (1ull << 20)) >> 20) << 31 | ((imm & ((1ull << 10) - 1) << 1) >> 1) << 21 |
                   ((imm & (1ull << 11)) >> 11) << 20 | ((imm & ((1ull << 8) - 1) << 11) >> 11) << 12 | rd << 7 |
                   opcode;
        } else if (strcmp(command, "jr") == 0) {
            char c_rs1[5] = "", c_imm[15] = "";
            ch = line[strlen(command) + 1];
            while (ch != ' ' && ch != '\0') {
                c_rs1[strlen(c_rs1)] = ch;
                ch = line[strlen(command) + strlen(c_rs1) + 1];
            }

            uint32_t rs1 = char2addr(c_rs1);
            uint32_t rd = 0, imm = 0;

            uint32_t opcode = 0x67, func3 = 0x0;

            code = imm << 20 | rs1 << 15 | func3 << 12 | rd << 7 | opcode;
        } else if (strcmp(command, "mv") == 0) {
            char c_rd[5] = "", c_rs1[5] = "";
            ch = line[strlen(command) + 1];
            while (ch != ' ') {
                c_rd[strlen(c_rd)] = ch;
                ch = line[strlen(command) + strlen(c_rd) + 1];
            }
            ch = line[strlen(c_rd) + strlen(command) + 2];
            while (ch != ' ' && ch != '\0') {
                c_rs1[strlen(c_rs1)] = ch;
                ch = line[strlen(c_rs1) + strlen(c_rd) + strlen(command) + 2];
            }

            uint32_t rd = char2addr(c_rd);
            uint32_t rs1 = char2addr(c_rs1);

            uint32_t opcode = 0x13, func3 = 0x0;

            code = 0 << 20 | rs1 << 15 | func3 << 12 | rd << 7 | opcode;
        } else if (strcmp(command, "li") == 0) {
            char c_rd[5] = "", c_imm[20] = "";
            ch = line[strlen(command) + 1];
            while (ch != ' ') {
                c_rd[strlen(c_rd)] = ch;
                ch = line[strlen(command) + strlen(c_rd) + 1];
            }
            ch = line[strlen(c_rd) + strlen(command) + 2];
            while (ch != ' ' && ch != '\0') {
                c_imm[strlen(c_imm)] = ch;
                ch = line[strlen(command) + strlen(c_rd) + strlen(c_imm) + 2];
            }

            uint32_t rd = char2addr(c_rd);
            uint32_t imm = strtol(c_imm, NULL, 0);

            uint32_t opcode;
            uint32_t rs1 = 0;
            if (imm >= (1ull << 12) - 1) {
                // split this code to two command: lui + addi
                opcode = 0x37;
                code = (imm >> 12) << 12 | rd << 7 | opcode;
                dump_code(output_file, code);
                imm &= 0xFFF;
                rs1 = rd;
            }
            opcode = 0x13;
            uint32_t func3 = 0x0;
            code = imm << 20 | rs1 << 15 | func3 << 12 | rd << 7 | opcode;
        }

        // Error check: check if the command is not exist: after all if-else statement, if code is still 0, then it is an invalid command
        if (code != ASSEMBLER_ERROR && code != 0) {
            dump_code(output_file, code);
        } else {
            dump_error_information(output_file);
        }
    }
    return 0;
}

// Error check: check if the register name is valid (char2addr returns ASSEMBLER_ERROR)
// TODO Error check: check if the imm is out of range: if the imm is out of range, then return ASSEMBLER_ERROR
// Error check: check if the imm is not a number: if the imm is not a number, then return ASSEMBLER_ERROR

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

    if (rd == ASSEMBLER_ERROR || rs1 == ASSEMBLER_ERROR || rs2 == ASSEMBLER_ERROR) return ASSEMBLER_ERROR;

    uint32_t opcode = 0x33;

    return func7 << 25 | rs2 << 20 | rs1 << 15 | func3 << 12 | rd << 7 | opcode;
}

uint32_t I_type(const char *line, size_t cmd_length, uint32_t func3, uint32_t func7, uint32_t opcode) {
    uint32_t imm;
    uint32_t rs1;
    uint32_t rd;
    char *endptr;

    char c_rs1[5] = "", c_rd[5] = "", c_imm[10] = "";
    char ch = line[cmd_length + 1];
    if (opcode == 0x73) {
        imm = 0x0;
        rs1 = 0x0;
        rd = 0x0;
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

        imm = strtol(c_imm, &endptr, 0);
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
        imm = strtol(c_imm, &endptr, 0);
        // if func3 is 0x5, then it is srli or srai; if func3 is 0x1, then it is slli
        if (func3 == 0x5 || func3 == 0x1) {
            // judge the range of imm
            if (imm >= (2 << 5)) {
                return ASSEMBLER_ERROR;
            }
        }
        // if func7 is 0x20, then it is srai
        if (func7 == 0x20) imm |= func7 << 5;
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
        imm = strtol(c_imm, &endptr, 0);
    } else return ASSEMBLER_ERROR; // the opcode is not valid

    if (rd == ASSEMBLER_ERROR || rs1 == ASSEMBLER_ERROR) return ASSEMBLER_ERROR;
    if (imm >= (1ull << 12)) return ASSEMBLER_ERROR;
    if (*endptr != '\0') return ASSEMBLER_ERROR;

    return imm << 20 | rs1 << 15 | func3 << 12 | rd << 7 | opcode;
}

uint32_t S_type(const char *line, size_t cmd_length, uint32_t func3) {
    uint32_t opcode = 0x23;
    uint32_t imm;
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
    imm = strtol(c_imm, &endptr, 0);

    if (rs1 == ASSEMBLER_ERROR || rs2 == ASSEMBLER_ERROR) return ASSEMBLER_ERROR;
    if (*endptr != '\0') return ASSEMBLER_ERROR;

    return (imm >> 5) << 25 | rs2 << 20 | rs1 << 15 | func3 << 12 | (imm & ((1ull << 5) - 1)) << 7 | opcode;
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
    uint32_t imm = strtol(c_imm, &endptr, 0);

    uint32_t opcode = 0x63;

    if (rs1 == ASSEMBLER_ERROR || rs2 == ASSEMBLER_ERROR) return ASSEMBLER_ERROR;
    if (*endptr != '\0') return ASSEMBLER_ERROR;

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

    if (rd == ASSEMBLER_ERROR) return ASSEMBLER_ERROR;
    if (*endptr != '\0') return ASSEMBLER_ERROR;

    // FIXME: imm & 0xFFFFF000
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
    uint32_t imm = strtol(c_imm, &endptr, 0);

    uint32_t opcode = 0x6F;

    if (rd == ASSEMBLER_ERROR) return ASSEMBLER_ERROR;
    if (*endptr != '\0') return ASSEMBLER_ERROR;

    return ((imm & (1ull << 20)) >> 20) << 31 | ((imm & ((1ull << 10) - 1) << 1) >> 1) << 21 |
           ((imm & (1ull << 11)) >> 11) << 20 | ((imm & ((1ull << 8) - 1) << 11) >> 11) << 12 | rd << 7 | opcode;
}
#include "../inc/assembler.h"
#include "../inc/util.h"
#include <stdint.h>

uint32_t R_type(const char *line, size_t cmd_length, uint32_t func3, uint32_t func7);

uint32_t I_type(const char *line, size_t cmd_length, uint32_t func3, uint32_t func7, uint32_t opcode);

// TODO Error check: check if the command is not exist: after all if-else statement, if code is still 0, then it is an invalid command

/* DO NOT MODIFY THE GIVEN API*/
int assembler(FILE *input_file, FILE *output_file) {
    /*YOUR CODE HERE*/
    if (output_file == NULL) {
        dump_error_information(output_file);
        return 1;
    }
    while (!feof(input_file)) {
        char line[100] = "";
        read_line(input_file, line);

        char command[10] = "";
        char ch = line[0];
        while (ch != ' ' && ch != '\0') {
            command[strlen(command)] = ch;
            ch = line[strlen(command)];
        }
        printf("%s\n", command);
        uint32_t code = 0;
        if (strcmp(command, "add") == 0) {
            uint32_t func3 = 0x0;
            uint32_t func7 = 0x00;
            code = R_type(line, strlen(command), func3, func7);
        } else if (strcmp(command, "mul") == 0) {
            uint32_t func3 = 0x0;
            uint32_t func7 = 0x01;
            code = R_type(line, strlen(command), func3, func7);
        } else if (strcmp(command, "sub") == 0) {
            uint32_t func3 = 0x0;
            uint32_t func7 = 0x20;
            code = R_type(line, strlen(command), func3, func7);
        } else if (strcmp(command, "sll") == 0) {
            uint32_t func3 = 0x1;
            uint32_t func7 = 0x00;
            code = R_type(line, strlen(command), func3, func7);
        } else if (strcmp(command, "mulh") == 0) {
            uint32_t func3 = 0x1;
            uint32_t func7 = 0x01;
            code = R_type(line, strlen(command), func3, func7);
        } else if (strcmp(command, "slt") == 0) {
            uint32_t func3 = 0x2;
            uint32_t func7 = 0x00;
            code = R_type(line, strlen(command), func3, func7);
        } else if (strcmp(command, "sltu") == 0) {
            uint32_t func3 = 0x3;
            uint32_t func7 = 0x00;
            code = R_type(line, strlen(command), func3, func7);
        } else if (strcmp(command, "xor") == 0) {
            uint32_t func3 = 0x4;
            uint32_t func7 = 0x00;
            code = R_type(line, strlen(command), func3, func7);
        } else if (strcmp(command, "div") == 0) {
            uint32_t func3 = 0x4;
            uint32_t func7 = 0x01;
            code = R_type(line, strlen(command), func3, func7);
        } else if (strcmp(command, "srl") == 0) {
            uint32_t func3 = 0x5;
            uint32_t func7 = 0x00;
            code = R_type(line, strlen(command), func3, func7);
        } else if (strcmp(command, "sra") == 0) {
            uint32_t func3 = 0x5;
            uint32_t func7 = 0x20;
            code = R_type(line, strlen(command), func3, func7);
        } else if (strcmp(command, "or") == 0) {
            uint32_t func3 = 0x6;
            uint32_t func7 = 0x00;
            code = R_type(line, strlen(command), func3, func7);
        } else if (strcmp(command, "rem") == 0) {
            uint32_t func3 = 0x6;
            uint32_t func7 = 0x01;
            code = R_type(line, strlen(command), func3, func7);
        } else if (strcmp(command, "and") == 0) {
            uint32_t func3 = 0x7;
            uint32_t func7 = 0x00;
            code = R_type(line, strlen(command), func3, func7);
        } else if (strcmp(command, "lb") == 0) {
            uint32_t opcode = 0x03;
            uint32_t func3 = 0x0;
            code = I_type(line, strlen(command), func3, 0, opcode);
        } else if (strcmp(command, "lh") == 0) {
            uint32_t opcode = 0x03;
            uint32_t func3 = 0x1;
            code = I_type(line, strlen(command), func3, 0, opcode);
        } else if (strcmp(command, "lw") == 0) {
            uint32_t opcode = 0x03;
            uint32_t func3 = 0x2;
            code = I_type(line, strlen(command), func3, 0, opcode);
        } else if (strcmp(command, "lbu") == 0) {
            uint32_t opcode = 0x03;
            uint32_t func3 = 0x4;
            code = I_type(line, strlen(command), func3, 0, opcode);
        } else if (strcmp(command, "lhu") == 0) {
            uint32_t opcode = 0x03;
            uint32_t func3 = 0x5;
            code = I_type(line, strlen(command), func3, 0, opcode);
        } else if (strcmp(command, "addi") == 0) {
            uint32_t opcode = 0x13;
            uint32_t func3 = 0x0;
            code = I_type(line, strlen(command), func3, 0, opcode);
        } else if (strcmp(command, "slli") == 0) {
            uint32_t opcode = 0x13;
            uint32_t func3 = 0x1;
            code = I_type(line, strlen(command), func3, 0, opcode);
        } else if (strcmp(command, "slti") == 0) {
            uint32_t opcode = 0x13;
            uint32_t func3 = 0x2;
            code = I_type(line, strlen(command), func3, 0, opcode);
        } else if (strcmp(command, "sltiu") == 0) {
            uint32_t opcode = 0x13;
            uint32_t func3 = 0x3;
            code = I_type(line, strlen(command), func3, 0, opcode);
        } else if (strcmp(command, "xori") == 0) {
            uint32_t opcode = 0x13;
            uint32_t func3 = 0x4;
            code = I_type(line, strlen(command), func3, 0, opcode);
        } else if (strcmp(command, "srli") == 0) {
            uint32_t opcode = 0x13;
            uint32_t func3 = 0x5;
            code = I_type(line, strlen(command), func3, 0, opcode);
        } else if (strcmp(command, "srai") == 0) {
            uint32_t opcode = 0x13;
            uint32_t func3 = 0x5;
            uint32_t func7 = 0x20;
            code = I_type(line, strlen(command), func3, func7, opcode);
        } else if (strcmp(command, "ori") == 0) {
            uint32_t opcode = 0x13;
            uint32_t func3 = 0x6;
            code = I_type(line, strlen(command), func3, 0, opcode);
        } else if (strcmp(command, "andi") == 0) {
            uint32_t opcode = 0x13;
            uint32_t func3 = 0x7;
            code = I_type(line, strlen(command), func3, 0, opcode);
        } else if (strcmp(command, "lui") == 0) {
            char c_rd[5] = "", c_imm[10] = "";
            ch = line[strlen(command) + 1];
            while (ch != ' ' && ch != '\0') {
                c_rd[strlen(c_rd)] = ch;
                ch = line[strlen(c_rd) + strlen(command) + 1];
            }
            ch = line[strlen(c_rd) + strlen(command) + 2];
            while (ch != ' ' && ch != '\0') {
                c_imm[strlen(c_imm)] = ch;
                ch = line[strlen(c_imm) + strlen(c_rd) + strlen(command) + 2];
            }
            uint32_t rd = char2addr(c_rd);
            uint32_t imm = strtol(c_imm, NULL, 0);
            uint32_t opcode = 0x37;
            code = imm << 12 | rd << 7 | opcode;
        }
        if (code != ASSEMBLER_ERROR && code != 0) {
            dump_code(output_file, code);
        } else {
            dump_error_information(output_file);
        }
        printf("0x%.8X\n", code);
    }
    return 0;
}

// TODO Error check: check if the register name is valid (char2addr returns ASSEMBLER_ERROR)
// TODO Error check: check if the imm is out of range: if the imm is out of range, then return ASSEMBLER_ERROR
// TODO Error check: check if the imm is not a number: if the imm is not a number, then return ASSEMBLER_ERROR

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

    uint32_t opcode = 0x33;

    return func7 << 25 | rs2 << 20 | rs1 << 15 | func3 << 12 | rd << 7 | opcode;
}

uint32_t I_type(const char *line, size_t cmd_length, uint32_t func3, uint32_t func7, uint32_t opcode) {
    uint32_t imm;
    uint32_t rs1;
    uint32_t rd;

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

        imm = strtoul(c_imm, NULL, 0);
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
        imm = strtol(c_imm, NULL, 0);
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
        imm = strtol(c_imm, NULL, 0);
    } else return ASSEMBLER_ERROR; // the opcode is not valid

    return imm << 20 | rs1 << 15 | func3 << 12 | rd << 7 | opcode;
}

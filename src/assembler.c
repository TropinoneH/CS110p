#include "../inc/assembler.h"
#include "../inc/util.h"

//// Fuck CA! proj1.1 never use label?
//
//typedef struct {
//    char label[100];
//    uint32_t line_number;
//} Label;
//
//Label labels[1000];
//int label_count = 0;
//
//void find_labels(FILE *input_file) {
//    // move file pointer to the end of the file, for getting the size of the file
//    fseek(input_file, 0, SEEK_END);
//    long file_size = ftell(input_file);
//    fseek(input_file, 0, SEEK_SET); // reset point to the beginning of file
//
//    // alloc memory for file size
//    char *file_content = (char *) malloc(file_size + 1);
//    if (!file_content) {
//        fprintf(stderr, "Memory allocation failed\n");
//        return;
//    }
//
//    fread(file_content, 1, file_size, input_file);
//    file_content[file_size] = '\0';
//
//    // use reg to find labels
//    regex_t regex;
//    regcomp(&regex, "([a-zA-Z0-9_]+):", REG_EXTENDED);
//
//    const char *p = file_content;
//    regmatch_t m;
//    int line_number = 0;
//
//    while (1) {
//        if (regexec(&regex, p, 1, &m, 0)) break; // 没有匹配则退出循环
//
//        // calc line number by '\n'
//        for (int i = 0; i < m.rm_so; ++i) {
//            if (p[i] == '\n') line_number++;
//        }
//
//        // save label name and line number
//        strncpy(labels[label_count].label, p + m.rm_so, m.rm_eo - m.rm_so - 1);
//        labels[label_count].label[m.rm_eo - m.rm_so - 1] = '\0'; // 确保字符串终止
//        labels[label_count].line_number = line_number - 2 * label_count;
//        label_count++;
//
//        p += m.rm_eo; // move to next position that matched
//        ++line_number; // move to next line
//    }
//
//    // test: print all the labels and line number
//    for (int i = 0; i < label_count; ++i) {
//        printf("Label: %s, Line: %u\n", labels[i].label, labels[i].line_number);
//    }
//
//    regfree(&regex); // release reg
//    free(file_content); // release memory
//
//    fseek(input_file, 0, SEEK_SET); // reset file pointer to the beginning of the file
//    // for the function `int assembler` will read the file again
//}

/* DO NOT MODIFY THE GIVEN API*/
int assembler(FILE *input_file, FILE *output_file) {
    /*YOUR CODE HERE*/
    int ret = 0;

    while (!feof(input_file)) {
        char line[100] = "";
        read_line(input_file, line);

        if (strlen(line) == 0) break;
        if (line[strlen(line) - 1] == ':') {
            continue;
        }

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
            char new_line[100] = "";
            strcat(new_line, "beq ");
            strcat(new_line, c_rs1);
            strcat(new_line, " x0 ");
            strcat(new_line, c_imm);
            code = SB_type(new_line, strlen("beq"), 0x0);
        } else if (strcmp(command, "bnez") == 0) {
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
            char new_line[100] = "";
            strcat(new_line, "bne ");
            strcat(new_line, c_rs1);
            strcat(new_line, " x0 ");
            strcat(new_line, c_imm);
            code = SB_type(new_line, strlen("bne"), 0x1);
        } else if (strcmp(command, "j") == 0) {
            char c_imm[20] = "";
            ch = line[strlen(command) + 1];
            while (ch != ' ' && ch != '\0') {
                c_imm[strlen(c_imm)] = ch;
                ch = line[strlen(command) + strlen(c_imm) + 1];
            }

            char new_line[100] = "";
            strcat(new_line, "jal x0 ");
            strcat(new_line, c_imm);
            code = UJ_type(new_line, strlen("jal"));
        } else if (strcmp(command, "jr") == 0) {
            char c_rs1[5] = "";
            ch = line[strlen(command) + 1];
            while (ch != ' ' && ch != '\0') {
                c_rs1[strlen(c_rs1)] = ch;
                ch = line[strlen(command) + strlen(c_rs1) + 1];
            }

            char new_line[100] = "";
            strcat(new_line, "jalr x0 ");
            strcat(new_line, c_rs1);
            strcat(new_line, " 0");
            code = I_type(new_line, strlen("jalr"), 0x0, 0, 0x67);
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

            char new_line[100] = "";
            strcat(new_line, "addi ");
            strcat(new_line, c_rd);
            strcat(new_line, " ");
            strcat(new_line, c_rs1);
            strcat(new_line, " 0");
            code = I_type(new_line, strlen("addi"), 0x0, 0, 0x13);
        } else if (strcmp(command, "li") == 0) {
            char *endptr;
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
            int64_t i64_imm = strtol(c_imm, &endptr, 0);
            uint32_t imm;

            uint32_t opcode;
            uint32_t rs1 = 0;
            if (i64_imm > 2047 || i64_imm < -2048) {
                // split this code to two command: lui + addi
                opcode = 0x37;
                imm = (uint32_t) i64_imm;
                code = ((imm >> 12) + ((imm & (1ull << 11)) ? 1 : 0)) << 12 | rd << 7 | opcode;
                if (rd != (uint32_t) ASSEMBLER_ERROR || *endptr == '\0') dump_code(output_file, code);
                imm &= 0xFFF;
                rs1 = rd;
            } else {
                imm = (uint32_t) i64_imm;
            }
            opcode = 0x13;
            uint32_t func3 = 0x0;
            code = imm << 20 | rs1 << 15 | func3 << 12 | rd << 7 | opcode;
            if (rs1 == (uint32_t) ASSEMBLER_ERROR || rd == (uint32_t) ASSEMBLER_ERROR || *endptr != '\0')
                code = ASSEMBLER_ERROR;
        }

        // Error check: check if the command is not exist: after all if-else statement, if code is still 0, then it is an invalid command
        if (code != (uint32_t) ASSEMBLER_ERROR && code != 0) {
            dump_code(output_file, code);
        } else {
            dump_error_information(output_file);
            ret = ASSEMBLER_ERROR;
        }
    }
    return ret;
}

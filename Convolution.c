#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char **argv) {
    if (argc < 3) {
        printf("Usage:\n");
        printf("./main <input file> <output file>\n");
        exit(0);
    }

    char *input_file_name = argv[1];
    char *output_file_name = argv[2];

    FILE *input_file = fopen(input_file_name, "r");
    FILE *output_file = fopen(output_file_name, "w");

    if (input_file == NULL) {
        printf("Error: unable to open input file %s\n", input_file_name);
        exit(0);
    }

    if (output_file == NULL) {
        printf("Error: unable to open output file %s\n", output_file_name);
        fclose(input_file);
        exit(0);
    }

    /* YOUR CODE HERE */
    int rows, cols, kernel_rows, kernel_cols;
    fscanf(input_file, "%d %d", &cols, &rows);
    int **image = (int **)malloc(rows * sizeof(int *));
    for (int i = 0; i < rows; i++) {
        image[i] = (int *)malloc(cols * sizeof(int));
        for (int j = 0; j < cols; j++) {
            fscanf(input_file, "%d", &image[i][j]);
        }
    }

    fscanf(input_file, "%d %d", &kernel_cols, &kernel_rows);
    int **kernel = (int **)malloc(kernel_rows * sizeof(int *));
    for (int i = 0; i < kernel_rows; i++) {
        kernel[i] = (int *)malloc(kernel_cols * sizeof(int));
        for (int j = 0; j < kernel_cols; j++) {
            fscanf(input_file, "%d", &kernel[i][j]);
        }
    }

    // Output dimensions
    int output_rows = rows - kernel_rows + 1;
    int output_cols = cols - kernel_cols + 1;
    int **output = (int **)malloc(output_rows * sizeof(int *));
    for (int i = 0; i < output_rows; i++) {
        output[i] = (int *)malloc(output_cols * sizeof(int));
    }

    // Perform convolution
    for (int i = 0; i < output_rows; i++) {
        for (int j = 0; j < output_cols; j++) {
            output[i][j] = 0; // Initialize output element
            for (int ki = 0; ki < kernel_rows; ki++) {
                for (int kj = 0; kj < kernel_cols; kj++) {
                    output[i][j] += image[i + ki][j + kj] * kernel[ki][kj];
                }
            }
        }
    }

    // Write output to file
    for (int i = 0; i < output_rows; i++) {
        for (int j = 0; j < output_cols; j++) {
            fprintf(output_file, "%d ", output[i][j]);
        }
        fprintf(output_file, "\n");
    }

    // Free memory and close files
    for (int i = 0; i < rows; i++) {
        free(image[i]);
    }
    free(image);

    for (int i = 0; i < kernel_rows; i++) {
        free(kernel[i]);
    }
    free(kernel);

    for (int i = 0; i < output_rows; i++) {
        free(output[i]);
    }
    free(output);

    fclose(input_file);
    fclose(output_file);

    return 0;
}

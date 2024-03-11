#include "vector.h"
#include <stdio.h>
#include <stdlib.h>

Vector *vector_create(void) {
    Vector *vector = malloc(sizeof(Vector));
    if (vector == NULL) {
        printf("Invalid vector\n");
        // exit(1);
        return NULL;
    }
    vector->size = 0;
    vector->capacity = VECTOR_INITIAL_CAPACITY;
    vector->data = malloc(sizeof(double) * vector->capacity);
    if (vector->data == NULL) {
        printf("Memory allocation failed\n");
        free(vector);
        return NULL;
    }
    return vector;
}

void vector_push(Vector *vector, double element) {
    if (vector == NULL) {
        printf("Invalid vector\n");
        // exit(1);
        return;
    }
    if (vector->size == vector->capacity) {
        vector->capacity *= 2;
        double *tmp = realloc(vector->data, sizeof(double) * vector->capacity);
        if (tmp == NULL) {
            printf("Memory allocation failed\n");
            free(vector->data);
            free(vector);
            // exit(1);
            return;
        }
        vector->data = tmp;
    }
    vector->data[vector->size++] = element;
}

double vector_get(const Vector *vector, int index) {
    if (vector == NULL || index < 0 || index >= vector->size) {
        printf("Invalid index\n");
        // exit(1);
        return 0;
    }
    return vector->data[index];
}

void vector_free(Vector *vector) {
    if (vector == NULL) {
        printf("Invalid vector\n");
        // exit(1);
        return;
    }
    free(vector->data);
    free(vector);
}

void another_vector_free(Vector **vector) {
    if (vector == NULL || *vector == NULL) {
        printf("Invalid vector\n");
        // exit(1);
        return;
    }
    free((*vector)->data);
    free(*vector);
    *vector = NULL;
}

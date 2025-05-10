#include "random_matrix_generator.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Allocate a matrix with the given number of rows and columns
long int** allocate_matrix(int rows, int cols) {
    long int **matrix = malloc(rows * sizeof(long int *));
    if (matrix == NULL) {
        printf("Memory allocation failed for matrix rows!\n");
        exit(1);
    }

    for (int i = 0; i < rows; i++) {
        matrix[i] = malloc(cols * sizeof(long int));
        if (matrix[i] == NULL) {
            printf("Memory allocation failed for matrix row %d!\n", i);
            exit(1);
        }
    }
    return matrix;
}

// Free the allocated matrix
void free_matrix(long int **matrix, int rows) {
    if (matrix != NULL) {
        for (int i = 0; i < rows; i++) {
            free(matrix[i]);
        }
        free(matrix);
    }
}

// Fill the matrix with random integers up to max_val
void generate_random_matrix(long int **matrix, int rows, int cols, int max_val) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            matrix[i][j] = rand() % max_val;
        }
    }
}

void print_matrix(long int **matrix, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%3ld ", matrix[i][j]);
        }
        printf("\n");
    }
}

// Function to read two n x n matrices from a file in row-major order
void read_matrix_from_file(const char* filename, long int*** A, long int*** B, int* n) {
    FILE *file = fopen(filename, "r");

    if (file == NULL) {
        printf("Error: Could not open file %s\n", filename);
        exit(1);
    }

    fscanf(file, "%d", n);
    printf("n is %3d\n", *n);

    *A = allocate_matrix(*n, *n);
    *B = allocate_matrix(*n, *n);

    for (int i = 0; i < *n; i++) {
        for (int j = 0; j < *n; j++) {
            fscanf(file, "%ld", &(*A)[i][j]);
        }
    }

    for (int i = 0; i < *n; i++) {
        for (int j = 0; j < *n; j++) {
            fscanf(file, "%ld", &(*B)[i][j]);
        }
    }

    fclose(file);
}

#include "random_matrix_generator.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Allocate a matrix to the (rows, columns) size
int** allocate_matrix(int rows, int cols) {
    int **matrix = malloc(rows * sizeof(int *));
    for (int i = 0; i < rows; i++) {
        matrix[i] = malloc(cols * sizeof(int));
    }
    return matrix;
}

// Fill the matrix with a random numbers
void generate_random_matrix(int **matrix, int rows, int cols, int max_val) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            matrix[i][j] = rand() % max_val;
        }
    }
}

// Print the matrix for easy verification (remove when evaluating the performance)
void print_matrix(int **matrix, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%3d ", matrix[i][j]);
        }
        printf("\n");
    }
}

// Deallocate the matrix from memory
void free_matrix(int **matrix, int rows) {
    for (int i = 0; i < rows; i++) {
        free(matrix[i]);
    }
    free(matrix);
}


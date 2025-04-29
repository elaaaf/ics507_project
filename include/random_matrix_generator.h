#ifndef RANDOM_MATRIX_GENERATOR_H
#define RANDOM_MATRIX_GENERATOR_H

// Allocate a matrix with given rows and cols
int** allocate_matrix(int rows, int cols);

// Free the allocated matrix
void free_matrix(int **matrix, int rows);

// Fill the matrix with random integers up to max_val
void generate_random_matrix(int **matrix, int rows, int cols, int max_val);

// Print the matrix nicely
void print_matrix(int **matrix, int rows, int cols);

#endif // RANDOM_MATRIX_GENERATOR_H


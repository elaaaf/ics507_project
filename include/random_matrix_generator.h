#ifndef RANDOM_MATRIX_GENERATOR_H
#define RANDOM_MATRIX_GENERATOR_H

// Allocate a matrix with given rows and cols
long int** allocate_matrix(int rows, int cols);

// Free the allocated matrix
void free_matrix(long int **matrix, int rows);

// Fill the matrix with random integers up to max_val
void generate_random_matrix(long int **matrix, int rows, int cols, int max_val);

// Print the matrix nicely
void print_matrix(long int **matrix, int rows, int cols);

// Function to read two n x n matrices from a file in row-major order
void read_matrix_from_file(const char* filename, long int*** A, long int*** B, int* n);
#endif // RANDOM_MATRIX_GENERATOR_H


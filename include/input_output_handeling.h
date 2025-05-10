#ifndef INPUT_OUTPUT_HANDELING_H
#define INPUT_OUTPUT_HANDELING_H

#include <time.h>
#include <string.h>

// Allocate a matrix with given rows and cols
long int** allocate_matrix(int rows, int cols);

// Free the allocated matrix
void free_matrix(long int **matrix, int rows);

// Fill the matrix with random integers up to max_val
void generate_random_matrix(long int **matrix, int rows, int cols, int max_val);

char * replace(
    char const * const original, 
    char const * const pattern, 
    char const * const replacement
);

// Print the matrix nicely
void print_matrix(long int **matrix, int rows, int cols);

// Function to read two n x n matrices from a file in row-major order
void read_matrix_from_file(const char* filename, long int*** A, long int*** B, int* n);

void write_time_to_file(const char* filename, double time_taken) ;

void write_output_to_file(const char* filename, long int** matrix, int n);

void generate_matrix_file(const char* filename, int n);

#endif // INPUT_OUTPUT_HANDELING_H


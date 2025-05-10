#include "input_output_handeling.h"
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


void write_matrix_to_file(const char* input_filename, int n, const char* method, long int** matrix) {
    char filename[512];
    snprintf(filename, sizeof(filename), "%s_%d_output_%s.txt", input_filename, n, method);
    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        printf("Error: Could not open file %s for writing.\n", filename);
        return;
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            fprintf(file, "%ld ", matrix[i][j]);
        }
        fprintf(file, "\n");
    }
    fclose(file);
    printf("Matrix written to %s\n", filename);
}

void write_time_to_file(const char* input_filename, int n, const char* method, double time_taken) {
    char filename[512];
    snprintf(filename, sizeof(filename), "%s_%d_info_%s.txt", input_filename, n, method);
    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        printf("Error: Could not open file %s for writing.\n", filename);
        return;
    }

    int hours = (int)(time_taken / 3600);
    int minutes = (int)((time_taken - hours * 3600) / 60);
    int seconds = (int)(time_taken - hours * 3600 - minutes * 60);

    fprintf(file, "Time taken: %02d:%02d:%02d\n", hours, minutes, seconds);
    fclose(file);
    printf("Time written to %s\n", filename);
}



void write_output_to_file(const char* filename, long int** matrix, int n) {
    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        printf("Error: Could not open file %s for writing\n", filename);
        return;
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            fprintf(file, "%ld ", matrix[i][j]);
        }
        fprintf(file, "\n");
    }

    fclose(file);
}

void write_time_to_filee(const char* filename, double time_taken) {
    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        printf("Error: Could not open file %s for writing\n", filename);
        return;
    }

    int hours = (int)(time_taken / 3600);
    int minutes = (int)((time_taken - hours * 3600) / 60);
    int seconds = (int)(time_taken - hours * 3600 - minutes * 60);

    fprintf(file, "Time taken: %02d:%02d:%02d\n", hours, minutes, seconds);
    fclose(file);
}
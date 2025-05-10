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


//from https://stackoverflow.com/questions/779875/what-function-is-to-replace-a-substring-from-a-string-in-c
char * replace(
    char const * const original, 
    char const * const pattern, 
    char const * const replacement
) {
  size_t const replen = strlen(replacement);
  size_t const patlen = strlen(pattern);
  size_t const orilen = strlen(original);

  size_t patcnt = 0;
  const char * oriptr;
  const char * patloc;

  // find how many times the pattern occurs in the original string
  for (oriptr = original; patloc = strstr(oriptr, pattern); oriptr = patloc + patlen)
  {
    patcnt++;
  }

  {
    // allocate memory for the new string
    size_t const retlen = orilen + patcnt * (replen - patlen);
    char * const returned = (char *) malloc( sizeof(char) * (retlen + 1) );

    if (returned != NULL)
    {
      // copy the original string, 
      // replacing all the instances of the pattern
      char * retptr = returned;
      for (oriptr = original; patloc = strstr(oriptr, pattern); oriptr = patloc + patlen)
      {
        size_t const skplen = patloc - oriptr;
        // copy the section until the occurence of the pattern
        strncpy(retptr, oriptr, skplen);
        retptr += skplen;
        // copy the replacement 
        strncpy(retptr, replacement, replen);
        retptr += replen;
      }
      // copy the rest of the string.
      strcpy(retptr, oriptr);
    }
    return returned;
  }
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

void write_time_to_file(const char* filename, double time_taken) {
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

void generate_matrix_file(const char* filename, int n) {
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        printf("Error: Could not open file %s for writing.\n", filename);
        return;
    }

    fprintf(file, "%d\n", n);
    srand(time(NULL));

    printf("Generating Matrix A...\n");
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            int value = (rand() % 19) - 9;  // Random number between -9 and 9
            fprintf(file, "%d ", value);
        }
        fprintf(file, "\n");
    }

    printf("Generating Matrix B...\n");
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            int value = (rand() % 19) - 9;  // Random number between -9 and 9
            fprintf(file, "%d ", value);
        }
        fprintf(file, "\n");
    }

    fclose(file);
    printf("Matrix file generated successfully: %s\n", filename);
}
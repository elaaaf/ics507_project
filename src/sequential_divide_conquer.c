#include "sequential_divide_conquer.h"
//#include "input_output_handeling.h"
#include <stdio.h>
#include <stdlib.h>

long int **allocate_matrix_dc(int size) {
    long int **matrix = malloc(size * sizeof(long int *));
    for (int i = 0; i < size; i++) {
        matrix[i] = calloc(size, sizeof(long int));
    }
    return matrix;
}

void free_matrix_dc(long int **matrix, int size) {
    for (int i = 0; i < size; i++)
        free(matrix[i]);
    free(matrix);
}

void add_matrix(long int **A, long int **B, long int **result, int size) {
    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++)
            result[i][j] = A[i][j] + B[i][j];
}

void subtract_matrix(long int **A, long int **B, long int **result, int size) {
    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++)
            result[i][j] = A[i][j] - B[i][j];
}

void copy_submatrix(long int **source, long int **dest, int row_offset, int col_offset, int size) {
    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++)
            dest[i][j] = source[i + row_offset][j + col_offset];
}

void set_submatrix(long int **dest, long int **source, int row_offset, int col_offset, int size) {
    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++)
            dest[i + row_offset][j + col_offset] = source[i][j];
}

long int **sequential_divide_conquer(long int **A, long int **B, int size) {
    long int **C = allocate_matrix_dc(size);

    if (size == 1) {
        C[0][0] = A[0][0] * B[0][0];
        return C;
    }

    int new_size = size / 2;

    // Allocate submatrices
    long int **A11 = allocate_matrix_dc(new_size);
    long int **A12 = allocate_matrix_dc(new_size);
    long int **A21 = allocate_matrix_dc(new_size);
    long int **A22 = allocate_matrix_dc(new_size);

    long int **B11 = allocate_matrix_dc(new_size);
    long int **B12 = allocate_matrix_dc(new_size);
    long int **B21 = allocate_matrix_dc(new_size);
    long int **B22 = allocate_matrix_dc(new_size);

    // Fill submatrices
    copy_submatrix(A, A11, 0, 0, new_size);
    copy_submatrix(A, A12, 0, new_size, new_size);
    copy_submatrix(A, A21, new_size, 0, new_size);
    copy_submatrix(A, A22, new_size, new_size, new_size);

    copy_submatrix(B, B11, 0, 0, new_size);
    copy_submatrix(B, B12, 0, new_size, new_size);
    copy_submatrix(B, B21, new_size, 0, new_size);
    copy_submatrix(B, B22, new_size, new_size, new_size);

    // Recursive multiplications
    long int **M1 = sequential_divide_conquer(A11, B11, new_size);
    long int **M2 = sequential_divide_conquer(A12, B21, new_size);
    long int **C11 = allocate_matrix_dc(new_size);
    add_matrix(M1, M2, C11, new_size);

    long int **M3 = sequential_divide_conquer(A11, B12, new_size);
    long int **M4 = sequential_divide_conquer(A12, B22, new_size);
    long int **C12 = allocate_matrix_dc(new_size);
    add_matrix(M3, M4, C12, new_size);

    long int **M5 = sequential_divide_conquer(A21, B11, new_size);
    long int **M6 = sequential_divide_conquer(A22, B21, new_size);
    long int **C21 = allocate_matrix_dc(new_size);
    add_matrix(M5, M6, C21, new_size);

    long int **M7 = sequential_divide_conquer(A21, B12, new_size);
    long int **M8 = sequential_divide_conquer(A22, B22, new_size);
    long int **C22 = allocate_matrix_dc(new_size);
    add_matrix(M7, M8, C22, new_size);

    // Combine result submatrices into C
    set_submatrix(C, C11, 0, 0, new_size);
    set_submatrix(C, C12, 0, new_size, new_size);
    set_submatrix(C, C21, new_size, 0, new_size);
    set_submatrix(C, C22, new_size, new_size, new_size);

    // Free memory
    free_matrix_dc(A11, new_size); free_matrix_dc(A12, new_size);
    free_matrix_dc(A21, new_size); free_matrix_dc(A22, new_size);
    free_matrix_dc(B11, new_size); free_matrix_dc(B12, new_size);
    free_matrix_dc(B21, new_size); free_matrix_dc(B22, new_size);
    free_matrix_dc(M1, new_size);  free_matrix_dc(M2, new_size);
    free_matrix_dc(M3, new_size);  free_matrix_dc(M4, new_size);
    free_matrix_dc(M5, new_size);  free_matrix_dc(M6, new_size);
    free_matrix_dc(M7, new_size);  free_matrix_dc(M8, new_size);
    free_matrix_dc(C11, new_size); free_matrix_dc(C12, new_size);
    free_matrix_dc(C21, new_size); free_matrix_dc(C22, new_size);

    return C;
}



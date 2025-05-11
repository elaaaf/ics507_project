#include "sequential_strassen.h"
#include "input_output_handeling.h"
#include <stdlib.h>

// Function to allocate submatrices for Strassen
long int*** allocate_submatrices(long int **A, long int **B, int n) {
    int new_size = n / 2;
    long int ***submatrices = malloc(8 * sizeof(long int **));

    for (int i = 0; i < 8; ++i) {
        submatrices[i] = allocate_matrix(new_size, new_size);
    }

    for (int i = 0; i < new_size; ++i) {
        for (int j = 0; j < new_size; ++j) {
            submatrices[0][i][j] = A[i][j]; // A11
            submatrices[1][i][j] = A[i][j + new_size]; // A12
            submatrices[2][i][j] = A[i + new_size][j]; // A21
            submatrices[3][i][j] = A[i + new_size][j + new_size]; // A22
            submatrices[4][i][j] = B[i][j]; // B11
            submatrices[5][i][j] = B[i][j + new_size]; // B12
            submatrices[6][i][j] = B[i + new_size][j]; // B21
            submatrices[7][i][j] = B[i + new_size][j + new_size]; // B22
        }
    }
    return submatrices;
}

// Function to combine the results into matrix C
void combine(long int **C, long int **M1, long int **M2, long int **M3, long int **M4, long int **M5, long int **M6, long int **M7, int new_size) {
    for (int i = 0; i < new_size; ++i) {
        for (int j = 0; j < new_size; ++j) {
            C[i][j] = M1[i][j] + M4[i][j] - M5[i][j] + M7[i][j];
            C[i][j + new_size] = M3[i][j] + M5[i][j];
            C[i + new_size][j] = M2[i][j] + M4[i][j];
            C[i + new_size][j + new_size] = M1[i][j] - M2[i][j] + M3[i][j] + M6[i][j];
        }
    }
}


// Function to add two matrices
long int** add(long int **A, long int **B, int n) {
    long int **result = allocate_matrix(n, n);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            result[i][j] = A[i][j] + B[i][j];
        }
    }
    return result;
}

// Function to subtract two matrices
long int** subtract(long int **A, long int **B, int n) {
    long int **result = allocate_matrix(n, n);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            result[i][j] = A[i][j] - B[i][j];
        }
    }
    return result;
}

long int** sequential_strassen(long int **A, long int **B, int n) {
    if (n == 1) {
        long int **C = allocate_matrix(1, 1);
        C[0][0] = A[0][0] * B[0][0];
        return C;
    }

    int new_size = n / 2;
    long int **C = allocate_matrix(n, n);

    // Allocate submatrices
    long int ***submatrices = allocate_submatrices(A, B, n);

    // Compute temporary matrices
    long int **temp1 = add(submatrices[0], submatrices[3], new_size); // A11 + A22
    long int **temp2 = add(submatrices[4], submatrices[7], new_size); // B11 + B22
    long int **M1 = sequential_strassen(temp1, temp2, new_size);

    // Free temporary matrices
    free_matrix(temp1, new_size);
    free_matrix(temp2, new_size);

    temp1 = add(submatrices[2], submatrices[3], new_size); // A21 + A22
    long int **M2 = sequential_strassen(temp1, submatrices[4], new_size);
    free_matrix(temp1, new_size);

    temp1 = subtract(submatrices[5], submatrices[7], new_size); // B12 - B22
    long int **M3 = sequential_strassen(submatrices[0], temp1, new_size);
    free_matrix(temp1, new_size);

    temp1 = subtract(submatrices[6], submatrices[4], new_size); // B21 - B11
    long int **M4 = sequential_strassen(submatrices[3], temp1, new_size);
    free_matrix(temp1, new_size);

    temp1 = add(submatrices[0], submatrices[1], new_size); // A11 + A12
    long int **M5 = sequential_strassen(temp1, submatrices[7], new_size);
    free_matrix(temp1, new_size);

    temp1 = subtract(submatrices[2], submatrices[0], new_size); // A21 - A11
    temp2 = add(submatrices[4], submatrices[5], new_size);      // B11 + B12
    long int **M6 = sequential_strassen(temp1, temp2, new_size);
    free_matrix(temp1, new_size);
    free_matrix(temp2, new_size);

    temp1 = subtract(submatrices[1], submatrices[3], new_size); // A12 - A22
    temp2 = add(submatrices[6], submatrices[7], new_size);      // B21 + B22
    long int **M7 = sequential_strassen(temp1, temp2, new_size);
    free_matrix(temp1, new_size);
    free_matrix(temp2, new_size);

    // Combine results to get final matrix C
    combine(C, M1, M2, M3, M4, M5, M6, M7, new_size);

    // Free intermediate results
    free_matrix(M1, new_size);
    free_matrix(M2, new_size);
    free_matrix(M3, new_size);
    free_matrix(M4, new_size);
    free_matrix(M5, new_size);
    free_matrix(M6, new_size);
    free_matrix(M7, new_size);

    // Free submatrices
    for (int i = 0; i < 8; ++i) {
        free_matrix(submatrices[i], new_size);
    }
    free(submatrices);

    return C;
}

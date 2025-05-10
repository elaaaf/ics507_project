#include "parallel_divide_conquer.h"
#include <stdio.h>
#include <stdlib.h>
#include <omp.h>


long int **allocate_matrix_pdc(int size) {
    long int **matrix = malloc(size * sizeof(long int *));
    for (int i = 0; i < size; i++) {
        matrix[i] = calloc(size, sizeof(long int));
    }
    return matrix;
}


void free_matrix_pdc(long int **matrix, int size) {
    for (int i = 0; i < size; i++)
        free(matrix[i]);
    free(matrix);
}


void add_matrix_pdc(long int **A, long int **B, long int **result, int size) {
    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++)
            result[i][j] = A[i][j] + B[i][j];
}


void subtract_matrix_pdc(long int **A, long int **B, long int **result, int size) {
    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++)
            result[i][j] = A[i][j] - B[i][j];
}


void copy_submatrix_pdc(long int **source, long int **dest, int row_offset, int col_offset, int size) {
    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++)
            dest[i][j] = source[i + row_offset][j + col_offset];
}


void set_submatrix_pdc(long int **dest, long int **source, int row_offset, int col_offset, int size) {
    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++)
            dest[i + row_offset][j + col_offset] = source[i][j];
}

long int** parallel_divide_conquer(long int **A, long int **B, int size) {
    long int **C = allocate_matrix_pdc(size);

    if (size == 1) { // Base case for recursion
        C[0][0] = A[0][0] * B[0][0];
        return C;
    }

    // Threshold for switching to sequential execution
    // This can be tuned for performance. If the size is too small,
    // the overhead of creating tasks might outweigh the benefits.
    // if (size <= 64) {
    //    return sequential_divide_conquer(A, B, size);
    // }


    int new_size = size / 2;

    // Allocate submatrices for A and B
    long int **A11 = allocate_matrix_pdc(new_size);
    long int **A12 = allocate_matrix_pdc(new_size);
    long int **A21 = allocate_matrix_pdc(new_size);
    long int **A22 = allocate_matrix_pdc(new_size);

    long int **B11 = allocate_matrix_pdc(new_size);
    long int **B12 = allocate_matrix_pdc(new_size);
    long int **B21 = allocate_matrix_pdc(new_size);
    long int **B22 = allocate_matrix_pdc(new_size);

    // Allocate submatrices for C
    long int **C11 = allocate_matrix_pdc(new_size);
    long int **C12 = allocate_matrix_pdc(new_size);
    long int **C21 = allocate_matrix_pdc(new_size);
    long int **C22 = allocate_matrix_pdc(new_size);

    // Temporary matrices for intermediate products
    long int **M1, **M2, **M3, **M4, **M5, **M6, **M7, **M8;

    // Parallel region for task creation
    // Only the main thread creates tasks initially
    // Tasks can then create more nested tasks if needed.
    #pragma omp parallel
    {
        #pragma omp single
        {
            // Fill submatrices Aij and Bij
            // These can be done in parallel if they are large enough, keep them sequential for now.
            // TODO parallelize the copy_submatrix function itself if beneficial.
            #pragma omp task
            copy_submatrix_pdc(A, A11, 0, 0, new_size);
            #pragma omp task
            copy_submatrix_pdc(A, A12, 0, new_size, new_size);
            #pragma omp task
            copy_submatrix_pdc(A, A21, new_size, 0, new_size);
            #pragma omp task
            copy_submatrix_pdc(A, A22, new_size, new_size, new_size);

            #pragma omp task
            copy_submatrix_pdc(B, B11, 0, 0, new_size);
            #pragma omp task
            copy_submatrix_pdc(B, B12, 0, new_size, new_size);
            #pragma omp task
            copy_submatrix_pdc(B, B21, new_size, 0, new_size);
            #pragma omp task
            copy_submatrix_pdc(B, B22, new_size, new_size, new_size);
            #pragma omp taskwait // Wait for all submatrix copies to complete


            // Recursive multiplications - these are the primary candidates for parallelism
            #pragma omp task shared(M1)
            M1 = parallel_divide_conquer(A11, B11, new_size);
            #pragma omp task shared(M2)
            M2 = parallel_divide_conquer(A12, B21, new_size);
            #pragma omp task shared(M3)
            M3 = parallel_divide_conquer(A11, B12, new_size);
            #pragma omp task shared(M4)
            M4 = parallel_divide_conquer(A12, B22, new_size);
            #pragma omp task shared(M5)
            M5 = parallel_divide_conquer(A21, B11, new_size);
            #pragma omp task shared(M6)
            M6 = parallel_divide_conquer(A22, B21, new_size);
            #pragma omp task shared(M7)
            M7 = parallel_divide_conquer(A21, B12, new_size);
            #pragma omp task shared(M8)
            M8 = parallel_divide_conquer(A22, B22, new_size);

            #pragma omp taskwait // Wait for all M_i multiplications to complete

            // Combine results: Cij = Mij + ...
            // These additions can also be parallelized.
            #pragma omp task
            add_matrix_pdc(M1, M2, C11, new_size); // C11 = M1 + M2
            #pragma omp task
            add_matrix_pdc(M3, M4, C12, new_size); // C12 = M3 + M4
            #pragma omp task
            add_matrix_pdc(M5, M6, C21, new_size); // C21 = M5 + M6
            #pragma omp task
            add_matrix_pdc(M7, M8, C22, new_size); // C22 = M7 + M8

            #pragma omp taskwait // Wait for Cij additions to complete
        } // End of single region
    } // End of parallel region


    // Combine result submatrices Cij into C
    // This can also be parallelized if new_size is large.
    set_submatrix_pdc(C, C11, 0, 0, new_size);
    set_submatrix_pdc(C, C12, 0, new_size, new_size);
    set_submatrix_pdc(C, C21, new_size, 0, new_size);
    set_submatrix_pdc(C, C22, new_size, new_size, new_size);

    // Free all allocated temporary matrices
    free_matrix_pdc(A11, new_size); free_matrix_pdc(A12, new_size);
    free_matrix_pdc(A21, new_size); free_matrix_pdc(A22, new_size);
    free_matrix_pdc(B11, new_size); free_matrix_pdc(B12, new_size);
    free_matrix_pdc(B21, new_size); free_matrix_pdc(B22, new_size);

    free_matrix_pdc(M1, new_size);  free_matrix_pdc(M2, new_size);
    free_matrix_pdc(M3, new_size);  free_matrix_pdc(M4, new_size);
    free_matrix_pdc(M5, new_size);  free_matrix_pdc(M6, new_size);
    free_matrix_pdc(M7, new_size);  free_matrix_pdc(M8, new_size);

    free_matrix_pdc(C11, new_size); free_matrix_pdc(C12, new_size);
    free_matrix_pdc(C21, new_size); free_matrix_pdc(C22, new_size);

    return C;
}


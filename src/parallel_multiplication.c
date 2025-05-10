#include "parallel_multiplication.h"
#include "input_output_handeling.h"

long int** parallel_multiplication(long int **A, long int **B, int n) {

    long int **C = allocate_matrix(n, n);


    #pragma omp parallel for collapse(2)
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            C[i][j] = 0;
        }
    }


    #pragma omp parallel for collapse(2)
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            for (int k = 0; k < n; k++) {
                #pragma omp atomic
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }

    return C;
}

#include "sequential_multiplication.h"
#include "random_matrix_generator.h"

long int** sequential_multiplication(long int **A, long int **B, int n) {

    long int **C = allocate_matrix(n, n);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            C[i][j] = 0;
        }
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            for (int k = 0; k < n; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }

    return C;
}

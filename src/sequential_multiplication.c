#include "sequential_multiplication.h"
#include "random_matrix_generator.h"

int** sequential_multiplication(int **A, int **B, int m, int p, int n) {

  int **C = allocate_matrix(m, n);

  for (int i =0; i < m; i++) {
    for (int j =0; j < n; j++) {
      C[i][j] = 0;
      for (int k =0; k < p; k++) {
	C[i][j] += A[i][k] * B[k][j];
      }
    }

  }
    return C;

}

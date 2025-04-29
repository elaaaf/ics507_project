#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "include/random_matrix_generator.h"
#include "include/sequential_multiplication.h"
#include "include/parallel_multiplication.h"
#include "include/sequential_divide_conquer.h"
#include "include/parallel_divide_conquer.h"
#include "include/sequential_strassen.h"

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <option>\n", argv[0]);
        printf("Options:\n");
        printf("  --seq-mul     : Sequential Multiplication Version\n");
        printf("  --par-mul     : Parallel Multiplication Version\n");
        printf("  --seq-dc      : Sequential Divide and Conquer Version\n");
        printf("  --par-dc      : Parallel Divide and Conquer Version\n");
        printf("  --strassen    : Sequential Strassen's Version\n");
        return 1;
    }

    srand(42);

    int m = 3, p = 4, n = 5, max_val = 10;

    int **A = allocate_matrix(m, p);
    int **B = allocate_matrix(p, n);

    generate_random_matrix(A, m, p, max_val);
    generate_random_matrix(B, p, n, max_val);
    
    printf("Matrix A:\n");
    print_matrix(A, m, p);
    printf("Matrix B:\n");
    print_matrix(B, p, n);
    printf("Matrix C:\n");

    if (strcmp(argv[1], "--seq-mul") == 0) {
        int **C = sequential_multiplication(A, B, m, p, n);
	print_matrix(C, m, n);
    } else if (strcmp(argv[1], "--par-mul") == 0) {
        parallel_multiplication(A, B, m, p, n);
    } else if (strcmp(argv[1], "--seq-dc") == 0) {
        sequential_divide_conquer(A, B, m, p, n);
    } else if (strcmp(argv[1], "--par-dc") == 0) {
        parallel_divide_conquer(A, B, m, p, n);
    } else if (strcmp(argv[1], "--strassen") == 0) {
        sequential_strassen(A, B, m, p, n);
    } else {
        printf("Invalid option: %s\n", argv[1]);
        printf("Current Options are: [--seq-mul, --par-mul, --seq-dc, --par-dc, --strassen]\n");
        return 1;
    }

    free_matrix(A, m);
    free_matrix(B, n);

    return 0;
}

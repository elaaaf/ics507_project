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

    const char *option = argv[1];
    int n;
    long int **A, **B;



    int mode;

    printf("Select Matrix Input Mode:\n");
    printf("1. Randomly Generated Matrices\n");
    printf("2. Read Matrices from File\n");
    printf("Enter choice (1 or 2): ");
    scanf("%d", &mode);
    
    if (mode == 1) {
    	srand(42);

    	int max_val = 1000;

        printf("Enter matrix size (must be power of 2): ");
        scanf("%d", &n);

        A = allocate_matrix(n, n);
        B = allocate_matrix(n, n);

	    //TODO: verify that n is a power of 2

    	generate_random_matrix(A, n, n, max_val);
    	generate_random_matrix(B, n, n, max_val);
    
    	printf("Matrix A:\n");
    	print_matrix(A, n, n);
    	printf("Matrix B:\n");
    	print_matrix(B, n, n);

    } else if  (mode == 2) {
	
        char filename[256];
        printf("Enter the input filename: ");
        scanf("%s", filename);

        read_matrix_from_file(filename, &A, &B, &n);

        printf("\nMatrix A:\n");
            print_matrix(A, n, n);

            printf("\nMatrix B:\n");
            print_matrix(B, n, n);


    } else {
        printf("Error: invalid mode");
        return 1;
    }

    printf("Matrix C:\n");

    if (strcmp(argv[1], "--seq-mul") == 0) {
        long int ** C = sequential_multiplication(A, B, n);
        print_matrix(C, n, n);
        free_matrix(C, n);
    } 
    /*else if (strcmp(argv[1], "--par-mul") == 0) {
        C = parallel_multiplication(A, B, n);
    } else if (strcmp(argv[1], "--seq-dc") == 0) {
        C = sequential_divide_conquer(A, B, n);
    } else if (strcmp(argv[1], "--par-dc") == 0) {
        C = parallel_divide_conquer(A, B, n);
    } else if (strcmp(argv[1], "--strassen") == 0) {
        C = sequential_strassen(A, B, n, n, n);
    } */else {
        printf("Invalid option: %s\n", argv[1]);
        printf("Current Options are: [--seq-mul, --par-mul, --seq-dc, --par-dc, --strassen]\n");
        return 1;
    }

    

    free_matrix(A, n);
    free_matrix(B, n);
    

    return 0;
}

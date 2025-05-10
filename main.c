#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <omp.h>

#include "include/input_output_handeling.h"
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
    printf("1. Generate Matrix File and Read\n");
    printf("2. Read Matrices from File (for debugging)\n");
    printf("Enter choice (1 or 2): ");
    scanf("%d", &mode);

    char filename[256];
    
    if (mode == 1) {
        printf("Enter matrix size (must be power of 2): ");
        scanf("%d", &n);

        // Set a filename for the generated matrix file
        sprintf(filename, "generated_matrix_%dx%d.txt", n, n);

        // Generate the matrix file
        generate_matrix_file(filename, n);

        // Read the matrices from the generated file
        read_matrix_from_file(filename, &A, &B, &n);

        // printf("\nMatrix A:\n");
        // print_matrix(A, n, n);

        // printf("\nMatrix B:\n");
        // print_matrix(B, n, n);

    } else if  (mode == 2) {
        printf("Enter the input filename: ");
        scanf("%s", filename);

        read_matrix_from_file(filename, &A, &B, &n);

        // printf("\nMatrix A:\n");
        // print_matrix(A, n, n);

        // printf("\nMatrix B:\n");
        // print_matrix(B, n, n);

    } else {
        printf("Error: invalid mode");
        return 1;
    }


    clock_t start, end;
    double time_taken;
    char output_filename[256];
    char time_filename[256];


    //printf("Matrix C:\n");

    if (strcmp(argv[1], "--seq-mul") == 0) {
        start = clock();
        long int ** C = sequential_multiplication(A, B, n);
        end = clock();

        time_taken = ((double)(end - start)) / CLOCKS_PER_SEC;

        char pattern[50];
        sprintf(pattern, "_%dx%d.txt", n, n); 
        char *filename_segment = replace(filename, pattern, "");

        sprintf(output_filename, "%s_%d_output_Sequential.txt", filename_segment, n);
        sprintf(time_filename, "%s_%d_info_Sequential.txt", filename_segment, n);

        write_output_to_file(output_filename, C, n);
        write_time_to_file(time_filename, time_taken);

        // print_matrix(C, n, n);
        free_matrix(C, n);

    } 
    else if (strcmp(argv[1], "--par-mul") == 0) {

        int num_threads = omp_get_max_threads();
        printf("Maximum OpenMP threads available: %d\n", num_threads);

        double start_time = omp_get_wtime();
        long int **C = parallel_multiplication(A, B, n);
        double end_time = omp_get_wtime();

        double time_taken = end_time - start_time;

        char pattern[50];
        sprintf(pattern, "_%dx%d.txt", n, n); 
        char *filename_segment = replace(filename, pattern, "");

        sprintf(output_filename, "%s_%d_output_ParallelP.txt", filename_segment, n);
        sprintf(time_filename, "%s_%d_info_ParallelP.txt", filename_segment, n);

        write_output_to_file(output_filename, C, n);
        write_time_to_file(time_filename, time_taken);

        // print_matrix(C, n, n);
        free_matrix(C, n);
        
    } /*else if (strcmp(argv[1], "--seq-dc") == 0) {
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

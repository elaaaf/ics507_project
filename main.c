#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "mmult/sequential_multiplication.h"
#include "mmult/parallel_multiplication.h"
#include "mmult/sequential_divide_conquer.h"
#include "mmult/parallel_divide_conquer.h"
#include "mmult/sequential_strassen.h"

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

    if (strcmp(argv[1], "--seq-mul") == 0) {
        sequential_multiplication();
    } else if (strcmp(argv[1], "--par-mul") == 0) {
        parallel_multiplication();
    } else if (strcmp(argv[1], "--seq-dc") == 0) {
        sequential_divide_conquer();
    } else if (strcmp(argv[1], "--par-dc") == 0) {
        parallel_divide_conquer();
    } else if (strcmp(argv[1], "--strassen") == 0) {
        sequential_strassen();
    } else {
        printf("Invalid option: %s\n", argv[1]);
        printf("Current Options are: [--seq-mul, --par-mul, --seq-dc, --par-dc, --strassen]\n");
        return 1;
    }

    return 0;
}

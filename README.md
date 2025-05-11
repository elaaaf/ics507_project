# ics507_project

## ICS507 Matrix Multiplication Project

This project implements multiple matrix multiplication techniques in C.


## Requirments

- gcc
- make
- build-essential

For Linux/WSL2 users:
```bash
sudo apt-get update
sudo apt-get install gcc make build-essential
```


## Compilation

To compile the project:
```bash
make
```

To clean up object files and binary:

```bash
make clean
```

## Usage

You will be prompted to select the mode for inputting the matrices:

1. Randomly Generated Matrices
This will generate matrices of a specified size filled with random values.

2. Read Matrices from File
You can provide a text file containing the matrices for multiplication. The file should contain the matrix size followed by the matrix values.

Run the compiled binary with the following flags:

```bash
./mxm --seq-mul       # Sequential Multiplication
./mxm --par-mul       # Parallel Multiplication
./mxm --seq-dc        # Sequential Divide and Conquer
./mxm --par-dc        # Parallel Divide and Conquer
./mxm --strassen      # Sequential Strassen's Algorithm
```



## Matrix File Format
When using the "Read Matrices from File" option, the input file should follow this format:

1. The first number is the matrix size n.
2. The next n x n numbers correspond to matrix A (in row-major order).
3. The following n x n numbers correspond to matrix B (in row-major order).

### Example of a valid matrix file:

```bash
4
1 2 3 4
1 2 2 0
0 0 3 3
1 0 1 1
1 0 0 0
0 3 3 0
0 1 1 1
1 1 1 1
```


## OPM Thread control
Change thread number before compilition with
```bash
 export OMP_NUM_THREADS=X
```

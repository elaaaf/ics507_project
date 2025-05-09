# ics507_project

## ICS507 Matrix Multiplication Project

This project implements multiple matrix multiplication techniques in C.


## Requirments

- gcc
- make
- build-essential

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

Run the compiled binary with the following flags:

```bash
./mxm --seq-mul       # Sequential Multiplication
./mxm --par-mul       # Parallel Multiplication
./mxm --seq-dc        # Sequential Divide and Conquer
./mxm --par-dc        # Parallel Divide and Conquer
./mxm --strassen      # Sequential Strassen's Algorithm
```

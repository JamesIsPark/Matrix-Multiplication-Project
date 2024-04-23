#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Function to perform matrix multiplication for 32-bit signed integers
int** matrix_multiply_int(int **A, int **B, int size) {
    int **C = (int **)malloc(size * sizeof(int *));
    for (int i = 0; i < size; i++)
        C[i] = (int *)malloc(size * sizeof(int));

    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            C[i][j] = 0;
            for (int k = 0; k < size; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }

    return C;
}

// Function to initialize a matrix with specified value
void init_matrix(int **matrix, int size, int value) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            matrix[i][j] = value;
        }
    }
}

// Function to measure wall-clock time for matrix multiplication
double measure_execution_time(int size, int **A, int **B) {
    clock_t start = clock();

    int **result = matrix_multiply_int(A, B, size);

    clock_t end = clock();
    double time_spent = ((double)(end - start)) / CLOCKS_PER_SEC;

    // Free memory
    for (int i = 0; i < size; i++) {
        free(result[i]);
    }
    free(result);

    return time_spent;
}

int main() {
    srand(time(NULL)); // Seed for randomization

    int sizes[] = {128, 256, 512}; // Sizes of matrices
    int num_sizes = sizeof(sizes) / sizeof(int);

    // Iterate over each size
    for (int s = 0; s < num_sizes; s++) {
        int size = sizes[s];
        printf("Matrix Size: %d\n", size);

        // Example multiplicand matrices
        int **A_int[] = {
            (int **)malloc(size * sizeof(int *)),
            (int **)malloc(size * sizeof(int *)),
            (int **)malloc(size * sizeof(int *))
        };

        // Example multiplier matrices
        int **B_int[] = {
            (int **)malloc(size * sizeof(int *)),
            (int **)malloc(size * sizeof(int *)),
            (int **)malloc(size * sizeof(int *))
        };

        // Initialize multiplicand and multiplier matrices
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < size; j++) {
                A_int[i][j] = (int *)malloc(size * sizeof(int));
                B_int[i][j] = (int *)malloc(size * sizeof(int));
            }
            if (i == 0) { // All elements 1
                init_matrix(A_int[i], size, 1);
                init_matrix(B_int[i], size, 1);
            } else if (i == 1) { // All elements 2
                init_matrix(A_int[i], size, 2);
                init_matrix(B_int[i], size, 1);
            } else { // Incrementing by row
                int val = 1;
                for (int row = 0; row < size; row++) {
                    for (int col = 0; col < size; col++) {
                        A_int[i][row][col] = val++;
                    }
                }
                init_matrix(B_int[i], size, 1);
            }
        }

        // Multiply matrices and measure execution time
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                double exec_time = measure_execution_time(size, A_int[i], B_int[j]);
                printf("Matrix A %d with Matrix B %d: Execution Time: %.2f seconds\n", i+1, j+1, exec_time);
            }
        }

        // Free memory for multiplier matrices
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < size; j++) {
                free(B_int[i][j]);
            }
            free(B_int[i]);
        }
    }

    return 0;
}


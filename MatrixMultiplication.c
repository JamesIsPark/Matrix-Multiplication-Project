#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Function to perform matrix multiplication for 32-bit signed integers
void matrix_multiply_int(int **A, int **B, int **C, int size) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            C[i][j] = 0;
            for (int k = 0; k < size; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

// Function to perform matrix multiplication for 64-bit floating point numbers
float** matrix_multiply_float(float **A, float **B, int size) {
    float **C = (float **)malloc(size * sizeof(float *));
    for (int i = 0; i < size; i++)
        C[i] = (float *)malloc(size * sizeof(float));

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
void init_matrix_int(int **matrix, int size, int value) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            matrix[i][j] = value;
        }
    }
}

void init_matrix_float(float **matrix, int size, float value) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            matrix[i][j] = value;
        }
    }
}

// Function to measure wall-clock time for matrix multiplication
double measure_execution_time_int(int size, int **A, int **B, int **C) {
    clock_t start = clock();

    matrix_multiply_int(A, B, C, size);

    clock_t end = clock();
    double time_spent = ((double)(end - start)) / CLOCKS_PER_SEC;

    return time_spent;
}

double measure_execution_time_float(int size, float **A, float **B) {
    clock_t start = clock();

    float **result = matrix_multiply_float(A, B, size);

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

        // Example multiplicand and multiplier matrices
        int **A_int[] = {
            (int **)malloc(size * sizeof(int *)),
            (int **)malloc(size * sizeof(int *)),
            (int **)malloc(size * sizeof(int *))
        };
        float **A_float[] = {
            (float **)malloc(size * sizeof(float *)),
            (float **)malloc(size * sizeof(float *)),
            (float **)malloc(size * sizeof(float *))
        };
        int **B_int[] = {
            (int **)malloc(size * sizeof(int *)),
            (int **)malloc(size * sizeof(int *)),
            (int **)malloc(size * sizeof(int *))
        };
        float **B_float[] = {
            (float **)malloc(size * sizeof(float *)),
            (float **)malloc(size * sizeof(float *)),
            (float **)malloc(size * sizeof(float *))
        };

        // Initialize multiplicand and multiplier matrices
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < size; j++) {
                A_int[i][j] = (int *)malloc(size * sizeof(int));
                A_float[i][j] = (float *)malloc(size * sizeof(float));
                B_int[i][j] = (int *)malloc(size * sizeof(int));
                B_float[i][j] = (float *)malloc(size * sizeof(float));
            }
            if (i == 0) { // All elements 1
                init_matrix_int(A_int[i], size, 1);
                init_matrix_float(A_float[i], size, 1.0f);
                init_matrix_int(B_int[i], size, 1);
                init_matrix_float(B_float[i], size, 1.0f);
            } else if (i == 1) { // All elements 2
                init_matrix_int(A_int[i], size, 2);
                init_matrix_float(A_float[i], size, 2.0f);
                init_matrix_int(B_int[i], size, 1);
                init_matrix_float(B_float[i], size, 1.0f);
            } else { // Incrementing by row
                int val = 1;
                for (int row = 0; row < size; row++) {
                    for (int col = 0; col < size; col++) {
                        A_int[i][row][col] = val;
                        A_float[i][row][col] = (float)val;
                        val++;
                    }
                }
                init_matrix_int(B_int[i], size, 1);
                init_matrix_float(B_float[i], size, 1.0f);
            }
        }

        // Multiply matrices and measure execution time for integers
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                int **result_int = (int **)malloc(size * sizeof(int *));
                for (int k = 0; k < size; k++)
                    result_int[k] = (int *)malloc(size * sizeof(int));

                double exec_time_int = measure_execution_time_int(size, A_int[i], B_int[j], result_int);
                printf("Matrix A %d with Matrix B %d (Int): Execution Time: %.2f seconds\n", i+1, j+1, exec_time_int);

                // Free memory for result matrix
                for (int k = 0; k < size; k++) {
                    free(result_int[k]);
                }
                free(result_int);
            }
        }

        // Multiply matrices and measure execution time for floats
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                double exec_time_float = measure_execution_time_float(size, A_float[i], B_float[j]);
                printf("Matrix A %d with Matrix B %d (Float): Execution Time: %.2f seconds\n", i+1, j+1, exec_time_float);
            }
        }

        // Free memory for matrices
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < size; j++) {
                free(A_int[i][j]);
                free(A_float[i][j]);
                free(B_int[i][j]);
                free(B_float[i][j]);
            }
            free(A_int[i]);
            free(A_float[i]);
            free(B_int[i]);
            free(B_float[i]);
        }
    }

    return 0;
}

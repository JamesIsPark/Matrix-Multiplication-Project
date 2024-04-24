#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

// Function to perform matrix multiplication for 32-bit signed integers
void matrix_multiply_int(int **A, int **B, int **C, int size) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            C[i][j] = 0;
            for (int k = 0; k < size; k++) {
                C[i][j] += A[i][k] * B[k][j]; // Multiply corresponding elements and accumulate in C
            }
        }
    }
}

// Function to perform matrix multiplication for 64-bit floating point numbers
float** matrix_multiply_float(float **A, float **B, int size) {
    // Allocate memory for the result matrix
    float **C = (float **)malloc(size * sizeof(float *));
    for (int i = 0; i < size; i++)
        C[i] = (float *)malloc(size * sizeof(float));

    // Perform matrix multiplication
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            C[i][j] = 0;
            for (int k = 0; k < size; k++) {
                C[i][j] += A[i][k] * B[k][j]; // Multiply corresponding elements and accumulate in C
            }
        }
    }

    return C; // Return the result matrix
}

// Function to initialize a matrix with specified value
void init_matrix_int(int **matrix, int size, int value) {
    // Loop through each element of the matrix and set it to the specified value
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            matrix[i][j] = value;
        }
    }
}

void init_matrix_float(float **matrix, int size, float value) {
    // Loop through each element of the matrix and set it to the specified value
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            matrix[i][j] = value;
        }
    }
}

// Function to measure wall-clock time for matrix multiplication using integers
double measure_execution_time_int(int size, int **A, int **B, int **C) {
    clock_t start = clock(); // Start the timer

    matrix_multiply_int(A, B, C, size); // Perform matrix multiplication

    clock_t end = clock(); // End the timer
    double time_spent = ((double)(end - start)) / CLOCKS_PER_SEC; // Calculate the elapsed time

    return time_spent; // Return the elapsed time
}

// Function to measure wall-clock time for matrix multiplication using floats
double measure_execution_time_float(int size, float **A, float **B) {
    clock_t start = clock(); // Start the timer

    float **result = matrix_multiply_float(A, B, size); // Perform matrix multiplication

    clock_t end = clock(); // End the timer
    double time_spent = ((double)(end - start)) / CLOCKS_PER_SEC; // Calculate the elapsed time

    // Free the memory allocated for the result matrix
    for (int i = 0; i < size; i++) {
        free(result[i]);
    }
    free(result);

    return time_spent; // Return the elapsed time
}

// Function to validate if the identity matrix is equal to the product of A and the identity matrix
bool validateIdentityMatrix(int size, int **A) {
    // Create identity matrix
    int **identityMatrix = (int **)malloc(size * sizeof(int *));
    for (int i = 0; i < size; i++) {
        identityMatrix[i] = (int *)malloc(size * sizeof(int));
    }

    // Fill identity matrix
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            identityMatrix[i][j] = (i == j) ? 1 : 0; // Identity matrix has 1s on diagonal
        }
    }

    // Allocate memory for the product matrix
    int **product = (int **)malloc(size * sizeof(int *));
    for (int i = 0; i < size; i++) {
        product[i] = (int *)malloc(size * sizeof(int));
    }

    // Multiply A with identity matrix
    matrix_multiply_int(A, identityMatrix, product, size);

    // Check if product equals A
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (product[i][j] != A[i][j]) {
                // Free memory
                for (int k = 0; k < size; k++) {
                    free(identityMatrix[k]);
                    free(product[k]);
                }
                free(identityMatrix);
                free(product);
                return false; // Return false if product does not match A
            }
        }
    }

    // Free memory
    for (int k = 0; k < size; k++) {
        free(identityMatrix[k]);
        free(product[k]);
    }
    free(identityMatrix);
    free(product);

    return true; // Return true if product matches A
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
        double totalExecTime = 0.0;

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

                // Accumulate total execution time
                totalExecTime += exec_time_int;
            }
        }

        // Multiply matrices and measure execution time for floats
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                double exec_time_float = measure_execution_time_float(size, A_float[i], B_float[j]);
                printf("Matrix A %d with Matrix B %d (Float): Execution Time: %.2f seconds\n", i+1, j+1, exec_time_float);

                // Accumulate total execution time
                totalExecTime += exec_time_float;
            }
        }

        // Validate identity matrix
        for (int i = 0; i < 3; i++) {
            if (validateIdentityMatrix(size, A_int[i])) {
                printf("Matrix A %d is equal to the product of A and the identity matrix.\n", i + 1);
            } else {
                printf("Matrix A %d is not equal to the product of A and the identity matrix.\n", i + 1);
            }
        }

        // Print average of the total execution time for the current matrix size
        double avgExecTime = totalExecTime / (3 * 6); // 3x3 operations, 6 total runs
        printf("Average of Total Execution Time for Size %d: %.2f seconds\n", size, avgExecTime);

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

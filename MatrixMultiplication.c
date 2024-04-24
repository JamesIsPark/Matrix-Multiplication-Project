#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

// Function to perform matrix multiplication for 32-bit signed integers
int** matrix_multiply_int(int **A, int **B, int **C, int size) {
    // Perform matrix multiplication
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            C[i][j] = 0;
            for (int k = 0; k < size; k++) {
                C[i][j] += A[i][k] * B[k][j]; // Multiply corresponding elements and accumulate in C
            }
        }
    }

    return C;
}

// Function to perform matrix multiplication for 64-bit floating point numbers
float** matrix_multiply_float(float **A, float **B, float **C, int size) {
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


// Function to measure wall-clock time for matrix multiplication using floats
double measure_execution_time_float(int size, float **A, float **B, float **C) {
    clock_t start = clock(); // Start the timer

    float **result = matrix_multiply_float(A, B, C, size); // Perform matrix multiplication

    clock_t end = clock(); // End the timer
    double time_spent = ((double)(end - start)) / CLOCKS_PER_SEC; // Calculate the elapsed time

    // Free the memory allocated for the result matrix
    for (int i = 0; i < size; i++) {
        free(result[i]);
    }
    free(result);

    return time_spent; // Return the elapsed time
}

// Function to measure wall-clock time for matrix multiplication using floats
double measure_execution_time_int(int size, int **A, int **B, int **C) {
    clock_t start = clock(); // Start the timer

    int **result = matrix_multiply_int(A, B, C, size); // Perform matrix multiplication

    clock_t end = clock(); // End the timer
    double time_spent = ((double)(end - start)) / CLOCKS_PER_SEC; // Calculate the elapsed time

    return time_spent; // Return the elapsed time
}


int main() {
    int sizes[] = {128, 256, 512}; // Sizes of matrices
    int num_sizes = sizeof(sizes) / sizeof(int);

    // Iterate over each size
    for (int s = 0; s < num_sizes; s++) {
        int size = sizes[s];
        printf("Matrix Size: %d\n", size);

        // Example multiplicand and multiplier matrices
        int ***A_int = (int ***)malloc(3 * sizeof(int **));
        float ***A_float = (float ***)malloc(3 * sizeof(float **));
        int ***B_int = (int ***)malloc(3 * sizeof(int **));
        float ***B_float = (float ***)malloc(3 * sizeof(float **));

        printf("Allocated memory for matrices\n");

        // Initialize multiplicand and multiplier matrices
        for (int i = 0; i < 3; i++) {
            A_int[i] = (int **)malloc(size * sizeof(int *));
            A_float[i] = (float **)malloc(size * sizeof(float *));
            B_int[i] = (int **)malloc(size * sizeof(int *));
            B_float[i] = (float **)malloc(size * sizeof(float *));
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
                init_matrix_int(B_int[i], size, 2);
                init_matrix_float(B_float[i], size, 2.0f);
            } else { // Incrementing by row
                for (int row = 0; row < size; row++) {
                    for (int col = 0; col < size; col++) {
                        A_int[i][row][col] = row;
                        A_float[i][row][col] = (float)row;
                        B_int[i][row][col] = (row == col) ? 1 : 0; // Identity matrix has 1s on diagonal
                        B_float[i][row][col] = (row == col) ? 1 : 0;
                    }
                }
            }
        }

        printf("Initialized matrices\n");

        // Multiply matrices and measure execution time for integers
        double totalExecTime_int = 0.0;
        double totalExecTime_float = 0.0;

        // Allocate memory for the result matrices
        int** result_int = (int**)malloc(size * sizeof(int*));
        if (result_int == NULL) {
            perror("Memory allocation failed");
            exit(EXIT_FAILURE);
        }

        for (int i = 0; i < size; i++) {
            result_int[i] = (int*)malloc(size * sizeof(int));
            if (result_int[i] == NULL) {
                perror("Memory allocation failed");
                exit(EXIT_FAILURE);
            }
        }

        float** result_float = (float**)malloc(size * sizeof(float*));
        if (result_float == NULL) {
            perror("Memory allocation failed");
            exit(EXIT_FAILURE);
        }

        for (int i = 0; i < size; i++) {
            result_float[i] = (float*)malloc(size * sizeof(float));
            if (result_float[i] == NULL) {
                perror("Memory allocation failed");
                exit(EXIT_FAILURE);
            }
        }

        printf("Allocated memory for result matrices\n");

        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                double exec_time_int = measure_execution_time_int(size, A_int[i], B_int[j], result_int);
                printf("Matrix A %d with Matrix B %d (Int): Execution Time: %.2f seconds\n", i+1, j+1, exec_time_int);

                double exec_time_float = measure_execution_time_float(size, A_float[i], B_float[j], result_float);
                printf("Matrix A %d with Matrix B %d (Float): Execution Time: %.2f seconds\n", i+1, j+1, exec_time_float);

                // Accumulate total execution time
                totalExecTime_int += exec_time_int;
                totalExecTime_float += exec_time_float;
            }
        }

        // Print average of the total execution time for the current matrix size
        double avgExecTime_int = totalExecTime_int / 9;
        double avgExecTime_float = totalExecTime_float / 9;
        printf("Average of Total int Execution Time for Size %d: %.2f seconds\n", size, avgExecTime_int);
        printf("Average of Total float Execution Time for Size %d: %.2f seconds\n", size, avgExecTime_float);

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

        // Free memory for result matrices
        for (int i = 0; i < size; i++) {
            free(result_int[i]);
            free(result_float[i]);
        }
        free(result_int);
        free(result_float);
    }

    return 0;
}

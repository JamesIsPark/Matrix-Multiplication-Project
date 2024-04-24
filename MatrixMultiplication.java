import java.io.*;

public class MatrixMultiplication {
    // Function to perform matrix multiplication for 32-bit signed integers
    public static int[][] matrixMultiply(int[][] A, int[][] B, int size) {
        int[][] C = new int[size][size];

        // Perform matrix multiplication
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
    public static void initMatrix(int[][] matrix, int size, int value) {
        // Set all elements of the matrix to the specified value
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                matrix[i][j] = value;
            }
        }
    }

    // Function to print a matrix to standard output
    public static void printMatrix(int[][] matrix, int size) {
        // Print each element of the matrix
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                System.out.print(matrix[i][j] + " ");
            }
            System.out.println();
        }
    }

    // Function to measure wall-clock time for matrix multiplication
    public static double measureExecutionTime(int size, int[][] A, int[][] B) {
        long startTime = System.nanoTime();

        // Perform matrix multiplication
        int[][] result = matrixMultiply(A, B, size);

        long endTime = System.nanoTime();
        double timeSpent = (endTime - startTime) / 1e9;

        return timeSpent;
    }

    // Function to validate if the identity matrix is equal to the product of A and the identity matrix
    public static boolean validateIdentityMatrix(int size, int[][] A) {
        int[][] identityMatrix = new int[size][size];

        // Create identity matrix
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                identityMatrix[i][j] = (i == j) ? 1 : 0; // Identity matrix has 1s on diagonal
            }
        }

        // Calculate the product of A and the identity matrix
        int[][] product = matrixMultiply(A, identityMatrix, size);

        // Check if product equals A
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                if (product[i][j] != A[i][j]) {
                    return false;
                }
            }
        }
        return true;
    }

    public static void main(String[] args) {
        int[] sizes = {128, 256, 512}; // Sizes of matrices

        int[] targetRuns = {1, 5, 10, 20}; // Target run numbers to print

        int precision = 100; // Precision for benchmark recording

        // Iterate over each size
        for (int size : sizes) {
            System.out.println("Matrix Size: " + size);

            double totalAvgExecTime = 0; // Total average execution time for the current matrix size

            // Example multiplicand matrices
            int[][][] A = new int[3][size][size];
            // Example multiplier matrices
            int[][][] B = new int[3][size][size];

            // Initialize multiplicand and multiplier matrices
            for (int i = 0; i < 3; i++) {
                for (int j = 0; j < size; j++) {
                    for (int k = 0; k < size; k++) {
                        A[i][j][k] = (i == 2) ? j * size + k + 1 : (i + 1);
                        B[i][j][k] = (i == 0) ? ((j == k) ? 1 : 0) : ((i == 1) ? 1 : 2); // Identity, all 1s, all 2s
                    }
                }
            }

            // Multiply matrices and measure execution time for multiple runs
            for (int run = 1; run <= 200; run++) { // Changed to run for 20 times
                if (run == 1 || run == 5 || run == 10 || run == 20) { // Check if the current run is in the target runs
                    double totalExecTime = 0; // Total execution time for the current matrix size

                    // Measure execution time
                    for (int i = 0; i < 3; i++) {
                        double execTime = measureExecutionTime(size, A[i], B[i]);
                        totalExecTime += execTime;
                    }

                    // Validation
                    boolean isValid = validateIdentityMatrix(size, A[0]);
                    System.out.println("Identity Matrix Validation Result: " + isValid);

                    // Calculate average execution time
                    double avgExecTime = totalExecTime / 3; // 3 (A) = 3
                    totalAvgExecTime += avgExecTime; // Add average execution time to the total

                    // Print benchmark recording
                    System.out.printf("Run %d: Average Execution Time: %.2f seconds\n", run, avgExecTime);
                }

                // Pause between runs to allow JIT optimization
                try {
                    Thread.sleep(100); // 100 milliseconds pause
                } catch (InterruptedException e) {
                    e.printStackTrace();
                }
            }

            // Calculate and print the average of the average execution time for the current matrix size
            double avgOfAvgExecTime = totalAvgExecTime / targetRuns.length;
            System.out.printf("Average of the Average Execution Time for Size %d: %.2f seconds\n", size, avgOfAvgExecTime);
        }
    }
}

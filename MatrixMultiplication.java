import java.util.Arrays;

public class MatrixMultiplication {
    
    // Function to perform matrix multiplication
    public static int[][] matrixMultiply(int[][] matrixA, int[][] matrixB, int size) {
        int[][] result = new int[size][size];
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                result[i][j] = 0;
                for (int k = 0; k < size; k++) {
                    result[i][j] += matrixA[i][k] * matrixB[k][j];
                }
            }
        }
        return result;
    }
        // Function to perform matrix multiplication
        public static float[][] matrixMultiply(float[][] matrixA, float[][] matrixB, int size) {
            float[][] result = new float[size][size];
            for (int i = 0; i < size; i++) {
                for (int j = 0; j < size; j++) {
                    result[i][j] = 0;
                    for (int k = 0; k < size; k++) {
                        result[i][j] += matrixA[i][k] * matrixB[k][j];
                    }
                }
            }
            return result;
        }

    // Function to measure wall-clock time for matrix multiplication
    public static double measureExecutionTime(int size, int[][] matrixA, int[][] matrixB, boolean isIdentityMatrix) {
        long startTime = System.currentTimeMillis();

        int[][] result = matrixMultiply(matrixA, matrixB, size);

        long endTime = System.currentTimeMillis();

        if (isIdentityMatrix) {
            if (!Arrays.deepEquals(matrixA, result)) {
                System.out.println("!Identity Test Failed!");
            }
        }

        double timeSpent = (endTime - startTime) / 1000.0;

        return timeSpent;
    }

    // Function to measure wall-clock time for matrix multiplication double
    public static double measureExecutionTime(int size, float[][] matrixA, float[][] matrixB, boolean isIdentityMatrix) {
        long startTime = System.currentTimeMillis();

        float[][] result = matrixMultiply(matrixA, matrixB, size);

        long endTime = System.currentTimeMillis();

        if (isIdentityMatrix) {
            if (!Arrays.deepEquals(matrixA, result)) {
                System.out.println("!Identity Test Failed!");
            }
        }

        double timeSpent = (endTime - startTime) / 1000.0;

        return timeSpent;
    }

    public static void main(String[] args) {
        int[] sizes = {128, 256, 512};

        for (int size : sizes) {
            System.out.printf("Benchmark for matrix size %d:%n", size);

            int[][][] matrixA = new int[3][size][size];
            float[][][] matrixA_float = new float[3][size][size];
            int[][][] matrixB = new int[3][size][size];
            float[][][] matrixB_float = new float[3][size][size];

            // Initialize matrixA
            for (int i = 0; i < 3; i++) {
                for (int j = 0; j < size; j++) {
                    for (int k = 0; k < size; k++) {
                        if (i == 0) {
                            matrixA[i][j][k] = 1;
                            matrixA_float[i][j][k] = 1;
                        } else if (i == 1) {
                            matrixA[i][j][k] = 2;
                            matrixA_float[i][j][k] = 2;
                        } else {
                            matrixA[i][j][k] = j + 1;
                            matrixA_float[i][j][k] = j + 1;
                        }
                    }
                }
            }

            // Initialize matrixB
            for (int i = 0; i < 3; i++) {
                for (int j = 0; j < size; j++) {
                    for (int k = 0; k < size; k++) {
                        if (i == 0) {
                            matrixB[i][j][k] = (j == k) ? 1 : 0; // Identity matrix
                            matrixB_float[i][j][k] = (j == k) ? 1 : 0; // Identity matrix
                        } else if (i == 1) {
                            matrixB[i][j][k] = 2; // All 2s
                            matrixB_float[i][j][k] = 2; // All 2s
                        } else {
                            matrixB[i][j][k] = 1; // All 1s
                            matrixB_float[i][j][k] = 1; // All 1s
                        }
                    }
                }
            }


            for(int run = 1; run <= 1000; run++){
                double totalExecTime_int = 0;
                double totalExecTime_float = 0;

                for (int i = 0; i < 3; i++) {
                    for (int j = 0; j < 3; j++) {
                        double execTime = measureExecutionTime(size, matrixA[i], matrixB[j], (j == 0));
                        totalExecTime_int += execTime;
                    }

                    for (int j = 0; j < 3; j++) {
                        double execTime = measureExecutionTime(size, matrixA_float[i], matrixB_float[j], (j == 0));
                        totalExecTime_float += execTime;
                    }
                }

                double avgExecTime_int = totalExecTime_int / 9;
                double avgExecTime_float = totalExecTime_float / 9;
                if (run % 100 == 0){
                    System.out.printf("Run: " + run + ". Average Int Execution Time: %.4f seconds%n", avgExecTime_int);
                    System.out.printf("Run: " + run + ". Average Float Execution Time: %.4f seconds%n%n", avgExecTime_float);
                }
            }
            
        }
    }
}

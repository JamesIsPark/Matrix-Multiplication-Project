import time
import numpy as np
# Optimized using Numpy
# Function to initialize the matrix with specified value
def initMatrix(matrix, size, value):
    for i in range(size):
        for j in range(size):
            matrix[i][j] = value
        # end for loop
    # end for loop
# end function

# Function to print matrix to standard output
def printMatrix(matrix, size):
    for i in range(size):
        for j in range(size):
            print(matrix[i][j] + " ")
        # end for loop
        print("\n")
    # end for loop
# end function

# Function to measure wall-clock time for matrix multiplication
def measureExecutionTime(size, matrixA, matrixB):
    start_time = time.time()

    result = np.multiply(matrixA, matrixB)

    end_time = time.time()
    time_spent = end_time - start_time

    return time_spent
# end function



def main():
    sizes = [128, 256, 512]

    numRuns = 20
    precision = 100 # for benchmarking recording

    # Iterate over each size
    for size in sizes:
        print("Matrix Size: " + str(size))

        # Example multiplicand matrices
        matrixA = [[[0 for _ in range(size)] for _ in range(size)] for _ in range(3)]
        # Example multiplier matrices
        matrixB = [[[0 for _ in range(size)] for _ in range(size)] for _ in range(3)]

        for i in range(3):
            for j in range(size):
                for k in range(size):
                    matrixA[i][j][k] = j * size + k + 1 if i == 2 else i + 1
                    matrixB[i][j][k] = 2 if i == 1 else 1
                # end for loop
            # end for loop
        # end for loop

        # Multiply matrices and measure execution time for multiple runs
        for run in range(1, numRuns + 1):
            total_exec_time = 0

            for i in range(3):
                for j in range(3):
                    exec_time = measureExecutionTime(size, matrixA[i], matrixB[j])
                    total_exec_time += exec_time

            # Calculate average execution time
            avg_exec_time = total_exec_time / 9  # 3 (A) * 3 (B) = 9

            # Print benchmark recording
            print("Run %d: Average Execution Time: %.2f seconds" % (run, avg_exec_time))

            # Pause between runs to allow JIT optimization
            time.sleep(0.1)  # 100 milliseconds pause
        # end for loop
    # enf for loop







# Needed to run the main function.
if __name__ == "__main__":
    main()
# end if

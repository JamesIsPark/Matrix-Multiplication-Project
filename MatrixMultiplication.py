import time
# Function to perform matrix multiplication
def matrixMultiply(matrixA, matrixB, size):
    result = [[0 for _ in range(size)] for _ in range(size)]
    for i in range(size):
        for j in range(size):
            result[i][j] = 0
            for k in range(size):
                result[i][j] += matrixA[i][k] * matrixB[k][j]
            # end for loop
        # end for loop
    # end for loop
    return result
# end function


# Function to measure wall-clock time for matrix multiplication
def measureExecutionTime(size, matrixA, matrixB, isIdentityMatrix):
    start_time = time.time()

    result = matrixMultiply(matrixA, matrixB, size)

    end_time = time.time()

    if(isIdentityMatrix):
        if(matrixA == result):
            print("!Identity Test Passed!")

    time_spent = end_time - start_time

    return time_spent
# end function


def main():
    sizes = [128, 256, 512]

    for size in sizes:
        print("Benchmark for matrix size %d:" % size)

        matrixA = [[[0 for _ in range(size)] for _ in range(size)] for _ in range(3)]
        matrixB = [[[0 for _ in range(size)] for _ in range(size)] for _ in range(3)]

        # Initialize matrixA
        for i in range(3):
            for j in range(size):
                for k in range(size):
                    if i == 0:
                        matrixA[i][j][k] = 1
                    elif i == 1:
                        matrixA[i][j][k] = 2
                    else:
                        matrixA[i][j][k] = j + 1

        # Initialize matrixB
        for i in range(3):
            for j in range(size):
                for k in range(size):
                    if i == 0:
                        matrixB[i][j][k] = 1 if j == k else 0  # Identity matrix
                    elif i == 1:
                        matrixB[i][j][k] = 2  # All 2s
                    else:
                        matrixB[i][j][k] = 1  # All 1s

        total_exec_time = 0

        for i in range(3):
            for j in range(3):
                exec_time = measureExecutionTime(size, matrixA[i], matrixB[j], isIdentityMatrix=True if i == 0 else False)
                total_exec_time += exec_time

        avg_exec_time = total_exec_time / 9

        print("Average Execution Time: %.4f seconds\n" % avg_exec_time)

if __name__ == "__main__":
    main()

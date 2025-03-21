#include <mpi.h>
#include <stdio.h>
#include <iostream>

#define MAX_N 10

void matrix_multiply(
    int *A, int *B, int *C, 
    int n, int rank, int size) {

    for (int i = rank; i < n; i += size) {
        for (int j = 0; j < n; j++) {
            C[i * n + j] = 0;
            for (int k = 0; k < n; k++) {
                C[i * n + j] += A[i * n + k] * B[k * n + j];
            }
        }
    }
    MPI_Allreduce(MPI_IN_PLACE, C, n * n, MPI_INT, MPI_SUM, MPI_COMM_WORLD);
}

int main(int argc, char *argv[]) {

    int rank, size, n;
    int A[MAX_N * MAX_N], 
        B[MAX_N * MAX_N], 
        C[MAX_N * MAX_N] = {0};

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (rank == 0) {
        printf("Enter the size of the matrix (n x n, n <= %d): ", MAX_N);
        std::cin >> n;

        printf("Enter the elements of matrix A (%d x %d):\n", n, n);
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                std::cin >> A[i * n + j];

        printf("Enter the elements of matrix B (%d x %d):\n", n, n);
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                std::cin >> B[i * n + j];
    }

    MPI_Bcast(&n, 1, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Bcast(A, n * n, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Bcast(B, n * n, MPI_INT, 0, MPI_COMM_WORLD);

    matrix_multiply(A, B, C, n, rank, size);

    if (rank == 0) {
        printf("Result matrix:\n");
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                printf("%d ", C[i * n + j]);
            }
            printf("\n");
        }
    }

    MPI_Finalize();
    return 0;
}

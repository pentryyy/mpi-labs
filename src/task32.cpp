#include <mpi.h>
#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>

int main(int argc, char *argv[]) {
    int rank, size;
    long long N = 0;
    double pi, local_sum = 0.0, step;

    if (MPI_Init(&argc, &argv) != MPI_SUCCESS) {
        fprintf(stderr, "Error initializing MPI.\n");
        return 1;
    }

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (rank == 0) {
        printf("Enter a number (calculation accuracy): ");
        
        if (!(std::cin >> N)) {
            fprintf(stderr, "Input error.\n");
            MPI_Abort(MPI_COMM_WORLD, 1);
        }

        if (N <= 0) {
            fprintf(stderr, "Error: N must be a positive number.\n");
            MPI_Abort(MPI_COMM_WORLD, 1);
        }
    }

    if (MPI_Bcast(&N, 1, MPI_LONG_LONG, 0, MPI_COMM_WORLD) != MPI_SUCCESS) {
        fprintf(stderr, "Error during MPI_Bcast.\n");
        MPI_Abort(MPI_COMM_WORLD, 1);
    }

    step = 1.0 / (double)N;

    double start_time = MPI_Wtime();

    #pragma omp parallel for reduction(+:local_sum) schedule(static)
    for (long long i = rank; i < N; i += size) {
        double x = (i + 0.5) * step;
        local_sum += 4.0 / (1.0 + x * x);
    }

    double global_sum = 0.0;
    if (MPI_Reduce(&local_sum, &global_sum, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD) != MPI_SUCCESS) {
        fprintf(stderr, "Error during MPI_Reduce.\n");
        MPI_Abort(MPI_COMM_WORLD, 1);
    }

    double end_time = MPI_Wtime();

    if (rank == 0) {
        pi = global_sum * step;
        printf("Calculated pi: %.8f\n", 
               pi);
        printf("Execution Time: %.6f seconds\n", 
               end_time - start_time);
    }

    MPI_Finalize();
    return 0;
}

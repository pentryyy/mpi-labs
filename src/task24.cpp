#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include <math.h>
#include <iostream>

int main(int argc, char *argv[]) {
    int    rank, size, N;
    long   local_in_circle = 0, total_in_circle = 0;
    double pi, start_time, end_time;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (rank == 0) {
        printf("Enter a number (calculation accuracy): ");
        std::cin >> N;
    }

    MPI_Bcast(&N, 1, MPI_INT, 0, MPI_COMM_WORLD);

    start_time = MPI_Wtime();

    srand(rank + 1);
    for (int i = 0; i < N / size; i++) {
        double x = (double)rand() / RAND_MAX;
        double y = (double)rand() / RAND_MAX;
        if (x * x + y * y <= 1) {
            local_in_circle++;
        }
    }

    if (rank == 0) {
        total_in_circle = local_in_circle;
        for (int i = 1; i < size; i++) {
            MPI_Recv(&local_in_circle, 1, MPI_LONG, i, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            total_in_circle += local_in_circle;
        }
        pi = 4.0 * total_in_circle / N;

        end_time = MPI_Wtime();

        printf("Calculated Pi: %.8f\n", pi);
        printf("Execution Time: %.6f seconds\n", end_time - start_time);
    } else {
        MPI_Send(&local_in_circle, 1, MPI_LONG, 0, 0, MPI_COMM_WORLD);
    }

    MPI_Finalize();
    return 0;
}

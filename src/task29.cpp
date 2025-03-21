#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <mpi.h>

double compute_pi(int N) {
    int count = 0;
    #pragma omp parallel for reduction(+:count)
    for (int i = 0; i < N; i++) {
        double x = (double)rand() / RAND_MAX;
        double y = (double)rand() / RAND_MAX;
        if (x * x + y * y <= 1.0) {
            count++;
        }
    }
    return (4.0 * count) / N;
}

int main(int argc, char* argv[]) {
    int rank, size;
    int N, threads;
    double local_pi, global_pi;
    double start_time, end_time;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    omp_set_num_threads(threads);

    if (rank == 0) {
        scanf("%d", &N);
        scanf("%d", &threads);
    }

    MPI_Bcast(&N, 1, MPI_INT, 0, MPI_COMM_WORLD);

    start_time = MPI_Wtime();

    local_pi = compute_pi(N / size);

    if (rank == 0) {
        global_pi = local_pi;
        double temp_pi;
        for (int i = 1; i < size; i++) {
            MPI_Recv(&temp_pi, 1, MPI_DOUBLE, i, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            global_pi += temp_pi;
        }
        global_pi /= size;
        end_time = MPI_Wtime();

        printf("Calculated pi: %.8f\n", global_pi);
        printf("Execution Time: %.6f seconds\n", end_time - start_time);
    } else {
        MPI_Send(&local_pi, 1, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD);
    }

    MPI_Finalize();
    return 0;
}

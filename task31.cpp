#include <stdio.h>
#include <mpi.h>
#include <omp.h>

int main(int argc, char *argv[]) {
    int n;
    int rank, size;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (rank == 0) {
        scanf("%d", &n);
    }

    MPI_Bcast(&n, 1, MPI_INT, 0, MPI_COMM_WORLD);

    int total_threads = n * size;

    #pragma omp parallel num_threads(n)
    {
        int thread_num = omp_get_thread_num();
        printf("I am %d thread from %d process. Number of hybrid threads = %d\n",
               thread_num, rank, total_threads);
    }

    MPI_Finalize();
    return 0;
}

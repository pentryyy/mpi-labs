#include <stdio.h>
#include <omp.h>
#include <mpi.h>

int main(int argc, char* argv[]) {
    int rank, size;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    printf("MPI process with %d rank from %d processes \n", rank, size);

    #pragma omp parallel
    {
        int thread_num = omp_get_thread_num();
        int threads_total = omp_get_num_threads();
        printf("MPI process %d: OpenMP stream %in from %in streams\n", rank, thread_num, threads_total);
    }

    MPI_Finalize();
    return 0;
}

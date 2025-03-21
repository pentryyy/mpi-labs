#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

int main(int argc, char *argv[]) {
    int rank, size, n;
    MPI_Comm intercomm;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (rank == 0) {
        scanf("%d", &n);
        
        MPI_Comm_spawn("executable/task27_child.exe", MPI_ARGV_NULL, n, MPI_INFO_NULL, 0, MPI_COMM_WORLD, &intercomm, MPI_ERRCODES_IGNORE);

        printf("I am %d process from %d processes!\nMy parent is none.\n", rank, size + n);
    }

    MPI_Finalize();
    return 0;
}

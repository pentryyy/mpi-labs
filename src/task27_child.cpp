#include <stdio.h>
#include <mpi.h>
#include <iostream>

int main(int argc, char *argv[]) {
    int rank, size, parent_rank;
    MPI_Comm parent_comm;

    MPI_Init(&argc, &argv);

    MPI_Comm_get_parent(&parent_comm);
    if (parent_comm == MPI_COMM_NULL) {
        fprintf(stderr, 
                "Error: The parent process was not found.\n");
        MPI_Abort(MPI_COMM_WORLD, 1);
    }

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    parent_rank = 0;

    printf("I am %d process from %d processes!\nMy parent is %d.\n", 
           rank, size, parent_rank);

    MPI_Finalize();
    return 0;
}

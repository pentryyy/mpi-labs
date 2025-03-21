#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    int rank, size;
    int message;

    MPI_Init(&argc, &argv);

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (size < 2) {
        printf("Необходимо минимум 2 процесса.\n");
        MPI_Finalize();
        return 0;
    }

    for (int i = 0; i < size; i++) {
        if (i != rank) {
            MPI_Send(&rank, 1, MPI_INT, i, 0, MPI_COMM_WORLD);
        }
    }

    for (int i = 0; i < size; i++) {
        if (i != rank) {
            MPI_Recv(&message, 1, MPI_INT, i, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            printf("[%d]: receive message '%d' from %d\n", rank, message, i);
        }
    }

    MPI_Finalize();

    return 0;
}

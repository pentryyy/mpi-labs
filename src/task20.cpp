#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    int rank, size;
    char message[100] = "45";

    
    MPI_Init(&argc, &argv);
    
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (size < 2) {
        printf("Необходимо минимум 2 процесса.\n");
        MPI_Finalize();
        return 0;
    }

    if (rank == 0) {
        
        MPI_Request request;
        MPI_Isend(message, 100, MPI_CHAR, 1, 0, MPI_COMM_WORLD, &request);

        
        MPI_Wait(&request, MPI_STATUS_IGNORE);
    } else if (rank == 1) {
        
        MPI_Request request;
        MPI_Status status;
        MPI_Irecv(message, 100, MPI_CHAR, 0, 0, MPI_COMM_WORLD, &request);

        MPI_Wait(&request, &status);

        printf("receive message '%s'\n", message);
    }

    MPI_Finalize();

    return 0;
}

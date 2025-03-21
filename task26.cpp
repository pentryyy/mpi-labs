#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

int main(int argc, char *argv[]) {
    int rank, size;
    char message[11];
    MPI_Comm new_comm;
    
    MPI_Init(&argc, &argv);
    
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    
    if (rank == 0) {
        scanf("%s", message);
    }
    
    if (rank % 2 == 0) {
        MPI_Comm_split(MPI_COMM_WORLD, 0, rank, &new_comm);
    } else {
        MPI_Comm_split(MPI_COMM_WORLD, MPI_UNDEFINED, rank, &new_comm);
    }
    
    if (rank % 2 == 0) {
        MPI_Bcast(message, 11, MPI_CHAR, 0, new_comm);
    }
    
    int new_rank, new_size;
    if (rank % 2 == 0) {
        MPI_Comm_rank(new_comm, &new_rank);
        MPI_Comm_size(new_comm, &new_size);
    } else {
        new_rank = -1;
        new_size = -1;
    }
    
    printf("MPI_COMM_WORLD: %d from %d. New comm: %d from %d. Message = %s\n", 
            rank, size, new_rank, new_size, message);
    
    if (rank % 2 == 0) {
        MPI_Comm_free(&new_comm);
    }
    
    MPI_Finalize();
    
    return 0;
}

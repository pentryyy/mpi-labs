#include <stdio.h>
#include <mpi.h>

int main(int argc, char** argv) {
    int rank, size;
    
    MPI_Init(&argc, &argv);
    
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    
    if (rank == 0) {
       
        for (int i = 1; i < size; i++) {
            int message;
            MPI_Recv(&message, 1, MPI_INT, i, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            printf("receive message '%d' from %d\n", message, i);
        }
    } else {
        MPI_Send(&rank, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
    }
    
    MPI_Finalize();
    
    return 0;
}

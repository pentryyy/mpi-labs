#include <mpi.h>
#include <iostream>

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);

    int world_size, world_rank;
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

    int message;
    
    if (world_rank == 0) {
        message = 3;

        MPI_Send(&message, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);
       
        MPI_Recv(&message, 1, MPI_INT, world_size - 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        std::cout << "[" << world_rank << "]: receive message '" << message << "'" << std::endl;
    } else {
        
        MPI_Recv(&message, 1, MPI_INT, world_rank - 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        message++;  
        std::cout << "[" << world_rank << "]: receive message '" << message - 1 << "'" << std::endl;
       
        if (world_rank != world_size - 1) {
            MPI_Send(&message, 1, MPI_INT, world_rank + 1, 0, MPI_COMM_WORLD);
        } else {
           
            MPI_Send(&message, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
        }
    }

    MPI_Finalize();
    return 0;
}

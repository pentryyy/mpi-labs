#include <mpi.h>
#include <iostream>

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);

    int size, rank;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    int message;
    
    if (rank == 0) {
        message = 0;

        MPI_Send(&message, 1, 
                 MPI_INT, 1, 0, MPI_COMM_WORLD);
        MPI_Recv(&message, 1, 
                 MPI_INT, size - 1, 0, MPI_COMM_WORLD, 
                 MPI_STATUS_IGNORE);

        std::cout << "[" 
                  << rank 
                  << "]: receive message '" 
                  << message 
                  << "'" 
                  << std::endl;
    } else {
        MPI_Recv(&message, 1, 
                 MPI_INT, rank - 1, 0, MPI_COMM_WORLD, 
                 MPI_STATUS_IGNORE);
        
        std::cout << "[" 
                  << rank 
                  << "]: receive message '" 
                  << message
                  << "'" 
                  << std::endl;

        message++;  
       
        if (rank != size - 1) {
            MPI_Send(&message, 1, 
                     MPI_INT, rank + 1, 0, MPI_COMM_WORLD);
        } else {
            MPI_Send(&message, 1, 
                     MPI_INT, 0, 0, MPI_COMM_WORLD);
        }
    }

    MPI_Finalize();
    return 0;
}

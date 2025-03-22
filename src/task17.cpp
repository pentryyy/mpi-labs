#include <iostream>
#include <cstring> 
#include <mpi.h>

int main(int argc, char* argv[]) {
    MPI_Init(&argc, &argv);

    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    if (rank == 0) {
        const char* message = "45";
        MPI_Send(message, strlen(message) + 1, 
                 MPI_CHAR, 1, 0, MPI_COMM_WORLD);
    } else if (rank == 1) {
        char message[100];
        MPI_Recv(message, 100, 
                 MPI_CHAR, 0, 0, MPI_COMM_WORLD, 
                 MPI_STATUS_IGNORE);
        std::cout << "receive message '" 
                  << message 
                  << "'" 
                  << std::endl;
    }

    MPI_Finalize();
    return 0;
}

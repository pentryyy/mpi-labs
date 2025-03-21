#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

#define ALPHABET_SIZE 26

int main(int argc, char *argv[]) {
    int rank, size;
    int n;
    char *str;
    int *counts = NULL;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    double start_time = MPI_Wtime();

    if (rank == 0) {
        
        scanf("%d", &n);
        str = (char*) malloc(n * sizeof(char));
        scanf("%s", str);
        counts = (int*) calloc(ALPHABET_SIZE, sizeof(int));

        MPI_Bcast(&n, 1, MPI_INT, 0, MPI_COMM_WORLD);
        MPI_Bcast(str, n, MPI_CHAR, 0, MPI_COMM_WORLD);
    } else {
        MPI_Bcast(&n, 1, MPI_INT, 0, MPI_COMM_WORLD);
        str = (char*) malloc(n * sizeof(char));
        MPI_Bcast(str, n, MPI_CHAR, 0, MPI_COMM_WORLD);
    }

    int local_count[ALPHABET_SIZE] = {0};
    for (int i = rank; i < n; i += size) {
        local_count[str[i] - 'a']++;
    }

    MPI_Reduce(local_count, counts, ALPHABET_SIZE, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

    if (rank == 0) {
        for (int i = 0; i < ALPHABET_SIZE; i++) {
            if (counts[i] > 0) {
                printf("%c = %d\n", i + 'a', counts[i]);
            }
        }

        free(str);
        free(counts);
    }

    double end_time = MPI_Wtime();

    if (rank == 0) {
        printf("Time taken: %f seconds\n", end_time - start_time);
    }

    MPI_Finalize();
    return 0;
}

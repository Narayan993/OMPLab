#include <mpi.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char **argv) {
    int rank, size;
    int data_to_broadcast;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (rank == 0) {  //root=0
        // Only the root process initializes the data
        data_to_broadcast = 123;
        printf("Process %d (root) is broadcasting the value: %d\n", rank, data_to_broadcast);
    }

    // All processes call MPI_Bcast to participate in the broadcast
    // The 'data_to_broadcast' variable will hold the received value for non-root processes
    MPI_Bcast(&data_to_broadcast, 1, MPI_INT, 0, MPI_COMM_WORLD);

    // All processes now have the broadcasted data
    printf("Process %d received the value: %d\n", rank, data_to_broadcast);

    MPI_Finalize();

    return 0;
}
#include <stdio.h>
#include <mpi.h>

int main(int argc, char *argv[]) {
    int rank, size;
    int data_send, data_recv;

    // Initialize the MPI environment
    MPI_Init(&argc, &argv);

    // Get the rank of the process and the total number of processes
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (size < 2) {
        if (rank == 0) {
            printf("This program requires atleast 2 processes.\n");
        }
        MPI_Finalize();
        return 0;
    }

    if (rank == 0) {
        // Process 0 waits for data from Process 1 first (altered sequence)
        MPI_Recv(&data_recv, 1, MPI_INT, 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        printf("Process 0 received data %d from Process 1\n", data_recv);

        // Then, Process 0 sends data to Process 1
        data_send = 100;
        printf("Process 0 is sending data %d to Process 1\n", data_send);
        MPI_Send(&data_send, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);
    }
    else if (rank == 1) {
        // Process 1 sends data first (altered sequence)
        data_send = 200;
        printf("Process 1 is sending data %d to Process 0\n", data_send);
        MPI_Send(&data_send, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);

        // Then, Process 1 waits for data from Process 0
        MPI_Recv(&data_recv, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        printf("Process 1 received data %d from Process 0\n", data_recv);
    }

    // Finalize the MPI environment
    MPI_Finalize();

    return 0;
}
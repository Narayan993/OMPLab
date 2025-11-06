#include <stdio.h>
#include <mpi.h>

int main(int argc, char *argv[]) {
    int rank, size;
    int number;
    
    // Initialize the MPI environment
    MPI_Init(&argc, &argv);
    
    // Get the rank of the process and the total number of processes
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    
    // Check if the number of processes is 2 (this example assumes 2 processes)
    if (size < 2) {
        if (rank == 0) {
            printf("This program requires atleast 2 processes.\n");
        }
        MPI_Finalize();
        return 0;
    }
    
    if (rank == 0) {
        // Process 0 sends a message
        number = 42;  // some data/number to send
        printf("Process 0 is sending number %d to Process 1\n", number);
        
        // Send the data to process 1
        MPI_Send(&number, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);
    } else if (rank == 1) {
        // Process 1 receives the message
        MPI_Recv(&number, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        printf("Process 1 received number %d from Process 0\n", number);
    }
    
    // Finalize the MPI environment
    MPI_Finalize();
    
    return 0;
}
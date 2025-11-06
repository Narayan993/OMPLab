#include <stdio.h>
#include <mpi.h>

int main(int argc, char** argv) {
    int rank, size;
    int senddat[4];
    int recdata;
    int gatherdata[4];
    int root = 0;    

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (size!=4) {
        if (rank==root)
            printf("Need more processes\n");
        MPI_Finalize();
        return 0;
    }

    if (rank == root) {
        for (int i=0; i<size; i++) {
            senddat[i] = i+1;
        }
        printf("Root process initialized data: ");
        for (int i = 0; i<size; i++) {
            printf("%d  ", senddat[i]);
        }
        printf("\n");
    }

    MPI_Scatter(senddat, 1, MPI_INT, &recdata, 1, MPI_INT, root, MPI_COMM_WORLD);
    recdata *= 2;
    MPI_Gather(&recdata, 1, MPI_INT, gatherdata, 1, MPI_INT, root, MPI_COMM_WORLD);

    if (rank == root) {
        printf("Root process gathered: ");
        for (int i = 0; i<size; i++) {
            printf("%d  ", gatherdata[i]);
        }
        printf("\n");
    }
    MPI_Finalize();

    return 0;
}

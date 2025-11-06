#include <stdio.h>
#include <mpi.h>

int main(int argc, char *argv[]){
    int rank, size;
    int min, max, sum, prod, all_min, all_max, all_sum, all_prod;
    
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int value = rank +1;

    MPI_Reduce(&value, &min, 1, MPI_CHAR, MPI_MIN, 0, MPI_COMM_WORLD);
    MPI_Reduce(&value, &max, 1, MPI_INT, MPI_MAX, 0, MPI_COMM_WORLD);
    MPI_Reduce(&value, &sum, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
    MPI_Reduce(&value, &prod, 1, MPI_INT, MPI_PROD, 0, MPI_COMM_WORLD);

    if(rank == 0){
        printf("Only process 0 has this\n");
        printf("Reduce value of Min: %d\n", min);
        printf("Reduce value of Max: %d\n", max);
        printf("Reduce value of Sum: %d\n", sum);
        printf("Reduce value of Prod: %d\n", prod);
    }

    MPI_Allreduce(&value, &all_min, 1, MPI_INT, MPI_MIN, MPI_COMM_WORLD);
    MPI_Allreduce(&value, &all_max, 1, MPI_INT, MPI_MAX, MPI_COMM_WORLD);
    MPI_Allreduce(&value, &all_sum, 1, MPI_INT, MPI_SUM, MPI_COMM_WORLD);
    MPI_Allreduce(&value, &all_prod, 1, MPI_INT, MPI_PROD, MPI_COMM_WORLD);
    

    printf("\nProcess %d has the output\n", rank);
    printf("AllReduce value of Min: %d\n", all_min);
    printf("AllReduce value of Max: %d\n", all_max);
    printf("AllReduce value of Sum: %d\n", all_sum);
    printf("AllReduce value of Prod: %d\n", all_prod);

    MPI_Finalize();
    return 0;

}



#include <stdio.h>
#include "mpi.h"

int main(int argc, char *argv[]){

	int np, rank, ierr;
    int i, n;

	ierr = MPI_Init(&argc , &argv);

	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &np);
    MPI_Status status;

    if(rank == 0){

        printf("enter num: ");
        scanf("%d",&n);
        
        for(i=1; i<=4 ; i++){
            MPI_Send(&n, 1, MPI_INT, i, i+1, MPI_COMM_WORLD);
        }
    }
    else if(rank == 1){
        MPI_Recv(&n, 1, MPI_INT, 0, 2, MPI_COMM_WORLD, &status);
        printf(" process %d : %d \n ", rank, n);
    }
    else if(rank == 2){
        MPI_Recv(&n, 1, MPI_INT, 0, 3, MPI_COMM_WORLD, &status);
        printf(" process %d : %d \n ", rank, n);
    }
    else if(rank == 3){
        MPI_Recv(&n, 1, MPI_INT, 0, 4, MPI_COMM_WORLD, &status);
        printf(" process %d : %d \n ", rank, n);
    }
    else if(rank == 4){
        MPI_Recv(&n, 1, MPI_INT, 0, 5, MPI_COMM_WORLD, &status);
        printf(" process %d : %d \n ", rank, n);
    }
    

	ierr = MPI_Finalize();

	return 0;
}
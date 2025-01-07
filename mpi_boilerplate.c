#include <stdio.h>
#include "mpi.h"

int main(int argc, char *argv[]){

	int np, rank, ierr;

	ierr = MPI_Init(&argc , &argv);

	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &np);

	if(rank){
		printf("Rank Exists\n");
	}

	ierr = MPI_Finalize();

	return 0;
}
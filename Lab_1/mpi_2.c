#include <stdio.h>
#include "mpi.h"

int main(int argc, char *argv[]){

	int np, rank, ierr;

	ierr = MPI_Init(&argc , &argv);

	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &np);

	if(rank%2 == 0){
		printf("Hello (my rank = %d)\n",rank);
	}
	else{
		printf("World (my rank = %d)\n",rank);
	}

	ierr = MPI_Finalize();

	return 0;
}
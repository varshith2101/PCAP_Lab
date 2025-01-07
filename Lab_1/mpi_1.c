#include <stdio.h>
#include "mpi.h"
#include <math.h>

int main(int argc, char *argv[]){

	int x = 5;
	int result;
	int np, rank, ierr;

	ierr = MPI_Init(&argc , &argv);

	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &np);

	if(rank){
		result = pow(x,rank);
		printf("%d\n", result);
	}

	ierr = MPI_Finalize();

	return 0;
}
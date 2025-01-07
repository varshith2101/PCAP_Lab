#include <stdio.h>
#include "mpi.h"
#include <string.h>

int main(int argc, char *argv[]){

	// a --> 97
	// A --> 65
	// Cap --> small => +32
	// Small --> Cap => -32

	char str[] = "vArSHiTh";

	int np, rank, ierr;

	ierr = MPI_Init(&argc , &argv);

	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &np);
		
	if(rank < 8){
		if(str[rank]<=96 && str[rank]>=65){
			str[rank]+=32;
		}
		else if(str[rank]>=97 && str[rank]<=122){
			str[rank]-=32;
		}

		printf("%s\n p-%d",str,rank);

	}	
	
	ierr = MPI_Finalize();
	return 0;
}


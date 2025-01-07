#include <stdio.h>
#include "mpi.h"


int fib(int a);
int fact(int a);


int main(int argc, char *argv[]){

	int np, rank, ierr;

	ierr = MPI_Init(&argc , &argv);

	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &np);

	if(rank%2 == 0){
		printf("process %d : %d\n", rank, fact(rank));
	}	
	else{
		printf("process %d : %d\n", rank, fib(rank));
	}
	

	ierr = MPI_Finalize();

	return 0;
}

int fact(int a){
	if(a==0){
		return 1;
	}
	return a*fact(a-1);
}

int fib(int a){
	int result,prev,prev_2;
	prev_2 = 0;
	prev = 1;
	if(a==0){
		return prev_2;
	}else if(a==1){
		return prev;
	}

	for (int i = 2; i < a; ++i)
	{
		result = prev + prev_2;
		prev_2 = prev;
		prev =  result;                           	
	}

	return result;
}
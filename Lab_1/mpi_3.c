#include <stdio.h>
#include "mpi.h"

int main(int argc, char *argv[]){

	int np, rank, ierr;
	int op1,op2,result;
	op1 = 19;
	op2 = 10;

	ierr = MPI_Init(&argc , &argv);

	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &np);

	switch(rank){
	case 0: printf("process 0 Add %d\n", (op1 + op2) );
		break;
	case 1: printf("process 1 Subtract %d\n", (op1 - op2) );
		break;
	case 2: printf("process 2 Multiply %d\n", (op1 * op2) );
		break;
	case 3: 
		if(op2==0){
			printf("process 3 Cant Divide, operand is zero %d\n", (op1 / op2) );
		}else{
			printf("process 3 Divide %d\n", (op1 / op2) );
		}
		break;
	case 4: printf("process 4 Modulo %d\n", (op1 % op2) );
		break;
	default : printf("Illegal process %d \n", rank);

	}

	ierr = MPI_Finalize();

	return 0;
}
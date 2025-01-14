#include <stdio.h>
#include "mpi.h"
#include <string.h>

#define MAX 50

char toggle(char c){
    if(c >=65 && c <= 90){
        c+=32;
    }
    else if(c >=97 && c <=122){
        c-=32;
    }

    return c;
}


int main(int argc, char *argv[]){

	int np, rank, ierr;
    char a[MAX];
    char b[MAX];


	ierr = MPI_Init(&argc , &argv);

	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &np);

    MPI_Status status;


	if(rank == 0){
		printf("send word: \n");
        scanf("%s",&a);

        MPI_Ssend(&a, MAX, MPI_CHAR, 1, 1, MPI_COMM_WORLD);

        printf("Sent out 'a' from process 0\n\n");

        MPI_Recv(&b, MAX, MPI_CHAR, 1, 2, MPI_COMM_WORLD, &status);

        printf("\nToggled word: %s\n",&b);
    }
    else{
        MPI_Recv(&a, MAX, MPI_CHAR, 0, 1, MPI_COMM_WORLD, &status);
        printf("recieved word %s\n", a);

        char temp = 'a';
        int i=0;

        while(temp != '\0'){
            temp = a[i];
            b[i] = toggle(temp);
            i++;
        }

        printf("sending toggled word...");
        MPI_Ssend(&b, MAX, MPI_CHAR, 0, 2, MPI_COMM_WORLD);
    }

	ierr = MPI_Finalize();

	return 0;
}
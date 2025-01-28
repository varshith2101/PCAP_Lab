#include <stdio.h>
#include <stdlib.h>
#include "mpi.h"

int fact(int n) {
    int result = 1;
    for (int i = 2; i <= n; i++) {
        result *= i;
    }
    return result;
}

int main(int argc, char* argv[]) {
    int rank, size, ierr;
    int mat[3][3], *recv_buffer;
    int occurences=0;
    int n;
    int local_count=0;
    int global_count=0;

    ierr = MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);


    if(rank==0){

        printf("enter 9 elements: \n ");
        for(int i=0;i<3;i++){
            for(int j=0;j<3;j++){
                scanf("%d",&mat[i][j]);
            }
        }

        printf("\nenter element to be found: ");
        scanf("%d", &n);
    }

    MPI_Bcast(&n,1,MPI_INT,0,MPI_COMM_WORLD);

    recv_buffer = (int*)malloc(3*sizeof(int));

    MPI_Scatter(mat,3,MPI_INT,recv_buffer,3,MPI_INT,0,MPI_COMM_WORLD);

    printf("Process %d received row: ", rank);

    for(int i=0;i<3;i++){
        printf("%d ", recv_buffer[i]);
        if(recv_buffer[i] == n){
            local_count++;
        }
    }
    printf("\n");


    MPI_Reduce(&local_count,&global_count,1,MPI_INT,MPI_SUM,0,MPI_COMM_WORLD);
    if(rank==0){
        printf("\n\nNo. of Occurences = %d\n",global_count);
    }
    free(mat);
    free(recv_buffer);

    ierr = MPI_Finalize();
    return 0;
}

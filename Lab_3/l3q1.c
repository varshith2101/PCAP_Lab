#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "mpi.h"

int fact(int n){
    if(n==1){
        return 1;
    }
    return n*fact(n-1);
}

int main(int argc, char* argv[]){

    int rank, size, ierr, num;
    
    ierr = MPI_Init(&argc,&argv);
    
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);
    MPI_Comm_size(MPI_COMM_WORLD,&size);
    
    int i=0;
    int arr[size];

    if(rank==0){
        printf("enter %d numbers : ", size);

        while(i<size){
            scanf("%d",&arr[i]);            
            i++;
        }    
    }

    MPI_Bcast(&arr, size, MPI_INT, 0, MPI_COMM_WORLD);

    printf("data recieved at P-%d is : %d\t",rank, arr[rank]);
    printf("factorial at p-%d is : %d\n",rank, fact(arr[rank]));

    ierr = MPI_Finalize();

    return 0;
}
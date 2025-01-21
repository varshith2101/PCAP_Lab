#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "mpi.h"



int main(int argc, char* argv[]){

    int rank, size, ierr, M;
    float *send = NULL;
    float *recv = NULL;
    float local_avg = 0;
    float global_sum = 0;
    
    ierr = MPI_Init(&argc,&argv);
    
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);
    MPI_Comm_size(MPI_COMM_WORLD,&size);
    

    if(rank==0){

        printf("enter M: ");
        scanf("%d",&M);
        
        send = (float*) malloc(M * size * sizeof(float));
        int i=0;

        printf("enter %d numbers : ", (M*size));

        while(i < (size*M)){
            scanf("%f",&send[i]);            
            i++;
        }    
    }

    MPI_Bcast(&M,1,MPI_INT,0,MPI_COMM_WORLD);
    recv = (float*) malloc(M*sizeof(float));

    MPI_Scatter(send, M, MPI_FLOAT, recv, M, MPI_FLOAT, 0, MPI_COMM_WORLD);


    int j=0;
    float local_sum=0;
    while(j < M){
        local_sum += recv[j];
        j++;
    }
    local_avg = local_sum/M;
    printf("%f\n",local_avg);
    printf("M: %d\n",M);

    MPI_Reduce(&local_avg,&global_sum,1,MPI_FLOAT,MPI_SUM,0,MPI_COMM_WORLD);


    if(rank == 0){
        printf("\nThe Sum of averages: %f\n", global_sum);

        free(send);
    }

    free(recv);

    ierr = MPI_Finalize();

    return 0;
}
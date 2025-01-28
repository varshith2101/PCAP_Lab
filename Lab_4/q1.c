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
    int N;
    int *arr, *send_buffer, *recv_buffer;
    int factsum_result = 0;

    ierr = MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    N = size;

    arr = (int*) malloc(N * sizeof(int));

    for (int i = 0; i < N; i++) {
        arr[i] = i + 1;
    }

    printf("Process : %d --> ",rank);
        for(int i=0;i<size;i++){
            printf("%d  ", arr[i]);
        }
        printf("\n");

    send_buffer = (int*) malloc(sizeof(int));  
    recv_buffer = (int*) malloc(sizeof(int));  

    *send_buffer = rank + 1;  

    MPI_Scan(send_buffer, recv_buffer, 1, MPI_INT, MPI_PROD, MPI_COMM_WORLD);

        printf("Process : %d --> ",rank);
        for(int i=0;i<size;i++){
            printf("%d  ", recv_buffer[i]);
        }
        printf("\n");
    

    MPI_Reduce(recv_buffer, &factsum_result, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

    if (rank == 0) {
        printf("The sum of factorials from 1! to %d! is: %d\n", N, factsum_result);
    }

    free(arr);
    free(send_buffer);
    free(recv_buffer);

    ierr = MPI_Finalize();
    return 0;
}

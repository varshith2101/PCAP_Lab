#include <stdio.h>
#include "mpi.h"
#include <stdlib.h>

int main(int argc, char *argv[]) {
    int np, rank, ierr, N;
    int *arr;
    int *buff;  // This will be the buffer for MPI_Bsend
    int buf_size;
    int i;

    ierr = MPI_Init(&argc , &argv);

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &np);
    MPI_Status status;

    if (rank == 0) {
        // Process 0: Take input for N integers
        printf("Enter the number of elements (N): ");
        scanf("%d", &N);

        // Dynamically allocate memory for the array
        arr = (int *)malloc(N * sizeof(int));

        printf("Enter %d integers:\n", N);
        for (i = 0; i < N; i++) {
            printf("Enter element %d: ", i + 1);
            scanf("%d", &arr[i]);
        }

        // Calculate buffer size needed for the buffered send
        buf_size = N * sizeof(int) + MPI_BSEND_OVERHEAD;

        // Allocate buffer for the buffered send
        buff = (int *)malloc(buf_size);

        // Attach the buffer to MPI
        MPI_Buffer_attach(buff, buf_size);

        // Send each element to the corresponding process
        for (i = 1; i < np; i++) {
            // Check if there are enough elements to send to each process
            if (i <= N) {
                MPI_Bsend(&arr[i-1], 1, MPI_INT, i, 0, MPI_COMM_WORLD);
            }
        }

        // Free the allocated array and buffer
        free(arr);
        free(buff);

    } else {
        // Process 1 to np-1: Receive the integer and process it
        int received_value;
        
        // Receive the data sent by Process 0
        MPI_Recv(&received_value, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, &status);

        // Print square or cube depending on whether the rank is even or odd
        if (rank % 2 == 0) {
            // Even-ranked process: print square
            printf("Process %d (Even): Square of %d = %d\n", rank, received_value, received_value * received_value);
        } else {
            // Odd-ranked process: print cube
            printf("Process %d (Odd): Cube of %d = %d\n", rank, received_value, received_value * received_value * received_value);
        }
    }

    ierr = MPI_Finalize();
    return 0;
}

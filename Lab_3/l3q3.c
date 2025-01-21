#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mpi.h"

int isVowel(char c){
    if(c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u'){
        return 1;
    }
    return 0;
}

int main(int argc, char* argv[]){

    int rank, size, ierr;
    char str[50];
    int total;
    
    ierr = MPI_Init(&argc,&argv);
    
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);
    MPI_Comm_size(MPI_COMM_WORLD,&size);


    

    if(rank==0){
        printf("Enter the String: ");
        scanf("%s",&str);
    }

    MPI_Bcast(str, 50, MPI_CHAR, 0, MPI_COMM_WORLD);

    int local_size = strlen(str)/size;
    char* recv = (char*)malloc((local_size+1) * sizeof(char));

    MPI_Scatter(str, local_size, MPI_CHAR, recv, local_size, MPI_CHAR, 0, MPI_COMM_WORLD);

    int i=0;
    int local_count=0;
    while(i<local_size){
        if(isVowel(recv[i])){
            local_count++;
        }
        i++;
    }


    MPI_Reduce(&local_count, &total, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

    
    printf("No. of vowels in P-%d: %d\n",rank, local_count);

    if(rank==0){
        printf("Total no. of vowels in the String: %d\n",total);
    }
    
    free(recv);
    ierr = MPI_Finalize();

    return 0;
}
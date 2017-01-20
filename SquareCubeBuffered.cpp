#include "mpi.h"
#include <stdio.h>
#include<stdlib.h>
#include <string.h>

int main(int argc,char* argv[]){
	int rank,size;
	MPI_Status status;
	int len;
	MPI_Init(&argc,&argv);
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	MPI_Comm_size(MPI_COMM_WORLD,&size);
	int *buffer=(int *)calloc(20,sizeof(int));
	MPI_Buffer_attach(buffer,20*sizeof(int));
	if(rank==0){
		int i=0;
		int arr[10];
		for(i=0;i<size;i++)
			scanf_s("%d",&arr[i]);
		for(i=1;i<size;i++)
			MPI_Bsend(&arr[i],1,MPI_INT,i,1,MPI_COMM_WORLD);
		printf("\nRank = %d : Square = %d",rank,arr[0]*arr[0]);
	}
	else{
		int a;
		MPI_Recv(&a,1,MPI_INT,0,1,MPI_COMM_WORLD,&status);
			if(rank%2==0)
				printf("\nRank = %d : Square = %d",rank,a*a);
			else
				printf("Rank = %d : Cube = %d",rank,a*a*a);
	}
	MPI_Buffer_detach(buffer,&len);
	MPI_Finalize();
	return 0;
}
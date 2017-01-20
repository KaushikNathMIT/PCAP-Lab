#include "mpi.h"
#include<stdio.h>
#include<string.h>

int main(int argc, char *argv[])
{
	int arr[50];
	int rank;
	MPI_Init(&argc, &argv);
	MPI_Status status;
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	
	if (rank==0)
	{
		int n=0;
		fprintf(stdout, "Enter the number of numbers to be sent: ");
		fflush(stdout);
		scanf("%d", &n);
		fprintf(stdout, "Enter the numbers to be sent: ");
		fflush(stdout);
		for(int i=0;i<n;i++){
			scanf("%d", &arr[i]);
		}
		fprintf(stdout, "input taken: ");
		fflush(stdout);
		//MPI_Ssend(&n, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);
		for(int i=0; i<n; i++){
			MPI_Ssend(&arr[i], 1, MPI_INT, i+1, 0, MPI_COMM_WORLD);	
		}
	}
	else
	{
		int val=0;
		MPI_Recv(&val, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, &status);
		printf("%d\n", val);
	}
	MPI_Finalize();
	
	return 0;
}
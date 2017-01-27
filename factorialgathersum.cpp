#include "mpi.h"
#include<stdio.h>
#include<stdlib.h>

int main(int argc, char* argv[])
{
	int rank, size, recieved;
	int arr[100], factRecieved[100];
	MPI_Init(&argc,&argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);

	if (rank==0)
	{
		fprintf(stdout, "Enter %d numbers", size);
		fflush(stdout);

		for (int i=0; i<size; i++) scanf("%d", &arr[i], 1);
	}

	MPI_Scatter(arr, 1, MPI_INT, &recieved, 1, MPI_INT, 0, MPI_COMM_WORLD);

	int fact=1;

	for (int i=1; i<=recieved; i++)
		fact=fact*i;

	fprintf(stdout, "Factorial of %d = %d (Process %d)\n", recieved, fact, rank);
	fflush(stdout);
	MPI_Gather(&fact, 1, MPI_INT, &factRecieved, 1, MPI_INT, 0, MPI_COMM_WORLD);
	int sum=0;
	if (rank==0)
	{
		 for (int i=0; i<size; i++)
			 sum+=factRecieved[i];

		 fprintf(stdout,"The sum of all factorials is (Process %d) : %d\n", rank, sum);
		 fflush(stdout);
	}

	MPI_Finalize();

	return 0;
}
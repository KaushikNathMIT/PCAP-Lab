#include "mpi.h"
#include<stdio.h>

int main(int argc, char * argv[])
{
	int rank, size;
	MPI_Init(&argc, &argv);
	MPI_Status status;
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);

	if (rank==0)
	{
		int num;
		fprintf(stdout,"Enter a number : ");
		fflush(stdout);
		scanf("%d",&num);
		num++;
		MPI_Send(&num, 1, MPI_INT, rank+1, rank, MPI_COMM_WORLD);
		fprintf(stdout, "\nNumber sent by process %d is %d.\n", rank, num);
		fflush(stdout);
		MPI_Recv(&num, 1, MPI_INT, size-1, size-1, MPI_COMM_WORLD, &status);
		fprintf(stdout,"Number received by process %d is %d.\n", rank, num);
		fflush(stdout);
	}

	else
	{
		int num1;
		MPI_Recv(&num1, 1, MPI_INT, rank-1, rank-1, MPI_COMM_WORLD, &status);
		fprintf(stdout,"Number received by process %d is %d.\n", rank, num1);
		fflush(stdout);
		num1++;
		MPI_Send(&num1, 1, MPI_INT, (rank+1)%size, rank, MPI_COMM_WORLD);
		fprintf(stdout, "Number sent by process %d is %d.\n", rank, num1);
		fflush(stdout);
	}

	MPI_Finalize();
	return 0;
}
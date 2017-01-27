#include "mpi.h"
#include<stdio.h>
#include<stdlib.h>

int main(int argc, char* argv[])
{
	int rank, size; int num_rec;
	int num[100];
	MPI_Init(&argc,&argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);

	if (rank==0)
	{
		fprintf(stdout, "Enter %d numbers", size);
		fflush(stdout);

		for (int i=0; i<size; i++) scanf("%d", &num[i], 1);
	}

	MPI_Scatter(num, 1, MPI_INT, &num_rec, 1, MPI_INT, 0, MPI_COMM_WORLD);

	int fact=1;

	for (int i=1; i<=num_rec; i++)
		fact=fact*i;

	fprintf(stdout, "Factorial of %d = %d , rank = %d\n", num_rec, fact, rank);
	fflush(stdout);

	MPI_Finalize();

	return 0;
}
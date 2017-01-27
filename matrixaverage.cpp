#include "mpi.h"
#include<stdio.h>

int main(int argc, char * argv[])
{
	int rank, size,m, a1[50], b1[50], s=0;
	float average, c[50], s1=0, average1;
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);

	if (rank==0)
	{
		fprintf(stdout, "Enter M : ");
		fflush(stdout);
		scanf("%d", &m);
		int totalSize = size*m;
		for (int i=0; i<totalSize; i++)
			scanf("%d",&a1[i]);
	}
	MPI_Bcast(&m, 1, MPI_INT, 0, MPI_COMM_WORLD);

	MPI_Scatter(a1, m, MPI_INT, b1, m, MPI_INT, 0, MPI_COMM_WORLD);

	for (int i=0; i<m; i++)
			s+=b1[i];
	
	average=(float)s/m;

	fprintf(stdout,"The average in Process %d is : %f\n", rank, average);
	fflush(stdout);
	
	MPI_Gather(&average, 1, MPI_FLOAT, c, 1, MPI_FLOAT, 0, MPI_COMM_WORLD);
	
	if (rank==0)
	{
		for (int i=0; i<size; i++)
			s1+=c[i];
		
		fprintf(stdout,"The sum of all averages is (from Process %d) : %f\n", s1, rank);
		fflush(stdout);
	}

	MPI_Finalize();
	return 0;
}
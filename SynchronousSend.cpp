#include "mpi.h"
#include<stdio.h>
#include<string.h>

int main(int argc, char *argv[])
{
	char c[30];
	int rank, len;
	MPI_Init(&argc, &argv);
	MPI_Status status;
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	
	if (rank==0)
	{
		fprintf(stdout, "Enter the word to be sent: ");
		fflush(stdout);
		scanf("%s",c);
		len=strlen(c);				
		MPI_Ssend(&len, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);
		MPI_Ssend(c, len, MPI_CHAR, 1, 1, MPI_COMM_WORLD);
		MPI_Recv(c, len, MPI_CHAR, 1, 2, MPI_COMM_WORLD, &status);
		c[len]='\0';
		printf("Result is %s", c);
	}
	else
	{
		MPI_Recv(&len, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, &status);
		MPI_Recv(c, len, MPI_CHAR, 0, 1, MPI_COMM_WORLD, &status);

		for (int i=0; i<len; i++)
		{
			if(c[i]>=97)
				c[i]=c[i]-32;
			else
				c[i]=c[i]+32;
		}

		MPI_Ssend(c, len, MPI_CHAR, 0, 2, MPI_COMM_WORLD);
	}
	MPI_Finalize();
	
	return 0;
}
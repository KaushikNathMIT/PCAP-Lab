#include"mpi.h"
#include<stdio.h>
#include<string.h>

int main(int argc,char *argv[])
{
	 int rank,size,i,j,m,n;
	 char S1[100],S2[100],c1[100],c2[100];
	 char b[100];

	 MPI_Init(&argc,&argv);
	 MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	 MPI_Comm_size(MPI_COMM_WORLD,&size);

	if(rank==0)
	{
		n=size;
		fprintf(stdout, "\n enter the strings one by one : ");
		fflush(stdout);
		scanf("%s", S1);
		scanf("%s", S2);
		m=strlen(S1)/n;
	}

	MPI_Bcast(&m,1,MPI_INT,0,MPI_COMM_WORLD);
	MPI_Scatter(S1,m,MPI_CHAR,&c1,m,MPI_CHAR,0,MPI_COMM_WORLD);
	MPI_Scatter(S2,m,MPI_CHAR,&c2,m,MPI_CHAR,0,MPI_COMM_WORLD);

	for(i=m,j=0;j<m;i++,j++)
		c1[i]=c2[j];
	c2[j]='\0';

	
	c1[2*m] = '\0';
	
	
	fprintf(stdout, "%s", c1);
	fflush(stdout);
	//fprintf(stdout, "%s", c2);
	//fflush(stdout);
	
	MPI_Gather(c1,2*m,MPI_CHAR,b,2*m,MPI_CHAR,0,MPI_COMM_WORLD);

	if(rank==0)
	{
		b[strlen(S1) + strlen(S2)] = '\0';
		fprintf(stdout, "\n%s", b);
		fflush(stdout);
	}
	
	MPI_Finalize();
	return 0;
}
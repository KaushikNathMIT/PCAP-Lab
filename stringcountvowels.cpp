#include"mpi.h"
#include<stdio.h>
#include<string.h>

int main(int argc,char *argv[])
{
	 int rank,size,i,j,m,n,count;
	 char a[100],c[100];
	 int b[100];
	 MPI_Init(&argc,&argv);
	 MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	 MPI_Comm_size(MPI_COMM_WORLD,&size);
	 if(rank==0)
	 {
		n=size;
		printf("\nEnter String : ");
		scanf("%s", a);
		m=strlen(a)/n;
	 }

	 MPI_Bcast(&m,1,MPI_INT,0,MPI_COMM_WORLD);
	 MPI_Scatter(a,m,MPI_CHAR,&c,m,MPI_CHAR,0,MPI_COMM_WORLD);
	 count=0;
	 
	 for(i=0;i<m;i++)
	 {
		if(c[i]!='a'&&c[i]!='e'&&c[i]!='i'&&c[i]!='o'&&c[i]!='u'&&c[i]!='A'&&c[i]!='E'&&c[i]!='I'&&c[i]!='O'&&c[i]!='U')
			count++;

	 }
	 
	 
	 c[m]='\0';
	 printf("\nString : %s", c);
	 printf("\nNumber of vowels = %d", count);

 	 MPI_Gather(&count,1,MPI_INT,b,1,MPI_INT,0,MPI_COMM_WORLD);
	
	 if(rank==0)
	 {
		int av=0;
		for(i=0;i<n;i++)
			av=av+b[i];
		printf("\n\nTotal Count of NON-VOWELS: %d", av);
	 }
	
	 MPI_Finalize();
	 return 0;
}
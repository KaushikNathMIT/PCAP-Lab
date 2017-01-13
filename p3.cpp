#include"mpi.h"
#include<stdio.h>
#include<stdlib.h>

int main(int argc,char *argv[]){
	int rank,size,a,b;
	a = atoi(argv[1]);
	b = atoi(argv[2]);
	MPI_Init(&argc,&argv);
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	MPI_Comm_size(MPI_COMM_WORLD,&size);
	if(rank==0) printf(" SUM = %d", a+b);
	else if(rank==1) printf(" DIFFERENCE = %d", a-b);
	else if(rank==2) printf(" PRODUCT = %d", a*b);
	else if(rank==3) printf(" QUOTIENT = %d", a/b);
	MPI_Finalize();
	return 0;
}

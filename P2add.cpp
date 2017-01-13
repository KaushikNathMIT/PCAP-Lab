#include "mpi.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>


bool isPrime(int n){
	if(n==0 || n==1) return false;
	for(int i=2;i<=pow(n,0.5);i++){
		if(n%i == 0) return false;
	}
	return true;
}

int main(int argc, char *argv[]) {
	int rank, size, z;
	//z = atoi(argv[1]);
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	if(rank ==0) {
		for(int i=0;i<50;i++){
			if(isPrime(i)) printf("\nrank : %d : %d", rank,i);
		}
	}
	if(rank ==1) {
		for(int i=50;i<100;i++){
			if(isPrime(i)) printf("\nrank : %d : %d", rank,i);
		}
	}
	MPI_Finalize();
	return 0;
}
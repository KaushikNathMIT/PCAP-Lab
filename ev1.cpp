#include "mpi.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

bool isPerfectSquare(int x)
{
    int s = pow(x,0.5);
    return (s*s == x);
}
 
bool isFibonacci(int n)
{
    return isPerfectSquare(5*n*n + 4) ||
           isPerfectSquare(5*n*n - 4);
}

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
	if(isPrime(rank)) {
		printf("\nHello : rank = %d", rank);
	}
	if(isFibonacci(rank)){
		printf("\nWorld : rank = %d", rank);
	}
	MPI_Finalize();
	return 0;
}
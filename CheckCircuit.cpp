#include "mpi.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void check_circuit(int z, int rank) {
	int v[5], i;
	for(i=0;i<5;i++) {
		v[i] = (z & ( 1 << i )) >> i;
	}
	if(v[0] || v[1] && ((v[2]&&v[3])&& !v[4])) {
		printf("\nrank %d :", rank);
		for(i=0;i<5;i++){
			printf(" %d", v[i]);
		}
	}
}

int main(int argc, char *argv[]) {
	int rank, size, z;
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	for(z=rank;z<32;z=z+size) check_circuit(z, rank);
	MPI_Finalize();
}
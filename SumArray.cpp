#include "mpi.h"
#include<stdio.h>
#include<string.h>

int main(int argc, char *argv[])
{
	int rank;
	MPI_Init(&argc, &argv);
	MPI_Status status;
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	
	if (rank==0)
	{
		int n=0;
		int arr[50];
		fprintf(stdout, "Enter the number of numbers to be added ");
		fflush(stdout);
		scanf("%d", &n);
		fprintf(stdout, "Enter the numbers to be added ");
		fflush(stdout);
		for(int i=0;i<n;i++){
			scanf("%d", &arr[i]);
		}
		int arr1[20], arr2[20];
		//MPI_Ssend(&n, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);
		int k1 = n/2+1;
		int k2 = n-n/2-1;
		for(int i=0; i<k1; i++){
			arr1[i] = arr[i];
		}
		for(int i=k1; i<n; i++){
			arr2[i-k1] = arr[i];
		}
		int sum1, sum2;
		MPI_Ssend(&k1, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);
		MPI_Ssend(arr1, k1, MPI_INT, 1, 1, MPI_COMM_WORLD);
		MPI_Ssend(&k2, 1, MPI_INT, 2, 0, MPI_COMM_WORLD);
		MPI_Ssend(arr2, k2, MPI_INT, 2, 1, MPI_COMM_WORLD);
		MPI_Recv(&sum1, 1, MPI_INT, 1, 2, MPI_COMM_WORLD, &status);
		MPI_Recv(&sum2, 1, MPI_INT, 2, 2, MPI_COMM_WORLD, &status);
		printf("Sum %d", sum1 + sum2);
	}
	else
	{
		int size, sum=0;
		int arr[20];
		MPI_Recv(&size, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, &status);
		MPI_Recv(arr, size, MPI_INT, 0, 1, MPI_COMM_WORLD, &status);
		for(int i=0;i<size;i++){
			sum+=arr[i];
		}
		MPI_Ssend(&sum, 1, MPI_INT, 0, 2, MPI_COMM_WORLD);
	}
	
	MPI_Finalize();
	
	return 0;
}
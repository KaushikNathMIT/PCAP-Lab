// P1.cpp : Defines the entry point for the console application.
//

#include <mpi.h>
#include <iostream>
#include <conio.h>
using namespace std;

int main(){
	int n,m,i,j;
	int a[10][10],b[10][10],c[10][10];
	cout<<"Enter the rows and column of the matrix ";
	cin>>m>>n;
	cout<<"Enter the first matrix ";
	for(i=0;i<m;i++){
		for(j=0;j<n;j++){
			cin>>a[i][j];
		}
	}
	cout<<"Enter the second matrix ";

	for(i=0;i<n;i++){
		for(j=0;j<m;j++){

		cin>>b[i][j];
	  }
	}
	for(i=0;i<m;i++){
		for(j=0;j<m;j++){
			c[i][j]=0;
			for(int k=0;k<n;k++){
				c[i][j]=c[i][j]+a[i][k]*b[k][j];
			}
		}
	}
	cout<<"Resultant Matrix"<<"\n";
	for(i=0;i<n;i++){
		for(j=0;j<m;j++){
			cout<<c[i][j]<<" ";
		}
		cout<<"\n";
	}
	getch();
	return 0;
}


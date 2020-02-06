/*
 ============================================================================
 Name        : Proyecto_SumaVectores.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Compute Pi in MPI C++
 ============================================================================
 */
#include <math.h> 
#include "mpi.h" 
#include <iostream>
#include <stdlib.h>
#include <time.h>
using namespace std;
 
int main() {
	int my_rank, comm_sz;
	int A[],B[],C[];
	int local_a[],local_b[],local_c[];
	//int suma_local[],suma_total[];
	int n, local_n;

	MPI_Init(NULL,NULL);
	MPI_Comm_rank(MPI_COMM_WORLD,&my_rank);
	MPI_Comm_size(MPI_COMM_WORLD,&comm_sz);

	if(my_rank == 0){
		printf("Indique la dimension del vector: ");
		scanf("%d",&n);
		srand(time(NULL));
		for(int i=0; i<n; i++){
			A[i] = rand() % 100;
			B[i] = rand() % 100;
		}
		for(int dest=1; dest<comm_sz;dest++){
			MPI_Send(&n, 1, MPI_INT, dest, 0, MPI_COMM_WORLD);
			MPI_Send(A, n, MPI_INT, dest, 1, MPI_COMM_WORLD);
			MPI_Send(B, n, MPI_INT, dest, 2, MPI_COMM_WORLD);
		}
	}
	else{
		MPI_Recv(&n, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
		MPI_Recv(A, n, MPI_INT, 0, 1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
		MPI_Recv(B, n, MPI_INT, 0, 2, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
	}

	local_n = n / comm_sz;
	for(int i=0; i<local_n;i++){
		local_a[i] = A[i+my_rank*local_n];
		local_b[i] = B[i+my_rank*local_n];
		local_c[i] = local_a[i] + local_b[i];
	}

	if(my_rank != 0){
		MPI_Send(local_c, local_n, MPI_INT, 0, my_rank+2, MPI_COMM_WORLD);
	}
	else{
		C = local_c;
		for(int i=1; i<comm_sz; i++){
			MPI_Recv(C+i*local_n, local_n, MPI_INT, i, i+2, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
		}
		printf("El resultado de la suma del vector A y B es: \n");
		for(int i=0; i<n; i++){
			printf("%d ",C[i]);
		}
	}

	MPI_Finalize();
	return 0;
}


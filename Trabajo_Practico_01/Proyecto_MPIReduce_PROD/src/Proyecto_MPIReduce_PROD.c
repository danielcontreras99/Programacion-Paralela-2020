/*
 ============================================================================
 Name        : Proyecto_MPIReduce_PROD.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description :
 ============================================================================
 */
#include <stdio.h>
#include <string.h>
#include "mpi.h"
#include <stdlib.h>
#include <time.h>

int main(){
	int my_rank, comm_sz;
	int a[10], n;
	double local_prod, total_prod;
	MPI_Init(NULL,NULL);
	MPI_Comm_rank(MPI_COMM_WORLD, &my_rank); 
	MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);
	
	srand(time(NULL));
	local_prod = 1;
	for(int i=0; i<10; i++){
		n = rand() % 100;
		local_prod = local_prod * n;
	}
	
	MPI_Reduce(&local_prod,&total_prod,1,MPI_DOUBLE,MPI_PROD,0,MPI_COMM_WORLD);
	
	if(my_rank == 0){
		printf("EL producto total es: %f\n",total_prod);
	}
	
	MPI_Finalize();
	return 0;
}

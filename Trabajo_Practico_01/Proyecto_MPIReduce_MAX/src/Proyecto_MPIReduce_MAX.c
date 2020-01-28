/*
 ============================================================================
 Name        : Proyecto_MPIReduce_MAX.c
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

int main(int argc, char* argv[]){
	int my_rank, comm_sz;
	int a[10], n, sum, max;
	
	MPI_Init(NULL,NULL);
	MPI_Comm_rank(MPI_COMM_WORLD, &my_rank); 
	MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);
	
	srand(time(NULL));
	sum = 0;
	for(int i=0; i<10; i++){
		n = rand() % 100;
		sum = sum + n;
	}

	MPI_Reduce(&sum,&max,1,MPI_INT,MPI_MAX,0,MPI_COMM_WORLD);
	
	if(my_rank == 0){
		printf("La mayor suma es: %d\n",max);
	}

	MPI_Finalize(); 
	return 0;
}

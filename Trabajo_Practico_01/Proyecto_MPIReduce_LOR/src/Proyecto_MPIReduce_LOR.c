/*
 ============================================================================
 Name        : Proyecto_MPIReduce_LOR.c
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
	int n, lor;
	MPI_Init(NULL,NULL);
	MPI_Comm_rank(MPI_COMM_WORLD, &my_rank); 
	MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);
	
	srand(time(NULL));
	n = rand() % 2;
	
	MPI_Reduce(&n,&lor,1,MPI_INT,MPI_LOR,0,MPI_COMM_WORLD);
	
	if(my_rank == 0){
		printf("Aplicando la operacion logica OR en todos los procesos, se obtiene: %d\n",lor);
	}
	
	MPI_Finalize();
	return 0;
}

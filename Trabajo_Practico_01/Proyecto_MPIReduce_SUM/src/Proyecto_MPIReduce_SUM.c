/*
 ============================================================================
 Name        : Proyecto_MPIReduce_SUM.c
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
	int a[10], n, local_sum, total_sum;
	
	MPI_Init(NULL,NULL);
	MPI_Comm_rank(MPI_COMM_WORLD, &my_rank); 
	MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);
	
	srand(time(NULL));
	local_sum = 0;
	for(int i=0; i<10; i++){
		n = rand() % 100;
		local_sum = local_sum + n;
	}
	
	MPI_Reduce(&local_sum,&total_sum,1,MPI_INT,MPI_SUM,0,MPI_COMM_WORLD);
	
	if(my_rank == 0){
		printf("La suma total es: %d\n",total_sum);
	}
	
	MPI_Finalize();
	return 0;
}

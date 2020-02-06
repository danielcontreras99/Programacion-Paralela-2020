#include "mpi.h" 
#include <iostream>
#include <stdlib.h>
#include <time.h>
using namespace std;
 
int main() {
	int my_rank, comm_sz;
	int n, x;
	int *A = NULL;
	MPI_Init(NULL,NULL);
	MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);
	MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
	if(my_rank==0){
		cout<<"Ingrese el numero de elementos del vector: ";
		cin>>n;
		cout<<"Ingrese el numero del 1 al 10: ";
		cin>>x;
		A = (int *) malloc(sizeof(int) * n);
		srand(time(NULL));
		cout<<"\nElementos del vector:\n";
		for(int i=0; i<n; i++){
			A[i] = rand()%10 + 1;
			cout<<A[i]<<" ";
		}
		cout<<endl;
	}
	MPI_Bcast(&n, 1, MPI_INT, 0, MPI_COMM_WORLD);
	MPI_Bcast(&x, 1, MPI_INT, 0, MPI_COMM_WORLD);

	int *A_local = NULL;
	A_local = (int *) malloc(sizeof(int) * n/comm_sz);
	MPI_Scatter(A, n/comm_sz, MPI_INT, A_local, n/comm_sz, MPI_INT,
			0, MPI_COMM_WORLD);
	int cont = 0;
	for(int i=0; i<n/comm_sz; i++){
		if(A_local[i] == x) cont++;
	}

	int total;
	MPI_Reduce(&cont, &total, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

	if(my_rank == 0){
		cout<<"\nEl numero "<<x<<" se encontro "<<total<<" veces en el vector\n";
		free(A);
	}
	free(A_local);

	MPI_Finalize();
	return 0;
}


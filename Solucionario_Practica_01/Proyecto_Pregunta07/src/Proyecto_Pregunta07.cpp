#include "mpi.h" 
#include <iostream>
using namespace std;
 
int main() {
	int my_rank, comm_sz, n;

	MPI_Init(NULL,NULL);
	MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);
	MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

	if(my_rank==0){
		cout<<"Ingrese un numero para hallar su factorial: ";
		cin>>n;
	}
	MPI_Bcast(&n, 1, MPI_INT, 0, MPI_COMM_WORLD);

	int nums_por_proc = n / comm_sz;
	if(n % comm_sz != 0) nums_por_proc++;

	double fact_local = 1;
	for(int i=my_rank*nums_por_proc; i<(my_rank+1)*nums_por_proc && i<n; i++)
		fact_local *= i+1;

	double fact_total;
	MPI_Reduce(&fact_local, &fact_total, 1, MPI_DOUBLE, MPI_PROD, 0,
			MPI_COMM_WORLD);

	if(my_rank==0){
		cout<<"\nEl factorial de "<<n<<" es: "<<fact_total<<endl;
	}

	MPI_Finalize();
	return 0;
}


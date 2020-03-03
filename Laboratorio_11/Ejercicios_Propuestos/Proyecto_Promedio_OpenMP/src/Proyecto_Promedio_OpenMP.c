#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main (int argc, char *argv[]) {

  int numThreads, tid;
  double *A = NULL;
  int n;
  double suma = 0;
  scanf("%d",&n);
  A = (double *) malloc(n*sizeof(double));
  srand(time(NULL));
  for(int i=0; i<n; i++){
	  A[i] = rand()%100;
  }

#pragma omp parallel private(numThreads, tid)
{
   tid = omp_get_thread_num();
   numThreads = omp_get_num_threads();
   double suma_local = 0;
   int nums = n/numThreads;
   int inicio = tid*nums;
   int final = inicio + nums;
   for(int i=inicio; i<final; i++)
	   suma_local += A[i];
#pragma omp critical
   suma += suma_local;
}

   printf("El promedio es: %lf\n", suma/n);
   return 0;
}



#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

int thread_count;
int n;
double *A = NULL;
sem_t* semaphores;


void Usage(char* prog_name);
void *Fibonacci(void* rank);

int main(int argc, char* argv[]) {
   long       thread, i;
   pthread_t* thread_handles;

   if (argc != 2)
      Usage(argv[0]);
   thread_count = strtol(argv[1], NULL, 10);
   thread_handles = malloc (thread_count*sizeof(pthread_t));
   semaphores = malloc(thread_count * sizeof(sem_t));

   scanf("%d",&n);
   A = (double *) malloc(n * sizeof(double));
   A[0] = 0;
   A[1] = 1;

   sem_init(&semaphores[0], 0, 1);
   for (i = 1; i < thread_count; i++)
      sem_init(&semaphores[i], 0, 0);

   for (thread = 0; thread < thread_count; thread++)
      pthread_create(&thread_handles[thread], (pthread_attr_t*) NULL,
          Fibonacci, (void*) thread);

   for (thread = 0; thread < thread_count; thread++) {
      pthread_join(thread_handles[thread], NULL);
   }


   free(thread_handles);
   return 0;
}

void Usage(char* prog_name) {

   fprintf(stderr, "usage: %s <number of threads>\n", prog_name);
   exit(0);
}  /* Usage */

void *Fibonacci(void* rank) {
	long my_rank = (long) rank;
	int nums = (n-2)/thread_count;
	int resto = (n-2)%thread_count;
	int inicio = my_rank*nums + 2 + resto;
	int final = inicio + nums;
	if(my_rank < resto){
		inicio = inicio - resto + my_rank;
		final = final - resto + my_rank;
	}

	sem_wait(&semaphores[my_rank]);
	for(int i=inicio;i<final;i++)
		A[i]=A[i-1]+A[i-2];

	if(my_rank+1 < thread_count)
		sem_post(&semaphores[my_rank+1]);

}

#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#define N       100

int main (int argc, char *argv[]) {

int nthreads, tid, i, j;
float a[N];

/* Some initializations */
for (i=0; i < N; i++)
  a[i] = i;


#pragma omp parallel shared(a,nthreads) private(i,tid)
  {
  tid = omp_get_thread_num();
  if (tid == 0)
    {
    nthreads = omp_get_num_threads();
    printf("Number of threads = %d\n", nthreads);
    }

  printf("Thread %d starting...\n",tid);

	j = 20;
	#pragma omp parallel for firstprivate(j)
	   for(i=1; i<=N; i++){
		  if(i == 1 || i == N)
			 j = j + 1;
		  a[i] = a[i] + j;
		  printf("Thread number: %d     j: %d\n",tid,j);
	   }
  }  /* end of parallel section */
  printf("j is equal to %d",j);

}

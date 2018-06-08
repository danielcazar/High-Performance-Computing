#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#define Ndim       5
#define Mdim       5
#define Pdim       5


int main (int argc, char *argv[]) {

int nthreads, tid, i, j, k;
int *A, *B, *C;
int tmp=1;

/* Some initializations */
for (i=0; i < Ndim; i++)
    for (j=0; j < Mdim; j++)
        for (k=0; k < Pdim; k++)
          A=B=C=&tmp;


#pragma omp parallel shared(A,B,C,nthreads) private(i,tid)
  {
  tid = omp_get_thread_num();
  if (tid == 0)
    {
    nthreads = omp_get_num_threads();
    printf("Number of threads = %d\n", nthreads);
    }

  printf("Thread %d starting...\n",tid);


#pragma omp parallel for schedule(dynamic) private(tmp, i, j, k)
	for (i=0; i<Ndim; i++){
		for (j=0; j<Mdim; j++){
                        tmp = 0.0;
			for(k=0;k<Pdim;k++){
				tmp += *(A+(i*Ndim+k)) *  *(B+(k*Pdim+j));
			}
			*(C+(i*Ndim+j)) = tmp;
			printf("Thread %d: tmp(%d) = %f\n",tid,i,tmp);
		}
	}
  }  /* end of parallel section */

}

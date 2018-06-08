 #include <stdio.h>
 #include <omp.h>
 #include <stdlib.h>

 const int n = 1018, N = n + 1;  /* N = 1019 -- prime     */
 const int alpha = 2;            /* generator             */
 const int beta = 5;             /* 2^{10} = 1024 = 5 (N) */

 void new_xab( int& x, int& a, int& b ) {
   switch( x%3 ) {
   case 0: x = x*x     % N;
           a =  a*2  % n;
           b =  b*2  % n;
           break;
   case 1: x = x*alpha % N;
           a = (a+1) % n;
           break;
   case 2: x = x*beta  % N;
           b = (b+1) % n;
           break;
   }
 }

int main(void) {

volatile bool flag=false;

int nthreads, i, tid;
int x=1, a=0, b=0;
int X=x, A=a, B=b;

#pragma omp parallel shared(a,b,x,nthreads, flag) private(i,tid)
  {
  tid = omp_get_thread_num();
  if (tid == 0)
    {
    nthreads = omp_get_num_threads();
    printf("Number of threads = %d\n", nthreads);
    }

  printf("Thread %d starting...\n",tid);

   #pragma omp for schedule(dynamic) ordered
   for(int i = 1; i < n; ++i ) {

     if(flag) continue;

     new_xab( x, a, b );
     new_xab( X, A, B );
     new_xab( X, A, B );
     #pragma omp ordered
      {
     printf( "Thread %d: %3d  %4d %3d %3d  %4d %3d %3d\n", tid, i, x, a, b, X, A, B );
      }
     if( x == X )
     {
         flag=true;
     }
   }
   }

   return 0;
 }

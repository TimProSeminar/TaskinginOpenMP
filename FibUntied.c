#include <stdio.h>
#include <omp.h>
#include <time.h>
#define CUTOFF 15



double fib_cutoff (int n)
{
	double i, j;
	
	if (n < 2) 
	  return n;
   	else
   	{
	  i = fib_cutoff(n - 1);
	  j = fib_cutoff(n - 2);

	  return i + j;
	}
}

double fib(int n, int d)
{
	double i, j;
  
  	if (n<2)
   	  return n;
  	else
  	{
  		if (d < CUTOFF)
  		{
    		  #pragma omp task untied shared(i) firstprivate(n) 
        	  i=fib(n-1,d+1);
     		  #pragma omp task untied shared(j) firstprivate(n) 
       	   j=fib(n-2,d+1);
       
      		  #pragma omp taskwait
       		return i+j;
      		}
     	 	else
     	 	{
      	 	 i=fib_cutoff(n-1);
      		 j=fib_cutoff(n-2);
    		}
	}
}

int main()
{
  int n = 50;
  omp_set_dynamic(0);
  omp_set_num_threads(32);

  #pragma omp parallel shared(n)
  {
    #pragma omp single
    printf ("fib(%d) = %f\n", n, fib(n,1));    
  }
}

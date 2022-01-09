#include <stdio.h>
#include <omp.h>


double fib(int n)
{
	double i, j;
  
  	if (n<2)
   	  return n;
  	else
  	{
          i=fib(n-1);
          j=fib(n-2);
          return i+j;    		
	}
}

int main()
{
  int n = 50;

  {
    printf ("fib(%d) = %f\n", n, fib(n));    
  }
}

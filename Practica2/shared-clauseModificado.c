#include <stdio.h>
#ifndef _OPENMP
	#include <omp.h>
#endif

int main (){

	int i, n=7;
	int a[n];
	
	for (i = 0; i < n; i++)
		a[i] = i+1;	
	
	printf("Despues de parallel for:\n");
	for (i=0; i < n ; i++)
		printf("a[%d] = %d\n",i,a[i]);
}



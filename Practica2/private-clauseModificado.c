#include <stdio.h>
#ifndef _OPENMP
	#include <omp.h>
#else 
	#define omp_get_thread_num() 0	
#endif

int main (){

	int i, n=7,suma;
	int a[n];
	
	for (i = 0; i < n; i++)
		a[i] = i;	
	
	#pragma omp parallel
	{
		suma = 0;
		#pragma omp for 
		for (i = 0; i < n ; i++)
		{
			suma += a[i];
			printf("thread %d suma a[%d] / ", omp_get_thread_num(),i);
		}
		printf("\n* thread %d suma=%d",omp_get_thread_num(),suma );
	
	}	
	printf("\n\n* suma fuera de parallel= %d",suma );
	printf("\n\n");
	
}

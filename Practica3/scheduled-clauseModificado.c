#include <stdio.h>
#include <stdlib.h>

#ifdef _OPENMP
    #include <omp.h>
#else
    #define omp_get_thread_num() 0
#endif

int main(int argc, char **argv)
{
    int i, n=200, chunk, a[n], suma=0;
    
    if(argc < 3)
    {
        fprintf(stderr,"\nFalta iteraciones o chunk\n");
        exit(-1);
    }

    n = atoi(argv[1]);
    if (n>200)
        n=200;

    chunk = atoi(argv[2]); 

    for (i=0; i<n; i++)
        a[i] = i; 
 
    #pragma omp parallel for firstprivate(suma) \
                lastprivate(suma) schedule(dynamic,chunk)
    for (i=0; i<n; i++)
    {
        if (i == 0){
        	int nthreads_var = omp_get_max_threads();
        	int thread_limit_var = omp_get_thread_limit();
        	int dyn_var = omp_get_dynamic();
        	int modifier;
        	omp_sched_t kind;
        	omp_get_schedule(&kind, &modifier);
        	
        	printf("Dinámica (T 0, F 1): %d\n",dyn_var); 
        	printf("N threads: %d\n",nthreads_var);
        	printf("Límite de threads: %d\n", thread_limit_var);
        	printf("kind (static 1, dynamic 2, guided 3): %d\n",kind);
        	printf("Chunk: %d\n",modifier);
        
        }
        suma = suma + a[i];
        printf(" thread %d suma a[%d]=%d suma=%d \n",
               omp_get_thread_num(),i,a[i],suma);
    }

    printf("Fuera de 'parallel for' suma=%d\n",suma); 
    int nthreads_var = omp_get_max_threads();
        	int thread_limit_var = omp_get_thread_limit();
        	int dyn_var = omp_get_dynamic();
        	int modifier;
        	omp_sched_t kind;
        	omp_get_schedule(&kind, &modifier);
        	
        	printf("Dinámica (T 0, F 1): %d\n",dyn_var); 
        	printf("N threads: %d\n",nthreads_var);
        	printf("Límite de threads: %d\n", thread_limit_var);
        	printf("kind (static 1, dynamic 2, guided 3): %d\n",kind);
        	printf("Chunk: %d\n",modifier);
}


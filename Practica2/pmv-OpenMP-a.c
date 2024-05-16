#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>

#define MAX 1000

int main(int argc, char** argv) {
    unsigned int N;
    struct timespec cgt1, cgt2; double ncgt;
    int i, j;

    if (argc < 2) {
        printf("Usage: %s size\n", argv[0]);
        exit (EXIT_FAILURE);
    }
    
    N = atoi(argv[1]);
#ifdef VECTOR_GLOBAL
    if ( N > MAX) N = MAX;
#endif

#ifdef VECTOR_DYNAMIC
    double *v1, *v2, **m;
    v1 = (double*)malloc(N* sizeof(double));
    v2 = (double*)malloc(N* sizeof(double));
    m = (double**)malloc(N* sizeof(double*));
    if ( (v1 == NULL) || (v2 == NULL) || (m == NULL)) {
        printf("Not enough space for v1, v2 and m\n");
        exit (EXIT_FAILURE);
    }
    for (i = 0; i < N; i++) {
        m[i] = (double*)malloc(N* sizeof(double));
        if (m[i] == NULL) {
            printf("Not enough space for m\n");
            exit(EXIT_FAILURE);
        }
    }
#endif

    // Initialize vector and matriz
#pragma omp parallel for private (j)
    for (i=0; i < N; i++){
        v1[i] = 0.1*i;
        v2[i] = 0;
        for (j = 0; j < N; j++)
            m[i][j] = i*N+j;
    }

        // Calculate v2 = m * v1
        clock_gettime (CLOCK_REALTIME, &cgt1);
#pragma omp parallel private(i)
        for (i = 0; i < N ; i++){
        	//#pragma omp for
        	for(j = 0; j < N; j++){
        	   // #pragma omp critical
        	    v2[i] += m[i][j] * v1[j];
        	}
        
        
        }
        clock_gettime (CLOCK_REALTIME, &cgt2);
        ncgt = (double) (cgt2.tv_sec-cgt1.tv_sec) + 
               (double) ((cgt2.tv_sec-cgt1.tv_sec)/(1.e+9));

        // Print results
        if (N < 10) {
            printf("Time: %11.9f\t Size: %u\n", ncgt, N);
            printf("Matrix:\n\t");
            for (i = 0; i < N; i++) {
                for (j = 0; j < N; j++)
                    printf("%8.6f\t",m[i][j]);
                printf("\n\t");
            }
            printf("Vector:\n\t");
            for (i = 0; i < N; i++)
                printf("%8.6f", v1[i]);
            printf("\n\nVector resultado:\n\t");
            for (i = 0; i < N; i++)
                printf("%8.6f", v2[i]);
            printf("\n");
        } else {
            printf("Time: %11.9f \t Size: %u\t v2[0]: %8.6f \t v2 [N-1]: %8.6f \n", ncgt, N, v2[0], v2 [N-1]);
        }


    return(0);
}

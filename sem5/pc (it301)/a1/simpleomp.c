/*simpleomp.c*/
#include<omp.h> 
#include<stdio.h>

int main(){ 
    int nthreads,tid;
    #pragma omp parallel private(tid) num_threads(8) //set num_threads=8
    {
        tid = omp_get_thread_num();
        printf("Hello world from thread=%d\n",tid); 
        if(tid==0) 
        { 
            nthreads=omp_get_num_threads(); 
            printf("Number of threads (using num_threads()) = %d\n",nthreads); 
        } 
    }
} 
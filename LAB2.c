#include<stdio.h>
#include<omp.h>
int main(){
    int num_iterations;
    printf("Enter the number of iterations: ");
    fflush(stdout);
    scanf("%d",&num_iterations);
    omp_set_dynamic(0);
    omp_set_num_threads(4);
    #pragma omp parallel
    {
        #pragma omp for schedule(static,2)
        for(int i=0;i<num_iterations;i++){
            printf("Thread %d: Iteration %d\n",omp_get_thread_num(),i);
        }
    }
    return 0;
}
// Compile: gcc -fopenmp LAB2.c -o LAB2
// Run: LAB2.exe

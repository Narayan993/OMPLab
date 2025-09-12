#include<stdio.h>
#include<omp.h>
void main(){
    int n,itr;
	printf("Enter the number of threads: ");
	scanf("%d",&n);
	printf("Enter the number of iterations: ");
	scanf("%d",&itr);
	omp_set_num_threads(n);
    #pragma omp parallel for schedule(static , 2)
	for(int i = 0; i <itr; i++){
        printf("Thread %d \t Iteration %d\n" , omp_get_thread_num() , i);
    }
	
}
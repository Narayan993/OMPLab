#include <stdio.h>
#include <math.h>
#include <omp.h>
int is_prime(int n){
	if (n<=1){
		return 0;
	}
	for(int i=2;i <= sqrt(n) ;i++){
		if (n%i==0)
			return 0;
	}
	return 1;
}

int main(){
	double start_time,end_time,cpu_time,start_time1,end_time1,cpu_time1;
	int count=0;
	omp_set_num_threads(15);
	printf("Serial\n");
	start_time1=omp_get_wtime();
	for (int i=1;i<=10000000;i++){
		if (is_prime(i))
		{
			count++;
		}
	}
	end_time1=omp_get_wtime();
	cpu_time1=end_time1-start_time1;
	printf("\nTime : %lf for %d prime numbers",cpu_time1,count);
	printf("\nParallel\n");
	count=0;
	start_time=omp_get_wtime();
	#pragma omp parallel for
	for (int i=1;i<=10000000;i++){
		if (is_prime(i))
		{
			count++;
		}
	}
	end_time=omp_get_wtime();
	cpu_time=end_time-start_time;
	printf("\nTime : %lf for %d prime numbers\n",cpu_time,count);
	return 0;
}

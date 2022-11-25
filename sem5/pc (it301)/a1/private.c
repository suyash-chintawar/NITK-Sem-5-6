#include<stdio.h>
#include<omp.h>
int main()
{
	int x=0;
	printf("x is:%d",x);
	#pragma omp parallel private(x)
	{
		int tid=omp_get_thread_num();
		x=x+1;
		printf("tid:%d, x:%x",tid,x);
	}
	return 0;
}
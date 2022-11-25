#include<stdio.h>
#include<omp.h>
void main(void)
{
	int n,tid,min_value=100000000,i;
	printf("Enter size of array a: ");
	scanf("%d",&n);
	int a[n];
	printf("Enter elements of array a (%d numbers): ",n);
	for(int i=0;i<n;i++) 
	{
		scanf("%d",&a[i]);
	}
	#pragma omp parallel
	{
		int tid=omp_get_thread_num();
		#pragma omp for private(i) schedule(static,5) reduction(min:min_value)
		for(i=0;i<n;i++)
			if(a[i]<min_value) min_value=a[i];
	}
	printf("min_value = %d\n",min_value);
}

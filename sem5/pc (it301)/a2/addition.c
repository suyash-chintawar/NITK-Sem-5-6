/* Performs c[i]=a[i]+b[i] */
#include<stdio.h>
#include<omp.h>
int main()
{
	int threads,n;

	//Take input from user
	printf("Enter size of arrays a,b,c: ");
	scanf("%d",&n);
	printf("Enter number of threads: ");
	scanf("%d",&threads);
	omp_set_num_threads(threads); //set number of threads
	int a[n],b[n],c[n];
	printf("Enter elements of array a (%d numbers): ",n);
	for(int i=0;i<n;i++) 
	{
		scanf("%d",&a[i]);
	}
	printf("Enter elements of array b (%d numbers): ",n);
	for(int i=0;i<n;i++) 
	{
		scanf("%d",&b[i]);
	}

	int tid,low,high,i;
	#pragma omp parallel default(shared) private(tid,low,high,i)
	{
		tid = omp_get_thread_num();
		low = n*tid/threads;
		high = n*(tid+1)/threads;

		//check computation of each thread
		printf("tid:%d, low:%d, high-1:%d\n",tid,low,high-1);

		for(i=low; i<high; i++) c[i]=b[i]+a[i];
	}

	printf("Final array after addition:\n");
	for(i=0;i<n;i++) printf("%d ",c[i]);
	printf("\n");
}
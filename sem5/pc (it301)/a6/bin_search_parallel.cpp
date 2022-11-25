#include<bits/stdc++.h>
#include <sys/time.h>
#include <omp.h>
using namespace std;

bool found = false;
int index_found = -1;

void binary_search_serial(int a[],int l,int r,int target)
{
	if(l<=r)
	{	
		int mid = l + (r-l)/2;
		if(a[mid]==target)
		{
			found = true;
			index_found = mid;
			return;
		}
		binary_search_serial(a,l,mid-1,target);
		binary_search_serial(a,mid+1,r,target);
	}

}

void binary_search_parallel(int a[],int l,int r,int target)
{
	if(l<=r)
	{	
		int mid = l + ((r-l)/2);
		if(a[mid]==target)
		{
			found = true;
			index_found = mid;
			return;
		}
		if(r-l<1000) 
		{
			binary_search_serial(a,l,r,target);
			return;
		}
		#pragma omp task shared(a,target) firstprivate(l,mid,r) 
		{
			binary_search_parallel(a,l,mid-1,target);	
		}
		#pragma omp task shared(a,target) firstprivate(l,mid,r) 
		{
			binary_search_parallel(a,mid+1,r,target);	
		}
		#pragma omp taskwait
	}
}

int main()
{
	int n;
	cout<<"Enter size of array: ";
	cin>>n;
	int a[n];

	for(int i=0;i<n;i++)
	{
		a[i]=rand();
	}
	char c;
	// cout<<"Do you want element to be found in array?(y/n): ";
	// cin>>c;
	int target,idx;
	// if(c=='y')
	// {
	// 	idx = rand()%n;
	// 	target = a[idx];
	// }
	// else
	// {
	// 	target = rand();
	// }
	target = a[(n-1)/4];
	double t1,t2;
	t1=omp_get_wtime();
	#pragma omp parallel shared(n,a,target)
	{
		#pragma omp single
		{
			binary_search_parallel(a,0,n-1,target);
		}
	}
	t2=omp_get_wtime();
	if(found) cout<<"Found at index "<<index_found<<"!\n";
	else cout<<"Not found!!\n";
	printf("Time taken is %f seconds \n",t2-t1);
}
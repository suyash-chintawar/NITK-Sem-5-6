#include <stdio.h>
#include <sys/time.h>
#include <omp.h>
#include <stdlib.h>
#include<bits/stdc++.h>
using namespace std;


int main(){
	struct timeval TimeValue_Start;
	struct timezone TimeZone_Start;
	struct timeval TimeValue_Final;
	struct timezone TimeZone_Final;
	long time_start, time_end;
	double time_overhead;
	int i,n;
	// n=5000;
	// n=10000;
	// n=50000;
	// n=100000;
	n=10000000;
	vector<int> a(n,0),b(n,0),c(n,0);
	for(int i=0;i<n;i++)
	{
		a[i]=rand();
		b[i]=rand();
	}

	gettimeofday(&TimeValue_Start, &TimeZone_Start);
	#pragma omp parallel for private(i) schedule(runtime)
	for(i=0;i<n;i++){
		c[i]=a[i]*b[i];
	}
	gettimeofday(&TimeValue_Final, &TimeZone_Final);
	time_start = TimeValue_Start.tv_sec * 1000000 + TimeValue_Start.tv_usec;
	time_end = TimeValue_Final.tv_sec * 1000000 + TimeValue_Final.tv_usec;
	time_overhead = (time_end - time_start)/1000000.0;
	printf("\n\n\tTime in Seconds (T) : %lf\n",time_overhead);
}
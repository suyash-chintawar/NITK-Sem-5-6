#include <bits/stdc++.h>
#include <sys/time.h>
#include <omp.h>
using namespace std;

int arr[10000000];
int N = 10000000;

int binarySearch(int arr[], int start, int end, int ele){

    int x, y, mid = (start+end)/2;;
    if(start>=0 && start<=end && end<N)
    {
        if(arr[mid]==ele){
            return mid;
        }
        #pragma omp task shared(x) if(end-start > 1000)
        {
            x = binarySearch(arr, start, mid-1, ele);
        }
        #pragma omp task shared(y) if(end-start > 1000)
        {
            y = binarySearch(arr, mid+1, end, ele);
        }
        #pragma omp taskwait
        return max(x,y);
    }

    return -1;

}

int main(){

    int ele, x, y, z;
    double t1,t2;

    // random intput
    srand((unsigned) time(0));
    int temp;
    for(int i=0; i<N; i++){
        arr[i] = rand();
    }

    t1 = omp_get_wtime();
    #pragma omp parallel shared(N, arr)
    {
        #pragma omp single
        {
            y = binarySearch(arr,0,N-1,arr[(N-1)/2]);
        }
    }
    t2 = omp_get_wtime();

    cout<<"\nBest case when element is in middle position "<<endl;   
    printf("\tTime in Seconds (T) : %lf\n\n",t2-t1);

    t1 = omp_get_wtime();
    #pragma omp parallel shared(N, arr) num_threads(16)
    {
        #pragma omp single
        {
            x = binarySearch(arr,0,N-1,arr[0]);
        }
    }
    t2 = omp_get_wtime();

    cout<<"\nWorst case when element is in first or last position "<<endl;   
    printf("\tTime in Seconds (T) : %lf\n\n", t2-t1);

    t1 = omp_get_wtime();
    #pragma omp parallel shared(N, arr) num_threads(16)
    {
        #pragma omp single
        {
            z = binarySearch(arr,0,N-1,arr[100]);
        }
    }
    t2 = omp_get_wtime();

    cout<<"\nAverage case when element is in somewhere between mid and extreme ends"<<endl;   
    printf("\tTime in Seconds (T) : %lf\n\n", t2-t1);

    return 0;

}
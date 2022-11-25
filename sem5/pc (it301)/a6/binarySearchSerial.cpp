#include <bits/stdc++.h>
#include <sys/time.h>
#include <omp.h>
using namespace std;

int arr[10000000];
int N = 10000000;

int binarySearch(int arr[], int start, int end, int ele){

    if(start>=0 && start <= end && end<N){
        int mid = (start+end)/2;
        if(arr[mid]==ele){
            return mid;
        }
        int x = binarySearch(arr, start, mid-1, ele);
        int y = binarySearch(arr, mid+1, end, ele);
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
    y = binarySearch(arr,0,N-1,arr[(N-1)/2]);
    t2 = omp_get_wtime();

    cout<<"\nBest case when element is in middle position "<<endl;   
    printf("\tTime in Seconds (T) : %lf\n\n",t2-t1);

    t1 = omp_get_wtime();
    x = binarySearch(arr,0,N-1,arr[0]);
    t2 = omp_get_wtime();

    cout<<"\nWorst case when element is in first or last position "<<endl;   
    printf("\tTime in Seconds (T) : %lf\n\n", t2-t1);

    t1 = omp_get_wtime();
    x = binarySearch(arr,0,N-1,arr[100]);
    t2 = omp_get_wtime();

    cout<<"\nAverage case when element is in somewhare between mid and extreme ends"<<endl;  
    printf("\tTime in Seconds (T) : %lf\n\n", t2-t1);

    return 0;


}
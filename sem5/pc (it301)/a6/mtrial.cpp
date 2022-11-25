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
        // printf("%d\n",mid);
        if(arr[mid]==ele){
            return mid;
        }
        // #pragma omp task shared(x, arr, ele) firstprivate(start, end, mid) if(mid-start>100)
        // {
            // printf("Task A Created by Thread %d\n",omp_get_thread_num());
            x = binarySearch(arr, start, mid-1, ele);
        // }
        // #pragma omp task shared(y, arr, ele) firstprivate(start, end, mid) if(mid-start>100)
        // {
            // printf("Task B Created by Thread %d\n",omp_get_thread_num());
            y = binarySearch(arr, mid+1, end, ele);
        // }
        // #pragma omp taskwait
        return max(x,y);
    }

    return -1;

}

int main(){

    int ele, x, y;
    double t1,t2;

    // random intput
    srand((unsigned) time(0));
    int temp;
    for(int i=0; i<N; i++){
        arr[i] = rand();
        // cout<<arr[i];
    }

    t1 = omp_get_wtime();
    // #pragma omp parallel shared(N, arr)
    // {
    //     #pragma omp single
    //     {
            // printf("Task setter : %d\n",omp_get_thread_num());
            x = binarySearch(arr,0,N-1,arr[0]);
    //     }
    // }
    t2 = omp_get_wtime();

    cout<<"\nWorst case when element is in first or last position "<<endl;   
    printf("\tTime in Seconds (T) : %lf\n\n", t2-t1);
    cout<<x<<endl;


    t1 = omp_get_wtime();
    // #pragma omp parallel shared(N, arr)
    // {
    //     #pragma omp single
    //     {
            y = binarySearch(arr,0,N-1,arr[(N-1)/2]);
    //     }
    // }
    t2 = omp_get_wtime();

    cout<<"Best case when element is in middle position "<<endl;   
    printf("\tTime in Seconds (T) : %lf\n\n",t2-t1);
    cout<<y<<endl;

    return 0;


}
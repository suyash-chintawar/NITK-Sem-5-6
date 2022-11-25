/*
This program takes gives the minimum no. of
refills needed to reach destination
NOTE:
1) Please do not give wrong inputs
*/
#include<bits/stdc++.h>
using namespace std;

//Function to find minimum refills needed
int min_refills(int d,int m, int n, vector<int> stops)
{
    //no. of refills
    int cnt = 0;

    //max distance that can be travlled currently
    int max=m;

    //index to represent current stop
    int i=0;

    while(max<d)
    {
        //no stops left or next stop unreachable
        if(i>=n or stops[i]>max)
        {
            return -1;
        }

        //Refilling at the farthest stop possible
        while(i<n-1 and stops[i+1]<=max)
        {
            i++;
        }
        max = stops[i]+m;
        i++;
        cnt++;        
    }
    return cnt;
}

int main()
{
    //Take input
    int d,m,n;
    cout<<"Enter d: ";
    cin>>d;
    cout<<"Enter m: ";
    cin>>m;
    cout<<"Enter n: ";
    cin>>n;

    //storing stops(or gas stations)
    vector<int> stops(n+1);
    cout<<"Enter stops:\n";
    for(int i=0;i<n;i++) cin>>stops[i];

    //Counting minimum refills needed
    cout<<"Minimum refills needed: "<<min_refills(d,m,n,stops)<<endl;
}
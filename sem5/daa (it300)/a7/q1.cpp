/*
This program computes the min no. of steps needed 
to convert every word to every other word given in list
NOTE:
1) The matrix has rows and cols as per inputs words in order
2) Please do not give wrong inputs
*/
#include <bits/stdc++.h>
using namespace std;
#define INF 10000000

//Make adjacency list
void adjacency_list(int n, int k, int d, vector<string> wlist, vector<int> adj_list[])
{
    for(int i=0;i<n;i++) 
    {
        for(int j=i+1;j<n;j++) 
        {
            int nd=0; //num of different letters
            for(int l=0;l<k;l++) 
            {
                if(wlist[i][l]!=wlist[j][l]) 
                {
                    nd++;
                }
            }
            if(nd<=d) 
            {
                adj_list[i].push_back(j);
                adj_list[j].push_back(i);
            }
        }
    }
}

//BFS to get shortest path for one source and all destinations (words)
void bfs(int src, vector<int> adj_list[], vector<int>& min_steps)
{
    queue<int> q;
    q.push(src);

    min_steps[src] = 0;
    while(!q.empty()) 
    {
        int x=q.front();
        q.pop();
        for(auto y:adj_list[x]) 
        {
            if(min_steps[y]>min_steps[x]+1) 
            {
                min_steps[y]=min_steps[x]+1;
                q.push(y);
            }
        }
    }
}

int main()
{
    int n,k,d;
    cout<<"Enter n: ";
    cin>>n;
    cout<<"Enter k: ";
    cin>>k;
    cout<<"Enter d: ";
    cin>>d;

    vector<string> wlist(n);
    cout<<"Enter the words:\n";
    for(int i=0;i<n;i++) cin>>wlist[i];
    
    vector<int> adj_list[n];
    adjacency_list(n,k,d,wlist,adj_list);

    //Storing min_steps for each word
    vector<vector<int>> min_steps(n, vector<int>(n,INF));
    for(int i=0;i<n;i++) 
    {
        bfs(i, adj_list, min_steps[i]);//bfs on each word
    }
    cout<<endl;

    cout<<"Minimum steps needed to convert every word to every other word:\n";
    cout<<"NOTE: See code comments for matrix format\n";
    /*
    The rows and cols in the matrix will be 
    the words given in input in the same order..
    for eg.
    matrix[i][j] says the min steps needed to convert word i to j
    */
    for(int i=0;i<n;i++) 
    {
        for(int j=0;j<n;j++) 
        {
            cout<<min_steps[i][j]<<" ";
        }
        cout<<endl;
    }
}
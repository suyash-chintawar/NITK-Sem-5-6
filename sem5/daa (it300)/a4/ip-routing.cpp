/*
1)This program implements the Dijkstra's Algorithm for ip routing
considering edges as 1-based,
i.e. 1,2,3..n where 'n' is no. of routers
2)The program uses priority_queue C++STL to implement min heap
3)Time Complexity is O(ElogV) where E->#edges,V->#vertices
4)Adjacency list representation has been used to represent graphs
*/
#include<bits/stdc++.h>
using namespace std;
typedef pair<int,int> pii;//for easier declaration of variables

//Compute adjacency list of graph
void adjacency_list(int n,int edges,int edge[][3],vector<pii> adj_list[])
{
    for(int i=0;i<edges;i++)
    {
        adj_list[edge[i][0]-1].push_back(make_pair(edge[i][1],edge[i][2]));
        adj_list[edge[i][1]-1].push_back(make_pair(edge[i][0],edge[i][2]));
    }
}

//Implement Dijkstra's Algorithm
void dijkstra(int src,int n, vector<pii> adj_list[])
{
    vector<int> d(n,INT_MAX);//distances/costs of all routers, initialized to infinte
    vector<int> parent(n+1,-1);//parents of vertices(routers) to display final paths
    vector<int> found(n,0);//to store shortest distances/costs
    d[src-1]=0;
    priority_queue<pii,vector<pii>,greater<pii>> q;//min-heap
    q.push(make_pair(0,src));//pushing starting vertex(router) as distance is zero from itself
    while(!q.empty())
    {
        int dv=q.top().first;//distance of shortest distanced vertex
        int v=q.top().second;//vertex with shortest distance
        q.pop();
        if(dv!=d[v-1]) continue;//occur when path of adjacent vertex already is shortest
        found[v-1]=dv;
        for(auto x:adj_list[v-1])//check and update adjacent vertices' distances
        {
            int adj_x=x.first;
            int weight=x.second;
            if(dv+weight < d[adj_x-1])//shorter path found
            {
                d[adj_x-1]=dv+weight;
                q.push(make_pair(d[adj_x-1],adj_x));
                parent[adj_x]=v;
            }
        }
    }
    cout<<"\n*********SHORTEST PATHS AND THEIR DISTANCES (COSTS)*********\n";
    for(int i=0;i<n;i++)
    {
        cout<<"Router "<<i+1<<"\nShortest Distance(cost):"<<found[i]<<"\nPath: ";
        vector<int> path;
        for(int k=i+1;k!=-1;k=parent[k])
        {
            path.push_back(k);
        }
        for(int i=path.size()-1;i>=1;i--)
        {
            cout<<path[i]<<"->";
        }
        cout<<path[0];
        cout<<endl<<endl;
    }

}

int main()
{
    int n,edges,type;
    int edge[1000][3];
    cout<<"Enter number of routers(vertices) in the network:";
    cin>>n;
    cout<<"Enter number of edges:";
    cin>>edges;
    cout<<"Enter edges("<<edges<<" lines, 3 space separated integers on each line";
    cout<<"\nformat: router1 router2 edge_weight):\nNOTE: enter edges assuming 1-based vertices\n";
    for(int i=0;i<edges;i++)
    {
        cin>>edge[i][0]>>edge[i][1]>>edge[i][2];
    }

    vector<pii> adj_list[n];
    adjacency_list(n,edges,edge,adj_list);
    dijkstra(1,n,adj_list);
}

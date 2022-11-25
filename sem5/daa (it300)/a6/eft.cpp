#include<bits/stdc++.h>
using namespace std;
typedef pair<int,int> pii;

int main()
{
	int n;
	cout<<"Enter the no. of music festivals: ";
	cin>>n;
	priority_queue<pii,vector<pii>,greater<pii>> pq;
	cout<<"Enter the start and finish time of each festival\n";
	cout<<"Format: start_time finish_time\n";
	for(int i=0;i<n;i++)
	{
		int si,fi;
		cin>>si>>fi;
		pq.push({fi,si});
	}
	vector<pii> res;
	int finish = 0;
	for(int i=0;i<n;i++)
	{
		pii temp = pq.top();
		pq.pop();
        if(finish < temp.second)
        {
            res.push_back(temp);
            finish = temp.second;
        }
    }
    cout<<"Max no. of events that can be attended: "<<res.size()<<"\n";
    for(int i=0;i<res.size();i++)
    {
        cout<<res[i].second<<" to "<<res[i].first<<"\n";
    }
}
/*
This program finds the number of platforms needed
given train schedules.
NOTE:
1) Arrival and departure times must be in 24 hour format
2) Please refrain from giving wrong inputs
*/
#include<bits/stdc++.h>
using namespace std;
typedef pair<int,char> pic;

int main()
{
	int n;
	cout<<"Enter the number of trains: ";
	cin>>n;

	//Stores arr and dept times in sorted format
	priority_queue<pic,vector<pic>,greater<pic>> pq;

	cout<<"Enter the arrival and dept of each train: ";
	cout<<"\nFormat: arr_hr arr_min dept_hr dept_min\n";
	for(int i=0;i<n;i++)
	{
		//Take input as hours and mins for arr and dept
		//Must be in 24 hr format
		int ah,am,dh,dm;
		cin>>ah>>am>>dh>>dm;

		//convert hrs to mins and push in queue
		pq.push({60*ah+am,'a'});
		pq.push({60*dh+dm,'d'});
	}

	//Calcule=ate min no. of platforms
	int res = 0 , curr = 0;
	while(!pq.empty())
	{
		pic temp = pq.top();
		pq.pop();
		if(temp.second=='a') curr++;
		else curr--;
		res = max(res,curr);
	}

	cout<<"Minimum number of platforms: "<<res<<"\n";
}
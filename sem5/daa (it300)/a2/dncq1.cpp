/*
This program implements quick sort to sort the 
shopping list contents based on their priority
*/
#include<bits/stdc++.h>
using namespace std;

//function to partition the array into two parts and finding correct position of pivot
int partition(vector<pair<string,int>> &list,int low,int high)
{
	//Choose pivot as last element
	int x=list[high].second,j=low-1;
	for(int i=low;i<high;i++)
	{
	   if(list[i].second<x)
	   {
	       j++;
	       pair<string,int> temp=list[j];
	       list[j]=list[i];
	       list[i]=temp;
	   }
	}
	j++;
	pair<string,int> temp=list[j];
	list[j]=list[high];
	list[high]=temp;

	return j;
}

//Function to perform quicksort on the list from index low to high
void quicksort(vector<pair<string,int>> &list,int low,int high)
{
	if(low<high)
	{
		int q=partition(list,low,high);
		quicksort(list,low,q-1);
		quicksort(list,q+1,high);
	}
}

int main()
{
	//Take input
	 int n;
	 cout<<"Number of items: ";
	 cin>>n;
	 vector<pair<string,int>> list;
	 cout<<"\nEnter "<<n<<" items, i.e. shopping list contents:\n(NOTE: Format: item_name priority_value)\n";
	 for(int i=0;i<n;i++)
	 {
	 	string item;
	 	int priority;
	 	cin>>item>>priority;
	 	list.push_back({item,priority});
	 }

	 //Call function
	 quicksort(list,0,n-1);

	 //Display results
	 cout<<"\nFINAL SORTED SHOPPING LIST:\n(NOTE: Format: item_name priority_value)\n";
	 for(auto x:list)
	 {
	 	cout<<x.first<<" : "<<x.second<<'\n';
	 }
}
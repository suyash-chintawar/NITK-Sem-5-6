/*
This program takes in multiple arrays, sorts them individually,
and merges all of them together into a single array removing the duplicates
*/
#include<bits/stdc++.h>
using namespace std;

//function to partition the array into two parts and finding correct position of pivot
int partition(vector<int> &a,int low,int high)
{
	//Choose pivot as last element
	int x=a[high],j=low-1;
	for(int i=low;i<high;i++)
	{
	   if(a[i]<x)
	   {
	       j++;
	       int temp=a[j];
	       a[j]=a[i];
	       a[i]=temp;
	   }
	}
	j++;
	int temp=a[j];
	a[j]=a[high];
	a[high]=temp;

	return j;
}

//Function to perform quicksort on the list from index low to high
void quicksort(vector<int> &a,int low,int high)
{
	if(low<high)
	{
		int q=partition(a,low,high);
		quicksort(a,low,q-1);
		quicksort(a,q+1,high);
	}
}

//Function to merge to sorted arrays
vector<int> merge(vector<int> a,vector<int> b)
{
	int i=0,j=0;//pointers to each array
	vector<int> result;

	//merge the arrays into result
	while(i<a.size() and j<b.size())
	{
		if(a[i]<b[j])
		{
			if(result.size()==0) result.push_back(a[i]);
			else if(result[result.size()-1]!=a[i]) result.push_back(a[i]);
			i++;
		}
		else if(a[i]>b[j])
		{
			if(result.size()==0) result.push_back(b[j]);
			else if(result[result.size()-1]!=b[j]) result.push_back(b[j]);
			j++;
		}
		else
		{
			if(result.size()==0) result.push_back(a[i]);
			else if(result[result.size()-1]!=b[j]) result.push_back(b[j]);
			i++;
			j++;
		}
	}

	//If any of the arrays is still not covered 
	if(i!=a.size())
	{
		while(i<a.size())
		{
			if(result.size()==0) result.push_back(a[i]);
			else if(result[result.size()-1]!=a[i]) result.push_back(a[i]);
			i++;
		}
	}
	else if(j!=b.size())
	{
		while(j<b.size())
		{
			if(result.size()==0) result.push_back(b[j]);
			else if(result[result.size()-1]!=b[j]) result.push_back(b[j]);
			j++;
		}
	}

	return result;
}

int main()
{
	//Take input
	int n;
	cout<<"Enter number of arrays: ";
	cin>>n;
	vector<vector<int>> list;
	for(int i=0;i<n;i++)
	{
		int size,x;
		vector<int> v;
		cout<<"Enter size of array "<<i+1<<": ";
		cin>>size;
		cout<<"Enter elements of the array "<<i+1<<": ";
		for(int j=0;j<size;j++)
		{
			cin>>x;
			v.push_back(x);
		}
		list.push_back(v);
	}

	//quick sort each array
	for(int i=0;i<n;i++)
	{
		quicksort(list[i],0,list[i].size()-1);
	}

	//merge arrays pairwise
	vector<int> result;
	result = list[0];
	for(int i=1;i<n;i++)
	{
		result=merge(result,list[i]);
	}

	//Diplay resulting array
	cout<<"FINAL SORTED AND MERGED ARRAY IS: ";
	for(auto x:result) cout<<x<<" ";
	cout<<endl;
}
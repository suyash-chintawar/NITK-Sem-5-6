/*
This program is a divide and conquer technique to 
divide a loaf of bread into a number of divisons which is user input
NOTE: Number of divisions must be a power of 2
*/
#include<bits/stdc++.h>
using namespace std;

//Functio nto divide a partition of loaf into two parts
void divide(int div,float low, float high)
{
	//least possible divison reached
	if(div==1) cout<<"("<<low<<" , "<<high<<")"<<endl;

	if(div>1)
	{
		//find middle
		float mid=(low+high)/2;

		// num divisons gets halved
		div/=2;

		//call divide on both halves
		divide(div,low,mid);
		divide(div,mid,high);
	}
}

int main()
{
	int bread_len,divisions;
	cout<<"Enter the length of bread: ";
	cin>>bread_len;
	cout<<"Enter the number of divisons to make: ";
	cin>>divisions;
	if(ceil(log2(divisions))!=floor(log2(divisions)))
	{
		cout<<"Number of divisions must be power of 2!!\n";
		return 0;
	}
	cout<<"\nDivisions are as follows:\n";
	divide(divisions,0,bread_len);
}
/*
This program takes in n numbers and
displays the largest number possible
NOTE:
1) Please do not give wrong inputs
*/
#include<bits/stdc++.h>
using namespace std;

//Using a custom comparator to sort in descending order
bool comparator(string n1, string n2)
{
    string n12 = n1 + n2;
    string n21 = n2 + n1;

    //after appending both strings check which is greater
    if(n12>n21) return true;
    return false;
}

int main()
{
    //no. of numbers
    int n;
    cout<<"Enter no. of numbers: ";
    cin>>n;

    //all numbers are taken in as strings
    vector<string> nums(n);
    cout<<"Enter the "<<n<<" numbers:\n";
    for(int i=0;i<n;i++) cin>>nums[i];

    //sort the array in descending order
    sort(nums.begin(),nums.end(),comparator);

    //append all the sorted string to form our result
    string res = "";
    for(int i=0;i<n;i++) res+=nums[i];
    cout<<"Maximum salary: "<<res<<endl;
}
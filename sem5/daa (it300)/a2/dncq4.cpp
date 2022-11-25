/*
This program performs binary multiplication of two binary numbers using
divide and conquer techinque
*/
#include<bits/stdc++.h> 
using namespace std;
#define mod 1000000007
typedef long long int ll;

//Compute power a^b efficiently
ll pow(ll a,ll b)
{
    ll res=1;
    while(b>0)
    {
        if(b%2==1) res=(res*a)%mod;
        a=(a*a)%mod;
        b/=2;
    }
    return res;
}

//Function to make the two strings of equal length (append zeros at start if not)
int same_lengths(string &s1, string &s2)
{
    int n1 = s1.size();
    int n2 = s2.size();

    //append zeros to smaller string
    if (n1<n2)
    {
        for(int i=0;i<n2-n1;i++) s1='0'+s1;
        return n2;
    }
    else if(n1>n2)
    {
        for(int i=0;i<n1-n2;i++) s2='0'+s2;
    }
    return n1;
}
 
//Function to perform addition of two binary numbers
string binary_addition(string s1,string s2)
{
    string result; //stores final added result
 
    int n = same_lengths(s1,s2);
    int c = 0;
 
    for (int i=n-1;i>=0;i--)
    {
        int a=s1[i]-'0';
        int b=s2[i]-'0';
        int s=(a^b^c)+'0'; //sum of three bits
        result = (char)s + result;
        c = (a&b)|(b&c)|(a&c); //carry of three bits
    }
 
    if(c!=0) // if carry still not zero
    {
        result='1'+result; 
    }  
 
    return result;
}

//Function to perform binary ultiplication using divide and conquer technique 
ll binary_multiplication(string s1, string s2)
{
    int n=same_lengths(s1, s2);
 
    if(n==0) return 0;
    else if(n==1) //single digit binary numbers
    {
        int a = s1[0]-'0';
        int b = s2[0]-'0';
        return a*b;
    }
    
    //calculating number of digits in two halves
    int num_left = n/2;   
    int num_right = n - num_left; 

    //dividing binary numbers in two halves
    string s1_left = s1.substr(0, num_left);
    string s1_right = s1.substr(num_left, num_right);
    
    string s2_left = s2.substr(0, num_left);
    string s2_right = s2.substr(num_left, num_right);
 
    //perform multiplication of the halves
    ll product_left = binary_multiplication(s1_left, s2_left);
    ll product_right = binary_multiplication(s1_right, s2_right);

    //addition of left and right halves
    string s1lr = binary_addition(s1_left, s1_right);
    string s2lr = binary_addition(s2_left, s2_right);

    ll product_mid = binary_multiplication(s1lr,s2lr);

    //calculate final result 
    ll result = product_left*(pow(2,2*num_right)) + (product_mid - product_left - product_right)*(pow(2,num_right)) + product_right;

    return result;
}
 
int main()
{
    //Take input
    string num1,num2;
    cout<<"Enter binary number 1: ";
    cin>>num1;
    cout<<"Enter binary number 2: ";
    cin>>num2;

    //Display final result
    ll res = binary_multiplication(num1,num2);
    cout<<"\nFINAL RESULT AFTER MULTIPLICATION: "<<res<<endl;
}
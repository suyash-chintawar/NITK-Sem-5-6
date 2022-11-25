#include<bits/stdc++.h>
using namespace std;
#define pi acos(-1)
typedef complex<double> cd;

void fft(vector<cd> &coef, bool inverse) {
    int n = coef.size();
    if (n == 1) return;

    vector<cd> left(n/2),right(n/2);

    for(int i=0;2*i<n;i++)
    {
    	left[i]=coef[2*i];
    	right[i]=coef[2*i+1];
    }

    fft(left, inverse);
    fft(right, inverse);

    double angle = 2*pi/n;
    if(inverse==false) angle*=-1;

    cd w(1), wn(cos(angle),sin(angle));

    for(int i=0;2*i<n;i++)
    {
    	coef[i]=left[i]+w*right[i];
    	coef[i+n/2]=left[i]-w*right[i];
    	if (inverse == true) 
    	{
            coef[i]/=2;
            coef[i+n/2]/=2;
        }
        w*=wn;
    }
}

int main()
{
	int n1,n2;
    cout<<"Enter degree of polynomial 1:";
    cin>>n1;
    vector<int> p1(n1+1);
    cout<<"Enter the "<<n1+1<<" coefficients (space seperated integers): \n";
    for(int i=0;i<n1+1;i++)
    {
        cin>>p1[i];
    }
    cout<<"Enter degree of polynomial 2:";
    cin>>n2;
    vector<int> p2(n2+1);
    cout<<"Enter the "<<n2+1<<" coefficients (space seperated integers): \n";
    for(int i=0;i<n2+1;i++)
    {
        cin>>p2[i];
    }

    int n = 1;
    while (n < p1.size()+p2.size()) 
        n <<= 1;

    vector<cd> coef_p1(p1.begin(),p1.end());
    vector<cd> coef_p2(p2.begin(),p2.end());
    coef_p1.resize(n);
    coef_p2.resize(n);

    fft(coef_p1,false);
    fft(coef_p2,false);

    for (int i = 0; i < n; i++)
        coef_p1[i] *= coef_p2[i];
    fft(coef_p1, true);

    vector<int> result(n);
    for (int i = 0; i < n; i++)
        result[i] = round(coef_p1[i].real());

    cout<<"\nCoefficients of final poylnomial are:";
    cout<<"(In the order of x^0...x^n-1)\n";

    for (int i=0;i<result.size();i++) 
    {
        cout<<result[i]<<' ';
    }
    cout<<endl;
}
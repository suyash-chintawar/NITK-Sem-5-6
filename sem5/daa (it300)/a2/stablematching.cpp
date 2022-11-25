/*
NOTE:
1) This program performs stable matching for admission in hospitals in given loactions
2) Hospitals will send proposals to students in this program
3) There can be multiple perfect matches, one of them is computed
4) The program doesn't check for incorrect input so please refrain from inserting wrong inputs
*/

#include<bits/stdc++.h>
using namespace std;

//to store ids of hospitals and students for easy computation
unordered_map<string,int> id; 

//Function to perform stable matching
void matching(int n,vector<string> shlist,vector<vector<int>> preference)
{
	vector<int> matching(n,-1);// stores matched ids of students with hospitals
	vector<bool> assigned(n,false); // stores whether a student has been assigned or not
	int free=n; //number of free hospitals left
	while(free>0) //until all hospitals have been paired
	{
		int student;//find the student who is not assigned
		for(int i=0;i<n;i++)
		{
			if(!assigned[i])
			{
				student=i;
				break;
			}
		}

		//find suitable match for him
		for(int i=0;i<n;i++)
		{
			if(assigned[student]) break;// if he's already assigned

			//if the student in the hospital's pref list is not assigned
			if(matching[preference[student][i]-n]==-1) 
			{
				//match both of them
				matching[preference[student][i]-n] = student;
				assigned[student]=true;
				free--;
			}
			else //if a student is assigned, see whether our student has higher pref than the other student 
			{
				int prev_student = matching[preference[student][i]-n]; //the student shes assigned with
				int temp;
				for(int j=0;j<n;j++)
				{
					if(preference[preference[student][i]][j]==prev_student or preference[preference[student][i]][j]==student)
					{
						temp = preference[preference[student][i]][j];
						break;
					}
				}
				if(temp==student) //if our student has higher preference, update the matching
				{
					matching[preference[student][i]-n] = student;
					assigned[prev_student] = false;
					assigned[student] =true;
				}
			}
		}
	}

	//Final answer is stored 'matching' array 
	cout<<"\nFINAL MATCHING IS: (Format: (student,hospitals)):\n";
	for(int i=0;i<n;i++)
	{
		cout<<"("<<shlist[i+n]<<","<<shlist[matching[i]]<<")"<<'\n';
	}
}

int main()
{
	//Take input
	int n;
	cout<<"Number of hospitals/students: ";
	cin>>n;
	vector<string> shlist(2*n);
	cout<<"Enter names of hospitals ("<<n<<" space seperated strings):\n";
	for(int i=0;i<n;i++) cin>>shlist[i];
	cout<<"Enter names of students ("<<n<<" space seperated strings):\n";
	for(int i=0;i<n;i++) cin>>shlist[i+n];
	
	//assign ids to hospitals and students in order
	for(int i=0;i<2*n;i++)
	{
		id[shlist[i]]=i;
	}

	//Stores preferences of hospitals and students in order
	vector<vector<int>> preference(2*n,vector<int> (n,-1));
	cout<<"\nEnter preference list of hospitals.. \nNOTE:("<<n<<" Space seperated strings of students from highest to lowest preference)\n";
	for(int i=0;i<n;i++)
	{
		string sender=shlist[i];
		cout<<"Preference list of "<<sender<<":\n";
		for(int j=0;j<n;j++)
		{
			string pref;
			cin>>pref;
			preference[id[sender]][j]=id[pref];
		}
	}
	cout<<"\nEnter preference list of students.. \nNOTE:("<<n<<" Space seperated strings of hospitals from highest to lowest preference)\n";
	for(int i=n;i<2*n;i++)
	{
		string receiver=shlist[i];
		cout<<"Preference list of "<<receiver<<":\n";
		for(int j=0;j<n;j++)
		{
			string pref;
			cin>>pref;
			preference[id[receiver]][j]=id[pref];
		}
	}

	matching(n,shlist,preference);
}
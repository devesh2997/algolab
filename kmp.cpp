#include<bits/stdc++.h>
using namespace std;

bool search(string s,string p,vector<int> pre)
{
	int i=0,j=-1;

	while(j+1!=p.length() && i<s.length())
	{
		if(s[i]==p[j+1])
		{
			i++;
			j++;
		}
		else
		{
			if(j==-1)
				i++;
			else
				j=pre[j]-1;
		}
	}
	if(j+1==p.length())
		return 1;
	return 0;
}

vector<int> prefix(string s)
{
	int n=s.length(),i,j;
	vector<int> F(n);
	F[0]=0;
	for(i=1;i<n;i++)
	{
		j=F[i-1];
		while(j>0 && s[i]!=s[j])
			j=F[j-1];
		if(s[i]==s[j])
			j++;
		F[i]=j;
	}
	return F;
}

int main()
{
	string s,p;
	cout<<"Enter String :";
	cin>>s;
	cout<<"Enter Pattern to find:";
	cin>>p;
	vector<int> pre = prefix(p);
	if(search(s,p,pre))
		cout<<"Found\n";
	else
		cout<<"Not Found.\n";
}

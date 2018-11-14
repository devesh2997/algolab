#include<iostream>
#define MAX 100
using namespace std;


void find(float L[][MAX],float U[][MAX],float A[][MAX],int p[][MAX],int n)
{
	int i,ind,j,k;
	double maxi;
	for(i=0;i<n-1;i++)
	{
		maxi=-10000.12;
		for(j=i;j<n;j++)
		{
			if(maxi<abs(A[j][i]))
			{
				maxi=abs(A[j][i]);
				ind=j;
			}
		}
		for(j=0;j<=n;j++)
			swap(A[i][j],A[ind][j]);
		for(j=i+1;j<n;j++)
			A[j][i] /= A[i][i];

		for(j=i+1;j<n;j++)
		{
			for(k=i+1;k<n;k++)
			{
				A[j][k] -= A[j][i]*A[i][k];
			}
		}
		/*for(j=0;j<n;j++)
		{
			for(k=0;k<n;k++)
				cout<<A[j][k]<<" ";
			cout<<endl;
		}
		cout<<endl;*/
	}
	for(i=0;i<n;i++)
	{
		for(j=0;j<i;j++)
			L[i][j]=A[i][j];
		for(j=i;j<n;j++)
			L[i][j]=0;
		L[i][i]=1;
		for(j=i;j<n;j++)
			U[i][j]=A[i][j];
		for(j=0;j<i;j++)
			U[i][j]=0;
	}
	
	cout<<"Printing L matrix :\n";
	for(i=0;i<n;i++)
	{
		for(j=0;j<n;j++)
			cout<<L[i][j]<<" ";
		cout<<endl;
	}
	cout<<"\nPrinting U Matrix :\n";
	for(i=0;i<n;i++)
	{
		for(j=0;j<n;j++)
			cout<<U[i][j]<<" ";
		cout<<endl;
	}
	cout<<endl;
	float Y[n],var;
	for(i=0;i<n;i++)
	{
		var=A[i][n];
		for(j=0;j<i;j++)
		{
			var -= Y[j]*L[i][j];
		}
		Y[i]=var;
		cout<<"y"<<i+1<<"="<<Y[i]<<endl;
	}
	float X[n];
	cout<<endl;
	for(i=n-1;i>=0;i--)
	{
		var=Y[i];
		for(j=n-1;j>i;j--)
			var -= X[j]*U[i][j];
		X[i]=var/U[i][i];
	}
	cout<<"Solutions -\n";
	for(i=0;i<n;i++)
		cout<<"x"<<i+1<<"="<<X[i]<<endl;
}

int main()
{
	int n,i,j;
	cout<<"Enter Variables: ";
	cin>>n;
	float A[MAX][MAX],L[MAX][MAX],U[MAX][MAX];
	cout<<"Enter Equation in form ax+by+cz=d\n";
	for(i=0;i<n;i++)
		for(j=0;j<=n;j++)
			cin>>A[i][j];

	/*for(i=0;i<n;i++)
	{
		for(j=0;j<n;j++)
			cout<<A[i][j]<<" ";
		cout<<endl;
	}*/
	cout<<endl;
	int p[1][MAX];
	for(i=0;i<n;i++)
		p[0][i]=i+1;
	find(L,U,A,p,n);
}

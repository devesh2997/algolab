#include<bits/stdc++.h>
using namespace std;

void Floyd_warshall(vector<vector<int> > &g, vector<vector<int> > &parent, int n)
{
	for(int k=1;k<=n;k++)
		for(int i=1;i<=n;i++)
			for(int j=1;j<=n;j++){
					if(g[i][j]>g[i][k]+g[k][j]){
						g[i][j]=g[i][k]+g[k][j];
						parent[i][j]=parent[k][j];
					}
					else if(parent[i][j]==-1)parent[i][j]=i;
				}
}

int main(){
	int v,m; cout<<"Enter the number of vertices and edges\n"; cin>>v>>m;
	long long a = INT_MAX/30;
	vector<vector<int> > g(v+1, vector<int>(v+1,a));
	vector<vector<int> > parent(v+1,vector<int>(v+1,-1)); for(int i=0;i<=v;i++)parent[i][i]=i;
	cout<<"Enter source first, then destination and weight\n";
	for(int i=0;i<m;i++)	{
		int s,d,w;		
		cin>>s>>d>>w;
		g[s][d]=w;
	}
	Floyd_warshall(g,parent,v);
	while(1)
	{
		cout<<"Enter pair of vertices , or -1 to exit:\n";
		int i,j; cin>>i; if(i==-1)break; cin>>j;
		cout<<"minimum path length is "<<g[i][j]<<"\n";
	}
}	


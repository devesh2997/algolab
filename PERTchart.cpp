#include <bits/stdc++.h>
using namespace std;
#define ll long long

vector<vector<pair<int,int> > > adj;
vector<bool> vis;
stack<int> st;

void Topsort(int v)
{
	vis[v]=true;
	for(int i(0); i<(int)adj[v].size();i++)
	{
		if(vis[adj[v][i].first]==false)
			Topsort(adj[v][i].first);			
	}
	st.push(v);
}
int main()
{
	int v,e;
	cout<<"Enter number of nodes and edges resp.\n";
	cin>>v>>e;
	adj.resize(v);
	vis.resize(v);
	for(int i(0);i<v;i++)
	vis[i]=false;
	cout<<"enter edges -> source first then destination,then weight\n";
	for(int i(0); i < e;i++)
	{
		int s,d,w;
		cin>>s>>d>>w;
		adj[s].push_back({d,-1*w});		
	}
	for(int i(0);i<v;i++)
	{
		if(vis[i] == false)
			Topsort(i);
	}
	int dist[v+1];
	for(int i(0);i<=v;i++)
	{
		dist[i]=(int)10e9;
	}
	
	int n =st.size();int madist=INT_MAX;
	for(int i(0);i<n;i++)
	{
		int curnode=st.top();
		
		if(dist[curnode]>10e8)
		dist[curnode]=0;
				for(int j(0);j<adj[curnode].size();j++)
			{
				int checknode=adj[curnode][j].first;
				dist[checknode]=min(dist[checknode],dist[curnode]+adj[curnode][j].second);
				madist=min(madist,dist[checknode]);
			}
			st.pop();
		}
	
	cout<<"The maximum distance between any two nodes is "<<-1*madist<<endl;
	//i/p  ---- 6 9 0 1 5 1 2 2 2 3 7 3 4 -1 4 5 -2 0 2 3 1 3 6 2 4 4 2 2 5
	
}

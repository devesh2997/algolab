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
		adj[s].push_back({d,w});		
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
	cout<<"Enter source node number:\n";
	int sc;cin>>sc;
	dist[sc]=0;
	int n =st.size();
	for(int i(0);i<n;i++)
	{
		int curnode=st.top();
		st.pop();
		if(dist[curnode]>10e8)
			continue;
		else
		{
			for(int j(0);j<adj[curnode].size();j++)
			{
				int checknode=adj[curnode][j].first;
				dist[checknode]=min(dist[checknode],dist[curnode]+adj[curnode][j].second);
			}
		}
	}
	cout<<"the shortest distances of node "<<sc<<" are : \n";
	for(int i(0);i<v;i++)
	{
		cout<<i<<" -> ";
		if(dist[i]>10e8)
			cout<<" not reachable\n";
		else
			cout<<dist[i]<<endl;	
	}
	
	
}

#include<iostream>
#include<string.h>
#include<stdio.h>
#include<limits.h>
#include<stdlib.h>
#include<vector>

#define MIN(x,y) (x>y)?y:x

using namespace std;

int dtcount=0;

void checkAP(vector<int> &arti_point,int dt[],int l[],int p[],int u,int v,int child_count)
{
	if(p[u]==-1 && child_count>1)
			arti_point.push_back(u);
	if(p[u]!=-1 && l[v]>=dt[u])
			arti_point.push_back(u);
}

void dfs1(vector<vector<int>> &g,int visited[],int u)
{
	visited[u]=1;
	cout<<u<<"---"<<g[u].size()<<" ";
	for(int i=0;i<g[u].size();i++)
	{
		if(visited[g[u][i]]==0)
		{
			dfs1(g,visited,g[u][i]);
		}
	}
}


void dfs(vector<vector<int>> &g,int visited[],int u,int dt[],int l[],int p[],vector<int> &arti_point)
{
	visited[u]=1;
	dt[u]=++dtcount;
	l[u]=dt[u];
	int child_count=0;
	for(int i=0;i<g[u].size();i++)
	{
		if(visited[g[u][i]]==0)
		{
			//cout<<u<<"--"<<g[u][i]<<endl;
			p[g[u][i]]=u;
			child_count++;
			dfs(g,visited,g[u][i],dt,l,p,arti_point);	
			l[u]=MIN(l[u],l[g[u][i]]);
			checkAP(arti_point,dt,l,p,u,g[u][i],child_count);
		}
		else if(p[u]!=g[u][i])
			l[u]=MIN(l[u],dt[g[u][i]]);
	}
}

int main()
{
	int n,m;
	cin>>n>>m;
	//n=n+1;
	vector<vector<int>> g(n);
	int dt[n];
	int l[n];
	int p[n];
	for(int i=0;i<n;i++)
	{
		dt[i]=l[i]=INT_MAX;
		p[i]=-1;
	}
	for(int i=0;i<m;i++)
	{
		int x,y;
		cin>>x>>y;
		g[x].push_back(y);
		g[y].push_back(x);
	}
	// for(int i=0;i<n;i++)
	// {	
	// 	cout<<i<<" : ";
	// 	for(int j=0;j<g[i].size();j++)
	// 	{
	// 		cout<<g[i][j]<<" ";
	// 	}
	// 	cout<<endl;
	// }
	int visited[n];
	vector<int> arti_point;
	memset(visited,0,sizeof(visited));
	for(int i=0;i<n;i++)
	{
		if(visited[i]==0)
		{
			dfs(g,visited,i,dt,l,p,arti_point);
			// dfs1(g,visited,i);
			// cout<<"hello";
		}
	}

	// for(int i=0;i<n;i++)
	// {
	// 	cout<<i<<"\t"<<dt[i]<<"\t"<<l[i]<<"\t"<<p[i]<<endl;
	// }
	cout<<"Articulation point : ";
	for(int i=0;i<arti_point.size();i++)
	{
		cout<<arti_point[i]<<" ";
	}
	cout<<"\n";
	return 0;
}
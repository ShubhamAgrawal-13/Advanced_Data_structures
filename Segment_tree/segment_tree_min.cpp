#include<bits/stdc++.h>
using namespace std;

#define MAX 400005
#define ll long long

int tree[MAX];


// For sum queries


void update(int* a, int node, int start, int end, int index, int value)
{
	//printf("(%d,%d,%d)\n",node,start,end);
	if(start == end)
	{
		a[index]=value;
		tree[node]=value;
	}	
	else
	{
		int mid = (start+end)/2;

		if(index<=mid)
		{
			update(a,2*node,start,mid,index,value);
		}
		else
		{
			update(a,2*node+1,mid+1,end,index,value);
		}

		tree[node]=min(tree[2*node], tree[2*node+1]);
	}
}

int query(int node, int start, int end, int left, int right)
{
	if( right < start || end < left)
	{
		return MAX;
	}
	//printf("(%d,%d,%d,%d,%d)\n",node,start,end,left,right);
	if( left <= start && right >= end)
	{
		return tree[node];
	}

	int mid = (start + end)/2;

	int q_left = query(2*node,start, mid ,left, min(right, mid));

	int q_right = query(2*node+1, mid+1, end, max(left,mid+1),right);

	return min(q_left, q_right);
}

void build(int* a,int node,int start, int end)
{
	if(end < start)
	{
		return;
	}

	if(start == end)
	{
		tree[node]=a[start];
		return;
	}
	int mid = (start+end)/2;
	build(a,2*node,start,mid);
	build(a,2*node+1,mid+1,end);


	//sum

	tree[node] = min(tree[2*node],tree[2*node +1]);
}


void print_tree(int node,int start,int end,int space)
{
	if(tree[node]==-1)
		return;

	int mid=(start+end)/2;
	print_tree(2*node+1,mid+1,end,space+10);
	for(int i=0;i<space;i++)
		cout<<" ";
	cout<<tree[node]<<"["<<start<<":"<<end<<"]\n";
	print_tree(2*node,start,mid,space+10);
}

int main()
{
	memset(tree,-1,MAX);
	int n,q;
	cin>>n>>q;
	int a[n+1];
	for(int i=1;i<=n;i++)
		cin>>a[i];
	build(a,1,1,n);
	//print_tree(1,1,n,0);
	for(int k=0;k<q;k++)
	{
		char ch;
		cin>>ch;

		if(ch=='q')
		{
			int l,r;
			cin>>l>>r;
			cout<<query(1,1,n,l,r)<<endl;
		}

		if(ch=='u')
		{
			int i,v;
			cin>>i>>v;
			update(a,1,1,n,i,v);
			//print_tree(1,1,n,0);
		}
	}

	// print_tree(1,0,9,0);
}
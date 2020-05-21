#include<bits/stdc++.h>
using namespace std;

class FenwickTree
{
public:
	vector<int> tree;
	int n;
	FenwickTree(int n){
		this->n = n+1;
		tree.assign(n+1,0);
	}
	
	void update(int idx, int delta)
	{
		idx++;
		// int delta=tree[idx]-value;
		for(;idx<n; idx += idx & -idx)
			tree[idx]+=delta;
	}

	void build(vector<int> &a)
	{
		for(int i=0;i<a.size();i++)
			update(i,a[i]);
	}

	int sum(int idx)
	{
		int ret=0;
		++idx;

		for(;idx>0; idx -= idx & -idx)
			ret+=tree[idx];

		return ret;
	}

	int query(int l, int r)
	{
		return sum(r)-sum(l-1);
	}

	void print()
	{
		cout<<"\n\nTree : ";
		for(int i=1;i<n;i++)
		{
			cout<<tree[i]<<" ";
		}
		cout<<"\n\n";
	}
	
};

int main()
{
	int n;
	cin>>n;
	vector<int> a(n);
	for(int i=0;i<n;i++)
		cin>>a[i];
	FenwickTree f(n);
	f.build(a);
	f.print();
}
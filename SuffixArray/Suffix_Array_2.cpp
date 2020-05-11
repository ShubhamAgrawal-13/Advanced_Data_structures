#include<stdio.h>
#include<iostream>
#include<stdlib.h>
#include<string.h>
#include<algorithm>
#include<vector>

using namespace std;

typedef struct SuffixNode
{
	int index;
	int rank;
	int nextrank;

}Node;

void radixsortrank(vector<Node> &a,int n,int d)
{
	//d=5;
	int base=1;
	for(int k=1;k<=d;k++)
	{
		int p=base;
		//cout<<"Rank Pass "<<k<<" : \n";
		vector<vector<Node>> v(10);
		for(int i=0;i<n;i++)
		{
			int m=(a[i].rank/p)%10;
			v[m].push_back(a[i]);
		}
		int id=0;
		for(int i=0;i<10;i++)
		{
			//cout<<i<<" : ";
			for(int j=0;j<v[i].size();j++)
			{
				a[id++]=v[i][j];	
				//cout<<v[i][j].rank<<" ";
			}
			//cout<<endl;
		}
		//cout<<endl;
		//cout<<"Array after Pass "<<k<<" : \n";
		// for(int i=0;i<n;i++)
		// {
		// 	cout<<a[i].rank<<" ";
		// }
		//cout<<endl;
		base*=10;

		//cout<<endl;
	}
}


void radixsortnextrank(vector<Node> &a,int n,int d)
{
	//d=3;
	int base=1;
	for(int k=1;k<=d;k++)
	{
		int p=base;
		//cout<<"Next rank Pass "<<k<<" : \n";
		vector<vector<Node>> v(10);
		for(int i=0;i<n;i++)
		{
			int m=(a[i].nextrank/p)%10;
			v[m].push_back(a[i]);
		}
		//cout<<"hello";
		int id=0;
		for(int i=0;i<10;i++)
		{
			//cout<<i<<" : ";
			for(int j=0;j<v[i].size();j++)
			{
				a[id++]=v[i][j];	
				//cout<<v[i][j].nextrank<<" ";
			}
			//cout<<endl;
		}
		// cout<<endl;
		// cout<<"Array after Pass "<<k<<" : \n";
		// for(int i=0;i<n;i++)
		// {
		// 	cout<<a[i].nextrank<<" ";
		// }
		//cout<<endl;
		base*=10;

		//cout<<endl;
	}
}

int numberOfDigits(int n)
{
	int k=0;
	int temp=n;
	while(temp!=0)
	{
		temp/=10;
		k++;
	}
	return k;
}

int compare_node(Node a,Node b)
{
	if(a.rank<b.rank)
		return 1;
	else if(a.rank>b.rank)
		return 0;
	else
	{
		if(a.nextrank<b.nextrank)
			return 1;
		else 
			return 0;
	}
}

int main()
{
	//cout<<"suffix array 1 - minimum lexicographic rotation : \n";
	int nlen,kk;
	cin>>nlen;
	cin>>kk;
	string s;
	//cout<<"Enter string : ";
	cin>>s;
	// int oldn = s.length();
	// //cout<<s<<" "<<oldn<<endl;
	// s=s+s;
	int n = s.length();
	//cout<<n<<" "<<s<<endl;

	int index[n]={0};
	vector<Node> suffixes(n);

	for(int i=0;i<n;i++)
	{
		suffixes[i].index=i; 
		suffixes[i].rank=s[i]-47;
		if((i+1)<n)
			suffixes[i].nextrank=s[i+1]-47;
		else
			suffixes[i].nextrank=-1;
	}	
	int d = numberOfDigits(n);
	radixsortrank(suffixes,n,d);
	sort(suffixes.begin(),suffixes.end(),compare_node);

	// radixsortnextrank(suffixes,n,d);

	// for(int i=0;i<n;i++)
	// {
	// 	cout<<endl;
	// 	cout<<"\n"<<suffixes[i].index<<"\t"<<suffixes[i].rank<<"\t"<<suffixes[i].nextrank<<endl;
	// }
	int prev;
	for(int k=4;k<2*n;)
	{
		index[suffixes[0].index]=0;
		int r=0;
		prev = suffixes[0].rank;
		suffixes[0].rank=0;

		for(int i=1;i<n;i++)
		{
			index[suffixes[i].index]=i;
			int flag1=0,flag2=0;
			if(suffixes[i].nextrank == suffixes[i-1].nextrank)
			{
				flag1=1;
			}
			if(suffixes[i].rank == prev)
			{
				flag2=1;
			}

			if(flag2 && flag1)
			{
				prev=suffixes[i].rank;
				suffixes[i].rank=r;
			}
			else
			{
				r++;
				prev=suffixes[i].rank;
				suffixes[i].rank=r;
			}
		}

		for(int i=0;i<n;i++)
		{
			int t=k/2,temp;

			if(suffixes[i].index+t < n)
				temp=suffixes[index[suffixes[i].index+t]].rank;
			else
				temp=-1;

			suffixes[i].nextrank=temp;
		}

		sort(suffixes.begin(),suffixes.end(),compare_node);
		// radixsortrank(suffixes,n,d);
		// radixsortnextrank(suffixes,n,d);

		k=k+k;
		
	}
	for(int i=0;i<n;i++)
	{
		index[suffixes[i].index]=i;
	}

	//Kasai's Algorithm

	int lcp[n];
	int k=0;
	int j=0;
	for(int i=0;i<n;i++)
	{
		if(index[i]==n-1)
		{
			k=0;
			continue;
		}
		j=suffixes[index[i]+1].index;

		int t1=i+k;
		int t2=j+k;
		while((i+k)<n && (j+k)<n  && s[i+k]==s[j+k])
		{
			k++;
		}

		lcp[index[i]]=k;
		if(k>0)
			k--;
	}

	lcp[n-1]=0;
	int max=0;
	for(int i=0;i<n;i++)
	{
		//cout<<lcp[i]<<endl;
		if(lcp[i]>max)
		{
			max=lcp[i];
		}
	}

	if(max==0)
		cout<<-1<<endl;
	else
		cout<<max<<endl;
	return 0;
}
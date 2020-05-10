#include<stdio.h>
#include<iostream>
#include<stdlib.h>
#include<string.h>
#include<vector>

using namespace std;

typedef class TrieNode
{
	public:
		TrieNode* characters[27];
		int end;
		TrieNode()
		{
			for(int i=0;i<27;i++)
			{
				characters[i]=NULL;
			}
			end=0;
		} 
}Node;

Node* root=new Node();
vector<string> allprefixes;

void insert(Node* root,string s)
{
	Node* temp = root;
	for(int i=0;i<s.length();i++)
	{
		int t = s[i]-97;
		if(temp->characters[t]!=NULL)
		{
			temp=temp->characters[t];
		}
		else
		{
			temp->characters[t]=new Node();
			temp=temp->characters[t];
		}
	}

	temp->end=1;
}


int search(Node* root,string s)
{
	Node* temp=root;
	for(int i=0;i<s.length();i++)
	{
		int t = s[i]-97;
		if(temp->characters[t]!=NULL)
		{
			temp=temp->characters[t];
		}
		else
		{
			break;
		}
	}
	if(temp->end==1)
		return 1;
	return 0;
}

void newprefix(Node* temp,string prefix)
{
	if(temp->end==1)
	{
		allprefixes.push_back(prefix);
	}

	for(int i=0;i<27;i++)
	{
		if(temp->characters[i]!=NULL)
		{
			char c = i+97;
			string np = prefix+c;
			newprefix(temp->characters[i],np);
		}
	}

}

vector<string> prefixes(Node* root,string prefix)
{
	Node* temp=root;
	allprefixes.clear();
	for(int i=0;i<prefix.length();i++)
	{
		int t = prefix[i]-97;
		if(temp->characters[t]!=NULL)
		{
			temp=temp->characters[t];
		}
		else
		{
			return allprefixes;
		}
	}
	
	newprefix(temp,prefix);
	return allprefixes;
}

int main()
{
	int n;
	cout<<"Trie : \n";
	cout<<"Enter n : ";
	cin>>n;
	string strs[n];
	for(int i=0;i<n;i++)
	{
		cin>>strs[i];
		insert(root,strs[i]);
	}
	// insert(root,"abcdef");
	// insert(root,"abchjf");
	// insert(root,"shubham");
	string p;
	// cout<<"Enter the prefix to be searched : ";
	// cin>>p;
	vector<string> v = prefixes(root,"");
	// for(int i=0;i<v.size();i++)
	// {
	// 	cout<<v[i]<<endl;
	// }
	while(1)
	{
		string ss;
		cout<<"Enter the string to be searched : ";
		cin>>ss;
		if(search(root,ss) == 1)
			cout<<"String is Present\n";
		else
			cout<<"String is not Present\n";
		char op;
		cout<<"Enter 1 to exit : ";
		cin>>op;
		if(op=='1')
			break;
	}
	return 0;
}
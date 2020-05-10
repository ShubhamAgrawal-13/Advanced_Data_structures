#include<stdio.h>
#include<iostream>
#include<stdlib.h>
#include<string.h>
#include<vector>

using namespace std;

#define ll long long

typedef class TrieNode
{
    public:
        TrieNode* characters[2];
        int end;
        TrieNode()
        {
            for(int i=0;i<2;i++)
            {
                characters[i]=NULL;
            }
            end=0;
        } 
}Node;

Node* root=new Node();
ll maxx;


string numtobinary(ll num)
{
    string s;
    ll j=num;
    int c=40;
    while(j>0)
    {
        char ch = j%2+48;
        s=ch+s;
        j=j/2;
        c--;
    }
    //char ch='0';
    for(int i=c;i>0;i--)
    {
        s='0'+s;
    }
    //cout<<s<<endl;
    return s;
}

ll binarytonum(string ss)
{
    ll sum=0,p=1;
    for(int i=ss.length()-1;i>=0;i--)
    {
        sum+=(ss[i]-48)*p;
        p=p*2;
    }
    return sum;
}

void insert(Node* root,string s)
{
    Node* temp = root;
    for(int i=0;i<s.length();i++)
    {
        int t = s[i]-48;
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
        int t = s[i]-48;
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


void newprefix(Node* temp,string prefix,ll x)
{
    if(temp->end==1)
    {
        //allprefixes.push_back(prefix);
        ll t = binarytonum(prefix);
        //cout<<t<<"---------"<<endl;
        t=t^x;
        if(t>maxx)
            maxx=t;
        //cout<<prefix<<endl;
    }
    for(int i=0;i<2;i++)
    {
        if(temp->characters[i]!=NULL)
        {
            char c = i+48;
            string np = prefix+c;
            newprefix(temp->characters[i],np,x);
        }
    }
}

void prefixes(Node* root,string prefix,ll x)
{
    Node* temp=root;
    string sxx="";
    for(int i=0;i<prefix.length();i++)
    {
        int t = prefix[i]-48;
        int tt;
        if(t==0)
            tt=1;
        else
            tt=0;
        if(temp->characters[tt]!=NULL)
        {
            char ck=tt+48;
            sxx+=ck;
            temp=temp->characters[tt];
        }
        else if(temp->characters[t]!=NULL)
        {
            char ck=t+48;
            sxx+=ck;
            temp=temp->characters[t];
        }
        else
        {
            return;
        }
    }
    newprefix(temp,sxx,x);
}

int main()
{
    int n;
    int m;
    //cout<<"Binary Trie : ";
    //cout<<"Enter n : ";
    cin>>n;
    cin>>m;
    string strs[n];
    ll num;
    for(int i=0;i<n;i++)
    {
        cin>>num;
        strs[i]=numtobinary(num);
        insert(root,strs[i]);
    }
    while(m-- >0)
    {
        ll x;
        cin>>x;
        maxx=0;
        string sx=numtobinary(x);
        //cout<<sx<<endl;
        prefixes(root,sx,x);
        cout<<maxx<<endl;
    }
    return 0;
}
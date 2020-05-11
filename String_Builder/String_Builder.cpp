#include<iostream>
#include<string.h>
#include<stdio.h>
#include<stdlib.h>

using namespace std;
char text[100000];

class Node
{
	public:
		char* a;
		Node* next;
		Node()
		{
			a=NULL;
			next=NULL;
		}
};

class stringBuilder
{
	public:
		Node* first;
		Node* last;

		stringBuilder()
		{
			first=NULL;
			last=NULL;
		}

		friend stringBuilder stringInitialize(char*);
		friend stringBuilder stringAppend(stringBuilder,stringBuilder);

		void printSB()
		{
			Node* start=this->first;
		    Node* stop=this->last;
		    while(start!=stop)
		    {
		    	cout<<start->a;
		    	start=start->next;
		    }
		    cout<<start->a;
		}
};


ostream& operator<<(ostream& ost, const stringBuilder& sb)
{
	    Node* start=sb.first;
	    Node* stop=sb.last;
	    while(start!=stop)
	    {
	    	ost<<start->a;
	    	start=start->next;
	    }
	    ost<<start->a;
	    return ost;
}


stringBuilder stringInitialize(char* na)
{
		stringBuilder sb;
		Node* temp = new Node();

		temp->a=na;
		temp->next=NULL;

		sb.first=temp;
		sb.last=temp;

		return sb;
}


int findSubstring(stringBuilder sb,char* pat)
{
	memset(text,'\0',100000);
	Node* start=sb.first;
	Node* stop=sb.last;
	while(start!=stop)
	{
	   	strcat(text,start->a);
	    start=start->next;
	}
	strcat(text,start->a);
	//cout<<text<<"------------"<<endl;
	int m = strlen(pat); 
    int n = strlen(text);  
    int lps[m]; 
    int len = 0; 
    lps[0] = 0; 
    int i = 1; 
    while(i<m) 
    { 
        if(pat[i] == pat[len]) 
        {  
            lps[i++] = ++len; 
        } 
        else 
        { 
            if(len != 0) 
            { 
                len=lps[len - 1]; 
            } 
            else
            { 
                lps[i] = 0; 
                i++; 
            } 
        } 
    }
  
    i=0; 
    int j=0; 
    while(i < n) 
    { 
        if(pat[j] == text[i]) 
        { 
        	i++;
            j++;  
        } 
  
        if(j == m) 
        { 
        	return (i-j); 
        } 
        else if(i < n && pat[j] != text[i]) 
        { 
            if(j != 0) 
                j=lps[j-1]; 
            else
                i=i+1; 
        } 
    } 
    return -1;
}

stringBuilder stringAppend(stringBuilder sb1,stringBuilder sb2)
{
		stringBuilder sb3=sb1;
		sb3.first=sb1.first;
		sb3.last=sb1.last;
		sb3.last->next=sb2.first;
		sb3.last=sb2.last;
		return sb3;
}

int main()
{
	stringBuilder sb1 = stringInitialize("shubham");
	stringBuilder sb2 = stringInitialize("agrawal");
	cout<<sb1<<" "<<sb2<<endl;
	stringBuilder sb3 = stringAppend(sb1,sb2); //sb1 string is changed 

	cout<<sb1<<" "<<sb2<<endl;
	cout<<sb3<<" \n";
	stringBuilder sb4 = stringInitialize("hello"); 
	stringBuilder sb5 = stringInitialize("world");
	stringBuilder sb6 = stringAppend(sb4,sb5); //sb4 string is changed 
	cout<<sb6<<" "<<endl;
	int x=findSubstring(sb6,"worl");
	cout<<x<<endl; 
	//cout<<KMP("agr","shubhamagrawal")<<endl;
	// stringBuilder sb4 = stringAppend(sb1,sb3);
	// cout<<sb4<<endl;
	return 0;
}
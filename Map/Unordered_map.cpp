#include<iostream>
#include<string.h>
#include<stdio.h>
#include<stdlib.h>

using namespace std;

template<typename K,typename V>
class UnorderedMap
{
public:
	class TP
	{
	public:
		V value;
		int present;
	};
	class Node
	{
		public:
			K key;
			V value;
			Node* next;
			Node()
			{

			}
			Node(K k,V v)
			{
				key=k;
				value=v;
				next=NULL;
			}
	};

	int msize=0;
	int capacity=0;
	Node** ht;

	UnorderedMap()
	{
		capacity=1003;
		msize=0;
		//cout<<"hello3\n";
		ht=new Node*[capacity];
		for(int i=0;i<capacity;i++)
		{
			ht[i]=NULL;
		}
	}

	unsigned long int hashfunction(K k)
	{
		string s=to_string(k);
		unsigned long int hash;
			    
		hash = 9911;
		//cout<<"hello hash\n";
		for (int i=0;i<s.length();i++)
		{
		        hash = s[i] + hash + hash/11; 
		}

		return (hash % capacity);
	}

	int size()
	{
		return msize;
	}

	bool empty()
	{
		if(msize==0)
			return true;
		return false;
	}

	V getValue(K k)
	{
		TP tp=find(k);
		if(tp.present==0)
			throw "-1";
		return tp.value;
	}

	TP find(K k)
	{
		int index=hashfunction(k);
		//cout<<"hello\n";
		Node* head = ht[index];
		TP tp;
		//cout<<index<<endl;
		//cout<<"hello4\n";
		while(head!=NULL)
		{
			//cout<<head->key<<endl;
			if(head->key == k)
			{
				tp.value=head->value;
				tp.present=1;
				//cout<<"hello1\n";
				return tp;
			}
			//cout<<"hello1\n";
			head=head->next;
		}
		tp.present=0;
		return tp;
	}

	void insert(K k,V v)
	{
		// Node* temp = new Node(k,v);

		int index=hashfunction(k);
		Node* head = ht[index];
		//cout<<"hello\n";
		//cout<<index<<endl;
		while(head!=NULL)
		{
			if(head->key==k)
			{
				head->value=v;
				return;
			}
			head=head->next;
		}

		msize++;
		head=ht[index];
		Node* temp = new Node(k,v);
		temp->next=head;
		ht[index]=temp;

		int loadfactor=(1.0*msize)/capacity;
		if (loadfactor > 0.55) 
        { 
            Node** temp1 = ht;
            int tempcap=capacity;
            capacity=capacity+capacity/2; 
            ht = new Node*[capacity]; 
             
            msize = 0; 
            for (int i = 0; i < capacity; i++) 
                ht[i]=NULL; 
  
            for (int i=0;i<tempcap;i++) 
            { 
                while (temp1[i] != NULL) 
                { 
                    //add(headNode.key, headNode.value);
                    insert(temp1[i]->key,temp1[i]->value); 
                    temp1[i] = temp1[i]->next; 
                } 
            } 
        } 
	}

};

int main()
{
	UnorderedMap<int,int> um;
	//cout<<"hello"<<endl;
	um.insert(2,45);
	um.insert(4,99);
	um.insert(7,34);
	try
	{
		cout<<um.getValue(2)<<endl;
		cout<<um.getValue(4)<<endl;
		cout<<um.getValue(99)<<endl;
	}
	catch(const char* msg)
	{
		cout<<msg<<endl;
	}
	return 0;
}
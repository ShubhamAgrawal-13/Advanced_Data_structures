#include<iostream>
#include<string.h>
#include<stdio.h>
#include<stdlib.h>
#include<algorithm>
#include<vector>
#include<time.h>

using namespace std;



template<typename K,typename V>
class OrderedMap
{
	public:
					class Node
					{
					public:
							K key;
							V value;
							Node* left;
							Node* right;
							int height;
							int bf;

							Node(K k,V v)
							{
								key=k;
								value=v;
								bf=0;
								height=0;
								left=NULL;
								right=NULL;
							}

							Node()
							{

							}
					};
	Node* root;
	int count;
	OrderedMap()
	{
		root=NULL;
		count=0;
	}
	void insert(K k,V v)
	{
		Node* p=new Node(k,v);
		int f=0;
		root=insertNode(root,p,f);
		if(f==0)
			count++;
		else
			free(p);
	}

	V find(K k)
	{
		Node* p = searchElement(root,k);
		if(p==NULL)
			throw "map range out of bounds\n";
		return p->value;
	}

	void update(K k,V v)
	{
		Node* p = searchElement(root,k);
		if(p==NULL)
			throw "map range out of bounds\n";
		p->value=v;
	}

	void print()
	{
		inorder(root);
	}

	void clear()
	{
		deleteTree(root);
		root=NULL;
		count=0;
	}

	int size()
	{
		return count;
	}

	bool empty()
	{
		if(count==0)
			return true;
		return false;
	}

	void erase(K k)
	{
		count--;
		root=deleteNode(root,k);
	}

		int fastheight(Node* root)
		{
		    if(root==NULL)
		    {
		        return -1;
		    }
		    else
		    {
		        int h = root->height;
		        return h;
		    }
		}


		int checkBalance(int balance)
		{
		    if(balance==1 || balance==0 || balance==-1)
		        return 1;
		    return 0;
		}

		int checkCase(Node* root,K item,int flag)
		{
		    // flag=1 for insertion and flag=2 for deletion
		    if(flag==1)
		    {
		        if(root->bf > 1)
		        {
		            //left rotation
		            if(root->left->key > item)
		            {
		                //cout<<"left-left rotation\n";
		                return 1;
		            }
		            else
		            {
		                //cout<<"left-right rotation\n";
		                return 3;
		            }
		        }
		        else
		        {
		            //right rotation
		            if(root->right->key > item)
		            {
		                //cout<<"right-left rotation\n";
		                return 4;
		            }
		            else
		            {
		                //cout<<"right-right rotation\n";
		                return 2;
		            }
		        }
		    }
		    if(flag==2)
		    {
		        if(root->bf > 1)
		        {
		            //left rotation
		            if(root->left->bf>=0)
		            {
		                //cout<<"left-left rotation\n";
		                return 1;
		            }
		            else
		            {
		                //cout<<"left-right rotation\n";
		                return 3;
		            }
		        }
		        else
		        {
		            //right rotation
		            if(root->right->bf>=0)
		            {
		                //cout<<"right-left rotation\n";
		                return 4;
		            }
		            else
		            {
		                //cout<<"right-right rotation\n";
		                return 2;
		            }
		        }
		    }
		}

		Node* llRot(Node* root)
		{
		    Node* roottemp = root;
		    Node* temp1 =root->left;
		    Node* temp1kaRight = temp1->right;
		    root->left=temp1kaRight;
		    root->height=max(fastheight(root->left),fastheight(root->right))+1;
		    root->bf = fastheight(root->left) - fastheight(root->right);
		    temp1->right=root;
		    temp1->height=max(fastheight(temp1->left),fastheight(temp1->right))+1;
		    temp1->bf=fastheight(temp1->left) - fastheight(temp1->right);

		    return temp1;
		}


		Node* rrRot(Node* root)
		{
		    Node* roottemp = root;
		    Node* temp1 = root->right;
		    Node* temp1kaLeft = temp1->left;
		    root->right=temp1kaLeft;
		    root->height=max(fastheight(root->left),fastheight(root->right))+1;
		    root->bf = fastheight(root->left) - fastheight(root->right);
		    temp1->left=root;
		    temp1->height=max(fastheight(temp1->left),fastheight(temp1->right))+1;
		    temp1->bf=fastheight(temp1->left) - fastheight(temp1->right);

		    return temp1;
		}

		Node* lrRot(Node* root)
		{
		    Node* temp1 = root->left;
		    Node* temp2 = temp1->right;
		    Node* temp2kaleft = temp2->left;
		    Node* temp2karight = temp2->right;
		    temp1->right= temp2kaleft;
		    root->left = temp2karight;

		    temp2->left=temp1;
		    temp2->right=root;

		    root->height=max(fastheight(root->left),fastheight(root->right))+1;
		    temp1->height=max(fastheight(temp1->left),fastheight(temp1->right))+1;
		    temp2->height=max(fastheight(temp2->left),fastheight(temp2->right))+1;

		    root->bf = fastheight(root->left) - fastheight(root->right);
		    temp1->bf=fastheight(temp1->left) - fastheight(temp1->right);
		    temp2->bf = fastheight(temp2->left) - fastheight(temp2->right);

		    return temp2;
		}


		Node* rlRot(Node* root)
		{
		    Node* temp1 = root->right;
		    Node* temp2 = temp1->left;
		    Node* temp2kaleft = temp2->left;
		    Node* temp2karight = temp2->right;
		    root->right=temp2kaleft;
		    temp1->left= temp2karight;

		    temp2->left=root;
		    temp2->right=temp1;

		    root->height=max(fastheight(root->left),fastheight(root->right))+1;
		    temp1->height=max(fastheight(temp1->left),fastheight(temp1->right))+1;
		    temp2->height=max(fastheight(temp2->left),fastheight(temp2->right))+1;

		    root->bf = fastheight(root->left) - fastheight(root->right);
		    temp1->bf=fastheight(temp1->left) - fastheight(temp1->right);
		    temp2->bf = fastheight(temp2->left) - fastheight(temp2->right);

		    return temp2;
		}

		Node* find_inorder_successor(Node* root)
		{
		    if(root->left==NULL)
		        return root;
		    if(root->left->key < root->key)
		        return find_inorder_successor(root->left); 
		}


		Node* insertNode(Node* root,Node* temp,int &f)
		{
		    if(root==NULL)
		    {
		        root=temp;
		        return root;
		    }
		    else
		    {
		        if(root->key > temp->key)
		        {
		            root->left = insertNode(root->left,temp,f);
		        }
		        else if(root->key < temp->key)
		        {
		            root->right = insertNode(root->right,temp,f);
		        }
		        else
		        {
		            cout<<"\nDuplicate element : "<<root->key<<endl;
		            f=1;
		        }
		        root->height=max(fastheight(root->left),fastheight(root->right))+1;
		        root->bf = fastheight(root->left) - fastheight(root->right);
		        if(checkBalance(root->bf))
		        {
		            return root;
		        }
		        else
		        {
		            int c = checkCase(root,temp->key,1);
		            switch(c)
		            {
		                case 1:
		                    return llRot(root);
		                    break;
		                case 2:
		                    return rrRot(root);
		                    break;
		                case 3:
		                    return lrRot(root);
		                    break;
		                case 4:
		                    return rlRot(root);
		                    break;
		            }
		        }
		    }
		    return root;
		}

		Node* deleteNode(Node* root,K item)
		{
		    if(root==NULL)
		    {
		    	count++;
		        cout<<"Element to be deleted is not present\n";
		        return NULL;
		    }
		    else
		    {
		        if(root->key == item)
		        {
		            if(root->left==NULL && root->right==NULL)
		            {
		                delete root;
		                return NULL;
		            }
		            else if(root->left==NULL)
		            {
		                Node* temp = root->right;
		                delete root;
		                root=temp;
		            }
		            else if(root->right==NULL)
		            {
		                Node* temp = root->left;
		                delete root;
		                root=temp;
		            }
		            else
		            {
		                Node* temp = find_inorder_successor(root->right);
		                K d=temp->key;
		                root->key=temp->key;
		                root->right=deleteNode(root->right,d);
		            }

		        }
		        else if(root->key > item)
		        {
		            root->left=deleteNode(root->left,item);
		        }
		        else
		        {
		            root->right=deleteNode(root->right,item);
		        }
		        root->height=max(fastheight(root->left),fastheight(root->right))+1;
		        root->bf = fastheight(root->left) - fastheight(root->right);
		        if(checkBalance(root->bf))
		        {
		            return root;
		        }
		        else
		        {
		            int c = checkCase(root,item,2); //no need for item, but to reuse the checkCase function call for deletion
		            switch(c)
		            {
		                case 1:
		                    return llRot(root);
		                    break;
		                case 2:
		                    return rrRot(root);
		                    break;
		                case 3:
		                    return lrRot(root);
		                    break;
		                case 4:
		                    return rlRot(root);
		                    break;
		            }
		        }
		        return root;
		    }
		    return root;
		}


		Node* searchElement(Node* root,K item)
		{
		    if(root == NULL)
		    {
		        return NULL;
		    }
		    if(root->key == item)
		    {
		        return root;
		    }
		    else if(root->key > item)
		    {
		        return searchElement(root->left,item);
		    }
		    else
		    {
		        return searchElement(root->right,item);
		    }
		}

		void inorder(Node* root)
		{
		    if(root==NULL)
		        return;
		    else
		    {
		        inorder(root->left);
		        cout<<root->key<<":"<<root->value<<endl;
		        inorder(root->right);
		    }
		}

		void deleteTree(Node* root)  
		{  
		    if (root == NULL) return;  
		  
		    deleteTree(root->left);  
		    deleteTree(root->right);  
		    free(root);  
		}
		V operator[](K k)
		{
			Node* p = searchElement(root,k);
			if(p==NULL)
				throw "map range out of bound";
			return p->value;
		}
};

int main()
{
	// OrderedMap<int,string> mp;
	// mp.insert(1,"shubham");
	// mp.insert(2,"shrayans");
	// mp.insert(3,"shanu");
	// mp.insert(4,"harshit");
	// mp.insert(2,"yash");
	// mp.print();
	// mp.erase(3);
	// cout<<"[2]"<<mp[2]<<endl;
	// mp.update(2,"Nikita");
	// cout<<"[2]"<<mp[2]<<endl;
	// mp.print();
	// cout<<mp.find(1)<<endl;
	// cout<<mp.size()<<endl;
	// if(!mp.empty())
	// {
	// 	cout<<"Not empty\n";
	// }
	// else
	// {
	// 	cout<<"empty\n";
	// }
	// mp.clear();
	// cout<<mp.size()<<endl;
	// if(!mp.empty())
	// {
	// 	cout<<"Not empty\n";
	// }
	// else
	// {
	// 	cout<<"empty\n";
	// }
	// mp.print();
	OrderedMap<string,float> mp;
	mp.insert("shubham",1.0);
	mp.insert("shrayans",2.0);
	mp.insert("shanu",3.0);
	mp.insert("harshit",0.9);
	mp.insert("yash",0.9);
	mp.print();
	mp.erase("shanu");
	cout<<"[2]"<<mp["shrayans"]<<endl;
	mp.update("shrayans",10.0);
	cout<<"[2]"<<mp["shrayans"]<<endl;
	mp.print();
	cout<<mp.find("shubham")<<endl;
	cout<<mp.size()<<endl;
	if(!mp.empty())
	{
		cout<<"Not empty\n";
	}
	else
	{
		cout<<"empty\n";
	}
	mp.clear();
	cout<<mp.size()<<endl;
	if(!mp.empty())
	{
		cout<<"Not empty\n";
	}
	else
	{
		cout<<"empty\n";
	}
	mp.print();
	return 0;
}
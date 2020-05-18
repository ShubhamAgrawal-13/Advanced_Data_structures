#include<bits/stdc++.h>
using namespace std;

class Node
{
public:
	int data;
	Node* left=NULL;
	Node* right=NULL;

	Node(int data)
	{
		this->data=data;
		this->left=NULL;
		this->right=NULL;
	}
};

void print_tree(Node* root,int space)
{
	if(root==NULL)
		return;
	print_tree(root->right,space+5);
	for(int i=0;i<space;i++)
		cout<<" ";
	cout<<root->data<<"\n";
	print_tree(root->right,space+5);
}


int main()
{
	Node *root = new Node(1);  
    root->left = new Node(2);  
    root->right = new Node(3);  
  
    root->left->left = new Node(4);  
    root->left->right = new Node(5);  
    root->right->left = new Node(6);  
    root->right->right = new Node(7);  
  
    root->left->left->left = new Node(8);  
    root->left->left->right = new Node(9);  
    root->left->right->left = new Node(10);  
    root->left->right->right = new Node(11);  
    root->right->left->left = new Node(12);  
    root->right->left->right = new Node(13);  
    root->right->right->left = new Node(14);  
    root->right->right->right = new Node(15);  
      
    print_tree(root,0);
}
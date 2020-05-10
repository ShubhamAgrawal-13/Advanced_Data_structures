#include<iostream>
#include<climits>
#include<cmath>
#include<stdio.h>
using namespace std;

#define MAX(a,b) (a>b)?a:b

typedef class AVLNode
{
        public:
        int data;
        AVLNode * left;
        AVLNode * right;
        int bf; //balancing Factor = left - right
        int height;
        int con; //count of nodes

        AVLNode()
        {

        }
        AVLNode(int cdata)
        {
            data=cdata;
            left=NULL;
            right=NULL;
            height=0;
            con=1;
            bf=0;
        }
}Node;

Node* root=NULL;
int count=0;

int find_height(Node* root)
{
    if(root==NULL)
        return -1;
    int left_height = find_height(root->left)+1;
    int right_height = find_height(root->right)+1;
    int max = (left_height > right_height)?  left_height  :  right_height;
    return max;
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

int fastcon(Node* root)
{
    if(root==NULL)
    {
        return 0;
    }
    else
    {
        int c = root->con;
        return c;
    }
}

int checkBalance(int balance)
{
    if(balance==1 || balance==0 || balance==-1)
        return 1;
    return 0;
}

int checkCase(Node* root,int item,int flag)
{
    // flag=1 for insertion and flag=2 for deletion
    if(flag==1)
    {
        if(root->bf > 1)
        {
            //left rotation
            if(root->left->data > item)
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
            if(root->right->data > item)
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
    return 0;
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

    root->con=fastcon(root->left)+fastcon(root->right)+1;
    temp1->con=fastcon(temp1->left)+fastcon(temp1->right)+1;
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

    root->con=fastcon(root->left)+fastcon(root->right)+1;
    temp1->con=fastcon(temp1->left)+fastcon(temp1->right)+1;
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

    root->con=fastcon(root->left)+fastcon(root->right)+1;
    temp1->con=fastcon(temp1->left)+fastcon(temp1->right)+1;
    temp2->con=fastcon(temp2->left)+fastcon(temp2->right)+1;
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

    root->con=fastcon(root->left)+fastcon(root->right)+1;
    temp1->con=fastcon(temp1->left)+fastcon(temp1->right)+1;
    temp2->con=fastcon(temp2->left)+fastcon(temp2->right)+1;
    return temp2;
}

Node* insertNode(Node* root,Node* temp)
{
    if(root==NULL)
    {
        root=temp;
        return root;
    }
    else
    {
        if(root->data > temp->data)
        {
            root->left = insertNode(root->left,temp);

        }
        else if(root->data <= temp->data)
        {
            root->right = insertNode(root->right,temp);
        }
        root->height=max(fastheight(root->left),fastheight(root->right))+1;
        root->bf = fastheight(root->left) - fastheight(root->right);
        root->con=fastcon(root->left)+fastcon(root->right)+1;
        if(checkBalance(root->bf))
        {
            return root;
        }
        else
        {
            int c = checkCase(root,temp->data,1);
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

Node* findMedian(Node* root,int m,int flag)
{
    if(flag==1)
    {
        m=m-1;
        flag=0;
    }
    if(root!=NULL)
    {
        int l=fastcon(root->left);
        int r=fastcon(root->right);
        if(m==l)
            return root;
        if(m>l)
        {
            m=m-l-1;    
            return findMedian(root->right,m,flag);
        }
        if(m<l)
        {
            return findMedian(root->left,m,flag);
        }
    }
    return root;
}


float calculateMedian(Node* root)
{
    int n=root->con;
    int l=fastcon(root->left);
    int r=fastcon(root->right);
    if(n%2==0)
    {
        Node* temp1=findMedian(root,n/2,1);
        Node* temp2=findMedian(root,n/2+1,1);
        return (temp1->data+temp2->data)/2.0;
    }
    else
    {
        if(l==r)
            return root->data;
        Node* temp = findMedian(root,n/2+1,1);
        return temp->data;
    }
}

void inorder(Node* root)
{
    if(root==NULL)
        return;
    else
    {
        inorder(root->left);
        cout<<"("<<root->data<<" "<<root->con<<") ";
        inorder(root->right);
    }
}

void preorder(Node* root)
{
    if(root==NULL)
        return;
    else
    {
        cout<<"("<<root->data<<" "<<root->con<<") ";
        //cout<<root->data<<" ";
        preorder(root->left);
        preorder(root->right);
    }
}

int main()
{
    int n,x;
    cin>>n;
    for(int i=1;i<=n;i++)
    {
        cin>>x;
        Node* temp = new Node(x);    
        root=insertNode(root,temp);
        // inorder(root);
        // cout<<"\n";
        // preorder(root);
        // cout<<"\n";
        cout<<calculateMedian(root)<<endl;
        //cout<<1<<endl;
    }
    return 0;
}

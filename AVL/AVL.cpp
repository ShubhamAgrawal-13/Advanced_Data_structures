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
// int flag=0;

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

Node* find_inorder_successor(Node* root)
{
    if(root->left==NULL)
        return root;
    if(root->left->data < root->data)
        return find_inorder_successor(root->left); 
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
        else if(root->data < temp->data)
        {
            root->right = insertNode(root->right,temp);
        }
        else
        {
            cout<<"\nDuplicate element : "<<root->data<<endl;
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

Node* deleteNode(Node* root,int item)
{
    if(root==NULL)
    {
        cout<<"Element to be deleted is not present\n";
        return NULL;
    }
    else
    {
        if(root->data == item)
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
                int d=temp->data;
                root->data=temp->data;
                root->right=deleteNode(root->right,d);
            }

        }
        else if(root->data > item)
        {
            root->left=deleteNode(root->left,item);
        }
        else
        {
            root->right=deleteNode(root->right,item);
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


int searchElement(Node* root,int item)
{
    if(root == NULL)
    {
        return 0;
    }
    if(root->data == item)
    {
        return 1;
    }
    else if(root->data > item)
    {
        return searchElement(root->left,item);
    }
    else
    {
        return searchElement(root->right,item);
    }
}

int closestElement(Node* root,int item)
{
    int minE=root->data;
    int min=INT_MAX;
    Node* temp = root;
    while(temp!=NULL)
    {
        int k=abs(temp->data-item);
        if(k<min)
        {
            min=k;
            minE=temp->data;
        }
        if(k==min)
        {
            if(minE>temp->data)
            {
                minE=temp->data;
            }
        }
        if(temp->data > item)
        {
            temp=temp->left;
        }
        else
        {
            temp=temp->right;
        }
    }
    return minE;
}



Node* kthlargest(Node* root,int m,int flag)
{
    if(flag==1)
    {
        m=fastcon(root)-m;
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
            return kthlargest(root->right,m,flag);
        }
        if(m<l)
        {
            return kthlargest(root->left,m,flag);
        }
    }
    return root;
}

int findk(Node* root,int m)
{
        int l = fastcon(root->left);
        if(root->data==m)
        {
            return l+1;
        }
        if(root->data>m)
        {
            return findk(root->left,m);
        }
        if(root->data<m)
        {
            return l+1+findk(root->right,m);
        }
}

int Range(Node* root,int m1,int m2)
{
    int closeset_m1=closestElement(root,m1);
    int closeset_m2=closestElement(root,m2);

    int k1 = findk(root,closeset_m1);
    int k2 = findk(root,closeset_m2);
    //cout<<"------"<<k1<<"  "<<k2<<"--------\n";
    int count=k2-k1+1;
    if(closeset_m1<m1)
        count--;
    if(closeset_m2>m2)
        count--;
    return count;
}


void inorder(Node* root)
{
    if(root==NULL)
        return;
    else
    {
        inorder(root->left);
       // cout<<"("<<root->data<<" "<<root->con<<") ";
        cout<<root->data<<" ";
        inorder(root->right);
    }
}

void preorder(Node* root)
{
    if(root==NULL)
        return;
    else
    {
        //cout<<"("<<root->data<<" "<<root->con<<") ";
        cout<<root->data<<" ";
        preorder(root->left);
        preorder(root->right);
    }
}

int main()
{
    int op=1,ch,i,x,y;
    cout<<"\n----- * Ordered Set * -----\n";
    while(op)
    {
        cout<<"\n1:Insert\t2:delete\t3:search\n\n4:closest element\t5:Kth largest element\t6:Range \t7:exit\n\n";
        cin>>ch;
        switch(ch)
        {
            case 1:
                {
                    cout<<"Enter node to be inserted : ";
                    cin>>x;
                    Node* temp = new Node(x);   
                    root=insertNode(root,temp);
                    count++;
                }
                break;
            case 2:
                cout<<"Enter node to be deleted: ";
                cin>>x;
                root=deleteNode(root,x);
                count--;
                break;
            case 3:
                cout<<"Enter node to be searched : ";
                cin>>x;
                i=searchElement(root,x);
                //cout<<i<<endl;
                if(i==1)
                    cout<<"\nElement is present in Set\n"<<endl;
                else
                    cout<<"\nElement is not present in Set\n"<<endl;
                break;
            case 4:
                cout<<"Enter node the closestElement : ";
                cin>>x;
                if(root!=NULL)
                        cout<<"\nClosest Element : "<<closestElement(root,x)<<endl;
                    else
                        cout<<"\nSet is Empty\n";
                break;
            case 5:
                {
                    cout<<"Kth largest element : ";
                    cin>>x;
                    int flag=1;
                    Node* temp=kthlargest(root,x,flag);
                    if(temp!=NULL)
                        cout<<x<<" largest element : "<<temp->data<<endl;
                    else
                        cout<<"\nNot in Range\n";
                }
                break;
            case 6:
                {
                    cout<<"Enter Range : ";
                    cin>>x>>y;
                    cout<<"\ncount = "<<Range(root,x,y)<<endl;
                }
                break;
            case 7:
                op=0;
                break;
            default:
                cout<<"\nPlease a valid choice (1-7) \n\n";
        }
        cout<<"\nElements in set : \n";
        inorder(root);
        cout<<endl;
        //preorder(root);
        //cout<<endl;
    }
    return 0;
}

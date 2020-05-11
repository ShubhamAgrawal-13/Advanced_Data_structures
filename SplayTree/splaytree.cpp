#include<iostream>
#include<climits>
#include<cmath>
#include<stdio.h>
#include<vector>
using namespace std;

#define MAX(a,b) (a>b)?a:b

typedef class SNode
{
        public:
        int data;
        SNode * left;
        SNode * right;

        SNode()
        {

        }
        SNode(int cdata)
        {
            data=cdata;
            left=NULL;
            right=NULL;
        }
}Node;

// Node* root=NULL;
int count=0;
int cnt=0;
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

Node* llRot(Node* root)
{
    Node* roottemp = root;
    Node* temp1 =root->left;
    Node* temp1kaRight = temp1->right;
    root->left=temp1kaRight;
    temp1->right=root;
    return temp1;
}



Node* rrRot(Node* root)
{
    Node* roottemp = root;
    Node* temp1 = root->right;
    Node* temp1kaLeft = temp1->left;
    root->right=temp1kaLeft;
    temp1->left=root;
    //cout<<"bye\n";
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

    return temp2;
}


Node* max_predecessor(Node* root)
{
    if(root->right==NULL)
        return root;
    return max_predecessor(root->right); 
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


Node* splay(Node* root,int item)
{
   // cout<<"splay : "<<root->data<<" ---> "<<cnt++<<endl;
    if(root->data == item)
    {
        return root;
    }
    else if(root->data > item)
    {
        root->left=splay(root->left,item);
        return llRot(root);
    }
    else
    {
        root->right=splay(root->right,item);
        return rrRot(root);
    }
}

Node* searchElement(Node* root,int item)
{
    if(root == NULL)
    {
        return NULL;
    }
    Node* temp = root;
    Node* tempp=temp;
    while(temp!=NULL)
    {
        if(temp->data == item)
        {
            root=splay(root,item);
            return root;
        }
        else if(temp->data > item)
        {
            tempp=temp;
            temp=temp->left;
        }
        else
        {
            tempp=temp;
            temp=temp->right;
        }
    }
    root=splay(root,tempp->data);
    return root;
}


// Node* insertNode(Node* root,Node* temp)
// {
//     if(root==NULL)
//     {
//         root=temp;
//         return root;
//     }
//     else
//     {
//         if(root->data > temp->data)
//         {
//             root->left = insertNode(root->left,temp);
//         }
//         else if(root->data < temp->data)
//         {
//             root->right = insertNode(root->right,temp);
//         }
//         else
//         {
//             root=splay(root,temp->data);
//             return root;
//         }

//     }
//     root=splay(root,temp->data);
//     return root;
// }

Node* insertNode(Node* root,Node* temp)
{
    if(root==NULL)
    {
        root=temp;
        return root;
    }
    else
    {
        root=searchElement(root,temp->data);
        if(temp->data == root->data)
        {
            return root;
        }
        else if(temp->data > root->data)
        {
            temp->left=root;
            temp->right=root->right;
            root->right=NULL;
            root=temp;
        }
        else
        {
            temp->right=root;
            temp->left=root->left;
            root->left=NULL;
            root=temp;
        }
    }
    //root=splay(root,temp->data);
    return root;
}


Node* deleteNode(Node* root,int item)
{
    if(root==NULL)
    {
        cout<<"Element to be deleted is not present\n";
        return NULL;
    }
    root=splay(root,item);
    preorder(root);
    cout<<endl;
    if(root->left!=NULL)
    {
        cout<<"Left is not NULL\n";
        Node* temp=max_predecessor(root->left);
        cout<<temp->data<<endl;
        temp=splay(root->left,temp->data);
        temp->right=root->right;
        Node* temp2=root;
        delete temp2;
        root=temp;
    }
    else
    {
        cout<<"Left is NULL\n";
        Node* temp2=root;
        root=root->right;
        delete (temp2); 
    }
    return root;
}

// Node* deleteNode(Node* root,int item)
// {
//     if(root==NULL)
//     {
//         cout<<"Element to be deleted is not present\n";
//         return NULL;
//     }
//     else
//     {
//         int item1;
//         if(root->data == item)
//         {
//             if(root->left==NULL && root->right==NULL)
//             {
//                 delete root;
//                 return NULL;
//             }
//             else if(root->left==NULL)
//             {
//                 Node* temp = root->right;
//                 delete root;
//                 root=temp;
//             }
//             else if(root->right==NULL)
//             {
//                 Node* temp = root->left;
//                 delete root;
//                 root=temp;
//             }
//             else
//             {
//                 Node* temp = max_predecessor(root->right);
//                 int d=temp->data;
//                 root->data=temp->data;
//                 root->right=deleteNode(root->right,d);
//             }
//         }
//         else if(root->data > item)
//         {
//             root->left=deleteNode(root->left,item);
//         }
//         else
//         {
//             root->right=deleteNode(root->right,item);
//         }

//     }
//     return root;
// }



Node* search(Node* root,int data)
{
    if(root == NULL) 
    {
        return NULL;
    }
    if(root->data==data)
    {
        return root;
    }
    else if(root->data > data)
    {
        return search(root->left,data);
    }
    else
    {
        return search(root->right,data);
    }
}


int minElement(Node* root)
{
    if(root==NULL)
    {
        cout<<"Tree is empty\n";
        return -1;
    }
    Node* temp=root;
    while(temp->left!=NULL)
    {
        temp=temp->left;
    }
    return temp->data;
}

int maxElement(Node* root)
{
    if(root==NULL)
    {
        cout<<"Tree is empty\n";
        return -1;
    }
    Node* temp=root;
    while(temp->right!=NULL)
    {
        temp=temp->right;
    }
    return temp->data;
}

Node* findSmallest(Node* root)
{
        if(root->left != NULL) 
        {
            return findSmallest(root->left);
        }
        return root;
}

Node* findLargest(Node* root)
{
        if(root->right!= NULL) 
        {
            return findLargest(root->right);
        }
        return root;
}

Node* successor(Node* root,int data)
{
    Node* temp = search(root,data);

    if(temp==NULL)
    {
        return NULL;
    }

    if(temp->right!=NULL)
    {
        return findSmallest(temp->right);
    }

    Node* succ=NULL;

    Node* temproot=root;
    while(temproot!=NULL)
    {
        if(temp->data < temproot->data)
        {
            succ=temproot;
            temproot=temproot->left;
        }
        else if(temp->data > temproot->data)
            temproot=temproot->right;
        else
            break;
    }
    return succ;
}

Node* predecessor(Node* root,int data)
{
    Node* temp = search(root,data);

    if(temp==NULL)
    {
        return NULL;
    }

    if(temp->left!=NULL)
    {
        return findLargest(temp->left);
    }

    Node* prec=NULL;

    Node* temproot=root;
    while(temproot!=NULL)
    {
        if(temp->data < temproot->data)
        {
            temproot=temproot->left;
        }
        else if(temp->data > temproot->data)
        {
            prec=temproot;
            temproot=temproot->right;
        }
        else
            break;
    }
    return prec;
}


int main()
{
    int op=1,x;
    char ch;
    cout<<"\n----- * Splay Tree * -----\n";

        Node* root = NULL;
        clock_t t,local_t; 
        int n=1048576;
        int a[n];

        FILE *fp = fopen("dataset.txt","r");
        size_t len = 0;
        ssize_t read;

        char * line = NULL;
        int i=0;
        while ((read = getline(&line, &len, fp)) != -1 ) 
        {
            // cout<<line<<" ";
            int x = atoi(line);
            a[i]=x;
            // cout<<a[i]<<" ";
            i++;
        }
        int base=100;
        vector<double> v;
        t = clock(); 
        local_t=clock();
        for (int i = 0; i < n; ++i)
        {
            // cout<<a[i]<<" "<<i<<"\t";
            Node* temp = new Node(a[i]);
            root = insertNode(root, temp);
            if(i==base)
            {
                base+=10000;
                local_t = clock() - t;
                double time_taken = ((double)local_t)/CLOCKS_PER_SEC; // in seconds
                //local_t=clock();
                //cout<<time_taken<<endl;
                v.push_back(time_taken);
            }

        }
        t = clock() - t; 
        double time_taken = ((double)t)/CLOCKS_PER_SEC; // in seconds 
        printf("Tree took %f seconds to execute \n", time_taken);
        v.push_back(time_taken); 
        FILE* f=fopen("output_splay.txt","w");
        for (int i = 0; i < v.size(); ++i)
        {
            double x = v[i];
            fprintf(f, "%f\n", x );
            //cout<<i<<" "<<v[i]<<"\n";
        }
        cout<<root->data<<endl;
        fclose(fp);
        fclose(f);

        // v.clear();
        // fp = fopen("dataset_search.txt","r");
        // len = 0;
        // line = NULL;
        // i=0;
        // while ((read = getline(&line, &len, fp)) != -1 ) 
        // {
        //     // cout<<line<<" ";
        //     int x = atoi(line);
        //     a[i]=x;
        //     // cout<<a[i]<<" ";
        //     i++;
        // }
        // base=100;
        // t = clock(); 
        // local_t=clock();
        // for (int i = 0; i < n; ++i)
        // {
        //     // cout<<a[i]<<" "<<i<<"\t";
        //     searchElement(root, a[i]);
        //     if(i==base)
        //     {
        //         base+=10000;
        //         local_t = clock() - t;
        //         double time_taken = ((double)local_t)/CLOCKS_PER_SEC; // in seconds
        //         //local_t=clock();
        //         //cout<<time_taken<<endl;
        //         v.push_back(time_taken);
        //     }

        // }
        // t = clock() - t; 
        // time_taken = ((double)t)/CLOCKS_PER_SEC; // in seconds 
        // printf("Tree took %f seconds to execute \n", time_taken);
        // v.push_back(time_taken); 
        // FILE* f1=fopen("output_splay_search.txt","w");
        // for (int i = 0; i < v.size(); ++i)
        // {
        //     double x = v[i];
        //     fprintf(f1, "%f\n", x );
        //     //cout<<i<<" "<<v[i]<<"\n";
        // }
        // //cout<<root->data<<endl;
        // fclose(f1);

        v.clear();
        fp = fopen("dataset.txt","r");
        len = 0;
        line = NULL;
        i=0;
        while ((read = getline(&line, &len, fp)) != -1 ) 
        {
            // cout<<line<<" ";
            int x = atoi(line);
            a[i]=x;
            // cout<<a[i]<<" ";
            i++;
        }
        base=100;
        t = clock(); 
        local_t=clock();
        for (int i = 0; i < n; ++i)
        {
            // cout<<a[i]<<" "<<i<<"\t";
            root=deleteNode(root, a[i]);
            if(i==base)
            {
                base+=10000;
                local_t = clock() - t;
                double time_taken = ((double)local_t)/CLOCKS_PER_SEC; // in seconds
                //local_t=clock();
                //cout<<time_taken<<endl;
                v.push_back(time_taken);
            }

        }
        t = clock() - t; 
        time_taken = ((double)t)/CLOCKS_PER_SEC; // in seconds 
        printf("Tree took %f seconds to execute \n", time_taken);
        v.push_back(time_taken); 
        FILE* f1=fopen("output_splay_s.txt","w");
        for (int i = 0; i < v.size(); ++i)
        {
            double x = v[i];
            fprintf(f1, "%f\n", x );
            //cout<<i<<" "<<v[i]<<"\n";
        }
        cout<<root<<endl;
        fclose(f1);


    // while(op)
    // {
    //     cnt=0;
    //     cout<<"\n1:Insert\t2:delete\t3:search\t4:Min element\t5:Max element\n6:Successor\t7:Precedessor\t8:exit\n\n";
    //     cin>>ch;
    //     //cout<<ch<<"---\n";
    //     switch(ch) 
    //     {
    //         case '1':
    //             {
    //                 cout<<"Enter node to be inserted : ";
    //                 cin>>x;
    //                 Node* temp = new Node(x);   
    //                 root=insertNode(root,temp);
    //                 count++;
    //             }
    //             break;
    //         case '2':
    //             cout<<"Enter node to be deleted: ";
    //             cin>>x;
    //             root=deleteNode(root,x);
    //             count--;
    //             break;
    //         case '3':
    //             cout<<"Enter node to be searched : ";
    //             cin>>x;
    //             root=searchElement(root,x);
    //             //cout<<i<<endl;
    //             if(root->data==x)
    //                 cout<<"\nElement is present in splay tree\n"<<endl;
    //             else
    //                 cout<<"\nElement is not present in splay tree\n"<<endl;
    //             break;
            
    //         case '4':
    //             cout<<"Minimum Element of the tree : "<<minElement(root)<<endl;
    //             break;
    //         case '5':
    //             cout<<"Maximum Element of the tree : "<<maxElement(root)<<endl;
    //             break;
    //         case '6':
    //             {
    //                 int x;
    //                 cin>>x;
    //                 Node* temp=successor(root,x);
    //                 if(temp==NULL)
    //                 {
    //                     cout<<"No Successor\n";
    //                 }
    //                 else
    //                 {
    //                     cout<<"Successor of "<< x <<" is : "<<temp->data<<endl;
    //                 }
    //             }
    //             break;
    //         case '7':
    //             {
    //                 int x;
    //                 cin>>x;
                    
    //                 Node* temp=predecessor(root,x);
    //                 if(temp==NULL)
    //                 {
    //                     cout<<"No Predecessor\n";
    //                 }
    //                 else
    //                 {
    //                     cout<<"Predecessor of "<< x <<" is : "<<temp->data<<endl;
    //                 }
    //             }
    //             break;
    //         case '8':
    //             op=0;
    //             break;
    //         default:
    //             cout<<"\nPlease a valid choice (1-8) \n\n";
    //     }
    //     cout<<"\nElements in splay tree : \n";
    //     inorder(root);
    //     cout<<endl;
    //     preorder(root);
    //     cout<<endl;
    // }
    return 0;
}


// Node* deleteNode(Node* root,int item)
// {
//     if(root==NULL)
//     {
//         cout<<"Element to be deleted is not present\n";
//         return NULL;
//     }
//     else
//     {
//         int item1;
//         if(root->data == item)
//         {
//             if(root->left==NULL && root->right==NULL)
//             {
//                 delete root;
//                 return NULL;
//             }
//             else if(root->left==NULL)
//             {
//                 Node* temp = root->right;
//                 delete root;
//                 root=temp;
//             }
//             else if(root->right==NULL)
//             {
//                 Node* temp = root->left;
//                 delete root;
//                 root=temp;
//             }
//             else
//             {
//                 Node* temp = find_inorder_successor(root->right);
//                 int d=temp->data;
//                 root->data=temp->data;
//                 root->right=deleteNode(root->right,d);
//             }
//         }
//         else if(root->data > item)
//         {
//             root->left=deleteNode(root->left,item);
//         }
//         else
//         {
//             root->right=deleteNode(root->right,item);
//         }

//     }
//     return root;
// }

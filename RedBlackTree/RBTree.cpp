#include<bits/stdc++.h>
using namespace std;
#define BLACK 1
#define RED 0

class Node
{
public:
    int data;
    int color;
    Node* left;
    Node* right;
    Node* parent;
    int nullleaf;

    Node()
    {
        data=0;
        color=BLACK;
        left=NULL;
        right=NULL;
        parent=NULL;
        nullleaf=0;
    }
};


void deleteNodeCase1(Node*, Node**);
void deleteNodeCase2(Node*, Node**);
void deleteNodeCase3(Node*, Node**);
void deleteNodeCase4(Node*, Node**);
void deleteNodeCase5(Node*, Node**);
void deleteNodeCase6(Node*, Node**);

Node* createNULLNode(Node* p)
{
    Node* leaf = new Node();
    leaf->color=BLACK;
    leaf->nullleaf=1;
    leaf->parent=p;
    return leaf;
}

Node* createBlackNode(int data)
{
    Node* node = new Node();
    node->data=data;
    node->color=BLACK;
    node->left=createNULLNode(node);
    node->right=createNULLNode(node);
    return node;
}


Node* createRedNode(Node* p, int data) 
{
        Node* node = new Node();
        node->data = data;
        node->color = RED;
        node->parent = p;
        node->left = createNULLNode(node);
        node->right = createNULLNode(node);
        return node;
}




void rightRotate(Node* root, bool changeColor) 
{
        Node* parent = root->parent;
        root->parent = parent->parent;
        if(parent->parent != NULL) 
        {
            if(parent->parent->right == parent)
            {
                parent->parent->right = root;
            } 
            else
            {
                parent->parent->left = root;
            }
        }
        Node* right = root->right;
        root->right = parent;
        parent->parent = root;
        parent->left = right;
        if(right != NULL) 
        {
            right->parent = parent;
        }
        if(changeColor) 
        {
            root->color = BLACK;
            parent->color = RED;
        }
}

void leftRotate(Node* root, bool changeColor) 
{
        Node* parent = root->parent;
        root->parent = parent->parent;
        if(parent->parent != NULL) 
        {
            if(parent->parent->right == parent) 
            {
                parent->parent->right = root;
            }
            else 
            {
                parent->parent->left = root;
            }
        }
        Node* left = root->left;
        root->left = parent;
        parent->parent = root;
        parent->right = left;
        if(left != NULL) 
        {
            left->parent = parent;
        }
        if(changeColor) 
        {
            root->color = BLACK;
            parent->color = RED;
        }
}

bool isLeftChild(Node* root) 
{
        Node* parent = root->parent;
        if(parent->left == root) 
        {
            return true;
        } 
        else 
        {
            return false;
        }
}

Node* findSiblingNode(Node* root) 
{
        Node* parent = root->parent;
        if(isLeftChild(root))
        {
            return (parent->right->nullleaf==1) ? NULL : parent->right;
        } 
        else 
        {
            return (parent->left->nullleaf==1)? NULL : parent->left;
        }
}


Node* insert(Node* parent, Node* root, int data) 
{
        if(root  == NULL || root->nullleaf) 
        {
            if(parent != NULL) 
            {
                return createRedNode(parent, data);
            } 
            else 
            {
                return createBlackNode(data);
            }
        }

        if(root->data == data) 
        {
            //throw " Duplicate data not allowed \n";
        }
        
        bool isLeft;
        if(root->data > data) 
        {
            Node* left = insert(root, root->left, data);

            if(left == root->parent) 
            {
                return left;
            }

            root->left = left;
            isLeft = true;
        } 
        else 
        {
            Node* right = insert(root, root->right, data);
            
            if(right == root->parent) 
            {
                return right;
            }
            
            root->right = right;
            isLeft = false;
        }

        if(isLeft) 
        {
            if(root->color == RED && root->left->color == RED) 
            {
                Node* sibling = findSiblingNode(root);

                if(!sibling || sibling->color == BLACK) 
                {
                    if(isLeftChild(root)) 
                    {
                        rightRotate(root, true);
                    }
                    else 
                    {
                        rightRotate(root->left, false);
                        root = root->parent;
                        leftRotate(root, true);
                    }

                } 
                else 
                {
                    root->color = BLACK;
                    sibling->color = BLACK;
                    if(root->parent->parent != NULL) 
                    {
                        root->parent->color = RED;
                    }
                }
            }
        } 
        else 
        {
            if(root->color == RED && root->right->color == RED) 
            {
                Node* sibling = findSiblingNode(root);
                if(!sibling || sibling->color == BLACK) 
                {
                    if(!isLeftChild(root)) 
                    {
                        leftRotate(root, true);
                    } 
                    else 
                    {
                        leftRotate(root->right, false);
                        root = root->parent;
                        rightRotate(root, true);
                    }
                } 
                else 
                {
                    root->color = BLACK;
                    sibling->color = BLACK;
                    if(root->parent->parent != NULL) {
                        root->parent->color = RED;
                    }
                }
            }
        }
        return root;
}

Node* insert(Node* root, int data) 
{
        return insert(NULL, root, data);
}

void printInoder(Node* root) 
{
        if(root == NULL || root->nullleaf) 
        {
            return;
        }
        printInoder(root->left);
        cout<<root->data <<"("<<(root->color == BLACK ? "B)" : "R)")<<" ";
        printInoder(root->right);
}

void printPreorder(Node* root) 
{
        if(root == NULL || root->nullleaf) 
        {
            return;
        }
        cout<<root->data <<"("<<(root->color == BLACK ? "B)" : "R)")<<" ";
        printPreorder(root->left);
        printPreorder(root->right);
}

Node* findSmallest(Node* root)
{
        Node* temp = NULL;
        while(root != NULL && !root->nullleaf) 
        {
            temp = root;
            root = root->left;
        }
        return temp != NULL ? temp : root;
}

Node* findLargest(Node* root)
{
        Node* temp = NULL;
        while(root != NULL && !root->nullleaf) 
        {
            temp = root;
            root = root->right;
        }
        return temp != NULL ? temp : root;
}


void deleteNodeCase6(Node* doubleBlackNode, Node** rootReference) 
{
        Node* siblingNode = findSiblingNode(doubleBlackNode);
        siblingNode->color = siblingNode->parent->color;
        siblingNode->parent->color = BLACK;
        if(isLeftChild(doubleBlackNode)) 
        {
            siblingNode->right->color = BLACK;
            leftRotate(siblingNode, false);
        } 
        else 
        {
            siblingNode->left->color = BLACK;
            rightRotate(siblingNode, false);
        }
        if(siblingNode->parent == NULL) 
        {
            *rootReference=siblingNode;
        }
}

void deleteNodeCase5(Node* doubleBlackNode, Node** rootReference) 
{
        Node* siblingNode = findSiblingNode(doubleBlackNode);
        if(siblingNode->color == BLACK) 
        {
            if (isLeftChild(doubleBlackNode) && siblingNode->right->color == BLACK && siblingNode->left->color == RED) 
            {
                rightRotate(siblingNode->left, true);
            } 
            else if (!isLeftChild(doubleBlackNode) && siblingNode->left->color == BLACK && siblingNode->right->color == RED) 
            {
                leftRotate(siblingNode->right, true);
            }
        }
        deleteNodeCase6(doubleBlackNode, rootReference);
}


void deleteNodeCase4(Node* doubleBlackNode, Node** rootReference) 
{
        Node* siblingNode = findSiblingNode(doubleBlackNode);
        if(doubleBlackNode->parent->color == RED && siblingNode->color == BLACK && siblingNode->left->color == BLACK
        && siblingNode->right->color == BLACK) 
        {
            siblingNode->color = RED;
            doubleBlackNode->parent->color = BLACK;
            return;
        } 
        else 
        {
            deleteNodeCase5(doubleBlackNode, rootReference);
        }
}


void deleteNodeCase3(Node* doubleBlackNode, Node** rootReference) 
{
        Node* siblingNode = findSiblingNode(doubleBlackNode);

        if(doubleBlackNode->parent->color == BLACK && siblingNode->color == BLACK && siblingNode->left->color == BLACK
                && siblingNode->right->color == BLACK) 
        {
            siblingNode->color = RED;
            deleteNodeCase1(doubleBlackNode->parent, rootReference);
        } 
        else 
        {
            deleteNodeCase4(doubleBlackNode, rootReference);
        }
}

void deleteNodeCase2(Node* doubleBlackNode, Node** rootReference) 
{
        Node* siblingNode = findSiblingNode(doubleBlackNode);
        if(siblingNode->color == RED) 
        {
            if(isLeftChild(siblingNode)) 
            {
                rightRotate(siblingNode, true);
            } 
            else 
            {
                leftRotate(siblingNode, true);
            }
            if(siblingNode->parent == NULL) 
            {
                *rootReference=siblingNode;
            }
        }
        deleteNodeCase3(doubleBlackNode, rootReference);
}


void deleteNodeCase1(Node* doubleBlackNode, Node** rootReference) 
{
        if(doubleBlackNode->parent == NULL) 
        {
            *rootReference=doubleBlackNode;
            return;
        }
        deleteNodeCase2(doubleBlackNode, rootReference);
}

void replaceNode(Node* root, Node* child, Node** rootReference) 
{
        child->parent = root->parent;
        if(root->parent == NULL) 
        {
            *rootReference=child;
        }
        else 
        {
            if(isLeftChild(root)) 
            {
                root->parent->left = child;
            } 
            else 
            {
                root->parent->right = child;
            }
        }
}

void deleteNodeOneChild(Node* nodeToBedeleteNode, Node** rootReference) 
{
        Node* child;
        if(nodeToBedeleteNode->right->nullleaf==1)  
            child=nodeToBedeleteNode->left;
        else
            child=nodeToBedeleteNode->right;


        replaceNode(nodeToBedeleteNode, child, rootReference);


        if(nodeToBedeleteNode->color == BLACK) 
        {
            if(child->color == RED) 
            {
                child->color = BLACK;
            } 
            else 
            {
                deleteNodeCase1(child, rootReference);
            }
        }
}

void deleteNode(Node* root, int data, Node** rootReference) 
{
        if(root == NULL || root->nullleaf) 
        {
            return;
        }

        if(root->data == data) 
        {
            if(root->right->nullleaf || root->left->nullleaf) 
            {
                deleteNodeOneChild(root, rootReference);
            } 
            else 
            {
                Node* inorderSuccessor = findSmallest(root->right);
                root->data = inorderSuccessor->data;
                deleteNode(root->right, inorderSuccessor->data, rootReference);
            }
        }
        if(root->data < data) 
        {
            deleteNode(root->right, data, rootReference);
        }
        else 
        {
            deleteNode(root->left, data, rootReference);
        }
}

bool noRedRedParentChild(Node* root, int parentColor) 
{
    if(root == NULL) 
    {
        return true;
    }
    if(root->color == RED && parentColor == RED) 
    {
        return false;
    }

    return noRedRedParentChild(root->left, root->color) && noRedRedParentChild(root->right, root->color);
}

bool checkBlackNodesCount(Node* root, int* blackCount, int currentCount) 
{

    if(root->color == BLACK) 
    {
        currentCount++;
    }

    if(root->left == NULL && root->right == NULL) 
    {
        if(*blackCount == 0) 
        {
            *blackCount=currentCount;
            return true;
        } 
        else 
        {
            return currentCount == *blackCount;
        }
    }
    return checkBlackNodesCount(root->left, blackCount, currentCount) && checkBlackNodesCount(root->right, blackCount, currentCount);

}

bool validateRedBlackTree(Node* root) 
{
    if(root == NULL) 
    {
        return true;
    }
    if(root->color != BLACK) 
    {
        cout<<"Root is not black";
        return false;
    }
    
    int blackCount = 0;
    return checkBlackNodesCount(root, &blackCount, 0) && noRedRedParentChild(root,BLACK);
}


Node* delete_(Node* root, int data) 
{
        Node** rootReference = new Node*();
        deleteNode(root, data, rootReference);
        if(*rootReference == NULL) 
        {
            return root;
        } 
        else 
        {
            return *rootReference;
        }
}

Node* search(Node* root,int data)
{
    if(root == NULL || root->nullleaf) 
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
    if(root==NULL || root->nullleaf)
    {
        cout<<"Tree is empty\n";
        return -1;
    }
    Node* temp=root;
    while(!temp->left->nullleaf)
    {
        temp=temp->left;
    }
    return temp->data;
}

int maxElement(Node* root)
{
    if(root==NULL || root->nullleaf)
    {
        cout<<"Tree is empty\n";
        return -1;
    }
    Node* temp=root;
    while(!temp->right->nullleaf)
    {
        temp=temp->right;
    }
    return temp->data;
}


Node* successor(Node* root,int data)
{
    Node* temp = search(root,data);

    if(temp==NULL || temp->nullleaf)
    {
        return NULL;
    }

    if(temp->right!=NULL && !temp->right->nullleaf)
    {
        return findSmallest(temp->right);
    }

    Node* succ=NULL;

    Node* temproot=root;
    while(temproot!=NULL && !temproot->nullleaf)
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

    if(temp==NULL || temp->nullleaf)
    {
        return NULL;
    }

    if(temp->left!=NULL && !temp->left->nullleaf)
    {
        return findLargest(temp->left);
    }

    Node* prec=NULL;

    Node* temproot=root;
    while(temproot!=NULL && !temproot->nullleaf)
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
    cout<<"\n----- * Red Black Tree * -----\n";

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
            //Node* temp = new Node(a[i]);
            root = insert(root, a[i]);
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
        FILE* f=fopen("output_RB.txt","w");
        for (int i = 0; i < v.size(); ++i)
        {
            double x = v[i];
            fprintf(f, "%f\n", x );
            //cout<<i<<" "<<v[i]<<"\n";
        }
        cout<<root->data<<endl;
        fclose(fp);
        fclose(f);

        v.clear();
        fp = fopen("dataset_search.txt","r");
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
            search(root, a[i]);
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
        FILE* f1=fopen("output_RB_search.txt","w");
        for (int i = 0; i < v.size(); ++i)
        {
            double x = v[i];
            fprintf(f1, "%f\n", x );
            //cout<<i<<" "<<v[i]<<"\n";
        }
        //cout<<root->data<<endl;
        fclose(f1);

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
            root=delete_(root, a[i]);
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
        f1=fopen("output_RB_s.txt","w");
        for (int i = 0; i < v.size(); ++i)
        {
            double x = v[i];
            fprintf(f1, "%f\n", x );
            //cout<<i<<" "<<v[i]<<"\n";
        }
        //cout<<root->data<<endl;
        fclose(f1);

       //  root = insert(root, 15);
       //  root = insert(root, -10);
       //  root = insert(root, 20);
       //  root = insert(root, 30);
       //  root = insert(root, 40);
       //  root = insert(root, 50);
       //  root = insert(root, -15);
       //  root = insert(root, 25);
       //  root = insert(root, 17);
       //  root = insert(root, 21);
       //  root = insert(root, 24);
       //  root = insert(root, 28);
       //  root = insert(root, 34);
       //  root = insert(root, 32);
       //  root = insert(root, 26);
       //  root = insert(root, 35);
       //  root = insert(root, 19);
       //  printInoder(root);
       //  cout<<endl;
       //  printPreorder(root);
       //  cout<<endl;


       //  root = delete_(root, 50);
       // // cout<<validateRedBlackTree(root)<<endl;
       //  root = delete_(root, 40);
       //  root = delete_(root, -10);
       //  root = delete_(root, 15);
       //  root = delete_(root, 17);
       //  root = delete_(root, 24);
       //  root = delete_(root, 21);
    
       //  printInoder(root);
       //  cout<<endl;
       //  printPreorder(root);
       //  cout<<endl;


       //  Node* temp=search(root,19);
       //  if(temp==NULL || temp->nullleaf )
       //  {
       //      cout<<"Element Not present\n";
       //  }
       //  else
       //  {
       //      cout<<"Element is present : "<<temp->data<<endl;
       //  }


       //  cout<<"Minimum Element of the tree : "<<minElement(root)<<endl;
       //  cout<<"Maximum Element of the tree : "<<maxElement(root)<<endl;

       //  int x;
       //  cin>>x;

       //  temp=successor(root,x);
       //  if(temp==NULL || temp->nullleaf)
       //  {
       //      cout<<"No Successor\n";
       //  }
       //  else
       //  {
       //      cout<<"Successor of "<< x <<" is : "<<temp->data<<endl;
       //  }
        
       //  temp=predecessor(root,x);
       //  if(temp==NULL || temp->nullleaf)
       //  {
       //      cout<<"No Predecessor\n";
       //  }
       //  else
       //  {
       //      cout<<"Predecessor of "<< x <<" is : "<<temp->data<<endl;
       //  }

        return 0;
}
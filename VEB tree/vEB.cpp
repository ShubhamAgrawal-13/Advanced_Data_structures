#include<bits/stdc++.h>
using namespace std;

class vEB
{
public:
	int u;
	int min;
	int max;

	vEB * summary;
	vector<vEB *> cluster;


	vEB(int size)
	{
		u=size;
		min=-1;
		max=-1;

		if(size<=2)
		{
			summary=NULL;
			cluster=vector<vEB * >(0,NULL);
		}
		else
		{
			int child_size = ceil(sqrt(size));

			summary=new vEB(child_size);

			cluster = vector<vEB *>(child_size,NULL);

			for(int i=0 ; i<child_size ;i++)
			{
				cluster[i]= new vEB(child_size);
			}

		}
	}

	int high( int u , int x)
	{
		int temp = ceil(sqrt(u));
		return x/temp;
	}

	int low(int u,int x)
	{
		int temp = ceil(sqrt(u));
		return x%temp;		
	}

	void insert(vEB * , int);
	bool search(vEB * , int);
	void vEB_empty_tree_insert(vEB * , int);
	int minimum(vEB *  );
	int maximum(vEB *  );
	void deleteKey(vEB * , int);
	int successor(vEB *, int);
	int predecessor(vEB * ,int);
};


void vEB :: vEB_empty_tree_insert(vEB * root, int key)
{
	root->min=key;
	root->max=key;
}

int vEB:: minimum(vEB * root )
{
	return root->min;
}

int vEB:: maximum(vEB * root)
{
	return root->max;
}

void vEB:: insert(vEB * root , int key)
{

	if(root->min==-1)
	{
		root->min=key;
		root->max=key;
		vEB_empty_tree_insert(root,key);
	}
	else
	{
		if(root->min > key)
		{
			swap(key,root->min);
		}

		if(root->u >2)
		{
			if(root->cluster[high(root->u,key)]->min == -1)
			{
				// root->cluster[high(key)]->min=low(key);
				insert(root->summary,high(root->u,key));
				vEB_empty_tree_insert(root->cluster[high(root->u,key)],low(root->u,key));
				root->cluster[high(root->u,key)]->min=low(root->u,key);
				root->cluster[high(root->u,key)]->max=low(root->u,key);
					
			}
			else
			{
				insert(root->cluster[high(root->u,key)],low(root->u,key));
			}
		}
		if(key > root->max)
		{
			root->max=key;
		}
	}
}

bool vEB :: search(vEB * root , int key)
{
	if(key==root->min || key==root->max)
		return true;
	else if(root->u==2)
		return false;
	else
		return search(root->cluster[high(root->u,key)],low(root->u,key));
}

void vEB ::deleteKey(vEB *V, int x)
{
	int d = (int)sqrt(V->u);

	if(V->min == V->max)
	{
		V->min = -1;
		V->max = -1;
	}
	else if(V->u == 2)
	{
		if(x == 0)
			V->min = 1;
		else
			V->min = 0;
		
		V->max = V->min;
	}
	else
	{
		if(x == V->min)
		{
			int f_cluster = minimum(V->summary);
			x = f_cluster*d + minimum(V->cluster[f_cluster]);
			V->min = x;
		}
		
		deleteKey(V->cluster[high(V->u,x)], low(V->u,x));

		if(minimum(V->cluster[high(V->u,x)]) == -1)
		{
			deleteKey(V->summary, high(V->u,x));
			
			if(x == V->max)
			{
				int summary_max = maximum(V->summary);
				if(summary_max == -1)
				{
					V->max = V->min;
				}
				else
				{
					V->max = summary_max * d + maximum(V->cluster[summary_max]);
				}

			}
		}
		else if(x == V->max)
		{
			V->max = high(V->u, x) * d + maximum(V->cluster[high(V->u,x)]);
		}
	} 
	
}

int vEB :: successor( vEB * v , int x)
{
	int d = (int)sqrt(v->u); 

	if(v->u == 2)
	{
		if(x==0 && v->max==1)
			return 1;
		else
			return -1;
	}
	else if(v->min != -1 && x<v->min)
	{
		return v->min;
	}
	else
	{
		int max_low=maximum( v->cluster [ high(v->u,x) ] );

		if(max_low != -1 && low(v->u,x) < max_low )
		{
			int offset=successor(v->cluster[high(v->u,x)], low(v->u,x) );
			return high(v->u,x)*d+offset;
		}
		else
		{
			int successor_cluster = successor(v->summary,high(v->u,x));
			
			if(successor_cluster == -1)
			{
				return -1;
			}
			else
			{
				int offset = minimum(v->cluster[successor_cluster]);
				return successor_cluster*d + offset;
			}
		}
	}
}

int vEB :: predecessor(vEB * v,int x)
{

	int d = (int)sqrt(v->u); 

	if(v->u == 2)
	{
		if(x==1 && v->min==0 )
			return 0;
		else
			return -1;
	}
	else if(v->max!=-1 && x>v->max)
	{
		return v->max;
	}
	else
	{
		int min_low = minimum(v->cluster[high(v->u, x)]);

		if(min_low !=-1 && low(v->u,x) > min_low)
		{
			int offset = predecessor(v->cluster[high(v->u,x)],low(v->u,x));
			return high(v->u,x)*d +offset;
		}
		else
		{
			int predecessor_cluster = predecessor(v->summary,high(v->u,x));

			if(predecessor_cluster==-1)
			{
				if(v->min != -1 && x > v->min)
				{
					return v->min;
				}
				else
				{
					return -1;
				}
			}
			else
			{
				int offset = maximum(v->cluster[predecessor_cluster]);
				return predecessor_cluster*d + offset;
			}
		}
	
	}
}


int main()
{   
	cout<<"\n----- * VEB Tree * -----\n";

        vEB* root = NULL;
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
        root=new vEB(n);
        int base=100;
        vector<double> v;
        t = clock(); 
        local_t=clock();
        for (int i = 0; i < n; ++i)
        {
            // cout<<a[i]<<" "<<i<<"\t";
            //Node* temp = new Node(a[i]);
            root->insert(root, a[i]);
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
        FILE* f=fopen("output_veb.txt","w");
        for (int i = 0; i < v.size(); ++i)
        {
            double x = v[i];
            fprintf(f, "%f\n", x );
            //cout<<i<<" "<<v[i]<<"\n";
        }
        //cout<<root->data<<endl;
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
            root->search(root, a[i]);
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
        FILE* f1=fopen("output_veb_search.txt","w");
        for (int i = 0; i < v.size(); ++i)
        {
            double x = v[i];
            fprintf(f1, "%f\n", x );
            //cout<<i<<" "<<v[i]<<"\n";
        }
        //cout<<root->data<<endl;
        fclose(f1);

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
        	int x=root->search(root,a[i]);
        	//x=root->search(root,a[i]);
            // if(x!=-1)
            // {
            // 	cout<<x<<" ";
            // 	cout<<i<<" "<<a[i]<<endl;
            // 	root->deleteKey(root, a[i]);
            // }
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
        f1=fopen("output_veb_s.txt","w");
        for (int i = 0; i < v.size(); ++i)
        {
            double x = v[i];
            fprintf(f1, "%f\n", x );
            //cout<<i<<" "<<v[i]<<"\n";
        }
        //cout<<root->data<<endl;
        fclose(f1);
	return 0;
}
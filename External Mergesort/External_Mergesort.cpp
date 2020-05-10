#include<stdio.h>
#include<iostream>
#include<stdlib.h>
#include<string.h>
#include<algorithm>
#include<limits.h>
using namespace std;

#define SIZE 1024*1001

int as[SIZE]={0};

typedef struct HeapNode
{
	int element;
	int findex;

}node;

void merging(int a[],int l,int m,int h)
{
	int b[h+1];
	//memset(b,0,sizeof(b));
	int i=l;
	int j=m+1;
	int k=l;

	if(i<=m && j<=h)
	{
		while(i<=m && j<=h)
		{
			if(a[i]>a[j])
			{
				b[k++]=a[j++];
			}
			else
			{
				b[k++]=a[i++];
			}
		}
	}
	if(i<=m)
	{
		while(i<=m)
		{
			b[k++]=a[i++];
		}
	}

	while(j<=h)
	{
		b[k++]=a[j++];
	}

	for(int i=l;i<=h;i++)
	{
		a[i]=b[i];
	}
}

void mergesort(int a[],int l,int h)
{
	if(l>=h)
	{
		return;
	}
	int m=(l+h)/2;
	mergesort(a,l,m);
	mergesort(a,m+1,h);
	merging(a,l,m,h);
}

void swapNode(node* t1, node* t2) 
{ 
    node temp;
    temp = *t1; 
    *t1 = *t2; 
    *t2 = temp; 
} 

void heapify(node *a,int n,int i)
{
	int l = 2*i+1; 
    int r = 2*i+2; 
    int sm = i; 
    if (l < n && a[l].element < a[i].element) 
        sm = l; 
    if (r < n && a[r].element < a[sm].element) 
        sm = r; 
    if (sm != i) 
    { 
        swapNode(&a[i], &a[sm]); 
        heapify(a,n,sm); 
    } 
}

void insertHeap(node *a,int n)
{
	for(int i=(n-1)/2;i>=0;i--)
	{
		heapify(a,n,i);
	}
}


int main(int argc,char** argv)
{
	cout<<"External Merge Sort : \n";
	char fileinput[50],fileoutput[50];
	// cout<<"Enter Input File Name : ";
	// cin>>fileinput;
	// cout<<"Enter Output File Name : ";
	// cin>>fileoutput;
	if(argc<3)
	{
		cout<<"Enter name of input file and output from command prompt \n";
		exit(1);
	}

	strcpy(fileinput,argv[1]);
	strcpy(fileoutput,argv[2]);

	//cout<<fileinput<<"   "<<fileoutput<<endl;

	FILE* fr = fopen(fileinput,"r");
	FILE* foutput = fopen(fileoutput,"w");

	//FILE* fr = fopen("largefile.txt","r");
	//FILE* foutput = fopen("output.txt","w");

	size_t length=0;
	char* buffer=NULL;

	// ssize_t n =getline(&buffer,&length,fr);
	// //fscanf(fr,"[^\n]",ch);
	// int a=atoi(buffer);
	// cout<<a<<endl;    
	ssize_t n=0;
	int file=0;
	
	while (1)  
	{
		int i=0;
		memset(as,0,SIZE);
		while(i<SIZE && (n = getline(&buffer, &length, fr)) != -1)
		{
			as[i++]=atoi(buffer);
		}
		
		if(i==0 && n==-1)
		{
			//cout<<"hello\n";
			break;
		}

		//sort(as,as+i);
		mergesort(as,0,i-1);
		char ch[20];
		sprintf(ch,"%d.txt",file);

		FILE* fw = fopen(ch,"w");
		for(int j=0;j<i;j++)
		{
			fprintf(fw,"%d\n", as[j]);
		}
		fclose(fw);
		file++;
		if(n==-1)
		{
			cout<<"hey hello\n";
			break;
		}
	}

	int k=file,c=0;

	FILE* fk[k];

	for(int i=0;i<k;i++)
	{
		char ch[20];
		sprintf(ch,"%d.txt",i);
		fk[i]=fopen(ch,"r");
	}

	node heap[k];

	for(int i=0;i<k;i++)
	{
		char* buffer=NULL;
		size_t length=0;
		ssize_t n = getline(&buffer, &length, fk[i]);
		heap[i].findex=i;
		heap[i].element=atoi(buffer);
	}

	insertHeap(heap,k);

	while(1)
	{
		if(c==k)
		{
			break;
		}
		fprintf(foutput ,"%d\n", heap[0].element);
		cout<<heap[0].element<<endl;
		char* buffer=NULL;
		size_t length=0;
		//cout<<heap[0].findex<<"\n";
		ssize_t n = getline(&buffer, &length, fk[heap[0].findex]);
		if(n==-1)
		{
			heap[0].element=2147483647;
			c++;
			//continue;
		}
		else
		{
			heap[0].element=atoi(buffer);
			//cout<<heap[0].element<<endl;
		}
		//heap[0].findex
		//changemin(heap,n,heap[0]);
		heapify(heap,k,0);
	}

	// while ( i<SIZE && ((n = getline(&buffer, &length, fr)) != -1) ) 
	// {
	//     //printf("Retrieved line of length %zu:\n", n);
	//     as[i++]=atoi(buffer);
	// 	//cout<<i<<" "<<a<<endl;
	// }
	
	fclose(foutput);
	for(int i=0;i<k;i++)
	{
		fclose(fk[i]);
	}

	for(int i=0;i<k;i++)
	{
		char ch[20];
		sprintf(ch,"%d.txt",i);
		remove(ch);
	}
	cout<<"Completed \n";
	free(buffer);
	fclose(fr);
	return 0;
}
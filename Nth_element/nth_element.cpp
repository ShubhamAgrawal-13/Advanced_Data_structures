#include<iostream>
#include<string.h>
#include<stdio.h>
#include<stdlib.h>
#include<algorithm>
#include<vector>
#include<time.h>

#define MIN(x,y) (x>y)?y:x
#define ll long long

using namespace std;

int partition(int a[],int l,int r)
{
	int pivot = l;  
 	int p=l+1;
 	int q=r; 

    while(p<=q)
    {
    	while(a[p]<a[pivot])
    		p++;
    	while(a[q]>a[pivot])
    		q--;
    	if(p<q)
    	{
    		int temp;
    		temp=a[p];
    		a[p]=a[q];
    		a[q]=temp;
    	}
    }
    int temp;
    temp=a[q];
    a[q]=a[pivot];
    a[pivot]=temp;
    return q;
}

// void quicksort(int a[],int l,int r)
// {
// 	if(l<r)
// 	{
// 		int p = partition(a,l,r);
// 		quicksort(a,l,p-1);
// 		quicksort(a,p+1,r);
// 	}
// }

int nthelement(int a[],int l,int r,int k)
{
	int size=r-l+1;
	int random=rand()%size+l;
	int temp = a[random];
	a[random]=a[l];
	a[l]=temp;

	if(l<=r)
	{
		int i = partition(a,l,r);
		if(i>size/4 && i<3*size/4)
		{
			size=r-l+1;
			random=rand()%size+l;
			temp = a[random];
			a[random]=a[l];
			a[l]=temp;
		}
		if(i==k)
		{
			return a[k];
		}
		else if(i>k)
		{
			return nthelement(a,l,i-1,k);
		}
		else
		{
			return nthelement(a,i+1,r,k);
		}
	}
}

int main()
{
	int n;
	cin>>n;
	int *a=new int[n];
	int *b=new int[n];
	for(int i=0;i<n;i++)
	{
		a[i]=rand()%99999999;
		b[i]=a[i];
	}

	int k;
	cin>>k;
	clock_t s;

	s=clock();
	//sort(a,a+n);
	cout<<"nth element : "<<nthelement(a,0,n-1,k-1)<<endl;
	s=clock()-s;
	cout<<(float)s/CLOCKS_PER_SEC<<endl;

	s=clock();
	nth_element(b,b+k,b+n);
	cout<<"nth element by method : "<<a[k-1]<<endl;
	s=clock()-s;
	cout<<(float)s/CLOCKS_PER_SEC<<endl;
		

	// quicksort(a,0,n-1);
	// cout<<"array : \n";
	// for(int i=0;i<n;i++)
	// {
	// 	cout<<a[i]<<" ";
	// }
	// cout<<"\n";
	return 0;
}
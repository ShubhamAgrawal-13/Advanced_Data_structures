#include<iostream>
#include<string>

using namespace std;

//#define ll long long

//Task 2 : Implementation of Deque 

template<typename T>
class deque
{
	unsigned int d_size=0,maxsize=0;
	T* a;
	int Front=0,Rear=0;
	public:
		deque()
		{
			maxsize=10;
			a=new T[maxsize];
			d_size=0;
		}
		deque(unsigned int n)
		{
			maxsize=n+1;
			a=new T[maxsize];
			d_size=0;
		}
		deque(unsigned int n,T x)
		{
			maxsize=n+1;
			a=new T[maxsize];
			for(int i=0;i<maxsize;i++)
			{
				a[i]=x;
			}
			d_size=0;
		}
		~deque()
		{
			delete[] a;
		}
		void push_back(T);
		void pop_back();
		void push_front(T);
		void pop_front();
		void erase(T key);
		T front()
		{
			if(d_size==0)
				cout<<"Empty Deque : some invalid value";
			return a[(Front+1)%maxsize];
		}
		int frontindex()
		{
			if(d_size==0)
				cout<<"Empty Deque : some invalid value";
			return (Front+1)%maxsize;
		}
		T back()
		{
			if(d_size==0)
				cout<<"Empty Deque : some invalid value";
			return a[Rear%maxsize];
		}
		int backindex()
		{
			if(d_size==0)
				cout<<"Empty Deque : some invalid value";
			return Rear%maxsize;
		}
		void clear()
		{
			d_size=0;
			Front=0;
			Rear=0;
		}
		int empty()
		{
			if(d_size==0)
				return 1;
			return 0;
		}
		void alloc_memory();
		void alloc_memory(unsigned int);
		int size()
		{
			return d_size;
		}
		int capacity()
		{
			return maxsize;
		}
		void resize(unsigned int size)
		{
			alloc_memory(size);
		}
		T operator[](unsigned int);
		void printdeque()
		{
			if(Rear>Front)
			{
				for(int i=(Front+1)%maxsize;i<=Rear;i++)
				{
					cout<<a[i]<<" ";
				}
				cout<<endl;
			}
			else if(Rear==Front)
			{
			}
			else
			{
				for(int i=Front+1;i<maxsize;i++)
				{
					cout<<a[i]<<" ";
				}
				for(int i=0;i<=Rear;i++)
				{
					cout<<a[i]<<" ";
				}
				cout<<endl;
			}
		}
		void printdeque1(T k[])
		{
			int ind=0;
			if(Rear>Front)
			{
				for(int i=(Front+1)%maxsize;i<=Rear;i++)
				{
					k[ind++]=a[i];
				}
				//cout<<endl;
			}
			else if(Rear==Front)
			{
			}
			else
			{
				for(int i=Front+1;i<maxsize;i++)
				{
					k[ind++]=a[i];
				}
				for(int i=0;i<=Rear;i++)
				{
					k[ind++]=a[i];
				}
				//cout<<endl;
			}
		}
};

template<typename T>
void deque<T>::push_back(T t)
{
	if(Front==(Rear+1)%maxsize)
	{
		if(d_size >= maxsize-1)
			alloc_memory();
	}
	Rear=(Rear+1)%maxsize;
	a[Rear]=t;	
	d_size++;
}

template<typename T>
void deque<T>::push_front(T t)
{
	if(Front==(Rear+1)%maxsize)
	{
		if(d_size >= maxsize-1)
			alloc_memory();
	}
	if(Front==0 && d_size<maxsize-1)
	{
		a[Front]=t;
		Front=maxsize-1;
	}
	else
	{
		if(d_size<maxsize-1)
		{
			a[Front]=t;
			Front--;
		}
	}
	d_size++;
}

template<typename T>
void deque<T>::pop_front()
{
	if(Front==Rear)
		cout<<"Deque is empty!!! --- cannot pop ---\n";
	else
	{
		Front=(Front+1)%maxsize;
		d_size--;
	}
}

template<typename T>
void deque<T>::pop_back()
{
	if(Front==Rear)
		cout<<"Deque is empty!!! --- cannot pop ---\n";
	else
	{
		if(Rear==0 && d_size<maxsize-1)
		{	
			Rear=maxsize-1;
		}
		else
		{
			Rear=Rear-1;
		}
		d_size--;
	}
}

template<typename T>
void deque<T>::alloc_memory()
{
	int tempm=maxsize;
	maxsize=d_size*2;
	T *temp = new T[maxsize];
	int j=1;
	if(Rear>Front)
	{
		for(int i=(Front+1)%tempm;i<=Rear;i++)
		{
			temp[j++]=a[i];
		}
	}
	else if(Rear==Front)
	{
	}
	else
	{
		for(int i=Front+1;i<tempm;i++)
		{
			temp[j++]=a[i];
		}
		for(int i=0;i<=Rear;i++)
		{
			temp[j++]=a[i];
		}
	}
	delete[] a;
	Front=0;
	Rear=j-1;
	d_size=Rear;
	a=temp;
}

template<typename T>
void deque<T>::alloc_memory(unsigned int size)
{
	int tempm=maxsize;
	maxsize=size;
	T *temp = new T[maxsize];
	int j=1;
	if(Rear>Front)
	{
		for(int i=(Front+1)%tempm;i<=Rear;i++)
		{
			temp[j++]=a[i];
		}
	}
	else if(Rear==Front)
	{
	}
	else
	{
		for(int i=Front+1;i<tempm;i++)
		{
			temp[j++]=a[i];
		}
		for(int i=0;i<=Rear;i++)
		{
			temp[j++]=a[i];
		}
	}
	delete[] a;
	Front=0;
	Rear=j-1;
	d_size=maxsize;
	a=temp;
}

template<typename T>
T deque<T>::operator[](unsigned int i)
{
	if(!(i<d_size && i>=0))
		cout<<"Invalid Index : (Garbage) ";
	return a[(Front+1+i)%maxsize];
}

template<typename T>
void deque<T>::erase(T key)
{
	//cout<<"hello\n";
	int c=maxsize-1,j=0;
	//cout<<c<<endl;
	T b[c];
	if(Rear>Front)
	{
		for(int i=(Front+1)%maxsize;i<=Rear;i++)
		{
			b[j]=a[i];
			j++;
			//cout<<b[j-1]<<endl;
		}
	}
	else if(Rear==Front)
	{
	}
	else
	{
		for(int i=Front+1;i<maxsize;i++)
		{
			b[j++]=a[i];
		}
		for(int i=0;i<=Rear;i++)
		{
			b[j++]=a[i];
		}
	}

	
	int i=0;
	//cout<<"hello1\n";
	for(i=0;i<c;i++)
	{
		if(b[i] == key)
		{
			break;
		}
	}
	//cout<<"hello2\n";
	while(i<d_size-1)
	{
		b[i]=b[i+1];
		i++;
	}
	//cout<<"hello3\n";
	b[d_size-1]=key;
	//cout<<"hello3\n";
	//for(int i=0;i<c;i++)
		//cout<<b[i]<<" ";
	//cout<<endl;
	j=0;
	if(Rear>Front)
	{
		for(int i=(Front+1)%maxsize;i<=Rear;i++)
		{
			a[i]=b[j++];
		}
	}
	else if(Rear==Front)
	{
	}
	else
	{
		for(int i=Front+1;i<maxsize;i++)
		{
			a[i]=b[j++];
		}
		for(int i=0;i<=Rear;i++)
		{
			a[i]=b[j++];
		}
	}
}

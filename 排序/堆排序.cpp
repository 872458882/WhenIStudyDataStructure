#include<iostream>
using namespace std;


struct Node
{
	int item;
	int key;
}; 


void swap(int &A,int &B)
{
	int temp=A;
	A=B;
	B=A;
}


void Restore(Node*R[],int low,int high)
{
	int i=low;
	int m;
	while(i<=high/2)
	{
		if(2*i<high && R[2*i]->key < R[2*i+1]->key)  
				m=2*i+1;
		//if(2*i<e && R[2*i]->key > R[2*i+1]->key||2*i==e) 
		else m=2*i;
		if(R[m]->key > R[i]->key) 
		{
			swap(R[i],R[m]);
			i=m;
		}	
		else i=high;
	}
}

void Heapsort(Node*R[],int n)
{
	for(int i=n/2;i>0;i--)
		Restore(R,i,n);//初始建堆 
	for(int i=n;i>1;i--)
	{
		swap(R[1],R[i]);
		Restore(R,1,i-1);
	}
}


int main()
{
	cout<<"输入要排序的数的个数"<<endl;
	int n;
	cin>>n; 
	Node**H=new Node*[n+1];
	int x;
	int i=1;
	while(i<=n&&cin>>x)
	{
		H[i]=new Node;
		H[i]->key=x;
		++i;
	} 
	Heapsort(H,n);
	for(int i=1;i<n+1;i++)
	{
		cout<<H[i]->key<<" ";
	}
	cout<<endl;
	
}



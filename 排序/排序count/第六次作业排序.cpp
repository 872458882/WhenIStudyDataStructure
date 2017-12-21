#include<iostream>
#include<fstream>
#include<stack>
#include <time.h>
#include <sys/timeb.h>
 
using namespace std;

int count;
void quicksort1(int k[],int low,int high)
{
	if(low>=high) //���û�м�¼����ֻ��һ����¼
		return;
	int i=low,j=high;//i��ǰ�������j�Ӻ���ǰ��
	int pivot=k[low];//ѡ����һ��Ԫ��Ϊ�ؼ�Ԫ 
	while(i<j) 
	{
		while(i<j && k[j]>=pivot) 
		{
			--j;
			count++;
		}
		count++;
		if(i<j)
		{
			k[i]=k[j];
			i++; 
			
		}	
		while(i<j && k[i]<=pivot) 
		{
			++i;
			count++;
		}
		count++;
		if(i<j)
		{
			k[j]=k[i];
			j--;
		}
	} 
	k[i]=pivot;
	quicksort1(k,low,i-1);
	quicksort1(k,i+1,high);
}

void swap(int& a,int& b)
{
	int temp=a;
	a=b;
	b=temp;
}

void quicksort2(int k[],int low,int high)
{
	if(low>=high) return;//���û�м�¼����ֻ��һ����¼
	
	int i=low;
	int j=high+1;
	int pivot=k[low];
	while(i<j)
	{
		i++;
		while(k[i]<pivot) {i++;count++;}
		count++;
		j--;
		while(k[j]>pivot) {j--;count++;}
		count++;
		if(i<j)
			swap(k[i],k[j]);
	}
	swap(k[low],k[j]);
	quicksort2(k,low,j-1);
	quicksort2(k,j+1,high);
} 

void quicksort3(int k[],int low,int high)
{
	if(low>=high) return;

	//STEP1:ѡ�м�ֵԪ�� 
	swap(k[(low+high)/2] ,k[low+1]);
	if(k[low+1]>k[high]) swap(k[low+1],k[high]);
	if(k[low]>k[high]) swap(k[low],k[high]);
	if(k[low+1]>k[low]) swap(k[low],k[low+1]);
	count=count+3;
	//STEP2:
	int i=low;
	int j=high+1;
	int pivot=k[low];
	while(i<j)
	{
		i++;
		while(k[i]<pivot) {i++;count++;}
		count++;
		j--;
		while(k[j]>pivot) {j--;count++;}
		count++;
		if(i<j)
			swap(k[i],k[j]);
	}
	swap(k[low],k[j]);
	quicksort3(k,low,j-1);
	quicksort3(k,j+1,high);
	
} 


int part4(int k[],int low,int high)
{
	
	//STEP1:ѡ�м�ֵԪ�� 
	swap(k[(low+high)/2] ,k[low+1]);
	if(k[low+1]>k[high]) swap(k[low+1],k[high]);
	if(k[low]>k[high]) swap(k[low],k[high]);
	if(k[low+1]>k[low]) swap(k[low],k[low+1]);
	count=count+3;
	//STEP2:
	int i=low;
	int j=high+1;
	int pivot=k[low];
	while(i<j)
	{
		i++;
		while(k[i]<pivot) {i++;count++;}
		count++;
		j--;
		while(k[j]>pivot) {j--;count++;}
		count++;
		if(i<j)
			swap(k[i],k[j]);
	}
	swap(k[low],k[j]);
	return j;	
} 



void insertsort(int k[],int n)
{
	for(int i=1;i<n;i++)
	{
		int j=i;
		int temp=k[i];
		while(i>0&&temp<k[j-1])
		{
			k[j]=k[j-1];
			j--;
			count++;
		}
		count++;
		k[j]=temp;
	}
}

void quicksort4(int k[],int low,int high,int M)
{
	stack<int>s;
	int temp;
	int n=high-low+1;
	s.push(0);
	s.push(0);
	while(low < high)
	{
		int mid=part4(k,low,high);
		if((mid-low<M) && (high-mid<M))
		{
			low=s.top(); s.pop();
			high=s.top();s.pop();
			continue;
		}
		if((mid-low<M)&&(high-mid>=M))
		{
			low=mid+1;continue;
		}
		if((mid-low>=M)&&(high-mid<M))
		{
			high=mid-1;continue;
		}
		if((mid-low>=M)&&(high-mid>=M))
		{
			if(mid-low>high-mid)
			{
				s.push(mid-1);s.push(low);
				low=mid+1;
			}
			else
			{
				s.push(high);s.push(mid+1);
				high=mid-1;
			}
		}
	}
	insertsort(k,n);
}

void selectsort(int k[],int n)
{
	for(int i=n-1;i>0;i--)
	{
		int t=0;
		for(int j=1;j<i+1;j++)
		{
			if(k[j]>k[t]) {t=j;count++;}
		}
		swap(k[i],k[t]);
	}
} 


struct Node
{
	int item;
	int key;
}; 

void Restore(Node*R[],int low,int high)
{
	int i=low;
	int m;
	while(i<=high/2)
	{
		if(2*i<high && R[2*i]->key < R[2*i+1]->key)  
		{
			m=2*i+1;
		}
		else m=2*i;
		count++;
		if(R[m]->key > R[i]->key) 
		{
			swap(R[i],R[m]);
			i=m;
		}
		else i=high;
		count++;
	}
}

void Heapsort(Node*R[],int n)
{
	for(int i=n/2;i>0;i--)
		Restore(R,i,n);//��ʼ���� 
	for(int i=n;i>1;i--)
	{
		swap(R[1],R[i]);
		Restore(R,1,i-1);
	}
}

int main()
{
	Node**H=new Node*[501];


	srand((unsigned)time(NULL)); 
	ofstream outfile("paixu.txt");
	if(!outfile.is_open()) 
	{
		cout<<"�ļ�д�����"<<endl;
		return 0; 
	}
	cout<<"�������500�������x��-1000<=x<=1000"<<endl;
	outfile<<"�������500�������x��-1000<=x<=1000"<<endl;
	int unsorted1[500];
	int unsorted2[500];
	int unsorted3[500];
	int unsorted4[500];
	
	for(int i=0;i<20;i++)
	{
		for(int j=0;j<25;j++)
		{
			H[i*25+j+1]=new Node;
			H[i*25+j+1]->key=unsorted4[25*i+j]=unsorted3[25*i+j]=unsorted2[25*i+j]=unsorted1[25*i+j]=rand()%2000-1000;
			cout<<unsorted1[25*i+j]<<" ";
			outfile<<unsorted1[25*i+j]<<" ";
		}
		cout<<endl; 
	}
	
	cout<<"\n\n�������£�"<<endl;
	outfile<<"\n\n�������£�"<<endl;
	cout<<"\n���������㷨:"<<endl;
	outfile<<"\n\n���������㷨��"<<endl;
	count=0; 
	quicksort2(unsorted2,0,499);
	for(int i=0;i<20;i++)
	{
		for(int j=0;j<25;j++)
		{
			cout<<unsorted2[25*i+j]<<" ";
			outfile<<unsorted2[25*i+j]<<" ";
		}
		cout<<endl; 
	}
	cout<<"\n�Ƚϴ���:"<<count<<endl;
	outfile<<"\n�Ƚϴ���:"<<count<<endl;
	
	cout<<"\n����ȡ��ֵ�Ŀ��������㷨:"<<endl;
	outfile<<"\n����ȡ��ֵ�Ŀ��������㷨:"<<endl;
	count=0; 
	quicksort3(unsorted3,0,499);
	for(int i=0;i<20;i++)
	{
		for(int j=0;j<25;j++)
		{
			cout<<unsorted3[25*i+j]<<" "; 
			outfile<<unsorted3[25*i+j]<<" ";
		}
		cout<<endl; 
	}
	cout<<"\n�Ƚϴ���:"<<count<<endl;
	outfile<<"\n�Ƚϴ���:"<<count<<endl;
	
	cout<<"\n�Ľ��Ŀ��������㷨:"<<endl;
	outfile<<"\n�Ľ��Ŀ��������㷨:"<<endl;
	count=0;
	quicksort4(unsorted4,0,499,5);
	for(int i=0;i<20;i++)
	{
		for(int j=0;j<25;j++)
		{
			cout<<unsorted4[25*i+j]<<" ";
			outfile<< unsorted4[25*i+j]<<" ";
		}
		cout<<endl; 
	}
	cout<<"\n�Ƚϴ���:"<<count<<endl;
	outfile<<"\n�Ƚϴ���:"<<count<<endl;
	
	count=0;
	cout<<"������"<<endl;
	outfile<<"������: "<<endl; 
	Heapsort(H,500);
	for(int i=1;i<501;i++)
	{
		cout<<H[i]->key<<" ";
		outfile<<H[i]->key<<" "; 
	}
	cout<<endl;
	outfile<<endl; 
	cout<<"\n�Ƚϴ�����"<<count<<endl;
	outfile<<"\n�Ƚϴ�����"<<count<<endl;
	
	cout<<"\n\n�����������"<<endl; 
	outfile<<"\n\n�����������"<<endl; 
	cout<<"\n���������㷨:"<<endl;
	outfile<<"\n���������㷨:"<<endl;
	count=0; 
	quicksort2(unsorted2,0,499);
	for(int i=0;i<20;i++)
	{
		for(int j=0;j<25;j++)
		{
			cout<<unsorted2[25*i+j]<<" "; 
			outfile<<unsorted2[25*i+j]<<" "; 
		}
		cout<<endl; 
	}
	cout<<"\n�Ƚϴ���:"<<count<<endl;
	outfile<<"\n�Ƚϴ���:"<<count<<endl;
	
	cout<<"\n����ȡ��ֵ�Ŀ��������㷨:"<<endl;
	outfile<<"\n����ȡ��ֵ�Ŀ��������㷨:"<<endl;
	count=0; 
	quicksort3(unsorted3,0,499);
	for(int i=0;i<20;i++)
	{
		for(int j=0;j<25;j++)
		{
			cout<<unsorted3[25*i+j]<<" "; 
			outfile<<unsorted3[25*i+j]<<" "; 
		}
		cout<<endl; 
	}
	cout<<"\n�Ƚϴ���:"<<count<<endl;
	outfile<<"\n�Ƚϴ���:"<<count<<endl;
	
	
	cout<<"\n�Ľ��Ŀ��������㷨:"<<endl;
	outfile<<"\n�Ľ��Ŀ��������㷨:"<<endl;
	count=0;
	quicksort4(unsorted4,0,499,5);
	for(int i=0;i<20;i++)
	{
		for(int j=0;j<25;j++)
		{
			cout<<unsorted4[25*i+j]<<" "; 
			outfile<<unsorted4[25*i+j]<<" ";
		}
		cout<<endl; 
	}
	cout<<"\n�Ƚϴ���:"<<count<<endl;
	outfile<<"\n�Ƚϴ���:"<<count<<endl;
	
	count=0;
	cout<<"������"<<endl;
	outfile<<"������: "<<endl; 
	Heapsort(H,500);
	for(int i=1;i<501;i++)
	{
		cout<<H[i]->key<<" ";
		outfile<<H[i]->key<<" "; 
	}
	cout<<endl;
	outfile<<endl; 
	cout<<"\n�Ƚϴ�����"<<count<<endl;
	outfile<<"\n�Ƚϴ�����"<<count<<endl;
	
	outfile.close(); 
	return 0; 
}




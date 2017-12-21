#include<iostream>
#include<stack>
using namespace std;

void quicksort1(int k[],int low,int high)
{
	if(low>=high) //如果没有记录或者只有一个记录
		return;
	int i=low,j=high;//i从前向后数，j从后向前数
	int pivot=k[low];//选定第一个元素为关键元 
	while(i<j) 
	{
		while(i<j && k[j]>=pivot) --j;
		if(i<j)
		{
			k[i]=k[j];
			i++; 
		}	
		while(i<j && k[i]<=pivot) ++i;
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
	if(low>=high) return;//如果没有记录或者只有一个记录
	
	int i=low;
	int j=high+1;
	int pivot=k[low];
	while(i<j)
	{
		i++;
		while(k[i]<pivot) i++;
		j--;
		while(k[j]>pivot) j--;
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

	//STEP1:选中间值元素 
	swap(k[(low+high)/2] ,k[low+1]);
	if(k[low+1]>k[high]) swap(k[low+1],k[high]);
	if(k[low]>k[high]) swap(k[low],k[high]);
	if(k[low+1]>k[low]) swap(k[low],k[low+1]);

	//STEP2:
	int i=low;
	int j=high+1;
	int pivot=k[low];
	while(i<j)
	{
		i++;
		while(k[i]<pivot) i++;
		j--;
		while(k[j]>pivot) j--;
		if(i<j)
			swap(k[i],k[j]);
	}
	swap(k[low],k[j]);
	quicksort3(k,low,j-1);
	quicksort3(k,j+1,high);
	
} 
int part4(int k[],int low,int high)
{
	
	//STEP1:选中间值元素 
	swap(k[(low+high)/2] ,k[low+1]);
	if(k[low+1]>k[high]) swap(k[low+1],k[high]);
	if(k[low]>k[high]) swap(k[low],k[high]);
	if(k[low+1]>k[low]) swap(k[low],k[low+1]);

	//STEP2:
	int i=low;
	int j=high+1;
	int pivot=k[low];
	while(i<j)
	{
		i++;
		while(k[i]<pivot) i++;
		j--;
		while(k[j]>pivot) j--;
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
		}
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
			if(k[j]>k[t]) t=j;
		}
		swap(k[i],k[t]);
	}
} 



int main()
{

	
	int unsorted[10]={11,0,4,6,23,5,2,18,7,7};
	selectsort(unsorted,10);
	for(int i=0;i<10;i++) cout<<unsorted[i]<<" ";
	return 0; 
}

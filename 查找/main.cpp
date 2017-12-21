#include<iostream>
#include<cmath>
using namespace std;



int search(int x,int n,int A[]) //原始顺序查找 
{
	int i=0;
	while(i<n)
	{
		if(x==A[i]) return i;
		i++; 
	}
	return -1;
} 

int qsearch(int x,int n,int A[])//改进顺序查找1
{
	int i=0;
	A[n]=x;
	while(x!=A[i]) i++;
	if(i<n) return i; 
	return -1;
} 

int qsearch2(int x,int n,int A[])//改进的快速顺序查找
{
	int i=0;
	A[n]=x;
	for(;A[i]!=x;i+=2)
	{
		if(A[i+1]==x) {i++;break;}
	} 
	if(i<n) return i;
	return -1;
} 

int tsearch(int x,int n, int A[])//在已排序数组中顺序查找
{
	int i=0;
	A[n]=9999; 
	while(x>A[i]) i++;
	if(x==A[i]) return i;
	return -1;
} 

int bsearch(int x,int n,int A[])//在已排序数组中迭代二分查找
{
	int low=0,high=n-1;
	while(low<=high)
	{
		int mid=(low+high)/2;
		if(x==A[mid]) return mid;
		if(x<A[mid]) high=mid-1;
		else low=mid+1; 
	}
	return -1;
} 

int usearch(int x,int n,int A[])//一致对半查找
{
	int i=ceil((n-1)/2.0);
	int m=(n-1)/2;
	while(x!=A[i])
	{
		if(m==0) return -1;
		i= x<A[i]?i-ceil(m/2.0):i+ceil(m/2.0);
		m=m/2;
	} 
	return i;
} 

int cusearch(int x,int n,int A[])//辅助表一致对半查找
{
	int m;
	int Delta[m=(log(n)+2)/1];
	for(int i=0;i<m;i++)
	{
		Delta[i]=(n-1+pow(2,i-1))/pow(2,i);
	}
	int i=Delta[1],j=1;
	while(x!=A[i])
	{
		if(Delta[j]==0) return -1;
		i= x<A[i]? i-Delta[j]:i+Delta[j];
		j++;
	}
	return i;
}
int f[1000];
void getf()
{
	f[0]=0;
	f[1]=1;
	for(int i=2;i<1000;i++)
		f[i]=f[i-1]+f[i-2];
}

int fsearch(int x,int n,int m,int A[])//斐波那契查找
{
	int i=f[m];
	int p=f[m-1];
	int q=f[m-2];
	int t;
	while(x!=A[i])
	{
		if(x<A[i])
		{
			if(q==0) return -1;
			i-=q;//pq降一级 
			t=p;
			p=q;
			q=t-p;
		}else{
			if(p==1) return -1;
			i+=q;//pq降两级 
			p-=q;
			q-=p;
		}
	}
	return i;
}
 
int location2(int x,int low,int high,int A[])//在已排序数组中递归二分查找 
{
	if(x<A[low]||x>A[high])return 0;
	int mid=floor((low+high)/2);
	if(x==A[mid]) return mid+1;
	else if (x<A[mid]) return location2(x,low,mid-1,A);
	else return location2(x,mid+1,high,A);
}



int main()
{
	getf();
	int A[8]={1,3, 4,6, 22,56,88,0};
	cout<<search(22,7,A)<<endl;
	//cout<<qsearch(990,10,A)<<endl; 
	//cout<<qsearch2(990,10,A)<<endl; 
	//cout<<tsearch(990,10,A)<<endl;
	cout<<fsearch(22,7,5,A)<<endl;
	//cout<<cusearch(1,10,A)<<endl;
	
}

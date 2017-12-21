#include <iostream>
#include <memory.h>
#include <cmath>
#include <time.h>
#include <sys/timeb.h> 
using namespace std;

void merge(int R[],int low,int mid,int high,int X[])
{
	int i=low,j=mid+1,k=low;
	while(i<=mid&&j<=high)
		X[k++] = R[i]<R[j]? R[i++] : R[j++];
	if(i>mid)
		while(k<high+1)
			X[k++]=R[j++]; 
	else
		while(k<high+1)
			X[k++]=R[i++];
}

void mergepass(int R[],int n,int length,int X[])
{
	int i=0;
	while(i<n-length*2+1)
	{
		merge(R,i,i+length-1,i+2*length-1,X);
		i+=2*length;
	}
	if(i+length<n)
	{
		merge(R,i,i+length-1,n-1,X);
	}
	else 
	{
		while(i<n)
		{
			X[i]=R[i];
			i++;
		}
	}
} 

void mergesort(int R[],int n)
{
	int X[n];
	memset(X,0,sizeof(X));
	int length=1;
	while(length<n)
	{
		mergepass(R,n,length,X);
		length*=2;
		mergepass(X,n,length,R);
		length*=2; 
	}
}

void bubblesort(int R[],int n)
{
	int bound=n-1;
	while(bound!=-1)
	{
		int t=-1;
		for(int i=0;i<bound;i++)
		{
			if(R[i]>R[i+1]) 
			{
				int temp=R[i];
				R[i]=R[i+1];
				R[i+1]=temp;
				t=i; 
			}
			
		} 
		bound=t;
	} 
}
void shellsort(int a[], int n)
{
	int j, gap;	
	for (gap=n/2; gap>0; gap/= 2)
		for (j=gap; j<n; j++)//从数组第gap个元素开始
			if (a[j] < a[j-gap])//每个元素与自己组内的数据进行直接插入排序
			{
				int temp=a[j];
				int k=j-gap;
				while (k>=0 && a[k]>temp)
				{
					a[k+gap]=a[k];
					k-=gap;
				}
				a[k+gap]=temp;
			}
}


void countsort(int K[],int n,int u,int v)
{
	int S[n],count[n];
	memset(S,0,sizeof(S));
	memset(count,0,sizeof(count)); 
	for(int i=u;i<v+1;i++)//初始化 无错 
		count[i]=0;
	for(int j=0;j<n;j++)
		count[K[j]]++;
	for(int i=u+1;i<v+1;i++)
		count[i]+=count[i-1];
	for(int j=n-1;j>-1;j--)
	{
		int i=count[K[j]];
		S[i-1]=K[j];
		count[K[j]]=i-1;
		//for(int h=u;h<v+1;h++)//无错  
			//cout<<h<<":"<<count[h]<<" ";
		//cout<<endl;
	}
	for(int i=0;i<n;i++)
		K[i]=S[i];
} 


int maxbit(int data[], int n) //辅助函数，求数据的最大位数
{
    int d = 1; //保存最大的位数
    int p = 10;
    for(int i = 0; i < n; ++i) {
        while(data[i] >= p) {
            p *= 10;
            ++d;
        }
    }
    return d;
}
void radixsort(int data[], int n)   //基数排序
{
    int d = maxbit(data, n);   //数组中的元素的最大位数
    int tmp[n];
    int count[10];   //计数器
    int i, j, k;
    int radix = 1;
    for(i=1; i<=d; i++) {   //进行d次排序
        for(j=0; j<10; j++)
            count[j]=0;    //每次分配前清空计数器
        for(j=0; j<n; j++) 
		{
            k = (data[j]/radix)%10;   //计算每次循环某一位的数字
            count[k]++;    //统计每个桶中的记录数
        }
        for(j=1; j<10; j++)
            count[j] = count[j-1] + count[j];   //第j个桶以及之前所有桶中元素的总数
        for(j = n - 1; j >= 0; j--) 
		{    //将所有桶中记录依次收集到tmp中
            k = (data[j] / radix) % 10;
            tmp[count[k]-1] = data[j];
            count[k]--;
        }
        for(j=0; j<n; j++)   //将临时数组的内容复制到data中
            data[j]=tmp[j];
        radix*=10;
    }
}


int main()
{
	srand((unsigned)time(NULL));
	cout<<"请输入数组大小:"<<endl;
	int n;
	cin>>n;
	cout<<"随机产生数组:"<<endl; 
	int R[n];
	int i=0;
	while(i<n)
		cout<<(R[i++]=rand()%1000)<<" ";
	cout<<endl;
	radixsort(R,n);
	cout<<"排序结果为:"<<endl;
	for(i=0;i<n;i++)
		cout<<R[i]<<" ";
	cout<<endl;
}



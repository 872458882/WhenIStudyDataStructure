#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <sys/timeb.h>

#define MOD 256
#define N 4 

void Copy(unsigned char A[N][N],unsigned char B[N][N])  //N*N 矩阵复制A=B
{
	for(unsigned i=0;i<N;i++)
    {
        for(unsigned j=0;j<N;j++)
        {
           A[i][j]= B[i][j];
        }
    }
}


void Output(unsigned char m[N][N]) // 输出N*N矩阵m
{
    for(unsigned i=0;i<N;i++)
    {
        for(unsigned j=0;j<N;j++)
        {
            printf("% -5u ",m[i][j]);
        }
        putchar('\n');
    }
    putchar('\n');
}


void tobinary(int e,int&n,unsigned char k[])
{ 
	n=0;
	while(e!=0)
	{
	
		k[n]=e%2;
		e=e/2;
		n++;
	} 
}

void Multiply(unsigned char a[N][N],unsigned char b[N][N],unsigned char v[N][N])  // N*N 矩阵相乘，v <- a*b
{
	unsigned char V[N][N]; 
    for(unsigned i=0;i<N;i++)
    {
        for(unsigned j=0;j<N;j++)
        {
            for(unsigned k=V[i][j]=0;k<N;k++)
            {
                V[i][j] = (V[i][j]+a[i][k]*b[k][j])%MOD;
            }
        }
    }
    Copy(v,V); 
}


void SetE(unsigned char A[N][N]) //A=E 
{ 
	for(int i=0;i<N;i++)
	{
		for(int j=0;j<N;j++)
		{
			if(i==j) A[i][j]=1;
			else A[i][j]=0;
		}
	}
}


void GetMat(unsigned char M[N][N])           //随机生成N*N矩阵并输出
{
    printf("\n随机寻找 Ｚ%u 上的 %u*%u 矩阵 M.\n",MOD,N,N);

    for(unsigned char i=0;i<N;i++)
        for(unsigned char j=0;j<N;j++)
            M[i][j] = rand()%MOD;
	Output(M);
}


void QuickPow(int e,unsigned char A[N][N],unsigned char v[N][N])//快速乘幂 
{
	printf("\n矩阵M 在Z%d的%d次幂：\n",MOD,e);
	unsigned char k[2000];
	int n=0;
	tobinary(e,n,k);
	//for(int i=0;i<n;i++) printf("\nk%d = %d    \n",i ,k[i]);
	unsigned char V[N][N];
	
	if(k[0]==1) 
		Copy(V,A);
	else SetE(V);
	
	unsigned char T[N][N];
	Copy(T,A);//T=V
	//printf("n=%d",n);
	for(int i=1;i<n;i++)
	{
		Multiply(T,T,T);//T=T*T
		if(k[i]==1) 
		{
			Multiply(V,T,V);
		}
	}
	Copy(v,V);
} 
 
int main(){
	srand((unsigned)time(NULL));
	unsigned char A[N][N];
	unsigned char R[N][N];
	printf("快速乘幂：\n");
	int e=rand()%MOD;
	printf("e=%d",e);
	GetMat(A);
	QuickPow(e,A,R);
	Output(R);

	//QuickPow(3,A,M);
	//Multiply(A,M,R);
	//Output(R);
	
}

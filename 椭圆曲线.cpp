//作业：计算P的周期     P=(3,10)∈E23(1,1)
#include <stdio.h>
#include <cmath>
#include <malloc.h>
#define M 23

int Reverse[M];
int euclid(int a,int b);
void getR(int Re[])
{
	printf("mod%d下的逆：\n",M); 
	for(int i=0;i<M;i++)
	{
		Re[i]=euclid(M,i);	
		printf("R[%d]=%d\n",i,Re[i]);
	}
	printf("求逆完毕\n");
}

struct Node
{
	int x;
	int y;
}; 

Node*O; 
void plus(Node *P,Node *Q,Node *R)
{
	//不存在其中一个为O的情况 
	if(P->x==Q->x&&(P->y+Q->y==0))      //P=-Q
	{
		R=O;
		return;
	}
	int k;
	if(P->x==Q->x)     //P=Q
	{
		if(P->y!=Q->y) return;
		k=(3*pow(P->x,2)+1) * Reverse[2*(P->y)];
		k=k%M;	
	}
	else
	{
		k=(Q->y-P->y+M) * Reverse[(Q->x-P->x+M)%M];
		k=k%M;
	}
	
	R->x=pow(k,2)-P->x-Q->x;
	R->x=(R->x+M)%M;
	
	R->y=k*(P->x-R->x+M)-P->y;
	R->y=(R->y+M)%M;
	
}


int  euclid(int a,int b)  
//假定a>b>0.求的是b模a的乘法逆元。
{
	int x1,x2,x3;  
	int y1,y2,y3;  
	int t1,t2,t3;  
	int q;  
	x1=1;  
	x2=0;  
	x3=a;  
	y1=0;  
	y2=1;  
	y3=b;  
	while(1)  
	{     
		if(y3==0)     
		{           
		//printf("最大公因数是：%u\n",x3);        
		//printf("没有逆元\n");  
		return -1;
		}     
		if(y3==1)     
		{         
			//printf("最大公因数是：%u\n",y3);      
			while(y2<0)
			{
				y2=y2+a;
			}
			//printf("逆元是：%u\n",y2);          
			return y2;
		}     
		q=x3/y3;     
		t1=x1-q*y1;     
		t2=x2-q*y2;     
		t3=x3-q*y3;     
		x1=y1;     
		x2=y2;     
		x3=y3;     
		y1=t1;      
		y2=t2;     
		y3=t3;  
	}
}

bool Equal(Node*A,Node*B)
{
	return A->x==B->x&&A->y==B->y; 
} 

void print(Node*P)
{
	if(P->x==0&&P->y==0) {printf("O"); return;}
	printf("(%d,%d)",P->x,P->y);
}

int main()
{
	getR(Reverse);
	Node*O=(Node*)malloc(sizeof(Node*));
	O->x=0;O->y=0;
	Node*P[1000];
	P[0]=(Node*)malloc(sizeof(Node*));
	P[0]->x=3;
	P[0]->y=10;
	printf("P=");
	print(P[0]);
	printf("\n");
	int i=1; 
	while(!Equal(P[i-1],O))
	{
		P[i]=(Node*)malloc(sizeof(Node*));
		plus(P[i-1],P[0],P[i]);
		printf("%dP=",i+1);
		print(P[i]);
		printf("\n");
		i++;
	}
	printf("周期是：%d",i); 
}

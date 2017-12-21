/*
	44150804 万蔓芊 11班 
 *homework3.c
 * 假定a>b>0
 *求的是b模a的乘法逆元
 */


#include <stdio.h>
#include <stdlib.h>
#include <math.h>
void euclid(int,int); 
void main()
{  
	int a;
	int b;
	while(scanf("%d %d",&a,&b))
	{
		euclid(a,b);
	}
}

void euclid(int a,int b)  
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
		printf("最大公因数是：%u\n",x3);        
		printf("没有逆元\n");  
		break;    
		}     
		if(y3==1)     
		{         
			printf("最大公因数是：%u\n",y3);      
			while(y2<0)
			{
				y2=y2+a;
			}
			printf("逆元是：%u\n",y2);          
			break;   
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


/*
	44150804 ����ܷ 11�� 
 *homework3.c
 * �ٶ�a>b>0
 *�����bģa�ĳ˷���Ԫ
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
//�ٶ�a>b>0.�����bģa�ĳ˷���Ԫ��
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
		printf("��������ǣ�%u\n",x3);        
		printf("û����Ԫ\n");  
		break;    
		}     
		if(y3==1)     
		{         
			printf("��������ǣ�%u\n",y3);      
			while(y2<0)
			{
				y2=y2+a;
			}
			printf("��Ԫ�ǣ�%u\n",y2);          
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


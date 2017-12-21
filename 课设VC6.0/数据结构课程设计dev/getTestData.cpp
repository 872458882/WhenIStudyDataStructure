#include <fstream>
#include <iostream>
#define n 20
using namespace std;
//生成测试数据
void getTestData(int *x,int *y)
{
	ofstream fout("text.txt");
	for(int i=0;i<n;i++)
	{
		x[i]=rand()%n+1;
		y[i]=rand()%n+1; 
		printf("(%d,%d) ",x+i,y+i);
		fout<<"("<<x[i]<<","<<y[i]<<") ";
	}
}

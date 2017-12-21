#include <iostream>
#include <fstream>
#include <queue>
#include <stack>
#include <cmath>
#include <time.h>//用于生成随机数 
#include <sys/timeb.h>//用于生成随机数 
using namespace std;

class ComNet
{
	public:
		ComNet();
		ComNet(const ComNet& obj);
		~ComNet();
		
		void getTestData(int *x, int *y);
		void ConstructMul(int *x, int *y);
		void ConstructSingle(int *x,int *y);
		bool IsReliable(int *x,int *y);		
		
		bool IsExcess(int x,int y);
		
		static bool IsConnectAccord(const ComNet& before,const ComNet& after);
		
		bool Insert(int from, int to){ if(from>0 && to>0 && from<=iCityNum && to<=iCityNum){Line[from-1][to-1]=Line[to-1][from-1]=1;return 1;}else return 0;} 
		
		bool Delete(int from, int to){ if(from>0 && to>0 && from<=iCityNum && to<=iCityNum){Line[from-1][to-1]=Line[to-1][from-1]=0;return 1;}else return 0;}
		
		//重载赋值运算符 
		ComNet* operator=(const ComNet& obj);
		 
		int getCityNum(){return iCityNum;}
		int getLineNum(){return iLineNum;}
		
		void DrawInWindows();
		void Output();
	
	private:
		int iCityNum;//城市数 
		int iLineNum;//线路数	
		int **Line;
};


//构造函数
ComNet::ComNet()
{
	cout<<"请输入城市个数和通讯线路条数：\n";
	cin>> iCityNum >> iLineNum; 
	while(pow(2,iCityNum) - iCityNum < iLineNum)
	{
		cout<<"输入不合理, 请重新输入.\n";
		cin>>iCityNum>>iLineNum; 
	} 
	Line = new int*[iCityNum];
	for(int i=0; i<iCityNum; i++)
		Line[i] = new int[iCityNum];
	for(int i=0;i<iCityNum;i++)
		for(int j=0;j<iCityNum;j++)
			Line[i][j]=0;
} 


ComNet::ComNet(const ComNet& obj) //拷贝构造函数 
:iCityNum(obj.iCityNum),iLineNum(obj.iLineNum)
{
	Line = new int*[iCityNum];
	for(int i=0; i<iCityNum; i++)
		Line[i] = new int[iCityNum];
	for(int i=0; i<iCityNum; i++)
		for(int j=0; j<iCityNum ;j++)
			Line[i][j]=obj.Line[i][j];
}


//生成测试数据
void ComNet::getTestData(int *x, int *y)
{
	int tempx=0,tempy=0; 
	ofstream fout("text.txt");
	cout<<"\n随机生成城市间的通讯线路为：\n"; 
	for(int i=0;i<iLineNum&&fout.is_open();i++)
	{
		//随机生成一个不同的(tempx,tempy)对 
		
 		bool flag=0;
		while(!flag) //检查不合理输入 
		{
			tempx = rand()%iCityNum + 1;
			tempy = rand()%iCityNum + 1; 
			
			if(tempx == tempy) //检查是否tempX=tempY
				continue; 
				
			int j;
			for(j=0;j<i;j++) //检查是否和已经生成的重复 
				if(tempx==x[j] && tempy==y[j])
					break;
					
			if(j==i) {flag=1;}//正常退出循环则没有重复 
		
		}
	
		x[i]=tempx;
		y[i]=tempy;
			
		cout<<"("<<x[i]<<","<<y[i]<<") ";
		fout<<"("<<x[i]<<","<<y[i]<<") "<<endl; 
	}
	
	cout<<endl;
	fout<<endl;
	
	fout.close();
}


void ComNet::ConstructMul(int *x, int *y)//生成复杂网络 
{
	for(int i=0;i<iLineNum;i++)
	{
		Insert(x[i],y[i]); 
		cout<<"x"<<x[i]<<"y"<<y[i]<<endl;
	}
}


void ComNet::ConstructSingle(int *x,int *y)//生成简单网络 
{
	for(int i=0;i<iLineNum;i++)
	{
		if(IsExcess(x[i],y[i]))
			cout<<"("<<x[i]<<","<<y[i]<<")"
			<< "是冗余线路，故不添加入线路网\n";
	
		else
		{
			cout<<"("<<x[i]<<","<<y[i]<<")"
			<<"不是冗余线路，加入线路网\n"; 	
			Insert(x[i],y[i]); 
		}
	}
} 


bool ComNet::IsReliable(int *x,int *y)//可靠性检查并输出不可靠线路
{
	ComNet tempobj(*this);
	for(int i=0;i<iLineNum;i++)
	{
		ComNet tempobj(*this);
		tempobj.Delete(x[i],y[i]);
		if(!IsConnectAccord(*this,tempobj))
		{
			cout<<"("<<x[i]<<","<<y[i]<<")"<<"不可靠\n";
		}
	}
	
	//分配交换机？？？？？？？？？？？？？？？？？？？？？？？？？？？？？？？？？？？？？？？？？？？？？/
	///////////////WTF？？？？？？？？？？？？？？？？？？
	//交换机???????????????
	 //
}


bool ComNet::IsExcess(int x,int y)               //检查是否冗余 
{
	bool Connect[iCityNum][iCityNum];
	for(int i=0;i<iCityNum;i++)
	{
		for(int j=0;j<iCityNum;j++)
		{
			Connect[i][j]=Line[i][j]?1:0;
		}
		cout<<endl;
	}		
	for(int k=0; k<iCityNum; k++) 
		for(int i=0; i<iCityNum; i++)
			if(k!=i)
			{
				for(int j=iCityNum-1; j>i; j--)
					if(j!=k && j!=i && Connect[i][k] && Connect[k][j]) 
						Line[i][j]=Line[j][i]=1;
			}

	if(Connect[x][y]) return 1;
	return 0;
}


bool ComNet::IsConnectAccord(const ComNet& before,const ComNet& after)      //检测是否可及性一致 
{
	if(before.iCityNum!=after.iCityNum) cout<<"对象错误"<<endl;
	bool Connectb[before.iCityNum][before.iCityNum];
	bool Connecta[after.iCityNum][after.iCityNum];
	for(int i=0;i<before.iCityNum;i++)
	{
		for(int j=0;j<before.iCityNum;j++)
		{
			Connectb[i][j]=before.Line[i][j]?1:0;
			Connecta[i][j]=after.Line[i][j]?1:0;
		}
		cout<<endl;
	}
		
	for(int k=0; k<before.iCityNum; k++) 
		for(int i=0; i<before.iCityNum; i++)
			if(k!=i)
			{
				for(int j=before.iCityNum-1; j>i; j--)
					if(j!=k && j!=i && Connecta[i][k] && Connecta[k][j]) 
						Connecta[i][j]=Connecta[j][i]=1;
			}
	
	for(int k=0; k<before.iCityNum; k++) 
		for(int i=0; i<before.iCityNum; i++)
			if(k!=i)
			{
				for(int j=before.iCityNum-1; j>i; j--)
					if(j!=k && j!=i && Connectb[i][k] && Connectb[k][j]) 
						Connectb[i][j]=Connectb[j][i]=1;
			}
			
	for(int i=0;i<before.iCityNum;i++)
		for(int j=0;j<before.iCityNum;j++)
			if(Connectb[i][j]&&!Connectb[i][j])//在原来可及性矩阵中可及,但删掉边后不可及了，则为不可靠的 
				return 0;

	return 1; 
}

void ComNet::Output()
{
	for(int i=0;i<iCityNum;i++)
	{
		for(int j=0;j<iCityNum;j++)
			cout<<Line[i][j]<<" ";
			//if(Line[i][j]) cout<<" ";
			//else cout<<"*"; 
	}
}


void ComNet::DrawInWindows()
{
	//生成每个点的左边 
	//4个区域[0,200][200,400] 
	int pos[2] ={0,200}; 
	int posx[iCityNum];
	int posy[iCityNum];
	for(int i=0;i<iCityNum;i++)
	{
		int part = i%4; 
		posx[i] = rand()%200 +pos[i%2];
		posy[i] = rand()%200 +pos[i/2];
	}
	//连线============================================================================ 
}


ComNet* ComNet::operator=(const ComNet& obj)
{
	iCityNum = obj.iCityNum;
	iLineNum = obj.iLineNum;
	Line = new int*[iCityNum];
	for(int i=0; i<iCityNum; i++)
		Line[i] = new int[iCityNum];
	for(int i=0; i<iCityNum; i++)
		for(int j=0; j<iCityNum ;j++)
			Line[i][j]=obj.Line[i][j];
	return this;
} 


ComNet::~ComNet()         //析构函数 
{
	for(int i=0;i<iCityNum;i++)
		delete []Line[i];
	delete [] Line;
}


int main() {
	srand((unsigned)time(NULL));
	ComNet A;
	int x[A.getLineNum()]={0};
	int y[A.getLineNum()]={0};
	A.getTestData(x,y);
	A.ConstructSingle(x,y);
	
	return 0;
}

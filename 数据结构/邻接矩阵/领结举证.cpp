#include <iostream>
#include <memory.h>
using namespace std;

const int MaxWeight=1000;

class Graph_Matrix
{
private:
	int MaxGraphSize; 
	int **Edge;
	int GraphSize;//顶点数		 
	int e;//边数 
	int alllengthflag; 
	int**path; 
	int**A;
public:
	Graph_Matrix(int Max);
	Graph_Matrix(const Graph_Matrix&A);
	void Create();
	virtual~Graph_Matrix(); 
	
	
	int IsEmpty() const{return !GraphSize;};
	int GraphFull()const{return GraphSize==MaxGraphSize;}
	int NumberOfVertices()const{return GraphSize;}
	int NumberOfEdges()const;//返回图的边的个数
	int	GetWeight(const int &v1,const int&v2);//返回指定边的权值 
	void GetNeighbors(const int &v,int A[]);//返回顶点v的邻接顶点表 
	
	//void InsertVertex(const int &v);//向图中插入一个顶点 
	bool InsertEdge(const int &v1,const int &v2,int weight);//向图中插入一条边 
	bool SetEdge(const int &v1,const int &v2,int weight);
	
	bool DeleteVertex(const int &v);//在图中删除一个顶点 
	bool DeleteEdge(const int &v1,const int &v2);//在图中删除一条边
	
	int GetDiameter(); 
							//void DepthFirstSearch();//采用递归的方法从顶点表的第一个顶点开始进行图的深度优先搜索 
							//void DFS(const int v);//从顶点V开始进行图的深度优先搜索  
							//void BFS(const int v);//从顶点V开始进行图的广度优先搜索
							
	bool TopoOrder();//检测是否有环，如果无环输出图的拓扑序列 
	
	                    //void CriticalPath();//输出图的关键路径
	
	                    //void ShortestPath(const int v);//在非权图中求指定顶点到其他所有顶点的最短路径 
                      	//void DShortestPath(const int v);//在正权图中求指定定点到其他所有定点的最短路径
	
	void AllLength();//在正权图中求每对顶点间的最短路径
	
	bool IsFreeTree(); //检测是否为自由树 
	
	

                     	//void Prim();//构造图的最小支撑树的普里姆算法 
	                    //void Output();//用来测试 
};

Graph_Matrix::Graph_Matrix(int Max=100):MaxGraphSize(Max),alllengthflag(0)
{
	cout<<"开始"<<endl;
	Edge=new int*[Max];
	for(int i=0;i<Max;i++)
		Edge[i]=new int[Max];
	for(int i=0;i<Max;i++)
		for(int j=0;j<Max;j++)
			Edge[i][j]=MaxWeight;
	Create();
}


void Graph_Matrix::Create()
{
	int from,to,weight;
	int E;
	int i=0; 
	cout<<"请输入顶点和边的个数"<<endl;
	cin>>GraphSize>>E;
	while(i<E)
	{
		cout<<"请输入第"<<++i<<"条边的始点 终点 权"<<endl;
		cin>>from>>to>>weight;
		InsertEdge(from,to,weight); 
	}
	cout<<"创建成功！"<<endl;
}


Graph_Matrix::Graph_Matrix(const Graph_Matrix&A)
{
	e=A.e;
	GraphSize=A.GraphSize;
	MaxGraphSize=A.MaxGraphSize;
	Edge=new int*[MaxGraphSize];
	for(int i=0;i<MaxGraphSize;i++)
		Edge[i]=new int[MaxGraphSize];
	for(int i=0;i<MaxGraphSize;i++)
		for(int j=0;j<MaxGraphSize;j++)
			Edge[i][j]=A.Edge[i][j];

}


bool Graph_Matrix::IsFreeTree()
{
	Graph_Matrix A(*this);//建立自己的副本 
	//计算每个结点的入度 
	int count[A.GraphSize];
	memset(count,0,sizeof(count));
	for(int j=0;j<A.GraphSize;j++)//列 
	{
		for(int i=0;i<A.GraphSize;i++) //行 
		{
			if(A.Edge[i][j]!=MaxWeight) count[j]++;	
		}
		cout<<"count["<<j<<"]="<<count[j]<<endl;	
	} 
	
	int temp=0; //计算度为0的点的个数
	 
	int top=-1;//初始化栈顶指针
	for(int i=0;i<A.GraphSize;i++)
	{
		if(count[i]==0)//将入度为0的点入栈 
		{
			count[i]=top;
			top=i;
			temp++; 
		}
	} 
	
	if(temp!=1) return 0;/*如果有多个度为0的点，则不可能为自由树*/ 
	
	
	for(int i=0;i<A.GraphSize;i++)
	{
		//cout<<"top="<<top<<endl; 
		
		/*循环群体还未被执行GraphSize次，已经没有入度为0的点，说明有回路*/ 
		if(top==-1)
		{
			//cout<<"有回路"<<endl;
			return 0; 
		}
		else
		{
			int j=top;top=count[top];/*从栈中弹出一个顶点 j*/ 
			cout<<j<<" ";
			
			/*删除与j相关的边并更新count*/ 
			for(int p=0;p<A.GraphSize;p++)
			{
				if(A.Edge[j][p]!=MaxWeight) 
				{
					A.Edge[j][p]=MaxWeight;
					count[p]--; 
					A.e--;
				}
			}
			//for(int p=0;p<A.GraphSize;p++)
			//	cout<<"count["<<p<<"]="<<count[p]<<endl;	
			
			for(int p=0;p<A.GraphSize;p++)
			{
				if(count[p]==0)/*将入度为0的点入栈*/ 
				{
					count[p]=top;
					top=p;
				}
			} 
		
		}
	}
	return 1; 
}


void Graph_Matrix::AllLength()       //在正权图中求每对顶点间的最短路径
{
	alllengthflag=1;                    //方便析构函数处理，如调用此函数才析构相关数组 
	
	/*初始化*/ 
	int n=GraphSize;
	path=new int*[n]; //path记录最短路径终点前一个结点 
	A=new int*[n];    //A记录最短路径 
	for(int i=0;i<n;i++)
	{
		path[i]=new int[n];
		A[i]=new int[n]; 
	} 
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<n;j++)
		{
			A[i][j]=Edge[i][j];
			if(i!=j&&A[i][j]<MaxWeight)
			{
				path[i][j]=i;
			}
			else
			{
				path[i][j]=-1;
			}
		}
	}
	
	
	for(int k=0;k<n;k++)//加入k作为中间结点 
	{
		for(int i=0;i<n;i++)
		{
			if(i!=k)
			{
				for(int j=0;j<n;j++)
				{
					if(j!=k/*以k作为终点*/&&j!=i/*到自己*/&&A[i][j]!=MaxWeight&&A[i][k]+A[k][j]<A[i][j])
					{
						//更新 
						A[i][j]=A[i][k]+A[k][j];
						path[i][j]=path[k][j];
					}
				}
			}
		}
	}
	
	cout<<"最短路径最后经过的点为："<<endl; 
	printf("      ");
	for(int j=0;j<n;j++)
		printf("% 5d ",j);
	cout<<endl;
	for(int i=0;i<n;i++)
	{
		printf("% 5d ",i);
		for(int j=0;j<n;j++)
		{
			printf("% 5d ",path[i][j]);
		}
		cout<<endl;
	}
	cout<<"每对顶点最短路径长度为："<<endl; 
	printf("      ");
	for(int j=0;j<n;j++)
		printf("% 5d ",j);
	printf("\n");
	for(int i=0;i<n;i++)
	{
		printf("% 5d ",i);
		for(int j=0;j<n;j++)
		{
			printf("% 5d ",A[i][j]);
		}
		cout<<endl;
	}
} 


int Graph_Matrix::GetDiameter()
{
	if(IsFreeTree()==0) 
	{
		cout<<"不是有向树"<<endl; 
		return -1;
	}
	
	AllLength();
	
	int d=0;
	for(int i=0;i<GraphSize;i++)
	{
		for(int j=0;j<GraphSize;j++)
		{
			if(A[i][j]>d&&A[i][j]!=MaxWeight) d=A[i][j];
		}
	} 
	cout<<"直径是"<<d<<endl;
	return d;
} 

int	Graph_Matrix::GetWeight(const int &v1,const int&v2){
	if(v1==-1||v2==-1||v1>=GraphSize||v2>=GraphSize) return 0;
	
	return Edge[v1][v2];
}

bool Graph_Matrix::DeleteEdge(const int&v1,const int &v2)//删除指定边 
{
	if(v1==-1||v2==-1||v1>=GraphSize||v2>=GraphSize) return 0;
	if(Edge[v1][v2]==MaxWeight) return 0;
	Edge[v1][v2]==MaxWeight;
	e--;
	return 1;
}

bool Graph_Matrix::InsertEdge(const int &v1,const int &v2,int weight)//向图中插入一条边 	
{	 
	if(v1==-1||v2==-1||v1>=GraphSize||v2>=GraphSize) return 0;
	if(v1==v2) return 0;
	if(Edge[v1][v2]!=MaxWeight) return 0;
	Edge[v1][v2]=weight;
	e++;
	return 1;
}

bool Graph_Matrix::SetEdge(const int &v1,const int &v2,int weight)//修改指定边的权值 
{
	if(v1==v2) return 0;	
	if(v1==-1||v2==-1||v1>=GraphSize||v2>=GraphSize) return 0;
	if( InsertEdge(v1,v1,weight)==0)    //插入不成功则该边已存在 
		Edge[v1][v2]=weight;
	return 1;
}

bool Graph_Matrix::DeleteVertex(const int &v)//删除顶点 
{
	if(v==-1||v>=GraphSize) return 0;
	for(int i=0;i<GraphSize;i++)
	{
		if(Edge[i][v]!=MaxGraphSize) 
		{
			Edge[i][v]=MaxGraphSize;
			e--;
		}
	} 
	
	for(int i=0;i<GraphSize;i++)
	{
		if(Edge[v][i]!=MaxGraphSize) 
		{
			Edge[v][i]=MaxGraphSize;
			e--;
		}
	}
	
}





/* 
void Graph_Matrix::Output()
{
	for(int i=0;i<GraphSize;i++)
	{
		for(int j=0;j<GraphSize ;j++)
		{
			printf("% 5d ",Edge[i][j]);
		}
		cout<<endl;
	}
	
}//测试函数 
*/ 

bool Graph_Matrix::TopoOrder()
{	Graph_Matrix A(*this);//建立自己的副本 
	//计算每个结点的入度 
	int count[A.GraphSize];
	memset(count,0,sizeof(count));
	for(int j=0;j<A.GraphSize;j++)//列 
	{
		for(int i=0;i<A.GraphSize;i++) //行 
		{
			if(A.Edge[i][j]!=MaxWeight) count[j]++;	
		}
		//cout<<"count["<<j<<"]="<<count[j]<<endl;	
	} 
	 
	int top=-1;//初始化栈顶指针
	for(int i=0;i<A.GraphSize;i++)
	{
		if(count[i]==0)//将入度为0的点入栈 
		{
			count[i]=top;
			top=i;
		}
	} 
	
	cout<<"拓扑序列为：";
	
	
	for(int i=0;i<A.GraphSize;i++)
	{
		//cout<<"top="<<top<<endl; 
		//循环群体还未被执行GraphSize次，已经没有入度为0的点，说明有回路 
		if(top==-1)
		{
			cout<<"有回路"<<endl;
			return 0; 
		}
		else
		{
			int j=top;top=count[top];//从栈中弹出一个顶点 j
			cout<<j<<" ";
			//删除与j相关的边并更新count 
			
			for(int p=0;p<A.GraphSize;p++)
			{
				if(A.Edge[j][p]!=MaxWeight) 
				{
					A.Edge[j][p]=MaxWeight;
					count[p]--; 
					A.e--;
				}
			}
			//for(int p=0;p<A.GraphSize;p++)
			//	cout<<"count["<<p<<"]="<<count[p]<<endl;	
			
			for(int p=0;p<A.GraphSize;p++)
			{
				if(count[p]==0)//将入度为0的点入栈 
				{
					count[p]=top;
					top=p;
				}
			} 
		
		}
	}
} 
Graph_Matrix::~Graph_Matrix()
{
	for(int i=0;i<GraphSize;i++)
		delete[]Edge[i];
	delete[]Edge;
	
	if(alllengthflag==1)
	{
		for(int i=0;i<GraphSize;i++)
			delete[]A[i];
		delete[]A;
		for(int i=0;i<GraphSize;i++)
			delete[]path[i];
		delete[]path;
	}
}

int main() {
	Graph_Matrix A(100);
	//A.Output();
	
	//A.TopoOrder(); 
	A.GetDiameter();
	return 0;
}

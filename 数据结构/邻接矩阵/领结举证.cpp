#include <iostream>
#include <memory.h>
using namespace std;

const int MaxWeight=1000;

class Graph_Matrix
{
private:
	int MaxGraphSize; 
	int **Edge;
	int GraphSize;//������		 
	int e;//���� 
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
	int NumberOfEdges()const;//����ͼ�ıߵĸ���
	int	GetWeight(const int &v1,const int&v2);//����ָ���ߵ�Ȩֵ 
	void GetNeighbors(const int &v,int A[]);//���ض���v���ڽӶ���� 
	
	//void InsertVertex(const int &v);//��ͼ�в���һ������ 
	bool InsertEdge(const int &v1,const int &v2,int weight);//��ͼ�в���һ���� 
	bool SetEdge(const int &v1,const int &v2,int weight);
	
	bool DeleteVertex(const int &v);//��ͼ��ɾ��һ������ 
	bool DeleteEdge(const int &v1,const int &v2);//��ͼ��ɾ��һ����
	
	int GetDiameter(); 
							//void DepthFirstSearch();//���õݹ�ķ����Ӷ����ĵ�һ�����㿪ʼ����ͼ������������� 
							//void DFS(const int v);//�Ӷ���V��ʼ����ͼ�������������  
							//void BFS(const int v);//�Ӷ���V��ʼ����ͼ�Ĺ����������
							
	bool TopoOrder();//����Ƿ��л�������޻����ͼ���������� 
	
	                    //void CriticalPath();//���ͼ�Ĺؼ�·��
	
	                    //void ShortestPath(const int v);//�ڷ�Ȩͼ����ָ�����㵽�������ж�������·�� 
                      	//void DShortestPath(const int v);//����Ȩͼ����ָ�����㵽�������ж�������·��
	
	void AllLength();//����Ȩͼ����ÿ�Զ��������·��
	
	bool IsFreeTree(); //����Ƿ�Ϊ������ 
	
	

                     	//void Prim();//����ͼ����С֧����������ķ�㷨 
	                    //void Output();//�������� 
};

Graph_Matrix::Graph_Matrix(int Max=100):MaxGraphSize(Max),alllengthflag(0)
{
	cout<<"��ʼ"<<endl;
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
	cout<<"�����붥��ͱߵĸ���"<<endl;
	cin>>GraphSize>>E;
	while(i<E)
	{
		cout<<"�������"<<++i<<"���ߵ�ʼ�� �յ� Ȩ"<<endl;
		cin>>from>>to>>weight;
		InsertEdge(from,to,weight); 
	}
	cout<<"�����ɹ���"<<endl;
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
	Graph_Matrix A(*this);//�����Լ��ĸ��� 
	//����ÿ��������� 
	int count[A.GraphSize];
	memset(count,0,sizeof(count));
	for(int j=0;j<A.GraphSize;j++)//�� 
	{
		for(int i=0;i<A.GraphSize;i++) //�� 
		{
			if(A.Edge[i][j]!=MaxWeight) count[j]++;	
		}
		cout<<"count["<<j<<"]="<<count[j]<<endl;	
	} 
	
	int temp=0; //�����Ϊ0�ĵ�ĸ���
	 
	int top=-1;//��ʼ��ջ��ָ��
	for(int i=0;i<A.GraphSize;i++)
	{
		if(count[i]==0)//�����Ϊ0�ĵ���ջ 
		{
			count[i]=top;
			top=i;
			temp++; 
		}
	} 
	
	if(temp!=1) return 0;/*����ж����Ϊ0�ĵ㣬�򲻿���Ϊ������*/ 
	
	
	for(int i=0;i<A.GraphSize;i++)
	{
		//cout<<"top="<<top<<endl; 
		
		/*ѭ��Ⱥ�廹δ��ִ��GraphSize�Σ��Ѿ�û�����Ϊ0�ĵ㣬˵���л�·*/ 
		if(top==-1)
		{
			//cout<<"�л�·"<<endl;
			return 0; 
		}
		else
		{
			int j=top;top=count[top];/*��ջ�е���һ������ j*/ 
			cout<<j<<" ";
			
			/*ɾ����j��صı߲�����count*/ 
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
				if(count[p]==0)/*�����Ϊ0�ĵ���ջ*/ 
				{
					count[p]=top;
					top=p;
				}
			} 
		
		}
	}
	return 1; 
}


void Graph_Matrix::AllLength()       //����Ȩͼ����ÿ�Զ��������·��
{
	alllengthflag=1;                    //��������������������ô˺���������������� 
	
	/*��ʼ��*/ 
	int n=GraphSize;
	path=new int*[n]; //path��¼���·���յ�ǰһ����� 
	A=new int*[n];    //A��¼���·�� 
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
	
	
	for(int k=0;k<n;k++)//����k��Ϊ�м��� 
	{
		for(int i=0;i<n;i++)
		{
			if(i!=k)
			{
				for(int j=0;j<n;j++)
				{
					if(j!=k/*��k��Ϊ�յ�*/&&j!=i/*���Լ�*/&&A[i][j]!=MaxWeight&&A[i][k]+A[k][j]<A[i][j])
					{
						//���� 
						A[i][j]=A[i][k]+A[k][j];
						path[i][j]=path[k][j];
					}
				}
			}
		}
	}
	
	cout<<"���·����󾭹��ĵ�Ϊ��"<<endl; 
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
	cout<<"ÿ�Զ������·������Ϊ��"<<endl; 
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
		cout<<"����������"<<endl; 
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
	cout<<"ֱ����"<<d<<endl;
	return d;
} 

int	Graph_Matrix::GetWeight(const int &v1,const int&v2){
	if(v1==-1||v2==-1||v1>=GraphSize||v2>=GraphSize) return 0;
	
	return Edge[v1][v2];
}

bool Graph_Matrix::DeleteEdge(const int&v1,const int &v2)//ɾ��ָ���� 
{
	if(v1==-1||v2==-1||v1>=GraphSize||v2>=GraphSize) return 0;
	if(Edge[v1][v2]==MaxWeight) return 0;
	Edge[v1][v2]==MaxWeight;
	e--;
	return 1;
}

bool Graph_Matrix::InsertEdge(const int &v1,const int &v2,int weight)//��ͼ�в���һ���� 	
{	 
	if(v1==-1||v2==-1||v1>=GraphSize||v2>=GraphSize) return 0;
	if(v1==v2) return 0;
	if(Edge[v1][v2]!=MaxWeight) return 0;
	Edge[v1][v2]=weight;
	e++;
	return 1;
}

bool Graph_Matrix::SetEdge(const int &v1,const int &v2,int weight)//�޸�ָ���ߵ�Ȩֵ 
{
	if(v1==v2) return 0;	
	if(v1==-1||v2==-1||v1>=GraphSize||v2>=GraphSize) return 0;
	if( InsertEdge(v1,v1,weight)==0)    //���벻�ɹ���ñ��Ѵ��� 
		Edge[v1][v2]=weight;
	return 1;
}

bool Graph_Matrix::DeleteVertex(const int &v)//ɾ������ 
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
	
}//���Ժ��� 
*/ 

bool Graph_Matrix::TopoOrder()
{	Graph_Matrix A(*this);//�����Լ��ĸ��� 
	//����ÿ��������� 
	int count[A.GraphSize];
	memset(count,0,sizeof(count));
	for(int j=0;j<A.GraphSize;j++)//�� 
	{
		for(int i=0;i<A.GraphSize;i++) //�� 
		{
			if(A.Edge[i][j]!=MaxWeight) count[j]++;	
		}
		//cout<<"count["<<j<<"]="<<count[j]<<endl;	
	} 
	 
	int top=-1;//��ʼ��ջ��ָ��
	for(int i=0;i<A.GraphSize;i++)
	{
		if(count[i]==0)//�����Ϊ0�ĵ���ջ 
		{
			count[i]=top;
			top=i;
		}
	} 
	
	cout<<"��������Ϊ��";
	
	
	for(int i=0;i<A.GraphSize;i++)
	{
		//cout<<"top="<<top<<endl; 
		//ѭ��Ⱥ�廹δ��ִ��GraphSize�Σ��Ѿ�û�����Ϊ0�ĵ㣬˵���л�· 
		if(top==-1)
		{
			cout<<"�л�·"<<endl;
			return 0; 
		}
		else
		{
			int j=top;top=count[top];//��ջ�е���һ������ j
			cout<<j<<" ";
			//ɾ����j��صı߲�����count 
			
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
				if(count[p]==0)//�����Ϊ0�ĵ���ջ 
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

#include <iostream>
#include <memory.h>
#include <stack>
#include <queue>
using namespace std;


class GraphList; 


//边结点的结构体 
struct Edge
{
	friend class GraphList;
	int VerAdj; //邻接顶点序号，从0开始编号 
	int cost; //边的权值 
	Edge*Link; //指向下一边节点的指针
	Edge(int aVerAdj,int acost,Edge*aLink=NULL){ VerAdj=aVerAdj;cost=acost;Link=aLink;} 
	Edge(Edge*aLink=NULL){Link=aLink;} 
}; 

//顶点表中结点的结构体 
struct Vertex 
{
	friend class GraphList;
	int VerName;//顶点名称
	Edge*Adjacent;//边链表的头指针  
	Vertex(int name,Edge*adjacent=NULL){VerName=name;Adjacent=adjacent;}
	Vertex(Edge*adjacent=NULL){Adjacent=adjacent;}
};
 
 //采用邻接表储存的Graph_List类定义 其中所有边均为正权 
class GraphList
{
private:
	Vertex*Head; //顶点表头指针 
	int GraphSize;		 //图中当前顶点的个数 
	int MaxGraphSize;   //图中最大顶点个数
	int e;           //图中当前边的个数 
public:
	GraphList(int MaxGraphSize); 
	virtual ~GraphList();
	
	int IsEmpty() const{return !GraphSize;}       //判断图是否为空 
	int IsFull()const{return GraphSize==MaxGraphSize;} //判断顶点数是否已满 
	
	int NumberOfVertices()const{return GraphSize;}//返回图中顶点的个数 
	int NumberOfEdges()const{return e;}				//返回图中边的个数
	
	int	GetWeight(const int v1,const int v2)const;//返回指定边的权值 
	
	int GetFirstNeighbor(const int v)const;//返回序号为v的第一个邻接顶点的序号
	int GetNextNeighbor(const int v1,const int v2)const;//返回序号为v1的顶点相对于序号为v2的点的下一个邻接顶点的序号
	
	int GetNeighbors(const int v,int A[])const;//得到顶点v的邻接顶点表 返回邻接顶点个数 
	
					//	bool InsertVertex(const int v);//向图中插入一个顶点 
	bool InsertEdge(const int v1,const int v2,int weight);//向图中插入一条边 
	
					//	bool DeleteVertex(const int v);//在图中删除一个顶点 
	bool DeleteEdge(const int v1,const int v2);//在图中删除一条边
	
	
	void DepthFirstSearch();//从顶点表的第一个顶点开始进行图的深度优先搜索 
	void DFS(const int v,int visited[]);//从顶点V开始进行图的深度优先搜索
	void NDFS(const int v);//从顶点V开始进行图的深度优先搜索的迭代算法  
	void BFS(const int v);//从顶点V开始进行图的广度优先搜索
	
	void Output();//输出邻接表 
	
	void TopoOrder();//输出图的拓扑排序 
	void CriticalPath();//输出图的关键路径
	void Dijkstra(const int v);//在正权图中求指定定点到其他所有定点的最短路径
	//void ShortestPath(const int v);//在非权图中求指定顶点到其他所有顶点的最短路径 
								//void AllLength();//在正权图中求每对顶点间的最短路径
								//void Prim();//构造图的最小支撑树的普里姆算法 
								//void Krustral();
};


//=============================================================================
//构造函数 
GraphList::GraphList(int maxgraphsize):MaxGraphSize(maxgraphsize)
{
	int from,to,weight;
	//用数组实现顶点表，Head指向数组的第一个元素
	Head=new Vertex[MaxGraphSize];
	
	cout<<"请输入顶点数和边数"<<endl;
	cin>>GraphSize;
	cin>>e;
	
	//初始化：
	//顶点名字从0 -> GraphSize-1 
	for(int i=0;i<GraphSize;i++)
	{
		Head[i].VerName=i;
		Head[i].Adjacent=NULL;	
	}  
	//空结点初始化 
	for(int i=GraphSize;i<MaxGraphSize;i++)
	{
		Head[i].VerName=-1;
		Head[i].Adjacent=NULL;
	}

	for(int i=0;i<e;i++)
	{
		cout<<"输入始点，终点和权值：（这是第"<<i+1<<"条边) 空格隔开"<<endl; 
		cin>>from>>to>>weight;//输入新边的始点终点和权值 
		
		Edge*p=new Edge(to,weight,NULL);
		Edge*q=Head[from].Adjacent;
		 
		if(q==NULL){        
			Head[from].Adjacent=p;  //如果是第一条边 
		}else {
			while(q->Link!=NULL)    //如果不是第一条边，插到边结点最后 
			{
				q=q->Link;
			}
			q->Link=p;
		}
	} 
	cout<<"创建成功！"<<endl; 
}


//析构函数 
GraphList::~GraphList()
{
	for(int i=0;i<MaxGraphSize;i++)
	{
		Edge*p=Head[i].Adjacent;
		while(p!=NULL)
		{
			Edge*q=p->Link;
			delete p;
			p=q;
		}
	}
	delete []Head; 
}



int GraphList::GetWeight(const int v1,const int v2)const //返回v1->v2的边的权 
{
	//如果其中一个顶点不存在 
	if(v1==-1||v2==-1) return 0;
	
	
	Edge*p=Head[v1].Adjacent;
	while(p!=NULL)
	{
		if(p->VerAdj==v2)
			return p->cost;
		p=p->Link;
	}
	return 0;
}



int GraphList::GetFirstNeighbor(const int v)const //返回第一个邻接点 若找不到则返回-1 
{
	if(v==-1||v>=GraphSize) return -1;	
	
	Edge*p=Head[v].Adjacent;
	if(p!=NULL)
	    return p->VerAdj;
	else return -1;
}



int GraphList::GetNextNeighbor(const int v1,const int v2)const //返回v1除了v2以外的下一个邻接点 
{
	if(v1==-1||v1>=GraphSize||v2==-1||v2>=GraphSize) 
	{
		//cout<<"找不到"<<endl;
		return -1;
	}
	Edge*p=Head[v1].Adjacent;
	while(p!=NULL&&p->VerAdj!=v2)//找到v2 
		p=p->Link;
	
	if(p==NULL||p->Link==NULL)
	{
		//cout<<"找不到"<<endl;
		return -1;
	}
	p=p->Link;
	return p->VerAdj;
}

 
int GraphList::GetNeighbors(const int v,int A[])const  //得到顶点v的邻接顶点表 返回v的邻接顶点个数 
{
	if(v==-1||v>=GraphSize) return 0; 
	
	memset(A,0,sizeof(A));//初始化
	
	int i=0;
	Edge*p=Head[v].Adjacent;
	while(p!=NULL)
	{
		A[i++]=p->VerAdj;
		p=p->Link;
	}
	return i; 
}

/*
bool GraphList::InsertVertex(const int v)//插入一个顶点 
{
	if(v<MaxGraphSize&&v>=0)
	{
		if(Head[v].VerName==-1)
		{
			Head[v].VerName=v;
			GraphSize++;
			return 1; 
		}
		cout<<"顶点已存在";
		return 0; 
	}
	cout<<"越界，插入失败"<<endl;
	return 0; 
}
*/

bool GraphList::InsertEdge(const int v1,const int v2,int weight) //插入指定边 
{
	if(v1==-1||v2==-1||v1>=GraphSize||v2>=GraphSize) return 0;
	Edge*q=new Edge(v2,weight,NULL);
	Edge*p=Head[v1].Adjacent;
	
	if(p==NULL){
		Head[v1].Adjacent=q;
	}else {
		while(p->Link!=NULL&&p->VerAdj!=v2)
			p=p->Link;
		if(p->VerAdj==v2) return 0;//如果已经有这条边则插入失败 
		p->Link=q;
	}
	e++; 
	return 1;
}


bool GraphList::DeleteEdge(const int v1,const int v2)//删除指定边 
{
	if(v1==-1||v2==-1||v1>=GraphSize||v2>=GraphSize) return 0;
	Edge*p=Head[v1].Adjacent;
	Edge*q=Head[v1].Adjacent;
	if(p!=NULL)
	{
	
		if(p->VerAdj==v2) //如果V2是第一个节点 
		{
			Head[v1].Adjacent=p->Link;
			delete p;
			e--;
			return 1;
		}
		
		//如果V2不是第一个节点
		while(p!=NULL&&p->VerAdj!=v2) 
		{
			q=p;
			p=p->Link;
		}
		if(p==NULL) 
		{	
			//cout<<"无该边"<<endl; 
			return 0;
		}
		q->Link=p->Link;
		delete p;
		e--;
		return 1; 
	}
	//cout<<"无该边"<<endl; 
	return 0;
	
}

/*bool GraphList::DeleteVertex(const int v)
{
	if(v<0||v>=MaxGraphSize||Head[v].VerName==-1) return -1; 
	//删除始点为v的边 
	Edge*p=Head[v].Adjacent;
	while(p!=NULL)
	{
		Head[v].Adjacent=p->Link;
		delete p;
		e--;
		p=Head[v].Adjacent;
	}
	//删除终点为v的边 
	for(int i=0;i<GraphSize;i++)
	{
		if(i==v) continue;
		Edge*p=Head[i].Adjacent;
		Edge*q;
		while(p!=NULL)
		{
			q=p->Link;
			if(q!=NULL&&q->VerAdj==v)
			{
				p->Link=q->Link;
				delete q;
				e--;
			}
			p=p->Link;
		}
		
	}
	GraphSize--;
	Head[v]=Vertex(-1);
	return 1;
	
}
*/
 
//==============================================================

void GraphList::DepthFirstSearch()
{
	int*visited=new int[GraphSize];
	int i=0;
	while(i<GraphSize)
	{
		visited[i++]=0;
	}
	DFS(0,visited);
	delete[]visited;
}


void GraphList::DFS(int v,int visited[])
{
	cout<<v<<" ";
	visited[v]=1;
	Edge*p=Head[v].Adjacent; 
	while(p!=NULL)
	{
		if(visited[p->VerAdj]!=1)
		{
			DFS(p->VerAdj,visited);
		}
		p=p->Link;
	}
}

void GraphList::NDFS(int v)
{
	//初始化 
	if(v==-1||v>=GraphSize) return;
	int*visited=new int[GraphSize];
	int i=0;
	while(i<GraphSize) {visited[i++]=0;}
	stack<int>S;
	
	
	//访问顶点v 
	cout<<v<<" ";
	visited[v]=1; 
	S.push(v);
	
	int w;
	
	while(!S.empty())
	{
		int v=S.top();
		S.pop();
		w=GetFirstNeighbor(v);
		while(w!=-1)
		{
			if(!visited[w])
			{
				cout<<w<<" ";
				visited[w]=1;
				S.push(w);
			}
			w=GetNextNeighbor(v,w);
		}
		
	}
} 

void GraphList::BFS(const int s)
{
	//初始化 
	if(s==-1||s>=GraphSize) return;
	int*visited=new int[GraphSize];
	int i=0;
	while(i<GraphSize) {visited[i++]=0;}
	//访问顶点s 
	cout<<s<<" ";
	visited[s]=1;
	queue<int>q;
	q.push(s);
	while(!q.empty())
	{
		int v=q.front();
		q.pop();
		int w=GetFirstNeighbor(v);
		while(w!=-1)
		{
			if(!visited[w])
			{
				cout<<w<<" ";
				visited[w]=1;
				q.push(w);
			}
			w=GetNextNeighbor(v,w);
		}
		
	}
	delete []visited;
}


void GraphList::TopoOrder()
{
	//初始化 
	int n=GraphSize;
	int *count=new int[n];
	for(int i=0;i<n;i++) count[i]=0;
	for(int i=0;i<n;i++)
	{
		Edge*p=Head[i].Adjacent;
		while(p!=NULL){
			count[p->VerAdj]++;
			p=p->Link;
		}
	}
	int top=-1;
	
	
	for(int i=0;i<n;i++)
		if(count[i]==0)
		{
			count[i]=top;top=i; //入栈 
		}
	for(int i=0;i<n;i++)
	{
		if(top==-1)
		{
			cout<<"There is a cycle in network!"<<endl; 
		}
		else
			{
				int j=top;
				top=count[top];
				cout<<j<<" ";//出栈 
				Edge*p=Head[j].Adjacent;
				while(p!=NULL)
				{
					int k=p->VerAdj;
					if(--count[k]==0)
					{
						count[k]=top;top=k;
					}
					p=p->Link;
				}
			}
	}
	delete []count;
}


void GraphList::CriticalPath()//标准路径 
{
	//STEP1事件最早开始时间 
	int n;
	Edge *p; 
	int ve[n=GraphSize];
	for(int i=0;i<n;i++)//初始化 
	{
		ve[i]=0;
	}
	for(int i=0;i<n-1;i++)
	{
		p=Head[i].Adjacent;
		while(p!=NULL)
		{
			int k=p->VerAdj;
			if(ve[i] + p->cost > ve[k])
				ve[k]= ve[i] + p->cost;
			p=p->Link;
		}
	}
	//STEP2求事件最迟开始时间 
	int vl[n];
	for(int i=0;i<n;i++)//初始化 
	{
		vl[i]=ve[n-1];
	}

	for(int i=n-1;i>-1;i--)
	{
		p=Head[i].Adjacent;
		while(p!=NULL)
		{
			int k=p->VerAdj;
			if(vl[k] - p->cost < vl[i])
				vl[i] = vl[k] - p->cost;
			p=p->Link;

		}
	}

	//STEP3比较 
	for(int i=0;i<n;i++)
	{
		
		cout<<"i="<<i<<endl;
		int templ; int tempe;int k;
		p=Head[i].Adjacent;
		while(p!=NULL)
		{
			k=p->VerAdj;
			tempe = ve[i];
			templ = vl[k] - p->cost; 
			if(templ == tempe)
				printf("<%d,%d> is Critical Activity!\n",i,k);
			p=p->Link;
		}
	}
} 

void GraphList::Dijkstra(const int v)
{
	
	int n=GraphSize;
	const int max=9999;
	int path[n];
	int dist[n];
	int s[n];
	
	//STEP1:初始化
	for(int i=0;i<n;i++)
	{
		path[i]=-1;
		dist[i]=max;
		s[i]=0;
	}
	
	dist[v]=0;
	s[v]=1;
	Edge*p=Head[v].Adjacent;
	int u=v;
	int k;
	//STEP2:求从初始顶点v到其他各顶点的最短路径
	for(int j=0;j<n-1;j++)
	{
		while(p!=NULL)
		{
			k=p->VerAdj;
			if(s[k]!=1&&dist[u]+p->cost<dist[k])
			{
				dist[k]=dist[u]+p->cost;
				path[k]=u;
			}
			p=p->Link;
		}
		//确定即将被访问的顶点u
		int ldist=max;
		for(int i=0;i<n;i++)
		{
			if(dist[i]>0&&dist[i]<ldist&&s[i]==0)
			{
				ldist=dist[i];
				u=i;
			}
		
		} 	
		s[u]=1;
		p=Head[u].Adjacent;
	} 
	 
	
	for(int i=0;i<n;i++)
	{
	 	cout<<v<<"->"<<i<<":"<<dist[i]<<endl;
	}
}


void GraphList::Output(){
	cout<<"当前图如下："<<endl; 
	int A[e];
	for(int i=0;i<GraphSize;i++)
	{
		cout<<"H["<<i<<"]->";
		Vertex H=Head[i];
		int n=GetNeighbors(i,A);
		
		for(int j=0;j<n;j++)
		{
			cout<<A[j]<<"->";	
		}	
		cout<<"\n";
	} 
} 



int main() {
	GraphList A(20);
	A.Output();
	cout<<"插入一条边"<<endl;
	int x1,x2,weight;
	cin>>x1>>x2>>weight; 
	A.InsertEdge(x1,x2,weight);
	A.Output();
	/*cout<<"插入一条边"<<endl;
	cin>>x1>>x2>>weight; 
	A.InsertEdge(x1,x2,weight);
	A.Output();
	cout<<"删除一条边"<<endl;
	cin>>x1>>x2; 
	A.DeleteEdge(x1,x2);
	A.Output();
	cout<<"删除一条边"<<endl;
	cin>>x1>>x2; 
	A.DeleteEdge(x1,x2);
	*/
	A.Output();
	//A.CriticalPath(); 
	A.Dijkstra(0);
	A.BFS(0); 
	cout<<endl;
	//A.DepthFirstSearch();
	A.TopoOrder(); 
	cout<<endl;
	A.NDFS(0);
}

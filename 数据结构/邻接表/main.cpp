#include <iostream>
#include <memory.h>
#include <stack>
#include <queue>
using namespace std;


class GraphList; 


//�߽��Ľṹ�� 
struct Edge
{
	friend class GraphList;
	int VerAdj; //�ڽӶ�����ţ���0��ʼ��� 
	int cost; //�ߵ�Ȩֵ 
	Edge*Link; //ָ����һ�߽ڵ��ָ��
	Edge(int aVerAdj,int acost,Edge*aLink=NULL){ VerAdj=aVerAdj;cost=acost;Link=aLink;} 
	Edge(Edge*aLink=NULL){Link=aLink;} 
}; 

//������н��Ľṹ�� 
struct Vertex 
{
	friend class GraphList;
	int VerName;//��������
	Edge*Adjacent;//�������ͷָ��  
	Vertex(int name,Edge*adjacent=NULL){VerName=name;Adjacent=adjacent;}
	Vertex(Edge*adjacent=NULL){Adjacent=adjacent;}
};
 
 //�����ڽӱ����Graph_List�ඨ�� �������б߾�Ϊ��Ȩ 
class GraphList
{
private:
	Vertex*Head; //�����ͷָ�� 
	int GraphSize;		 //ͼ�е�ǰ����ĸ��� 
	int MaxGraphSize;   //ͼ����󶥵����
	int e;           //ͼ�е�ǰ�ߵĸ��� 
public:
	GraphList(int MaxGraphSize); 
	virtual ~GraphList();
	
	int IsEmpty() const{return !GraphSize;}       //�ж�ͼ�Ƿ�Ϊ�� 
	int IsFull()const{return GraphSize==MaxGraphSize;} //�ж϶������Ƿ����� 
	
	int NumberOfVertices()const{return GraphSize;}//����ͼ�ж���ĸ��� 
	int NumberOfEdges()const{return e;}				//����ͼ�бߵĸ���
	
	int	GetWeight(const int v1,const int v2)const;//����ָ���ߵ�Ȩֵ 
	
	int GetFirstNeighbor(const int v)const;//�������Ϊv�ĵ�һ���ڽӶ�������
	int GetNextNeighbor(const int v1,const int v2)const;//�������Ϊv1�Ķ�����������Ϊv2�ĵ����һ���ڽӶ�������
	
	int GetNeighbors(const int v,int A[])const;//�õ�����v���ڽӶ���� �����ڽӶ������ 
	
					//	bool InsertVertex(const int v);//��ͼ�в���һ������ 
	bool InsertEdge(const int v1,const int v2,int weight);//��ͼ�в���һ���� 
	
					//	bool DeleteVertex(const int v);//��ͼ��ɾ��һ������ 
	bool DeleteEdge(const int v1,const int v2);//��ͼ��ɾ��һ����
	
	
	void DepthFirstSearch();//�Ӷ����ĵ�һ�����㿪ʼ����ͼ������������� 
	void DFS(const int v,int visited[]);//�Ӷ���V��ʼ����ͼ�������������
	void NDFS(const int v);//�Ӷ���V��ʼ����ͼ��������������ĵ����㷨  
	void BFS(const int v);//�Ӷ���V��ʼ����ͼ�Ĺ����������
	
	void Output();//����ڽӱ� 
	
	void TopoOrder();//���ͼ���������� 
	void CriticalPath();//���ͼ�Ĺؼ�·��
	void Dijkstra(const int v);//����Ȩͼ����ָ�����㵽�������ж�������·��
	//void ShortestPath(const int v);//�ڷ�Ȩͼ����ָ�����㵽�������ж�������·�� 
								//void AllLength();//����Ȩͼ����ÿ�Զ��������·��
								//void Prim();//����ͼ����С֧����������ķ�㷨 
								//void Krustral();
};


//=============================================================================
//���캯�� 
GraphList::GraphList(int maxgraphsize):MaxGraphSize(maxgraphsize)
{
	int from,to,weight;
	//������ʵ�ֶ����Headָ������ĵ�һ��Ԫ��
	Head=new Vertex[MaxGraphSize];
	
	cout<<"�����붥�����ͱ���"<<endl;
	cin>>GraphSize;
	cin>>e;
	
	//��ʼ����
	//�������ִ�0 -> GraphSize-1 
	for(int i=0;i<GraphSize;i++)
	{
		Head[i].VerName=i;
		Head[i].Adjacent=NULL;	
	}  
	//�ս���ʼ�� 
	for(int i=GraphSize;i<MaxGraphSize;i++)
	{
		Head[i].VerName=-1;
		Head[i].Adjacent=NULL;
	}

	for(int i=0;i<e;i++)
	{
		cout<<"����ʼ�㣬�յ��Ȩֵ�������ǵ�"<<i+1<<"����) �ո����"<<endl; 
		cin>>from>>to>>weight;//�����±ߵ�ʼ���յ��Ȩֵ 
		
		Edge*p=new Edge(to,weight,NULL);
		Edge*q=Head[from].Adjacent;
		 
		if(q==NULL){        
			Head[from].Adjacent=p;  //����ǵ�һ���� 
		}else {
			while(q->Link!=NULL)    //������ǵ�һ���ߣ��嵽�߽����� 
			{
				q=q->Link;
			}
			q->Link=p;
		}
	} 
	cout<<"�����ɹ���"<<endl; 
}


//�������� 
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



int GraphList::GetWeight(const int v1,const int v2)const //����v1->v2�ıߵ�Ȩ 
{
	//�������һ�����㲻���� 
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



int GraphList::GetFirstNeighbor(const int v)const //���ص�һ���ڽӵ� ���Ҳ����򷵻�-1 
{
	if(v==-1||v>=GraphSize) return -1;	
	
	Edge*p=Head[v].Adjacent;
	if(p!=NULL)
	    return p->VerAdj;
	else return -1;
}



int GraphList::GetNextNeighbor(const int v1,const int v2)const //����v1����v2�������һ���ڽӵ� 
{
	if(v1==-1||v1>=GraphSize||v2==-1||v2>=GraphSize) 
	{
		//cout<<"�Ҳ���"<<endl;
		return -1;
	}
	Edge*p=Head[v1].Adjacent;
	while(p!=NULL&&p->VerAdj!=v2)//�ҵ�v2 
		p=p->Link;
	
	if(p==NULL||p->Link==NULL)
	{
		//cout<<"�Ҳ���"<<endl;
		return -1;
	}
	p=p->Link;
	return p->VerAdj;
}

 
int GraphList::GetNeighbors(const int v,int A[])const  //�õ�����v���ڽӶ���� ����v���ڽӶ������ 
{
	if(v==-1||v>=GraphSize) return 0; 
	
	memset(A,0,sizeof(A));//��ʼ��
	
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
bool GraphList::InsertVertex(const int v)//����һ������ 
{
	if(v<MaxGraphSize&&v>=0)
	{
		if(Head[v].VerName==-1)
		{
			Head[v].VerName=v;
			GraphSize++;
			return 1; 
		}
		cout<<"�����Ѵ���";
		return 0; 
	}
	cout<<"Խ�磬����ʧ��"<<endl;
	return 0; 
}
*/

bool GraphList::InsertEdge(const int v1,const int v2,int weight) //����ָ���� 
{
	if(v1==-1||v2==-1||v1>=GraphSize||v2>=GraphSize) return 0;
	Edge*q=new Edge(v2,weight,NULL);
	Edge*p=Head[v1].Adjacent;
	
	if(p==NULL){
		Head[v1].Adjacent=q;
	}else {
		while(p->Link!=NULL&&p->VerAdj!=v2)
			p=p->Link;
		if(p->VerAdj==v2) return 0;//����Ѿ��������������ʧ�� 
		p->Link=q;
	}
	e++; 
	return 1;
}


bool GraphList::DeleteEdge(const int v1,const int v2)//ɾ��ָ���� 
{
	if(v1==-1||v2==-1||v1>=GraphSize||v2>=GraphSize) return 0;
	Edge*p=Head[v1].Adjacent;
	Edge*q=Head[v1].Adjacent;
	if(p!=NULL)
	{
	
		if(p->VerAdj==v2) //���V2�ǵ�һ���ڵ� 
		{
			Head[v1].Adjacent=p->Link;
			delete p;
			e--;
			return 1;
		}
		
		//���V2���ǵ�һ���ڵ�
		while(p!=NULL&&p->VerAdj!=v2) 
		{
			q=p;
			p=p->Link;
		}
		if(p==NULL) 
		{	
			//cout<<"�޸ñ�"<<endl; 
			return 0;
		}
		q->Link=p->Link;
		delete p;
		e--;
		return 1; 
	}
	//cout<<"�޸ñ�"<<endl; 
	return 0;
	
}

/*bool GraphList::DeleteVertex(const int v)
{
	if(v<0||v>=MaxGraphSize||Head[v].VerName==-1) return -1; 
	//ɾ��ʼ��Ϊv�ı� 
	Edge*p=Head[v].Adjacent;
	while(p!=NULL)
	{
		Head[v].Adjacent=p->Link;
		delete p;
		e--;
		p=Head[v].Adjacent;
	}
	//ɾ���յ�Ϊv�ı� 
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
	//��ʼ�� 
	if(v==-1||v>=GraphSize) return;
	int*visited=new int[GraphSize];
	int i=0;
	while(i<GraphSize) {visited[i++]=0;}
	stack<int>S;
	
	
	//���ʶ���v 
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
	//��ʼ�� 
	if(s==-1||s>=GraphSize) return;
	int*visited=new int[GraphSize];
	int i=0;
	while(i<GraphSize) {visited[i++]=0;}
	//���ʶ���s 
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
	//��ʼ�� 
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
			count[i]=top;top=i; //��ջ 
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
				cout<<j<<" ";//��ջ 
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


void GraphList::CriticalPath()//��׼·�� 
{
	//STEP1�¼����翪ʼʱ�� 
	int n;
	Edge *p; 
	int ve[n=GraphSize];
	for(int i=0;i<n;i++)//��ʼ�� 
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
	//STEP2���¼���ٿ�ʼʱ�� 
	int vl[n];
	for(int i=0;i<n;i++)//��ʼ�� 
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

	//STEP3�Ƚ� 
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
	
	//STEP1:��ʼ��
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
	//STEP2:��ӳ�ʼ����v����������������·��
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
		//ȷ�����������ʵĶ���u
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
	cout<<"��ǰͼ���£�"<<endl; 
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
	cout<<"����һ����"<<endl;
	int x1,x2,weight;
	cin>>x1>>x2>>weight; 
	A.InsertEdge(x1,x2,weight);
	A.Output();
	/*cout<<"����һ����"<<endl;
	cin>>x1>>x2>>weight; 
	A.InsertEdge(x1,x2,weight);
	A.Output();
	cout<<"ɾ��һ����"<<endl;
	cin>>x1>>x2; 
	A.DeleteEdge(x1,x2);
	A.Output();
	cout<<"ɾ��һ����"<<endl;
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

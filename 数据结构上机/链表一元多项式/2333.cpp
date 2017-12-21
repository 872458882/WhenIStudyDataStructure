#include<iostream>
using namespace std;
struct Node
{
	int co;    //ϵ�� 
	int exp;   //ָ�� 
	
	Node* next;
	Node(int c=0,int e=0,Node*n=NULL):co(c),exp(e),next(n){}
};

class List{
public:		
	List(){head=rear=new Node;}
	void Create();
	void Display();
	bool Insert(int c,int e);
	void Add(List A,List B);
	~List();
private:
	Node*head,*rear;
}; 

List::~List()
{
	Node *tempptr;
	while(head->next!=NULL)
	{
		tempptr=head->next;
		delete head; 
		head=tempptr;
	}
}

void List::Create()
{
	int c,e;
	cout<<"������һ���µ�ϵ����ָ���������У�������2333������"<<endl;
	cin>>c>>e;
	while(c!=2333 && e!=2333) //���벢��� 
	{
		Insert(c,e);
		cout<<"������һ���µ�ϵ����ָ���������У�������2333������"<<endl;
		cin>>c>>e;
	}
}

bool List::Insert(int c,int e)
{
	rear->next=new Node(c,e,NULL);
	rear=rear->next; 
	return 1;
	
}

void List::Display()
{
	if(head->next==NULL)
	{
		cout<<"����ʽ�����ڣ�"<<endl;
		return ;
	}
	Node* p;
	p=head->next;
	while(p!=NULL)
	{
		if(p->co>0)
			cout<<p->co<<"x^"<<p->exp;
		else
			cout<<"("<<p->co<<")"<<"x^"<<p->exp;
		if(p->next!=NULL)
			cout<<"+";
		p=p->next;
	}
	cout<<endl<<endl;
}

void List::Add(List A,List B)
{
	Node * p1=A.head->next;
	Node * p2=B.head->next;
	
	while(p1!=NULL && p2!=NULL)
	{
		if(p1->exp < p2->exp)
		{
			Insert(p1->co,p1->exp);
			p1=p1->next;
			
		}
		else if (p1->exp > p2->exp)
		{
			Insert(p2->co,p2->exp);
			p2=p2->next;
			
		}
		else //p1->exp == p2->exp
		{
			if((p1->co + p2->co) != 0)
			{
				Insert(p2->co+p1->co,p2->exp);
			}
			p1=p1->next;
			p2=p2->next;
			
		}
	}
	if(p1==NULL)
	{
		while(p2!=NULL)
		{
			Insert(p2->co,p2->exp);
			p2=p2->next;
		}
	}
	else //p2==NULL
	{
		while(p1!=NULL)
		{
			Insert(p1->co,p1->exp);
			p1=p1->next;
		}
	}
	
}
int main()
{
	cout<<"����ʽA:"<<endl;
	List A;
	A.Create();
	cout<<"����ʽA=";
	A.Display();

	cout<<"����ʽB:"<<endl;
	List B;
	B.Create();
	cout<<"����ʽB=";
	B.Display();

	cout<<"����ʽA+B=";
	List C;
	C.Add(A,B);
	C.Display();

	system("pause");
	return 0;
}


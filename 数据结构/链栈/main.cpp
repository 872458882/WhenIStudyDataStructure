#include <iostream>
using namespace std;

template<class T>
struct SLNode
{
	T data;
	SLNode<T>* next;
	SLNode(SLNode<T>*nextNode=NULL){next=nextNode;}
	SLNode(const T&item,SLNode<T>*nextNode=NULL)
	{
		data=item;
		next=nextNode;
	}
};

template<class T>
class SLStack 
{
public:
	   //构造函数 构造一个只有哨位结点的空表 
	SLStack():length(0){head=tail=new SLNode<T>(); } 
	SLStack(const T&item);       //构造函数 
	~SLStack();                  //析构函数
		
		
	bool IsEmpty()const{return head->next==NULL;}//判断表是否为空 
	int Length()const{return length;};           //返回表的长度 
	bool Pop(T& ITEM);           //出栈 
	void Push(const T&item);     //插入：在哨位结点后插入字段值为item的结点 
	bool Peek(T& item,int outorin=1); //存取 
	void output();
private:
	int length; 
	SLNode<T>*head,*tail;//表头和表尾  
	SLNode<T>*currptr;
};


//=============================================================
template<class T>
SLStack<T>::SLStack( const T&item)               //构造函数 
{
	tail=currptr=new SLNode<T>(item);
	head=new SLNode<T>(currptr);
	length=1;
}


template<class T>
SLStack<T>::~SLStack()                            //析构函数 
{
	cout<<"析构单链表"<<endl; 
	currptr=head->next;
	while(length!=0)
	{
		output();
		currptr=head->next;
		head->next=currptr->next;
		delete currptr;
		length--;
	}
	
	delete head;
}

//======================================================= 
template<class T>
void SLStack<T>::Push(const T&item)//插入：在哨位结点后插入字段值为item的结点 
{
	if(!length)
	{
		tail=head->next=new SLNode<T>(item,NULL);
		
	}
	else
		head->next=new SLNode<T>(item,head->next);
	length++;
}

//==========================================================

template<class T>
bool SLStack<T>::Pop(T&ITEM)//出栈并将其字段值赋给item
{
	if(!length)
	{
		cout<<"空表!\n";
		return 0;		
	}
	SLNode<T>*temp=head->next;
	head->next=temp->next;
	length--;
	ITEM=temp->data;
	if(temp==tail) tail=head;
	delete temp;
	return 1;
}
	


template<class T>
bool SLStack<T>::Peek(T& item,int outorin)
{
	if(!length)
	{
		cout<<"空表!\n";
		return 0;		
	}
	SLNode<T>*temp=head->next;
	if(outorin==1) 
		item = temp->data;
	else 
		temp->data = item;
	return 1;
}

//========================================================= 
template<class T> 
void SLStack<T>::output()
{
	if(!IsEmpty()) 
	{
		currptr=head->next;
		while(currptr!=tail)
		{
			cout<<"["<<currptr->data<<"]"<<"->";
			currptr=currptr->next;
		}
		cout<<"["<<tail->data<<"]"<<endl;
	}
	else cout<<"空表！"<<endl; 
}


int main()
{
	int x;
	cin>>x;
	SLStack<int> A;
	A.Push(99);
	A.Push(x);
	A.Pop(x);
	cout<<x;
	A.output(); 
}


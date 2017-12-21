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
	   //���캯�� ����һ��ֻ����λ���Ŀձ� 
	SLStack():length(0){head=tail=new SLNode<T>(); } 
	SLStack(const T&item);       //���캯�� 
	~SLStack();                  //��������
		
		
	bool IsEmpty()const{return head->next==NULL;}//�жϱ��Ƿ�Ϊ�� 
	int Length()const{return length;};           //���ر�ĳ��� 
	bool Pop(T& ITEM);           //��ջ 
	void Push(const T&item);     //���룺����λ��������ֶ�ֵΪitem�Ľ�� 
	bool Peek(T& item,int outorin=1); //��ȡ 
	void output();
private:
	int length; 
	SLNode<T>*head,*tail;//��ͷ�ͱ�β  
	SLNode<T>*currptr;
};


//=============================================================
template<class T>
SLStack<T>::SLStack( const T&item)               //���캯�� 
{
	tail=currptr=new SLNode<T>(item);
	head=new SLNode<T>(currptr);
	length=1;
}


template<class T>
SLStack<T>::~SLStack()                            //�������� 
{
	cout<<"����������"<<endl; 
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
void SLStack<T>::Push(const T&item)//���룺����λ��������ֶ�ֵΪitem�Ľ�� 
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
bool SLStack<T>::Pop(T&ITEM)//��ջ�������ֶ�ֵ����item
{
	if(!length)
	{
		cout<<"�ձ�!\n";
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
		cout<<"�ձ�!\n";
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
	else cout<<"�ձ�"<<endl; 
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


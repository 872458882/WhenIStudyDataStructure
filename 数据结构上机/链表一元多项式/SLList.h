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
class SLList 
{
public:
	   //构造函数 构造一个只有哨位结点的空表 
	SLList():length(0){head=tail=new SLNode<T>(); } 
	SLList(const T&item);       //构造函数 
	~SLList();                  //析构函数
		
		
	bool IsEmpty()const{return head->next==NULL;}//判断表是否为空 
	int Length()const{return length;};           //返回表的长度 
	
	
	//取数 将链表中第k个结点的字段值赋给item 
	bool Findk(int k,T&item)const; 
	//取数 当前结点的字段值赋给item 
	bool Findc(T&item)const; 
	
	
	//存数 item赋给链表中第k个结点
	bool Storek(int k,const T&item); 
	//存数 item赋给当前结点
	bool Storec(const T&item); 
	
	
	//查找 在链表中查找字段值为x的结点并返回其在表中的位置 
	int Search(const T&item)const; 
	 
	 
	bool Delete(T& ITEM);                   //删除：删除当前结点并将其字段值赋给item
	bool DeleteFromHead(T& ITEM);           //删除：删除表头结点并将其字段值赋给item
	bool DeleteFromTail(T& ITEM);           //删除：删除表尾结点并将其字段值赋给item
	
	
	void Insert(const T& item);            //插入：在当前结点后插入字段值为item的结点
	void InsertFromTail(const T&item);     //插入：在表尾插入字段值为item的结点
	void InsertFromHead(const T&item);     //插入：在哨位结点后插入字段值为item的结点 
	
	
	void output();
	
	
	void SetCH(){currptr=head;}   //设置当前指针为表头结点 
	void next(){
		currptr=currptr->next;
	} 
	bool SetCK(int k);            //设置当前指针为第k个结点 
	
private:
	int length; 
	SLNode<T>*head,*tail;//表头和表尾  
	SLNode<T>*currptr;
};


//=============================================================
template<class T>
SLList<T>::SLList( const T&item)               //构造函数 
{
	tail=currptr=new SLNode<T>(item);
	head=new SLNode<T>(currptr);
	length=1;
}


template<class T>
SLList<T>::~SLList()                            //析构函数 
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

//==========================================================


template<class T>
void SLList<T>::Insert(const T&item)        //插入：在当前结点后插入字段值为item的结点
{
	if(currptr==NULL)
		cout<<"未指定当前结点!"<<endl; 
	else if(currptr==head)
	{
		InsertFromHead(item);
	}
	else
	{ 
		currptr=new SLNode<T>(item,currptr->next);
		if(tail==currptr)               
			tail=tail->next;
		length++; 
	} 
}

template<class T>
void SLList<T>::InsertFromTail(const T&item)//插入：在表尾插入字段值为item的结点
{
	tail->next=new SLNode<T>(item,NULL);
	tail=tail->next;
	length++;
}

template<class T>
void SLList<T>::InsertFromHead(const T&item)//插入：在哨位结点后插入字段值为item的结点 
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
bool SLList<T>::Delete(T&ITEM)//删除：删除当前结点的后继节点并并将其字段值赋给item
{
	if(currptr==tail||IsEmpty())
	{
		cout<<"没有后继节点 或者 是空表！\n";
		return 0; 
	}
	
	if(currptr->next==tail) 
		tail=currptr;
		
	SLNode<T>*temp=currptr->next;
	currptr->next=temp->next;
	length--;
	ITEM=temp->data;
	delete temp;
	
	return 1;
} 

template<class T>
bool SLList<T>::DeleteFromHead(T&ITEM)//删除：删除表头结点的后继节点并将其字段值赋给item
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
bool SLList<T>::DeleteFromTail(T& ITEM)//删除：删除表尾结点并将其字段值赋给item
{
	if(tail==NULL)
	{
		cout<<"空表！\n";
		return 0; 
	}
	currptr=head;
	while(currptr->next!=tail)
	{
		currptr=currptr->next;
	}
	ITEM=tail->data;
	if(tail==NULL)cout<<"空表！\n";
	delete tail;
	length--;
	tail=currptr;
	return 1;
} 


//===============================================================

//取 将链表中第k个结点的字段值赋给item 

template<class T>
bool SLList<T>::Findk(int k,T&item)const
{ 
	if(k>length) 
	{
		cout<<"取数失败 表中没有第k个元素!"<<endl;  
		return 0;
	}
	SLNode<T>*temp=head;
	int i=0;
	while(k!=i)
	{
		temp=temp->next;
		i++;
	} 
	item=temp->data;
	return 1;
}	


//取 当前结点的字段值赋给item 

template<class T>
bool SLList<T>::Findc(T&item)const
{
	if(currptr!=NULL&&currptr!=head)
	{
		item=currptr->data;
		return 1;
	}
	cout<<"取数失败"<<endl; 
	return 0;
}
	
//=========================================================

//存数 item赋给链表中第k个结点
template<class T> 
bool SLList<T>::Storek(int k,const T&item)
{
	if(k>length) 
	{
		cout<<"存数失败 表中没有第k个元素!"<<endl;  
		return 0;
	}
	SLNode<T>*temp=head;
	int i=0;
	while(k!=i)
	{
		temp=temp->next;
		i++;
	} 
	temp->data=item;
	return 1;
}

//存数 item赋给当前结点 
template<class T> 
bool SLList<T>::Storec(const T&item)
{
	if(currptr!=NULL&&currptr!=head)
	{
		currptr->data=item;
		return 1;
	}
	cout<<"存数失败"<<endl; 
	return 0;
} 

//========================================================= 
template<class T> 
void SLList<T>::output()
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

//======================================================
template<class T>
int SLList<T>::Search(const T&item)const //查找data域为item的结点并返回其位置 
{ 
	SLNode<T>*temp=head;
	int i=0;
	while(temp->next!=NULL)
	{
		temp=temp->next;
		i++;
		if(temp->data==item)
			return i;
	} 
	cout<<"表中没有该元素"<<endl;  
	return -1; 
}	


//=======================================================
template<class T>
bool SLList<T>::SetCK(int k)                //设置当前指针为第k个结点 
{
	if(k>length) 
	{
		cout<<"表中没有第k个元素!"<<endl;  
		return 0;
	}
	SLNode<T>*temp=head;
	int i=0;
	while(k!=i)
	{
		temp=temp->next;
		i++;
	} 
	currptr=temp;	
	return 1;
}
//==========================================================

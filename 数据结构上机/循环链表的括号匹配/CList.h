#include <iostream>
using namespace std;

template<class T>
struct CNode
{
	T data;
	CNode<T>* next;
	CNode(CNode<T>*nextNode=NULL){next=nextNode;}
	CNode(const T&item,CNode<T>*nextNode=NULL)
	{
		data=item;
		next=nextNode;
	}
};

template<class T>
class CList 
{
public:
	   //构造函数 构造一个只有哨位结点的空表 
	CList():length(0){head=new CNode<T>(); head->next=head;} 
	CList(const T&item);       //构造函数 
	~CList();                  //析构函数
		
	bool IsEmpty()const{return head->next==head;}//判断表是否为空 
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

	
	void Insert(const T& item);            //插入：在当前结点后插入字段值为item的结点
	void InsertFromHead(const T&item);     //插入：在哨位结点后插入字段值为item的结点 
	
	
	void output();
	
	
	void SetCH(){currptr=head;}   //设置当前指针为表头结点 
	void next(){
		currptr=currptr->next;
	//	if(currptr==head)cout<<"当前结点变成头节点！"<<endl;
	} 
	
	bool SetCK(int k);            //设置当前指针为第k个结点 
	
private:
	int length; 
	CNode<T>*head;//表头和表尾  
	CNode<T>*currptr;
};


//=============================================================
template<class T>
CList<T>::CList( const T&item)               //构造函数 
{
	currptr=new CNode<T>(item);
	head=new CNode<T>(currptr);
	currptr->next=head;
	length=1;
//	cout<<"链表创建成功！"<<endl;
}


template<class T>
CList<T>::~CList()                            //析构函数 
{
	
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
//	cout<<"析构链表成功"<<endl; 
}

//==========================================================


template<class T>
void CList<T>::Insert(const T&item)        //插入：在当前结点后插入字段值为item的结点
{
	if(currptr==NULL)
	{
	//    cout<<"未指定当前结点!"<<endl;
	    return ;
	} 
	if(currptr==head)
	{
		InsertFromHead(item);
		return ;
	}
	currptr->next=new CNode<T>(item,currptr->next);
	length++; 

}


template<class T>
void CList<T>::InsertFromHead(const T&item)//插入：在哨位结点后插入字段值为item的结点 
{
	if(!length)
	{
		head->next=new CNode<T>(item,head);
	}
	else
		head->next=new CNode<T>(item,head->next);
	length++;
}

//==========================================================

template<class T>
bool CList<T>::Delete(T&ITEM)//删除：删除当前结点的后继节点并并将其字段值赋给item
{
	if(currptr==NULL||IsEmpty())
	{
	//	cout<<"未指定当前结点 或者 链表是空表！\n";
		return 0; 
	}
	
	if(currptr->next==head) //如果当前结点是最后一个结点，则删除头节点的下一节点
	{
		DeleteFromHead(ITEM); 
	} 
	else{					//正常删除 
		CNode<T>*temp=currptr->next;
		currptr->next=temp->next;
		ITEM=temp->data;
		delete temp;
		length--;
	}
	return 1;
} 

template<class T>
bool CList<T>::DeleteFromHead(T&ITEM)//删除：删除表头结点的后继节点并将其字段值赋给item
{
	if(!length)
	{
	//	cout<<"空表!\n";
		return 0;		
	}
	CNode<T>*temp=head->next;
	head->next=temp->next;
	length--;
	ITEM=temp->data;
	delete temp;
	return 1;
}
	
//===============================================================

//取 将链表中第k个结点的字段值赋给item 

template<class T>
bool CList<T>::Findk(int k,T&item)const
{ 
	if(k>length) 
	{
	//	cout<<"取数失败 表中没有第k个元素!"<<endl;  
		return 0;
	}
	CNode<T>*temp=head;
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
bool CList<T>::Findc(T&item)const
{
	if(currptr!=NULL&&currptr!=head)
	{
		item=currptr->data;
		return 1;
	}
//	cout<<"取数失败"<<endl; 
	return 0;
}
	
//=========================================================

//存数 item赋给链表中第k个结点
template<class T> 
bool CList<T>::Storek(int k,const T&item)
{
	if(k>length) 
	{
	//	cout<<"存数失败 表中没有第k个元素!"<<endl;  
		return 0;
	}
	CNode<T>*temp=head;
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
bool CList<T>::Storec(const T&item)
{
	if(currptr!=NULL&&currptr!=head)
	{
		currptr->data=item;
		return 1;
	}
	//cout<<"存数失败"<<endl; 
	return 0;
} 

//========================================================= 
template<class T> 
void CList<T>::output()
{
	if(!IsEmpty()) 
	{
		currptr=head->next;
		while(currptr!=head)
		{
			cout<<"["<<currptr->data<<"]"<<"->";
			currptr=currptr->next;
		}
		cout<<endl;
	}
	else cout<<"空表！"<<endl; 
}

//======================================================
template<class T>
int CList<T>::Search(const T&item)const //查找data域为item的结点并返回其位置 
{ 
	CNode<T>*temp=head;
	int i=0;
	while(temp->next!=head)
	{
		temp=temp->next;
		i++;
		if(temp->data==item)
			return i;
	} 
//	cout<<"表中没有该元素"<<endl;  
	return -1; 
}	


//=======================================================
template<class T>
bool CList<T>::SetCK(int k)                //设置当前指针为第k个结点 
{
	if(k>length) 
	{
	//	cout<<"表中没有第k个元素!"<<endl;  
		return 0;
	}
	CNode<T>*temp=head;
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

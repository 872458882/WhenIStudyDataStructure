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
	   //���캯�� ����һ��ֻ����λ���Ŀձ� 
	SLList():length(0){head=tail=new SLNode<T>(); } 
	SLList(const T&item);       //���캯�� 
	~SLList();                  //��������
		
		
	bool IsEmpty()const{return head->next==NULL;}//�жϱ��Ƿ�Ϊ�� 
	int Length()const{return length;};           //���ر�ĳ��� 
	
	
	//ȡ�� �������е�k�������ֶ�ֵ����item 
	bool Findk(int k,T&item)const; 
	//ȡ�� ��ǰ�����ֶ�ֵ����item 
	bool Findc(T&item)const; 
	
	
	//���� item���������е�k�����
	bool Storek(int k,const T&item); 
	//���� item������ǰ���
	bool Storec(const T&item); 
	
	
	//���� �������в����ֶ�ֵΪx�Ľ�㲢�������ڱ��е�λ�� 
	int Search(const T&item)const; 
	 
	 
	bool Delete(T& ITEM);                   //ɾ����ɾ����ǰ��㲢�����ֶ�ֵ����item
	bool DeleteFromHead(T& ITEM);           //ɾ����ɾ����ͷ��㲢�����ֶ�ֵ����item
	bool DeleteFromTail(T& ITEM);           //ɾ����ɾ����β��㲢�����ֶ�ֵ����item
	
	
	void Insert(const T& item);            //���룺�ڵ�ǰ��������ֶ�ֵΪitem�Ľ��
	void InsertFromTail(const T&item);     //���룺�ڱ�β�����ֶ�ֵΪitem�Ľ��
	void InsertFromHead(const T&item);     //���룺����λ��������ֶ�ֵΪitem�Ľ�� 
	
	
	void output();
	
	
	void SetCH(){currptr=head;}   //���õ�ǰָ��Ϊ��ͷ��� 
	void next(){
		currptr=currptr->next;
	} 
	bool SetCK(int k);            //���õ�ǰָ��Ϊ��k����� 
	
private:
	int length; 
	SLNode<T>*head,*tail;//��ͷ�ͱ�β  
	SLNode<T>*currptr;
};


//=============================================================
template<class T>
SLList<T>::SLList( const T&item)               //���캯�� 
{
	tail=currptr=new SLNode<T>(item);
	head=new SLNode<T>(currptr);
	length=1;
}


template<class T>
SLList<T>::~SLList()                            //�������� 
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

//==========================================================


template<class T>
void SLList<T>::Insert(const T&item)        //���룺�ڵ�ǰ��������ֶ�ֵΪitem�Ľ��
{
	if(currptr==NULL)
		cout<<"δָ����ǰ���!"<<endl; 
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
void SLList<T>::InsertFromTail(const T&item)//���룺�ڱ�β�����ֶ�ֵΪitem�Ľ��
{
	tail->next=new SLNode<T>(item,NULL);
	tail=tail->next;
	length++;
}

template<class T>
void SLList<T>::InsertFromHead(const T&item)//���룺����λ��������ֶ�ֵΪitem�Ľ�� 
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
bool SLList<T>::Delete(T&ITEM)//ɾ����ɾ����ǰ���ĺ�̽ڵ㲢�������ֶ�ֵ����item
{
	if(currptr==tail||IsEmpty())
	{
		cout<<"û�к�̽ڵ� ���� �ǿձ�\n";
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
bool SLList<T>::DeleteFromHead(T&ITEM)//ɾ����ɾ����ͷ���ĺ�̽ڵ㲢�����ֶ�ֵ����item
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
bool SLList<T>::DeleteFromTail(T& ITEM)//ɾ����ɾ����β��㲢�����ֶ�ֵ����item
{
	if(tail==NULL)
	{
		cout<<"�ձ�\n";
		return 0; 
	}
	currptr=head;
	while(currptr->next!=tail)
	{
		currptr=currptr->next;
	}
	ITEM=tail->data;
	if(tail==NULL)cout<<"�ձ�\n";
	delete tail;
	length--;
	tail=currptr;
	return 1;
} 


//===============================================================

//ȡ �������е�k�������ֶ�ֵ����item 

template<class T>
bool SLList<T>::Findk(int k,T&item)const
{ 
	if(k>length) 
	{
		cout<<"ȡ��ʧ�� ����û�е�k��Ԫ��!"<<endl;  
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


//ȡ ��ǰ�����ֶ�ֵ����item 

template<class T>
bool SLList<T>::Findc(T&item)const
{
	if(currptr!=NULL&&currptr!=head)
	{
		item=currptr->data;
		return 1;
	}
	cout<<"ȡ��ʧ��"<<endl; 
	return 0;
}
	
//=========================================================

//���� item���������е�k�����
template<class T> 
bool SLList<T>::Storek(int k,const T&item)
{
	if(k>length) 
	{
		cout<<"����ʧ�� ����û�е�k��Ԫ��!"<<endl;  
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

//���� item������ǰ��� 
template<class T> 
bool SLList<T>::Storec(const T&item)
{
	if(currptr!=NULL&&currptr!=head)
	{
		currptr->data=item;
		return 1;
	}
	cout<<"����ʧ��"<<endl; 
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
	else cout<<"�ձ�"<<endl; 
}

//======================================================
template<class T>
int SLList<T>::Search(const T&item)const //����data��Ϊitem�Ľ�㲢������λ�� 
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
	cout<<"����û�и�Ԫ��"<<endl;  
	return -1; 
}	


//=======================================================
template<class T>
bool SLList<T>::SetCK(int k)                //���õ�ǰָ��Ϊ��k����� 
{
	if(k>length) 
	{
		cout<<"����û�е�k��Ԫ��!"<<endl;  
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

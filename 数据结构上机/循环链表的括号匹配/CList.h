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
	   //���캯�� ����һ��ֻ����λ���Ŀձ� 
	CList():length(0){head=new CNode<T>(); head->next=head;} 
	CList(const T&item);       //���캯�� 
	~CList();                  //��������
		
	bool IsEmpty()const{return head->next==head;}//�жϱ��Ƿ�Ϊ�� 
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

	
	void Insert(const T& item);            //���룺�ڵ�ǰ��������ֶ�ֵΪitem�Ľ��
	void InsertFromHead(const T&item);     //���룺����λ��������ֶ�ֵΪitem�Ľ�� 
	
	
	void output();
	
	
	void SetCH(){currptr=head;}   //���õ�ǰָ��Ϊ��ͷ��� 
	void next(){
		currptr=currptr->next;
	//	if(currptr==head)cout<<"��ǰ�����ͷ�ڵ㣡"<<endl;
	} 
	
	bool SetCK(int k);            //���õ�ǰָ��Ϊ��k����� 
	
private:
	int length; 
	CNode<T>*head;//��ͷ�ͱ�β  
	CNode<T>*currptr;
};


//=============================================================
template<class T>
CList<T>::CList( const T&item)               //���캯�� 
{
	currptr=new CNode<T>(item);
	head=new CNode<T>(currptr);
	currptr->next=head;
	length=1;
//	cout<<"�������ɹ���"<<endl;
}


template<class T>
CList<T>::~CList()                            //�������� 
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
//	cout<<"��������ɹ�"<<endl; 
}

//==========================================================


template<class T>
void CList<T>::Insert(const T&item)        //���룺�ڵ�ǰ��������ֶ�ֵΪitem�Ľ��
{
	if(currptr==NULL)
	{
	//    cout<<"δָ����ǰ���!"<<endl;
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
void CList<T>::InsertFromHead(const T&item)//���룺����λ��������ֶ�ֵΪitem�Ľ�� 
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
bool CList<T>::Delete(T&ITEM)//ɾ����ɾ����ǰ���ĺ�̽ڵ㲢�������ֶ�ֵ����item
{
	if(currptr==NULL||IsEmpty())
	{
	//	cout<<"δָ����ǰ��� ���� �����ǿձ�\n";
		return 0; 
	}
	
	if(currptr->next==head) //�����ǰ��������һ����㣬��ɾ��ͷ�ڵ����һ�ڵ�
	{
		DeleteFromHead(ITEM); 
	} 
	else{					//����ɾ�� 
		CNode<T>*temp=currptr->next;
		currptr->next=temp->next;
		ITEM=temp->data;
		delete temp;
		length--;
	}
	return 1;
} 

template<class T>
bool CList<T>::DeleteFromHead(T&ITEM)//ɾ����ɾ����ͷ���ĺ�̽ڵ㲢�����ֶ�ֵ����item
{
	if(!length)
	{
	//	cout<<"�ձ�!\n";
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

//ȡ �������е�k�������ֶ�ֵ����item 

template<class T>
bool CList<T>::Findk(int k,T&item)const
{ 
	if(k>length) 
	{
	//	cout<<"ȡ��ʧ�� ����û�е�k��Ԫ��!"<<endl;  
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


//ȡ ��ǰ�����ֶ�ֵ����item 

template<class T>
bool CList<T>::Findc(T&item)const
{
	if(currptr!=NULL&&currptr!=head)
	{
		item=currptr->data;
		return 1;
	}
//	cout<<"ȡ��ʧ��"<<endl; 
	return 0;
}
	
//=========================================================

//���� item���������е�k�����
template<class T> 
bool CList<T>::Storek(int k,const T&item)
{
	if(k>length) 
	{
	//	cout<<"����ʧ�� ����û�е�k��Ԫ��!"<<endl;  
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

//���� item������ǰ��� 
template<class T> 
bool CList<T>::Storec(const T&item)
{
	if(currptr!=NULL&&currptr!=head)
	{
		currptr->data=item;
		return 1;
	}
	//cout<<"����ʧ��"<<endl; 
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
	else cout<<"�ձ�"<<endl; 
}

//======================================================
template<class T>
int CList<T>::Search(const T&item)const //����data��Ϊitem�Ľ�㲢������λ�� 
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
//	cout<<"����û�и�Ԫ��"<<endl;  
	return -1; 
}	


//=======================================================
template<class T>
bool CList<T>::SetCK(int k)                //���õ�ǰָ��Ϊ��k����� 
{
	if(k>length) 
	{
	//	cout<<"����û�е�k��Ԫ��!"<<endl;  
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

#include<iostream>
using namespace std ;

template<class T>/*��������ṹ*/
struct SQNode
{
 	T data;
 	SQNode<T>* next;
 	SQNode(SQNode<T>* nextnode=NULL){next=nextnode;}       //���캯��
 	SQNode(const T& item,SQNode*nextnode=NULL)             //���������ָ����ͬʱ���г�ʼ��������һ�㽫����Ϊ�� 
	{
		data=item ;
		next=nextnode ;
	}
}; 


template<class T>
class LQueue
{
private:
	SQNode<T> *front,*rear;         //ָ���β�Ͷ��׵�ָ��
	int count;
public:
	LQueue(){front=rear=NULL;count=0;}      //���캯��
	~LQueue(){QClear();}                 	//��������

	void QInsert(const T& item);          	//��β���Ԫ��
	bool QDelete(T& item);                	//ɾ������Ԫ�� 
	bool QFront(T& item)const;              //��ȡ����Ԫ�� 

	int IsEmpty()const{return rear==NULL;}         //���ջ�Ƿ�Ϊ��
	void QClear();                                     //��ն��� 
	
};

template<class T>
void LQueue<T>::QInsert(const T& item)
{
	if(IsEmpty())
	{
		front=rear=new SQNode<T>(item,NULL);
		count=1;
	}                                                
	else 
	{
		rear->next=new SQNode<T>(item,NULL);
		rear=rear->next;
		count++;
	}		
} //���β����Ԫ�� 


template<class T>
bool LQueue<T>::QDelete(T& item)
{
	if(IsEmpty())
	{
		cout<<"����Ϊ�գ�ɾ��ʧ��"<<endl;
		return false;
	}
	
	SQNode<T> *temp=front;
	item=front->data;
	front=front->next;
	delete temp;
	count--;
	
	if(count==0)
		 rear=NULL;                 
	return true; 
}  //ɾ������Ԫ�� 

template<class T>
bool LQueue<T>::QFront(T& item)const
{
	if(IsEmpty())
	{	cout<<"����Ϊ�գ�ȡ��ʧ��"<<endl;
		return false;
	}
	item=front->data;
	return true;
}  //��ȡ����Ԫ��

template<class T>
void LQueue<T>:: QClear()
{

	while(!IsEmpty())
	{
		SQNode<T> *temp=front;
		front=front->next;
		delete temp;
		count--;
		if(count==0)
			rear=NULL; 
	}
	rear=NULL;
}


int main()
{
	int X;
	LQueue<int> A;
	A.QInsert(2);
	A.QInsert(3);
	A.QInsert(3);
	A.QInsert(3);
	A.QInsert(3); 
	A.QDelete(X);
	cout<<X<<endl;
	
}
 






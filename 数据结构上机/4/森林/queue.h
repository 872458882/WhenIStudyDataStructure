#include<iostream>
using namespace std ;

template<class T>/*��������ṹ*/
struct LQNode
{
 	T data;
 	LQNode<T>* next;
 	LQNode(LQNode<T>* nextnode=NULL){next=nextnode;}       //���캯��
 	LQNode(const T& item,LQNode*nextnode=NULL)             //���������ָ����ͬʱ���г�ʼ��������һ�㽫����Ϊ�� 
	{
		data=item ;
		next=nextnode ;
	}
}; 


template<class T>
class LQueue
{
private:
	LQNode<T> *front,*rear;         //ָ���β�Ͷ��׵�ָ��
	int count;
public:
	LQueue(){front=rear=NULL;count=0;}      //���캯��
	~LQueue(){QClear();}                 	//��������

	void QInsert(const T& item);          	//��β���Ԫ��
	bool QDelete(T& item);                	//ɾ������Ԫ�� 
	bool QFront(T& item)const;              //��ȡ����Ԫ�� 

	int IsEmpty()const{return count==0;}         //���ջ�Ƿ�Ϊ��
	void QClear();                                     //��ն��� 
	
};

template<class T>
void LQueue<T>::QInsert(const T& item)
{
	if(IsEmpty())
	{
		front=rear=new LQNode<T>(item,NULL);
		count=1;
	}                                                
	else 
	{
		rear->next=new LQNode<T>(item,NULL);
		rear=rear->next;
		count++;
	}		
} //���β����Ԫ�� 


template<class T>
bool LQueue<T>::QDelete(T& item)
{
	if(IsEmpty())
	{
		//cout<<"����Ϊ�գ�ɾ��ʧ��"<<endl;
		return false;
	}
	
	LQNode<T> *temp=front;
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
	{	//cout<<"����Ϊ�գ�ȡ��ʧ��"<<endl;
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
		LQNode<T> *temp=front;
		front=front->next;
		delete temp;
		count--;
		if(count==0)
			rear=NULL; 
	}
	rear=NULL;
}



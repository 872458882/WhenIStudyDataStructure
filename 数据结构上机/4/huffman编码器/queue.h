#include<iostream>
using namespace std ;

template<class T>/*单链表结点结构*/
struct LQNode
{
 	T data;
 	LQNode<T>* next;
 	LQNode(LQNode<T>* nextnode=NULL){next=nextnode;}       //构造函数
 	LQNode(const T& item,LQNode*nextnode=NULL)             //对数据域和指针域同时进行初始化，我们一般将其设为空 
	{
		data=item ;
		next=nextnode ;
	}
}; 


template<class T>
class LQueue
{
private:
	LQNode<T> *front,*rear;         //指向队尾和队首的指针
	int count;
public:
	LQueue(){front=rear=NULL;count=0;}      //构造函数
	~LQueue(){QClear();}                 	//析构函数

	void QInsert(const T& item);          	//队尾添加元素
	bool QDelete(T& item);                	//删除队首元素 
	bool QFront(T& item)const;              //存取队首元素 

	int IsEmpty()const{return count==0;}         //检测栈是否为空
	void QClear();                                     //清空队列 
	
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
} //向队尾插入元素 


template<class T>
bool LQueue<T>::QDelete(T& item)
{
	if(IsEmpty())
	{
		//cout<<"队列为空，删除失败"<<endl;
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
}  //删除队首元素 

template<class T>
bool LQueue<T>::QFront(T& item)const
{
	if(IsEmpty())
	{	//cout<<"队列为空，取数失败"<<endl;
		return false;
	}
	item=front->data;
	return true;
}  //存取队首元素

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



#include <iostream>
using namespace std;


template<class T>
class LStack
{
private:
	int maxSize;
	int top;
	T* element;
public:
	LStack<T>(int MaxSize=10):maxSize(MaxSize),top(-1){element=new T[maxSize];}//构造函数
	~LStack<T>(){delete[]element;}//析构函数

	bool IsEmpty()const{return top==-1;}//判断栈是否为空
	bool IsFull()const{return top==maxSize-1;}//判断栈是否为满
	int Length()const{return top;}//返回栈的长度


	bool Peek(T& item)const;//读取栈顶元素 
	bool Pop(T& item);//弹出栈顶元素并赋给item
	bool Push(const T& item);//向栈中压入插入字段值为item的结点

	void output();
};

template<class T>
bool LStack<T>::Push(const T& item)
{
	if(top==maxSize-1)
	{
		//cout<<"栈满，入栈失败"<<endl;
		return 0;
	}
	else{
		element[++top]=item;
		//cout<<item<<"入栈成功"<<endl;
		return 1;
	}
}

template<class T>
bool LStack<T>::Pop(T& item)
{
	if(top==-1)
	{
		//cout<<"栈空，出栈错误"<<endl; 
		return 0;
	}
	else 
	{
		item=element[top--]; 
		//cout<<item<<endl;
		return 1;
	} 
}


template<class T>
bool LStack<T>::Peek(T& item)const
{
	if(top==-1)
	{
		//cout<<"栈空,存取失败"<<endl;
		return 0; 
	}
	else
	{
		item=element[top]; 
		//cout<<item<<endl;
		return 1;
	} 
}

template<class T>
void LStack<T>::output()
{
	for(int i=0;i<top+1;i++)
	{
		cout<<element[i]<<" ";
	}
	cout<<endl;
}

#include <iostream>
using namespace std;


template<class T>
class LStack
{
private:
	int maxSize;
	int top;
	T* element;
	int maxStackItemIndex;
	int* link2NextMaxItem;
public:
	LStack<T>(int MaxSize=10):maxSize(MaxSize),maxStackItemIndex(-1),top(-1){element=new T[maxSize];link2NextMaxItem= new int[maxSize];}//构造函数
	~LStack<T>(){delete[]element;delete link2NextMaxItem;}//析构函数

	bool IsEmpty()const{return top==-1;}//判断栈是否为空
	bool IsFull()const{return top==maxSize-1;}//判断栈是否为满
	int Length()const{return top;}//返回栈的长度


	void Peek(T& item)const;//读取栈顶元素 
	T Pop();//弹出栈顶元素并赋给item
	void Push(const T& item);//向栈中压入插入字段值为item的结点
	T Max();
	void output();
};

template<class T>
void LStack<T>::Push(const T& item)
{
	if(top==maxSize-1)
	{
		cout<<"栈满，入栈失败"<<endl;
	}
	else{
		element[++top]=item;
		//cout<<item<<"入栈成功"<<endl;
		if(item>Max())
		{
			link2NextMaxItem[top]=maxStackItemIndex;
			maxStackItemIndex=top;
		}
		else link2NextMaxItem[top]=-1;
	}
}

template<class T>
T LStack<T>::Pop()
{
	if(top==-1)
	{
		cout<<"栈空，出栈错误"<<endl; 
	}
	else 
	{
		
		T item=element[top];
		if(top==maxStackItemIndex)
		{
			maxStackItemIndex=link2NextMaxItem[top];
		} 
		top--;
		return item;
	} 
}


template<class T>
void LStack<T>::Peek(T& item)const
{
	if(top==-1)
	{
		cout<<"栈空,存取失败"<<endl; 
	}
	else
	{
		item=element[top]; 
		cout<<item<<endl;
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

template<class T>
T LStack<T>::Max()
{
	if(maxStackItemIndex>=0)
		return element[maxStackItemIndex];
	else 
	 	return -9999;
}



template<class T>
class DSQueue
{
private:
	LStack<T> A;
	LStack<T> B;	
public:
	T MaxValue(T x,T y){return x>y?x:y;}
	T Max(){return MaxValue(A.Max(),B.Max());}
	void Push(T&item){B.Push(item);}
	T Pop()
	{
		if(A.IsEmpty())
		{
			while(!B.IsEmpty())
				{A.Push(B.Pop());
				}
		}
		return A.Pop();
	}
};

int main()
{
	int x;
	DSQueue<int> ss;
	ss.Push(x=8);
	ss.Push(x=44);
	ss.Push(x=9);
	ss.Pop();
	ss.Pop();
	cout<<ss.Max();
	return 0;
}

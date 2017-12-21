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
	LStack<T>(int MaxSize=10):maxSize(MaxSize),maxStackItemIndex(-1),top(-1){element=new T[maxSize];link2NextMaxItem= new int[maxSize];}//���캯��
	~LStack<T>(){delete[]element;delete link2NextMaxItem;}//��������

	bool IsEmpty()const{return top==-1;}//�ж�ջ�Ƿ�Ϊ��
	bool IsFull()const{return top==maxSize-1;}//�ж�ջ�Ƿ�Ϊ��
	int Length()const{return top;}//����ջ�ĳ���


	void Peek(T& item)const;//��ȡջ��Ԫ�� 
	T Pop();//����ջ��Ԫ�ز�����item
	void Push(const T& item);//��ջ��ѹ������ֶ�ֵΪitem�Ľ��
	T Max();
	void output();
};

template<class T>
void LStack<T>::Push(const T& item)
{
	if(top==maxSize-1)
	{
		cout<<"ջ������ջʧ��"<<endl;
	}
	else{
		element[++top]=item;
		//cout<<item<<"��ջ�ɹ�"<<endl;
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
		cout<<"ջ�գ���ջ����"<<endl; 
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
		cout<<"ջ��,��ȡʧ��"<<endl; 
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

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
	LStack<T>(int MaxSize=10):maxSize(MaxSize),top(-1){element=new T[maxSize];}//���캯��
	~LStack<T>(){delete[]element;}//��������

	bool IsEmpty()const{return top==-1;}//�ж�ջ�Ƿ�Ϊ��
	bool IsFull()const{return top==maxSize-1;}//�ж�ջ�Ƿ�Ϊ��
	int Length()const{return top;}//����ջ�ĳ���


	bool Peek(T& item)const;//��ȡջ��Ԫ�� 
	bool Pop(T& item);//����ջ��Ԫ�ز�����item
	bool Push(const T& item);//��ջ��ѹ������ֶ�ֵΪitem�Ľ��

	void output();
};

template<class T>
bool LStack<T>::Push(const T& item)
{
	if(top==maxSize-1)
	{
		//cout<<"ջ������ջʧ��"<<endl;
		return 0;
	}
	else{
		element[++top]=item;
		//cout<<item<<"��ջ�ɹ�"<<endl;
		return 1;
	}
}

template<class T>
bool LStack<T>::Pop(T& item)
{
	if(top==-1)
	{
		//cout<<"ջ�գ���ջ����"<<endl; 
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
		//cout<<"ջ��,��ȡʧ��"<<endl;
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

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


	void Peek(T& item)const;//��ȡջ��Ԫ�� 
	void Pop(T& item);//����ջ��Ԫ�ز�����item
	void Push(const T& item);//��ջ��ѹ������ֶ�ֵΪitem�Ľ��

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
		cout<<item<<"��ջ�ɹ�"<<endl;
	}
}

template<class T>
void LStack<T>::Pop(T& item)
{
	if(top==-1)
	{
		cout<<"ջ�գ���ջ����"<<endl; 
	}
	else 
	{
		item=element[top--]; 
		cout<<item<<endl;
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


int main()
{
	char C;
	LStack<char> A(4);
	A.Push('a');
	A.Push('b');
	A.Push('c');
	A.Push('d');
	A.Pop(C);
	A.Pop(C); 
	A.Peek(C);
	A.Push('e');
	A.Pop(C);
	return 0;
}


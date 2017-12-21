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


int main() {
	LStack<char> bracket(100);
	char read_in=cin.get();
	bool is_matched=true;
	while(is_matched&&read_in!='\n')
	{
		if(read_in=='{'||read_in=='['||read_in=='(')
			bracket.Push(read_in);
		if(read_in=='}'||read_in==']'||read_in==')')
		{
			if(bracket.IsEmpty())
			{
				cout<<"Unmatched closing bracket"<<read_in<<"is detected"<<endl;
				is_matched=false;
				return 0;
			}
			char open_bracket;
			bracket.Pop(open_bracket);
			is_matched=(open_bracket=='('&&read_in==')')||(open_bracket=='['&&read_in==']')||(open_bracket=='{'&&read_in=='}');
			if(!is_matched)
			{
				cout<<"Bad match"<<open_bracket<<read_in<<endl;
				return 0;
			}
		}
		read_in=cin.get();
	}
	cout<<"ƥ��ɹ�"<<endl;
	return 0;
}

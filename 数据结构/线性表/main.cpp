#include <iostream>
#include<cstdlib>
using namespace std;
//�������Ա���±��0��ʼ

class LinearList
{
private:
	int maxSize;
	int length;
	double* element;
public:
	LinearList(int MaxListSize=10):maxSize(MaxListSize),length(0){element=new double[maxSize];}//���캯��
	~LinearList(){delete[]element;}//��������
	bool IsEmpty()const{return length==0;}//�жϱ��Ƿ�Ϊ��
	bool IsFull()const{return length==maxSize;}//�жϱ��Ƿ�Ϊ��
	int Length()const{return length;}//���ر�ĳ���
	void Find(int k,double& item)const;//��ȡ�����±�Ϊk�Ľ����ֶ�ֵ����item
	int Search(const double&item)const;//���ң��ڱ��в����ֶ�ֵΪitem�Ľ�㲢�������±�
	void Delete(int k,double& item);//ɾ����ɾ���±�Ϊk�Ľ�㲢�����ֶ�ֵ����item
	void Insert(int k,double item);//���룺���±�Ϊk�Ľ�������ֶ�ֵΪitem�Ľ��
	void output();
};


void LinearList::Insert(int k,double item)
{
	if(k<0||k>length||length==maxSize)
		cout<<"���벻�Ϸ�"<<endl;
	else if(k==length)
	{
		element[k]=item;
		length++;
	}
	else
	{for(int i=length;i>k;i--)
		{element[i]=element[i-1];}
	element[k]=item;
	length++
	;}
	cout<<"����ɹ�"<<endl;
}


void LinearList::Delete(int k,double& item)
{
	item=element[k];
	if(k<0||k>length-1||length==0) cout<<"ɾ�����Ϸ�"<<endl;
	for(int i=k;i<length;i++)
	{
		element[i]=element[i+1];
	}
	length=length-1;
}


int LinearList::Search(const double&item)const
{
	for(int i=0;i<length-1;i++)
	{
		if(element[i]==item) return i;
	}
	return -1;
}

void LinearList::Find(int k,double& item)const
{
	if(k<0||k>length-1) exit(0);
	else item=element[k];
}

void LinearList::output()
{
	for(int i=0;i<length;i++)
	{
		cout<<element[i]<<" ";
	}
	cout<<endl;
}

int main()
{
	LinearList A(4);
	A.Insert(0,9.1);
	A.Insert(1,1.0);
	A.Insert(1,2.0);
	A.Insert(2,1.0);
	A.output();
	return 0;
}

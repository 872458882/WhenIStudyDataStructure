#include <iostream>
#include<cstdlib>
using namespace std;
//假设线性表的下标从0开始

class LinearList
{
private:
	int maxSize;
	int length;
	double* element;
public:
	LinearList(int MaxListSize=10):maxSize(MaxListSize),length(0){element=new double[maxSize];}//构造函数
	~LinearList(){delete[]element;}//析构函数
	bool IsEmpty()const{return length==0;}//判断表是否为空
	bool IsFull()const{return length==maxSize;}//判断表是否为满
	int Length()const{return length;}//返回表的长度
	void Find(int k,double& item)const;//存取：将下标为k的结点的字段值赋给item
	int Search(const double&item)const;//查找：在表中查找字段值为item的结点并返回其下标
	void Delete(int k,double& item);//删除：删除下标为k的结点并将其字段值赋给item
	void Insert(int k,double item);//插入：在下表为k的结点后插入字段值为item的结点
	void output();
};


void LinearList::Insert(int k,double item)
{
	if(k<0||k>length||length==maxSize)
		cout<<"插入不合法"<<endl;
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
	cout<<"插入成功"<<endl;
}


void LinearList::Delete(int k,double& item)
{
	item=element[k];
	if(k<0||k>length-1||length==0) cout<<"删除不合法"<<endl;
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

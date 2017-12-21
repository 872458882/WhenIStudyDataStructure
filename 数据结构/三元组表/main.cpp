#include <iostream>
using namespace std;

/*��Ԫ������*/ 
template<class T>
class Trituple
{
	friend class SparseMatrix;
	private:
		int row,col;
		T value;
};

/*ϡ�������*/ 
template<class T>
class SparseMatrix
{
	private:
		int rows,cols,count;
		Trituple<T> *smArray;//������Ԫ��������
		int MaxTerm;/*����Ĺ�ģ*/ 
	public:
		SparseMatrix(int Mrows,int Mcols);
		SparseMatrix(int Mrows,int Mcols,int Mcount);
		SparseMatrix<T>& Transpose();//��ת�þ���
		SparseMatrix<T>& Add(SparseMatrix<T> sm);
 
		
};

template<class T>
SparseMatrix<T>::SparseMatrix(int Mrows,int Mcols)
{
	if(Mrows<=0||Mcols<=0)
	{
		cout<<"bad initializer"<<endl;
		exit(1);
	}
	if(Mrows==1&&Mcols==1)
	{
		cout<<"bad initializer"<<endl;
		exit(1);
	}
	rows=Mrows;
	cols=Mcols;
	count=0;
	Maxterm=Mrows*Mcols;
	smArray=new Trituple<T>[Mmaxterm];
} 

template<class T>
SparseMatrix<T>::SparseMatrix(int Mrows,int Mcols,int Mcount)
{
	if(Mrows<=0||Mcols<=0)
	{
		cout<<"bad initializer"<<endl;
		exit(1);
	}
	if(Mrows==1&&Mcols==1)
	{
		cout<<"bad initializer"<<endl;
		exit(1);
	}
	rows=Mrows;
	cols=Mcols;
	count=Mcount;
	Maxterm=Mrows*Mcols;
	smArray=new Trituple<T>[Maxterm];
}

template<class T>
SparseMatrix<T>& SparseMatrix<T>::Add(SparseMatrix<T> sm)
{
	if((count+=sm.count)==0)
	{
		return sm;
	}
	//����һ��ϡ�����temp������������ԭ��������� 
	SparseMatrix<T> temp(cols,rows,0);
	int k1,k2;
	k1=k2=0;
	while(k1<count)&&(k2<sm.count))
	{
		int a,b,c,d;
		T e,f;
		sm.smArray[k2].get
	}
	
	
	
}


template<class T>
SparseMatrix<T> SparseMatrix<T>::Transpose()
{
	SparseMatrix<T> b;
	b.rows=cols;
	b.cols=rows;
	b.count=count;
	if(count>0)
	{
		int Bnumber=0;
		for(int k=0;k<cols;k++)
		{
			for(int i=0;i<count;i++)
			{if(smArray
			

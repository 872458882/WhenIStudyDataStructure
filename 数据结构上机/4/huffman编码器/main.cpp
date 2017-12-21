#include <iostream>
#include <fstream>
#include <memory.h> 
#include <string>
#include"queue.h"//֮ǰд���� 
#include"stack.h" //֮ǰд���� 
using namespace std;






template <class T>
class Huffman;

//========================================
//Huffman���ڵ�������
template <class T>
class HuffmanNode
{ 
private:    
	T data;
    int weight;
    HuffmanNode<T>  *left,*right;//ָ������������ָ��
    string code;

public:
	friend class Huffman<T>;  
    //���캯��
    HuffmanNode(const T& item,const int& w=0,HuffmanNode *lptr=NULL,HuffmanNode *rptr=NULL):
        data(item),weight(w),left(lptr),right(rptr){}

    HuffmanNode<T> * GetLeft()const{return left;}//�������ӽڵ�

    void SetLeft(HuffmanNode<T> * L){left=L;}//�������ӽڵ�

    HuffmanNode<T> * GetRight()const{return right;}//�������ӽڵ�

    void SetRight(HuffmanNode<T> * R){right=R;}//�������ӽڵ�

    T GetData(){return data;}

    void SetData(T item){data=item;}

	int GetWeight(){return weight;}
	
	void SetWeight(int w){weight=w;}

};



//===============================================================
//Huffman����

#define m 128
template <class T>
class Huffman
{
private:
    HuffmanNode<T> *root;//����������
	T data[m];
    int weight[m];
    string Huffcode[m];
    int number;//��ǰ�ж������ַ� 
public:
    Huffman(HuffmanNode<T>*t=NULL):root(t){}//���캯��

    virtual ~Huffman(){Del(root);}//�������� ɾ������Huffman��

    //����Huffman��
    HuffmanNode<T>* CreateHuffman();//����huffman�� 
    
    void CodeNode();//����ÿ������huffman���� 
	
	void Read(string txtname); 
	
	void Del(HuffmanNode<T>*t);
	
	void sort(T Data[],int pData[],int left,int right);
    
    HuffmanNode<T>* GetRoot(){return root;}
    void SetRoot(HuffmanNode<T> * t){root=t;}
    bool IsEmpty(){return root==NULL;}
    
    void Input(); 
    
};



//======================================
//������ 
template <class T>
HuffmanNode<T>* Huffman<T>::CreateHuffman() {
   Input(); 
   HuffmanNode<T>* H[m];
   HuffmanNode<T>*p1=NULL,*p2=NULL,*p,*t;
   int i=0,j=0;
   for(i=0;i<m;i++)
   {
   		H[i]=new HuffmanNode<T>(data[i],weight[i],NULL,NULL);
   }
   for(i=0;i<m-1;i++)
   {
   		t =new HuffmanNode<T>(0);
		t->weight=H[i]->weight+H[i+1]->weight;
		t->left=H[i];
		t->right=H[i+1];
		//���½ڵ���뵽H�� 
		j=i+2;
		while(j<m && t->weight > H[j]->weight)
		{
			H[j-1]=H[j];
			j++;
		}
		H[j-1]=t;
	}
	root=H[m-1];
	return root;
}



//============================================
template <class T>
void Huffman<T>::Input()
{
	string txtname;
	cin>>txtname;
	Read(txtname);
	cout<<"�����ִ�����С����:\n";
	sort(data,weight,0,number-1); 
	for(int i=0;i<number-1;i++)
	{
		cout<<"\'"<<data[i]<<"\'"<<":"<<weight[i]<<endl;
	} 
}



//=============================================
//��ȡ�ı�ͳ��ÿ���ַ����ֵĴ��� 
template <class T>
void Huffman<T>::Read(string txtname)
{

	int TIMES[128];
	memset(TIMES,0,sizeof(TIMES));
	
	ifstream infile;
	infile.open(txtname);
	
	//ͳ��ÿ���ַ����ֵĴ��� 
	if(infile.is_open())
	{ 
		
		while(infile.good() && !infile.eof())
		{
			char c=infile.get();
			TIMES[c]++;
		}
	}
	infile.close(); 
	
	cout<<"�ļ�"<<txtname<<"�е��ַ�������ִ�����\n"; 
	
	//��������ַ� 
	int j=0;
	for(int i=0;i<128;i++)
	{
		if(TIMES[i]==0) continue;
		
		data[j]=i;
		weight[j]=TIMES[i];
		cout<<"\'"<<data[j]<<"\'"<<":"<<weight[j]<<endl;
		j++;
	}
	number=j;
	
}
//=======================================
//�����㷨 
template <class T>
void Huffman<T>::sort(T Data[],int pData[],int left,int right) 
{ 	
	int i,j;
	int iTemp;
	T Temp;
	i=left; 
	j=right; 
	int middle=(left+right)/2;//��ŦԪ 
	while(i<=j)
	{
		while((pData[i]<middle) && (i<right))//����ɨ�������ֵ���� 
			i++;
		while((pData[j]>middle) && (j>left))//����ɨ�������ֵ���� 
			j--; 
		if(i<=j)//�ҵ���һ��ֵ 
		{	 
			//���� 
			iTemp = pData[i]; 
			pData[i] = pData[j]; 
			pData[j] = iTemp; 
			Temp = Data[i]; 
			Data[i] = Data[j]; 
			Data[j] = Temp; 
			i++; 
			j--; 
		} 
	}//�������ɨ����±꽻����ֹͣ�����һ�Σ� 

	//����߲�����ֵ(left��j)���ݹ����� 
 	if(left<j) 
		sort(Data,pData,left,j); 
	//���ұ߲�����ֵ(right��i)���ݹ��Ұ�� 
 	if(right>i) 
		sort(Data,pData,i,right); 
}


//========================================
//ɾ����㼰����������
template <class T>
void Huffman<T>::Del(HuffmanNode<T> *t)
{
	if(t != NULL) {
    Del(t->GetLeft());
    Del(t->GetRight());
    delete t;
	}
}	 

//=============================================
template <class T>
void Huffman<T>::CodeNode() //ÿ���ڵ�����huffman���� 
{
	cout<<"ÿ���ַ���Huffman�������£�\n"; 
	LQueue<HuffmanNode<T>*> q;
	HuffmanNode<T>*temp;
	q.QInsert(root);
	while(!q.IsEmpty())
	{
		q.QDelete(temp);
		if(temp->left==NULL&&temp->right==NULL)
			cout<<"\'"<<temp->data<<"\':"<<temp->code<<endl;
		if(temp->left!=NULL)
		{
			(temp->left)->code=temp->code+='0';
			q.QInsert(temp->left);
		}
		
		if(temp->right!=NULL)
		{
			(temp->right)->code=temp->code+='1';
			q.QInsert(temp->right);
		}
	} 
}


int main()
{
	
	HuffmanNode<char> *root;
    Huffman<char> *tree = new Huffman<char>(root);
    root=tree->CreateHuffman();
    tree->SetRoot(root);
    cout<<"Huffman���Ѿ�������"<<endl;
    tree->CodeNode();
    
 } 



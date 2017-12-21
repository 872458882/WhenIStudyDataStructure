#include <iostream>
#include <fstream>
#include <memory.h> 
#include <string>
#include"queue.h"//之前写的类 
#include"stack.h" //之前写的类 
using namespace std;






template <class T>
class Huffman;

//========================================
//Huffman树节点类声明
template <class T>
class HuffmanNode
{ 
private:    
	T data;
    int weight;
    HuffmanNode<T>  *left,*right;//指向左右子树的指针
    string code;

public:
	friend class Huffman<T>;  
    //构造函数
    HuffmanNode(const T& item,const int& w=0,HuffmanNode *lptr=NULL,HuffmanNode *rptr=NULL):
        data(item),weight(w),left(lptr),right(rptr){}

    HuffmanNode<T> * GetLeft()const{return left;}//返回左子节点

    void SetLeft(HuffmanNode<T> * L){left=L;}//设置左子节点

    HuffmanNode<T> * GetRight()const{return right;}//返回右子节点

    void SetRight(HuffmanNode<T> * R){right=R;}//设置右子节点

    T GetData(){return data;}

    void SetData(T item){data=item;}

	int GetWeight(){return weight;}
	
	void SetWeight(int w){weight=w;}

};



//===============================================================
//Huffman树类

#define m 128
template <class T>
class Huffman
{
private:
    HuffmanNode<T> *root;//根结点的声明
	T data[m];
    int weight[m];
    string Huffcode[m];
    int number;//当前有多少种字符 
public:
    Huffman(HuffmanNode<T>*t=NULL):root(t){}//构造函数

    virtual ~Huffman(){Del(root);}//析构函数 删除整棵Huffman树

    //创建Huffman树
    HuffmanNode<T>* CreateHuffman();//创建huffman树 
    
    void CodeNode();//给出每个结点的huffman编码 
	
	void Read(string txtname); 
	
	void Del(HuffmanNode<T>*t);
	
	void sort(T Data[],int pData[],int left,int right);
    
    HuffmanNode<T>* GetRoot(){return root;}
    void SetRoot(HuffmanNode<T> * t){root=t;}
    bool IsEmpty(){return root==NULL;}
    
    void Input(); 
    
};



//======================================
//创建树 
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
		//把新节点插入到H中 
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
	cout<<"按出现次数由小到大:\n";
	sort(data,weight,0,number-1); 
	for(int i=0;i<number-1;i++)
	{
		cout<<"\'"<<data[i]<<"\'"<<":"<<weight[i]<<endl;
	} 
}



//=============================================
//读取文本统计每个字符出现的次数 
template <class T>
void Huffman<T>::Read(string txtname)
{

	int TIMES[128];
	memset(TIMES,0,sizeof(TIMES));
	
	ifstream infile;
	infile.open(txtname);
	
	//统计每个字符出现的次数 
	if(infile.is_open())
	{ 
		
		while(infile.good() && !infile.eof())
		{
			char c=infile.get();
			TIMES[c]++;
		}
	}
	infile.close(); 
	
	cout<<"文件"<<txtname<<"中的字符及其出现次数：\n"; 
	
	//清理多余字符 
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
//排序算法 
template <class T>
void Huffman<T>::sort(T Data[],int pData[],int left,int right) 
{ 	
	int i,j;
	int iTemp;
	T Temp;
	i=left; 
	j=right; 
	int middle=(left+right)/2;//枢纽元 
	while(i<=j)
	{
		while((pData[i]<middle) && (i<right))//从左扫描大于中值的数 
			i++;
		while((pData[j]>middle) && (j>left))//从右扫描大于中值的数 
			j--; 
		if(i<=j)//找到了一对值 
		{	 
			//交换 
			iTemp = pData[i]; 
			pData[i] = pData[j]; 
			pData[j] = iTemp; 
			Temp = Data[i]; 
			Data[i] = Data[j]; 
			Data[j] = Temp; 
			i++; 
			j--; 
		} 
	}//如果两边扫描的下标交错，就停止（完成一次） 

	//当左边部分有值(left＜j)，递归左半边 
 	if(left<j) 
		sort(Data,pData,left,j); 
	//当右边部分有值(right＞i)，递归右半边 
 	if(right>i) 
		sort(Data,pData,i,right); 
}


//========================================
//删除结点及其左右子树
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
void Huffman<T>::CodeNode() //每个节点生成huffman编码 
{
	cout<<"每个字符的Huffman编码如下：\n"; 
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
    cout<<"Huffman树已经创建好"<<endl;
    tree->CodeNode();
    
 } 



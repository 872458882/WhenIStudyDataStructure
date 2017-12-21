#include <iostream>
#include <memory.h>
#include "queue.h"//之前写的类 
#include "stack.h" //之前写的类 
#include <cmath>
#include <cstdio>
#include <string>
#include <cstring>
#include <time.h>
#include <sys/timeb.h>

using namespace std;


int error=0;
int suctime=0;



template <class T>
class BST;

//========================================
//二叉树节点类声明
template <class T>
class BSTNode
{ 
private:
    BSTNode<T>  *left,*right;//指向左右子树的指针
    T data;//数据
public:
	friend class BST<T>;  
    //构造函数
    BSTNode(const T& item,BSTNode *lptr=NULL,BSTNode *rptr=NULL):
        data(item),left(lptr),right(rptr){}

    BSTNode<T> * GetLeft()const{return left;}//返回左子节点

    void SetLeft(BSTNode<T> * L){left=L;}//设置左子节点

    BSTNode<T> * GetRight()const{return right;}//返回右子节点

    void SetRight(BSTNode<T> * R){right=R;}//设置右子节点

    T GetData(){return data;}

    void SetData(T item){data=item;}


};



//===============================================================
//二叉树类的声明

template <class T>
class BST
{
private:
    BSTNode<T> *root;//根结点的声明
	T Number[15];
public:
    BST():root(NULL){}//构造函数

    virtual ~BST(){Del(root);}//析构函数 删除整棵二叉树

    //在以节点t为根节点的子树中查找data域为item的结点(first)
    BSTNode<T>  *Find(const T&item);

	BSTNode<T>  *Insert(const T&item);

    //在以节点t为根节点的子树中搜索节点p的父节点
    BSTNode<T> * Father(BSTNode<T> *t,BSTNode<T> *p)const;

    //删除节点t及其左右子树
    void Del(BSTNode<T> *t);



    //中根遍历并输出以节点t为根节点的子树
    void InOrder( BSTNode<T> *t)const;


    //非递归中根遍历并输出以节点t为根节点的子树
   	void NoreInOrder(BSTNode<T> *t)const;


    //非递归层次遍历并输出以节点t为根节点的子树
    void NoreLevelOrder(BSTNode<T> *t);
    
    void DelLarge(BSTNode<T> *t);

    //创建二叉树
    BSTNode<T>* CreateBST();
		

	void getRandom(); 

    //其它操作
    BSTNode<T>* GetRoot(){return root;}
    void SetRoot(BSTNode<T> * t){root=t;}
    bool IsEmpty(){return root==NULL;}
    bool IsFull(BSTNode<T>*t); 
    void CompareTime();
    void output();

};

template <class T>
void BST<T>::output()
{

	cout<<"二叉树的中根遍历的序列为：";
    InOrder(GetRoot());
    cout<<endl;
    
         
    cout<<"二叉树的层次遍历的序列为：";
    NoreLevelOrder(GetRoot());
    cout<<endl;
}

template <class T>
void BST<T>::getRandom()
{
	for(int i=0;i<15;i++)
	{
		Number[i]=rand()%1000+1;
		cout<<Number[i]<<" ";
	}
	cout<<endl;
}


//=======================================
//在以节点t为根节点的子树中查找data域为item的结点
template <class T>
BSTNode<T>* BST<T>::Insert(const T&item)
{
    BSTNode<T>*p=root;
    BSTNode<T>*q=NULL;
    if(p!=NULL)
	{
		while(p!=NULL)
	    {
	    	if(p->GetData()==item) 
	    	{
	    		//cout<<"已经找到"<<item<<endl;
				return p;
			}
			if(item<p->GetData())
			{
				if(p->GetLeft()!=NULL)
					p=p->GetLeft();
				else 
				{
					//cout<<"未找到"<<item<<endl;
					break;
				}
			}
			if(item>p->GetData())
			{
				if(p->GetRight()!=NULL)
					p=p->GetRight();
				else 
				{
					//cout<<"未找到"<<item<<endl;
					break;
				}
			}
		}
		BSTNode<T>*q=new BSTNode<T>(item,NULL,NULL); 
		//插入
		if(item < p->GetData())
			p->SetLeft(q);
		else 
			p->SetRight(q);
	}
	else
	{
		root=q=new BSTNode<T>(item,NULL,NULL);
	}
	return q;
}



//======================================
//创建树 
template <class T>
BSTNode<T>* BST<T>::CreateBST() {
	for(int i=0;i<15;i++)
	{
	    Insert(Number[i]);
	}
	return root;
}




//=======================================
//在以节点t为根节点的子树中查找data域为item的结点
template <class T>
BSTNode<T>* BST<T>::Find(const T&item)
{
    BSTNode<T>*p=root;
    BSTNode<T>*q=NULL;
	int compare=0;
	if(p==NULL){
		return NULL;
	}
	else
		while(p!=NULL)
	    {
	    	compare++;
	    	if(p->GetData()==item) 
	    	{
	    		//cout<<"已经找到"<<item<<endl;
				suctime+=compare;
				return p;
			}
			compare++;
			if(item<p->GetData())
			{
				if(p->GetLeft()!=NULL)
					p=p->GetLeft();
				else 
				{
					//cout<<"未找到"<<item<<endl;
					error+=compare;
					break;
				}
			}
			compare++;
			if(item>p->GetData())
			{
				if(p->GetRight()!=NULL)
					p=p->GetRight();
				else 
				{
					//cout<<"未找到"<<item<<endl;
					error+=compare;
					break;
				}
			}
		}
	return q;
	
}



//中序遍历二叉树  
template <class T>
void BST<T>::InOrder( BSTNode<T>* t) const {
   	if(t == NULL) {
      	return;
   	}
   	InOrder(t->GetLeft());
   	cout<<t->GetData()<<" ";
   	InOrder(t->GetRight());
}

template <class T>
void BST<T>::NoreInOrder(BSTNode<T>* t) const{
    LStack<BSTNode<T>*> q;
    if(t!=NULL) {
       	q.Push(t);
   	}
    BSTNode<T> *node;
    while(!q.IsEmpty()) {
    	if(node->GetLeft() != NULL) {
         	q.Push(node->GetLeft());
      	}
      	q.Pop(node);
      	cout<<node->GetData()<<" ";
      	if(node->GetRight() != NULL) {
         	q.Push(node->GetRight());
      	}
   	}
}


//======================================
//层次遍历，非递归 
template <class T>
void BST<T>::NoreLevelOrder(BSTNode<T>*t)
{
	cout<<endl;
	int flag=0;
	int num[100];
	memset(num,0,sizeof(num));
	LQueue<BSTNode<T>*> q;
    if(t!=NULL) {
       	q.QInsert(t);
		q.QInsert(NULL); 
   	}
    BSTNode<T> *node;
    while(!q.IsEmpty()) {
      	q.QDelete(node);
      	if(node==NULL)
      	{
      		if(flag==1) break;//如果上一个出队的也是NULL,则退出循环 
      		q.QInsert(NULL);	
      		flag=1; 
      		cout<<endl;
			continue;
		}
      	cout<<node->GetData()<<" ";
      	if(node->GetLeft() != NULL) {
         	q.QInsert(node->GetLeft());
      	}
      	if(node->GetRight() != NULL) {
         	q.QInsert(node->GetRight());
      	}
      	flag=0;
   	}
}



//========================================
//删除结点及其左右子树
template <class T>
void BST<T>::Del(BSTNode<T> *t)
{
	if(t != NULL) {
    Del(t->GetLeft());
    Del(t->GetRight());
    delete t;
	}

}	 

template <class T>
void BST<T>::CompareTime()
{
 	cout<<"查找成功的平均比较次数："<<endl;
 	for(int i=0;i<15;i++)
 		Find(Number[i]);
 	cout<<suctime/15.0<<endl;
 	
 	T Numbererror[16];
 	Numbererror[0]=0;
 	Numbererror[15]=1000;
 	for(int i=1;i<15;i++)
 		Numbererror[i]=Number[i]+rand()%(Number[i]-Number[i-1]);
 	for(int i=0;i<16;i++)
 		Find(Numbererror[i]);
 	cout<<"查找失败的平均比较次数:"<<endl;
 	cout<<error/16.0<<endl;
 	
 }

int main() {
	srand((unsigned)time(NULL));
	
	BSTNode<int> *root=NULL;
    BST<int> *tree = new BST<int>();
   
	tree->getRandom(); 
	cout<<"创建树"<<endl;
    root=tree->CreateBST();
    cout<<"BST创建成功"<<endl;
	tree->output();
	
	tree->CompareTime();
	
	return 0;
}

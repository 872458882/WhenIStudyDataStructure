#include <iostream>
#include"queue.h"//之前写的类 
#include"stack.h" //之前写的类 
using namespace std;

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
//二叉树类Bindoubleree的声明

template <class T>
class BST
{
private:
    BSTNode<T> *root;//根结点的声明
   
    
public:int adata; int n;
    BST(BSTNode<T>*t=NULL):root(t),adata(0),n(0){}//构造函数

    virtual ~BST(){Del(root);}//析构函数 删除整棵二叉树

    //在以节点t为根节点的子树中查找data域为item的结点(first)
    BSTNode<T>  *Find(BSTNode<T> *t,const T&item);

    //在以节点t为根节点的子树中搜索节点p的父节点
    BSTNode<T> * Father(BSTNode<T> *t,BSTNode<T> *p)const;

    //删除节点t及其左右子树
    void Del(BSTNode<T> *t);

    //先根遍历并输出以节点t为根节点的子树
    void PreOrder( BSTNode<T> *t)const;

    //中根遍历并输出以节点t为根节点的子树
    void InOrder( BSTNode<T> *t)const;

    //后根遍历并输出以节点t为根节点的子树
    void PostOrder(BSTNode<T> *t)const;

    //层次遍历并输出以节点t为根节点的子树
    //void LevelOrder(BSTNode<T> *t)const;

    //非递归先根遍历并输出以节点t为根节点的子树
   	void NorePreOrder(BSTNode<T> *t)const;

    //非递归中根遍历并输出以节点t为根节点的子树
   	void NoreInOrder(BSTNode<T> *t)const;

    //非递归后根遍历并输出以节点t为根节点的子树
  	void NorePostOrder(BSTNode<T> *t)const;

    //非递归层次遍历并输出以节点t为根节点的子树
    void NoreLevelOrder(BSTNode<T> *t)const;
    
    void DelLarge(BSTNode<T> *t);

    //创建二叉树
    BSTNode<T>* CreateBST();
    
    
    //其它操作
    BSTNode<T>* GetRoot(){return root;}
    void SetRoot(BSTNode<T> * t){root=t;}
    bool IsEmpty(){return root==NULL;}
    bool IsFull(BSTNode<T>*t); 
    
    void output();

};

template <class T>
void BST<T>::output()
{
	cout<<"二叉树的先根遍历的序列为：";
    PreOrder(GetRoot());
    cout<<endl;
    
	cout<<"二叉树的中根遍历的序列为：";
    InOrder(GetRoot());
    cout<<endl;
    
    cout<<"二叉树的后根遍历的序列为：";
    PostOrder(GetRoot());
    cout<<endl;
         
    cout<<"二叉树的层次遍历的序列为：";
    NoreLevelOrder(GetRoot());
    cout<<endl;
}


//=======================================
//在以节点t为根节点的子树中查找data域为item的结点
template <class T>
BSTNode<T>* BST<T>::Find(BSTNode<T> *t,const T&item)
{
    BSTNode<T>*p=t;
    while(p!=NULL)
    {
    	if(p->GetData()==item) 
    	{
    		cout<<"已经找到"<<item<<endl;
			return p;
		}
		if(item<p->GetData())
		{
			if(p->GetLeft()!=NULL)
				p=p->GetLeft();
			else 
			{
				cout<<"未找到"<<item<<endl;
				break;
			}
		}
		if(item>p->GetData())
		{
			if(p->GetRight()!=NULL)
				p=p->GetRight();
			else 
			{
				cout<<"未找到"<<item<<endl;
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
	adata=(n*adata+p->GetData())/(n+1);
	n++;
	cout<<"new adata"<<adata;
}



//======================================
//创建树 
template <class T>
BSTNode<T>* BST<T>::CreateBST() {
   	BSTNode<T>* t;
   	T data;
   	cin>>data;
   	//每个叶结点外补两个虚叶结点
   	if(data == 999) {
      return NULL;
   	} 
	else 
	{
		if(!(t=new BSTNode<T>(data,NULL,NULL))) return NULL;
      	t->SetLeft(CreateBST());
      	t->SetRight(CreateBST());
      	adata=(adata*n+data)/(++n);
      	return t;
   }
}


//=============================================================
//先序遍历二叉树  
template <class T>
void BST<T>::PreOrder( BSTNode<T>* t) const {
   if(t == NULL) {
      return;
   }
   cout<<t->GetData()<<" ";
   PreOrder(t->GetLeft());
   PreOrder(t->GetRight());

}

template <class T>
void BST<T>::NorePreOrder(BSTNode<T>* t) const{
    LStack<BSTNode<T>*> q;
    if(t!=NULL) {
       	q.Push(t);
   	}
    BSTNode<T> *node;
    while(!q.IsEmpty()) {
      	q.Pop(node);
      	cout<<node->GetData()<<" ";
      	if(node->GetLeft() != NULL) {
         	q.Push(node->GetLeft());
      	}
      	if(node->GetRight() != NULL) {
         	q.Push(node->GetRight());
      	}
   	}
}
//=========================================

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
//=========================================== 
//后序遍历二叉树
template <class T>
void BST<T>::PostOrder(BSTNode<T>* t) const {
   if(t == NULL) {
      return;
   }
   PostOrder(t->GetLeft());
   PostOrder(t->GetRight());
   cout<<t->GetData()<<" ";
}


template <class T>
void BST<T>::NorePostOrder(BSTNode<T>* t) const{
    LStack<BSTNode<T>*> q;
    if(t!=NULL) {
       	q.Push(t);
   	}
    BSTNode<T> *node;
    while(!q.IsEmpty()) {
    	if(node->GetLeft() != NULL) {
         	q.Push(node->GetLeft());
      	}
      	
      	if(node->GetRight() != NULL) {
         	q.Push(node->GetRight());
      	}
      	
      	q.Pop(node);
   		cout<<node->GetData()<<" ";
	}
}
//======================================
//层次遍历，非递归 
template <class T>
void BST<T>::NoreLevelOrder(BSTNode<T>* t) const{
    LQueue<BSTNode<T>*> q;
    if(t!=NULL) {
       	q.QInsert(t);
   	}
    BSTNode<T> *node;
    while(!q.IsEmpty()) {
      	q.QDelete(node);
      	cout<<node->GetData()<<" ";
      	if(node->GetLeft() != NULL) {
         	q.QInsert(node->GetLeft());
      	}
      	if(node->GetRight() != NULL) {
         	q.QInsert(node->GetRight());
      	}
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
	adata= 0;
	n=0;
}	 

template <class T>
void BST<T>::DelLarge(BSTNode<T> *t)
{
	BSTNode<T>*p=t,*f=t;
	while(p->GetRight()!=NULL)
	{
		f=p;
		p=p->GetRight();
		getchar();
	}
	f->SetRight(p->GetLeft());
	adata=(adata*n-p->GetData())/(--n);
	delete p;
	cout<<"删除成功"<<endl; 
}

int main()
{
	BSTNode<int> *root;
    BST<int> *tree = new BST<int>(root);
    cout<<"创建树"<<endl;
    root=tree->CreateBST();
    tree->SetRoot(root);
    cout<<"二叉树已经创建好"<<endl;
    cout<<tree->adata;
	tree->output();
    BSTNode<int> *node, *temp;
    int ch; 
    cout<<"请输入所需要查找的结点的值";
    getchar();
	cin>>ch;
    node = tree->Find(tree->GetRoot(), ch);
    tree->output();
    cout<<"请输入所需要查找的结点的值";
    getchar();
	cin>>ch;
    node = tree->Find(tree->GetRoot(), ch);
    tree->output();
    cout<<"删除最大结点"<<endl;
    tree->DelLarge(tree->GetRoot());
    tree->output();
 } 


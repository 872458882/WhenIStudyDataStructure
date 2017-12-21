/*
1、 定义链接存储的二叉树类。
2、 实验验证如下算法的正确性、各种功能及指标：
1）创建一棵二叉树，并对其初始化；
2）先根、中根、后根遍历二叉树；
3）在二叉树中搜索给定结点的父结点；
4）搜索二叉树中符合数据域条件的结点；
3、 由教师随机指定树结构，测试上述功能
*/

#include <iostream>
#include <memory.h>
#include"queue.h"//之前写的类 
#include"stack.h" //之前写的类 
using namespace std;

template <class T>
class BinTree;

//========================================
//二叉树节点类声明
template <class T>
class BinTreeNode
{ 
private:
    BinTreeNode<T>  *left,*right;//指向左右子树的指针
    T data;//数据
public:
	friend class BinTree<T>;  
    //构造函数
    BinTreeNode(const T& item,BinTreeNode *lptr=NULL,BinTreeNode *rptr=NULL):
        data(item),left(lptr),right(rptr){}

    BinTreeNode<T> * GetLeft()const{return left;}//返回左子节点

    void SetLeft(BinTreeNode<T> * L){left=L;}//设置左子节点

    BinTreeNode<T> * GetRight()const{return right;}//返回右子节点

    void SetRight(BinTreeNode<T> * R){right=R;}//设置右子节点

    T GetData(){return data;}

    void SetData(T item){data=item;}


};



//===============================================================
//二叉树类Bindoubleree的声明

template <class T>
class BinTree
{
private:
    BinTreeNode<T> *root;//根结点的声明
public:
    BinTree(BinTreeNode<T>*t=NULL):root(t){}//构造函数

    virtual ~BinTree(){Del(root);}//析构函数 删除整棵二叉树

    //在以节点t为根节点的子树中查找data域为item的结点(first)
    BinTreeNode<T>  *Find(BinTreeNode<T> *t,const T&item)const;

    //在以节点t为根节点的子树中搜索节点p的父节点
    BinTreeNode<T> * Father(BinTreeNode<T> *t,BinTreeNode<T> *p)const;

    //删除节点t及其左右子树
    void Del(BinTreeNode<T> *t);

    //先根遍历并输出以节点t为根节点的子树
    void PreOrder( BinTreeNode<T> *t)const;

    //中根遍历并输出以节点t为根节点的子树
    void InOrder( BinTreeNode<T> *t)const;

    //后根遍历并输出以节点t为根节点的子树
    void PostOrder(BinTreeNode<T> *t)const;

    //层次遍历并输出以节点t为根节点的子树
    //void LevelOrder(BinTreeNode<T> *t)const;

    //非递归先根遍历并输出以节点t为根节点的子树
   	void NorePreOrder(BinTreeNode<T> *t)const;

    //非递归中根遍历并输出以节点t为根节点的子树
   	void NoreInOrder(BinTreeNode<T> *t)const;

    //非递归后根遍历并输出以节点t为根节点的子树
  	void NorePostOrder(BinTreeNode<T> *t)const;

    //非递归层次遍历并输出以节点t为根节点的子树
    void NoreLevelOrder(BinTreeNode<T> *t)const;

    //创建二叉树
    BinTreeNode<T>* CreateBinTree();
    
    //输出每层节点个数or第k层 
	int getLevelNodeNum(BinTreeNode<T>*t,int k);
    
    
    //其它操作
    BinTreeNode<T>* GetRoot(){return root;}
    void SetRoot(BinTreeNode<T> * t){root=t;}
    bool IsEmpty(){return root==NULL;}
    
    //判断是否完全二叉树 
    bool IsFull(BinTreeNode<T>*t); 
    
    void output();

};

template <class T>
void BinTree<T>::output()
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
BinTreeNode<T>* BinTree<T>::Find(BinTreeNode<T> *t,const T&item)const
{
    BinTreeNode<T> * p;
    //递归出口
    if(t==NULL)return NULL;
    if(t->GetData()==item) return t;
    //递归
    p=Find(t->GetLeft(),item);
    if(p!=NULL) return p;
    p=Find(t->GetRight(),item);
    if(p!=NULL) return p;
    return NULL;
}


//在以节点t为根节点的子树中搜索节点p的父结点
template <class T>
BinTreeNode<T>* BinTree<T>::Father(BinTreeNode<T>* t,BinTreeNode<T>*p)const
{
{
	BinTreeNode<T>*f=NULL;
	if(t==NULL||p==NULL) 
		return NULL;
	if(t->GetLeft()==p||t->GetRight()==p) 
		return t;
	f=Father(t->GetLeft(),p);
	if(f!=NULL) 
		return f;
	f=Father(t->GetRight(),p);
    if(f!=NULL) 
		return f;
	return NULL;
}
}

//======================================
//创建树 
template <class T>
BinTreeNode<T>* BinTree<T>::CreateBinTree() {
   	BinTreeNode<T>* t;
   	T data;
   	cin>>data;
   	//每个叶结点外补两个虚叶结点
   	if(data == '#') {
      t = NULL;
      return t;
   	} else {
      	if(!(t = new BinTreeNode<T>(data))) {
         	return NULL;
      	}
      	t->SetLeft(CreateBinTree());
      	t->SetRight(CreateBinTree());
      	return t;
   }
}


//=============================================================
//先序遍历二叉树  
template <class T>
void BinTree<T>::PreOrder( BinTreeNode<T>* t) const {
   if(t == NULL) {
      return;
   }
   cout<<t->GetData()<<" ";
   PreOrder(t->GetLeft());
   PreOrder(t->GetRight());

}

template <class T>
void BinTree<T>::NorePreOrder(BinTreeNode<T>* t) const{
    LStack<BinTreeNode<T>*> q;
    if(t!=NULL) {
       	q.Push(t);
   	}
    BinTreeNode<T> *node;
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
void BinTree<T>::InOrder( BinTreeNode<T>* t) const {
   	if(t == NULL) {
      	return;
   	}
   	InOrder(t->GetLeft());
   	cout<<t->GetData()<<" ";
   	InOrder(t->GetRight());
}

template <class T>
void BinTree<T>::NoreInOrder(BinTreeNode<T>* t) const{
    LStack<BinTreeNode<T>*> q;
    if(t!=NULL) {
       	q.Push(t);
   	}
    BinTreeNode<T> *node;
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
void BinTree<T>::PostOrder(BinTreeNode<T>* t) const {
   if(t == NULL) {
      return;
   }
   PostOrder(t->GetLeft());
   PostOrder(t->GetRight());
   cout<<t->GetData()<<" ";
}


template <class T>
void BinTree<T>::NorePostOrder(BinTreeNode<T>* t) const{
    LStack<BinTreeNode<T>*> q;
    if(t!=NULL) {
       	q.Push(t);
   	}
    BinTreeNode<T> *node;
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
void BinTree<T>::NoreLevelOrder(BinTreeNode<T>* t) const{
    LQueue<BinTreeNode<T>*> q;
    if(t!=NULL) {
       	q.QInsert(t);
   	}
    BinTreeNode<T> *node;
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
void BinTree<T>::Del(BinTreeNode<T> *t)
{
	if(t != NULL) {
    Del(t->GetLeft());
    Del(t->GetRight());
    delete t;
	}
}	 


template <class T>
bool BinTree<T>::IsFull(BinTreeNode<T>* t)//判断二叉树是否完全二叉树 是则返回1,否则返回0
{ 
    bool flag=0;
	LQueue<BinTreeNode<T>*> q;
    if(t!=NULL) {
       	q.QInsert(t);
   	}
    BinTreeNode<T> *node;
    while(!q.IsEmpty()) {
      	q.QDelete(node);
      	if (node==NULL){
		  	flag=1;
      	}else if(flag) {
			cout<<"非完全二叉树"<<endl;
			return 0;
      	}else{
			q.QInsert(node->GetLeft());
			q.QInsert(node->GetRight());
		}
	}
	cout<<"是完全二叉树"<<endl;
	return 1;
	
}


template <class T>
int BinTree<T>::getLevelNodeNum(BinTreeNode<T>*t,int k)
{
	int flag=0;
	int i=0;
	int num[100];
	memset(num,0,sizeof(num));
	LQueue<BinTreeNode<T>*> q;
    if(t!=NULL) {
       	q.QInsert(t);
		q.QInsert(NULL); 
   	}
    BinTreeNode<T> *node;
    while(!q.IsEmpty()) {
      	q.QDelete(node);
      	if(node==NULL)
      	{
      		if(flag==1) break;//如果上一个出队的也是NULL,则退出循环 
      		
			//if(k==i)
      		//{cout<<"第"<<k<<"层的结点数为："<<num[k]<<endl; return num[k];}
    		
			cout<<"第"<<i<<"层的结点数为"<<num[i++]<<endl; 
      		q.QInsert(NULL);	
      		flag=1; 
			continue;
		}
      	//cout<<node->GetData()<<" ";
      	num[i]++;
      	if(node->GetLeft() != NULL) {
         	q.QInsert(node->GetLeft());
      	}
      	if(node->GetRight() != NULL) {
         	q.QInsert(node->GetRight());
      	}
      	flag=0;
   	}
   	
   	//cout<<"第"<<k<<"层的结点数为："<<num[k]<<endl; 
   	return 1;
}


//重建二叉树
template <class T>
BinTreeNode<T>* ReBuildTree(T *preOrder, T *inOrder, int n){
	if(preOrder == NULL || inOrder == NULL || n <= 0){
	   return NULL;
	}
	BinTreeNode<T> *root = new BinTreeNode<T>();
	root->value = preOrder[0];
	root->left = NULL;
	root->right = NULL;
	//找到中序遍历中根节点的位置
	int index = 0;
	while(index < n && preOrder[0] != inOrder[index]){
	    ++index;
	}
	//不合法数据
	if(index >= n){
	    return NULL;
	}
	root->left = ReBuildTree(preOrder+1, inOrder, index);
	root->right = ReBuildTree(preOrder+1+index, inOrder+1+index, n-index-1);
	return root;
}


void LongestPath(BiTree bt)//求二叉树中的第一条最长路径长度,并输出最长路径上的节点
{
	BiTree p = bt, l[MaxSize], s[MaxSize]; //l, s是栈，元素是二叉树结点指针，l中保留当前最长路径中的结点
	int i,top = 0, tag[MaxSize], longest = 0;
	while (p || top >0)
	{
		while (p)
		{
			s[++top] = p;
			tag[top] = 0;
			p = p->lchild;
		} //沿左分枝向下
		if (tag[top] == 1)    //当前结点的右分枝已遍历
		{
			if (!s[top]->lchild && !s[top]->rchild)  //只有到叶子结点时，才查看路径长度
				if (top>longest)
				{
					for (i = 1; i <= top; i++)
						l[i] = s[i];
					longest = top;
					top--;
				}//保留当前最长路径到l栈，记住最高栈顶指针，退栈
		}
		else if (top>0)
		{
			tag[top] = 1;
			p = s[top]->rchild;
		}   //沿右子分枝向下
	}//while(p!=null||top>0)
	int k = 0;
	for (k = 0; k < longest; k++)
	{
		printf("%d ", l[k]->data);
	}
}//结束LongestPath






int main()
{
	BinTreeNode<char> *root;
    BinTree<char> *tree = new BinTree<char>(root);
    root=tree->CreateBinTree();
    tree->SetRoot(root);
    cout<<"二叉树已经创建好"<<endl;
    tree->output();
    //tree->NorePreOrder(root);
    //tree->NoreInOrder(root);
    //tree->NorePostOrder(root);
    BinTreeNode<char> *node, *temp;
    char ch; 
    cout<<"请输入所需要查找的结点的值";
    cin>>ch;
    node = tree->Find(tree->GetRoot(), ch);
    if(node != NULL) {
        cout<<"找到结点"<<endl;
    } else {
        cout<<"未找到结点"<<endl;
    }
    cout<<"查找结点p的父节点,请输入结点p的值"<<endl;
    cin>>ch;
    node = tree->Find(tree->GetRoot(), ch);
    temp = tree->Father(tree->GetRoot(), node);
    if(temp != NULL) {
        cout<<"值为"<<node->GetData()<<"的结点的父结点的值为"<<temp->GetData()<<endl;
    } else {
        cout<<"未找到p的父节点"<<endl;
    }
    tree->IsFull(tree->GetRoot()); 
    tree->getLevelNodeNum(tree->GetRoot(),3);
 } 


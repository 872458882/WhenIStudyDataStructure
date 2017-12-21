#include <iostream>
#include"queue.h" 
#include"stack.h"  
using namespace std;

template <class T>
class Tree;



//========================================
// 树节点类声明
template <class T>
class TreeNode
{ 
private:
    TreeNode<T>  *firstChild,*nextBrother;
	//指向大孩子结点的指针和指向大兄弟结点的指针 
    T data;//数据
public:
	friend class Tree<T>;  
    //构造函数
    TreeNode(const T& item,TreeNode *lptr=NULL,TreeNode *rptr=NULL):
        data(item),firstChild(lptr),nextBrother(rptr){}

    TreeNode<T> * GetFirstChild()const{return firstChild;}//返回大儿子节点

    void SetFirstChild(TreeNode<T> * L){firstChild=L;}//设置大儿子结点 

    TreeNode<T> * GetNextBrother()const{return nextBrother;}//返回大兄弟节点

    void SetNextBrother(TreeNode<T> * R){nextBrother=R;}//设置大兄弟节点

    T GetData(){return data;}

    void SetData(T item){data=item;}


};



//===============================================================
// 树类的声明

template <class T>
class Tree
{
private:
    TreeNode<T> *root;//根结点的声明
	T stop; 
public:
	
    Tree(TreeNode<T>*t=NULL):root(t),stop('*'){}//构造函数

    virtual ~Tree(){Del(root);}//析构函数 删除整棵 树

    //在以节点t为根节点的子树中查找data域为item的结点
    TreeNode<T>  *Find(TreeNode<T> *t,const T&item)const;

    //在以节点t为根节点的子树中搜索节点p的父节点
    TreeNode<T> * Father(TreeNode<T> *t,TreeNode<T> *p)const;

	//在以节点t为根节点的子树中删除节点t及其子树
	void DelSubTree(TreeNode<T>* t,TreeNode<T> *p);
	 
    //删除节点t及其子树
    void Del(TreeNode<T> *t);

    //先根遍历并输出以节点t为根节点的子树
    void PreOrder( TreeNode<T> *t)const;

    //后根遍历并输出以节点t为根节点的子树
    void PostOrder(TreeNode<T> *t)const;


    //非递归先根遍历并输出以节点t为根节点的子树
   	void NorePreOrder(TreeNode<T> *t)const;

    //非递归后根遍历并输出以节点t为根节点的子树
  	void NorePostOrder(TreeNode<T> *t)const;

    //非递归层次遍历并输出以节点t为根节点的子树
    void NoreLevelOrder(TreeNode<T> *t)const;


    //创建树
    TreeNode<T>* CreateTree();
    
    
    //其它操作
    TreeNode<T>* GetRoot(){return root;}
    void SetRoot(TreeNode<T> * t){root=t;}
    bool IsEmpty(){return root==NULL;}
    
    void output();

};

template <class T>
void Tree<T>::output()
{
	cout<<" 树的先根遍历的序列为：";
    PreOrder(GetRoot());
    cout<<endl;
    
    
    cout<<" 树的后根遍历的序列为：";
    PostOrder(GetRoot());
    cout<<endl;
         
    cout<<" 树的层次遍历的序列为：";
    NoreLevelOrder(GetRoot());
    cout<<endl;
}


//=======================================
//在以节点t为根节点的子树中查找data域为item的结点
template <class T>
TreeNode<T>* Tree<T>::Find(TreeNode<T> *t,const T&item)const
{
    TreeNode<T> * p;
    //递归出口
    if(t==NULL)return NULL;
    if(t->GetData()==item) return t;
    //递归
    p=Find(t->GetFirstChild(),item);
    if(p!=NULL) return p;
    
    p=Find(t->GetNextBrother(),item);
    if(p!=NULL) return p;
    
	return NULL;
}


//在以节点t为根节点的子树中搜索节点p的父结点
template <class T>
TreeNode<T>* Tree<T>::Father(TreeNode<T>* t,TreeNode<T>*p)const
{
	
	
	if(t==NULL||p==NULL)//若t，p中有一个为空 
		return NULL;
	if(p==root) return NULL; //若t是根结点则没有父节点 
	
	TreeNode<T>*result=NULL;
	TreeNode<T>*q=t->GetFirstChild();//从第一棵子树开始搜索 
	while(q!=NULL&&q!=p)
	{
		result=Father(q,p);
		if(!result) q=q->GetNextBrother();
		else return result;
	}			
	if(q==p) return t;		
	return NULL;
}

//======================================
//非递归创建树 
template <class T>
TreeNode<T>* Tree<T>::CreateTree() {
	
	LQueue<TreeNode<T>*> Q;
	
	//处理根结点
	//cout<<"输入根结点，并回车\n"; 
	cout<<"输入根结点\n" ;
	T item;
	//item=getchar();
	cin>>item;
	if(item==stop)
		return NULL;
	root=new TreeNode<T>(item);
	Q.QInsert(root);
	
	
	TreeNode<T>* node;
	TreeNode<T>* child; 
	while(!Q.IsEmpty())
	{
		
		Q.QDelete(node);
		//getchar();//过滤回车
		//cout<<"输入"<<node->GetData()<<"的子节点( 用*结尾)，并回车\n"; 
		//item=getchar();
		cout<<"输入"<<node->GetData()<<"的子节点\n";
		cin>>item;
		while(item!=stop)
		{
			if(node->GetFirstChild()==NULL)
			{
				 
				child=new TreeNode<T>(item);
				node->SetFirstChild(child);
				Q.QInsert(child);
				//item=getchar();
			}
			else
			{
				TreeNode<T>*nextchild=new TreeNode<T>(item);
				child->SetNextBrother(nextchild);
				Q.QInsert(nextchild);
				child=nextchild;
				//item=getchar();
			}
			cin>>item;
		}
	}
	output();
	return root;
}


//=============================================================
//先序遍历树  
template <class T>
void Tree<T>::PreOrder( TreeNode<T>* t) const {
   if(t == NULL) {
      return;
   }
   cout<<t->GetData()<<" ";
   PreOrder(t->GetFirstChild());
   PreOrder(t->GetNextBrother());

}

template <class T>
void Tree<T>::NorePreOrder(TreeNode<T>* t) const{
    LStack<TreeNode<T>*> q;
    if(t!=NULL) {
       	q.Push(t);
   	}
    TreeNode<T> *node;
    while(!q.IsEmpty()) {
      	q.Pop(node);
      	cout<<node->GetData()<<" ";
      	if(node->GetFirstChild() != NULL) {
         	q.Push(node->GetFirstChild());
      	}
      	if(node->GetNextBrother() != NULL) {
         	q.Push(node->GetNextBrother());
      	}
   	}
}
//=========================================

//后序遍历树  
template <class T>
void Tree<T>::PostOrder( TreeNode<T>* t) const {
   	if(t == NULL) {
      	return;
   	}
   	PostOrder(t->GetFirstChild());
   	cout<<t->GetData()<<" ";
   	PostOrder(t->GetNextBrother());
}

template <class T>
void Tree<T>::NorePostOrder(TreeNode<T>* t) const{
    LStack<TreeNode<T>*> s;
    if(t!=NULL) s.Push(t); 
    TreeNode<T> *node;
    while(!s.IsEmpty()) {
    	s.Pop(node);
		if(node->GetFirstChild() != NULL) {
         	s.Push(node->GetFirstChild());
      	}
      	cout<<node->GetData()<<" ";
      	if(node->GetNextBrother() != NULL) {
         	s.Push(node->GetNextBrother());
      	}
   	}
}


//======================================
//层次遍历，非递归 
template <class T>
void Tree<T>::NoreLevelOrder(TreeNode<T>* t) const{
    LQueue<TreeNode<T>*> q;
	TreeNode<T>*s=NULL; 
	//所有firstchild都入队，brother立即访问 
    if(t!=NULL) {
       	q.QInsert(t);
   	}
    TreeNode<T> *node;
    while(s!=NULL||!q.IsEmpty())
	{
	  	while(s!=NULL)
		{
			node=s;
			s=NULL;
			cout<<node->data<<" ";
		
      		if(node->GetFirstChild() != NULL) {
         		q.QInsert(node->GetFirstChild());
      		}
      		if(node->GetNextBrother() != NULL) {
      			s=node->GetNextBrother();
			}
   		}
   		if(!q.IsEmpty())
   		{
		   	q.QDelete(node);
			 
			cout<<node->GetData()<<" ";
		
      		if(node->GetFirstChild() != NULL) {
         		q.QInsert(node->GetFirstChild());
      		}
      		if(node->GetNextBrother() != NULL) {
      			s=node->GetNextBrother();
			  }
   		}
	}
}
 
//========================================
//删除结点及其左右子树
template <class T>
void Tree<T>::Del(TreeNode<T> *t)
{
	if(t != NULL) {
    Del(t->GetFirstChild());
    Del(t->GetNextBrother());
    delete t;
	}
}	 

template <class T>
void Tree<T>::DelSubTree(TreeNode<T>* t,TreeNode<T> *p)
{
	
	if(t != NULL&&p!=NULL) {
		TreeNode<T>*q=NULL,*result=NULL;
		result=FindFather(t,p);
		if(result)//如果p父节点存在 
		{
			if(result->GetFirstChild()==p)//如果p是f的大孩子节点 
			{
				result->SetFirstChild(p->GetNextBrother());
				Del(p);
				return;	
			}	
			else//如果不是大孩子结点 
			{ 
				q=result->GetFirstChild();
				while(q->GetNextBrother()!=p)
					q=q->GetNextBrother();
				q->SetNextBrother(p->GetNextBrother());
				Del(p);
				return;
			}
		}
		else
		{
			Del(p);
			root=NULL; 
		} 	
	}

}	 


#include <iostream>
#include"queue.h"//之前写的类 
#include"stack.h" //之前写的类 
using namespace std;




/*
	用二叉树的方式实现
	root指针指向第一棵树的根节点 
*/ 





 
template <class T>
class Forest;

//========================================
// 森林节点类声明
template <class T>
class ForestNode
{ 
private:
    ForestNode<T>  *firstChild,*nextBrother;
	//指向大孩子结点的指针和指向大兄弟结点的指针 
    T data;//数据
public:
	friend class Forest<T>;  
    //构造函数
    ForestNode(const T& item,ForestNode *lptr=NULL,ForestNode *rptr=NULL):
        data(item),firstChild(lptr),nextBrother(rptr){}
        
    ForestNode(){}

    ForestNode<T> * GetFirstChild()const{return firstChild;}//返回大儿子节点

    void SetFirstChild(ForestNode<T> * L){firstChild=L;}//设置大儿子结点 

    ForestNode<T> * GetNextBrother()const{return nextBrother;}//返回大兄弟节点

    void SetNextBrother(ForestNode<T> * R){nextBrother=R;}//设置大兄弟节点

    T GetData(){return data;}

    void SetData(T item){data=item;}


};



//===============================================================
// 森林类的声明

template <class T>
class Forest
{
private:
    ForestNode<T> *root;//虚根结点的声明
    int number;//树数 
public:
    Forest(ForestNode<T>*t=NULL):root(t){}//构造函数

    virtual ~Forest(){Del(root);}//析构函数 删除整个森林

    //在以节点t为根节点的森林中查找data域为item的结点
    ForestNode<T>  *Find(ForestNode<T> *t,const T&item)const;

	ForestNode<T>* CreateNewTree(); //森林中增加一棵树 
	
	ForestNode<T>* CreateTree(); //创建树 
	 
	ForestNode<T>* GetTree(int n);//获得森林中的第n棵数 
	
    //删除节点t及其子森林
    void Del(ForestNode<T> *t);
    

    //先根遍历并输出以节点t为根节点的子森林
    void PreOrder( ForestNode<T> *t)const;

    //后根遍历并输出以节点t为根节点的子森林
    void PostOrder(ForestNode<T> *t)const;


    //非递归先根遍历并输出以节点t为根节点的子森林
   	void NorePreOrder(ForestNode<T> *t)const;

    //非递归后根遍历并输出以节点t为根节点的子森林
  	void NorePostOrder(ForestNode<T> *t)const;

    //递归层次遍历并输出以节点t为根节点的子森林
    void LevelOrder(ForestNode<T> *t)const;


    //创建森林
    ForestNode<T>* CreateForest();
    
    
    //其它操作
    ForestNode<T>* GetRoot(){return root;}
    void SetRoot(ForestNode<T> * t){root=t;}
    bool IsEmpty(){return root==NULL;}
    
    void output();

};

template <class T>
void Forest<T>::output()
{
	cout<<" 森林的先根遍历的序列为：";
    PreOrder(GetRoot());
    cout<<endl;
    
    
    cout<<" 森林的后根遍历的序列为：";
    PostOrder(GetRoot());
    cout<<endl;
         
    cout<<" 森林的层次遍历的序列为：";
    LevelOrder(GetRoot());
    cout<<endl;
}


//=======================================
//在以节点t为根节点的子森林中查找data域为item的结点
template <class T>
ForestNode<T>* Forest<T>::Find(ForestNode<T> *t,const T&item)const
{
    ForestNode<T> * p;
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



//======================================
//创建森林 
template <class T>
ForestNode<T>* Forest<T>::CreateForest() {
	ForestNode<T>*p,*t;
	
	cout<<"森林中树的数量:";
	cin>>number;
	int i=1;
	if(number!=0)
	{
		cout<<"创建第"<<i<<"棵树"<<endl; 
		t=root=CreateTree();
		i++; 
		while(i<=number)
		{
			cout<<"创建第"<<i<<"棵树"<<endl;
			p=CreateTree();
			t->SetNextBrother(p);
			t=p;
			i++;
		}
	}
	return root;
}

template <class T>
ForestNode<T>* Forest<T>::CreateTree() 
{
	cout<<"输入节点的值";
	ForestNode<T>* currptr;
   	T data;
   	cin>>data;
   	currptr=new ForestNode<T>(data,NULL,NULL); 
   	cout<<"输入该结点的子树数";
   	int n;
	cin>>n;
	int i=1;
	if(n!=0)
	{
		cout<<"创建"<<data<<"的第1棵子树"<<endl; 
		ForestNode<T>* temp1 = CreateTree();
		currptr->SetFirstChild(temp1);
		i++;
		while(i<=n)
		{
			cout<<"创建"<<data<<"的第"<<i<<"棵子树"<<endl;
			ForestNode<T>* temp2=CreateTree();
			temp1->SetNextBrother(temp2);
			temp1=temp2;
			temp2=NULL;
			i++;
		}
	}
	return currptr;
}



template <class T>
ForestNode<T>* Forest<T>::CreateNewTree()//在森林中增加一棵树 
{
	ForestNode<T>* p=CreateTree();
	ForestNode<T>* t=root;
	while(t->GetNextBrother()!=NULL) t=t->GetNextBrother();
	t->SetNextBrother(p); 
	return p;
} 



template <class T>
ForestNode<T>* Forest<T>::GetTree(int k)//返回第k棵树 
{
	if(k>number&&k<1) return NULL;//越界 
	int i=1; 
	ForestNode<T>*t=root;
	while(i!=k) 
	{
		t=t->GetNextBrother();
		i++;
	}
	return t;
	
}

//=============================================================
//先序遍历森林  
template <class T>
void Forest<T>::PreOrder( ForestNode<T>* t) const {
   if(t == NULL) {
      return;
   }
   	cout<<t->GetData()<<" ";
   		
   	PreOrder(t->GetFirstChild());
   	PreOrder(t->GetNextBrother());
}

template <class T>
void Forest<T>::NorePreOrder(ForestNode<T>* t) const{
    LStack<ForestNode<T>*> q;
    if(t!=NULL) {
       	q.Push(t);
   	}
    ForestNode<T> *node;
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

//后序遍历森林 
template <class T>
void Forest<T>::PostOrder( ForestNode<T>* t) const {
   	if(t == NULL) {
      	return;
   	}
   	PostOrder(t->GetFirstChild());
	cout<<t->GetData()<<" ";
   	PostOrder(t->GetNextBrother());
}

template <class T>
void Forest<T>::NorePostOrder(ForestNode<T>* t) const{
    LStack<ForestNode<T>*> q;
    if(t!=NULL) {
       	q.Push(t);
   	}
    ForestNode<T> *node;
    while(!q.IsEmpty()) {
    	q.Pop(node);
		if(node->GetFirstChild() != NULL) {
         	q.Push(node->GetFirstChild());
      	}
      	
		cout<<node->GetData()<<" ";
      	if(node->GetNextBrother() != NULL) {
         	q.Push(node->GetNextBrother());
      	}
   	}
}


//======================================
//层次遍历 
template <class T>
void Forest<T>::LevelOrder(ForestNode<T>* t) const
{ 
	LQueue<ForestNode<T>*> q;
	ForestNode<T>*s=NULL; 
	//所有firstchild都入队，brother立即访问 
    if(t!=NULL) {
       	q.QInsert(t);
   	}
    ForestNode<T> *node;
    while(s!=NULL||!q.IsEmpty())
	{
	  	while(s!=NULL)
		{
			node=s;
			s=NULL;
			cout<<node->GetData()<<" ";
		
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
//删除森林 
template <class T>
void Forest<T>::Del(ForestNode<T> *t)
{
	if(t != NULL) {
    Del(t->GetFirstChild());
    Del(t->GetNextBrother());
    delete t;
	}
}	 


int main()
{
	ForestNode<char> *root;
    Forest<char> *tree = new Forest<char>(root);
    root=tree->CreateForest();
    tree->SetRoot(root);
    cout<<" 森林已经创建好"<<endl;
    tree->output();
    ForestNode<char> *node, *temp;
    char ch; 
    cout<<"\n请输入所需要查找的结点的值\n";
    cin>>ch;
    node = tree->Find(tree->GetRoot(), ch);
    if(node != NULL) {
        cout<<"找到结点"<<endl;
    } else {
        cout<<"未找到结点"<<endl;
    }

 } 




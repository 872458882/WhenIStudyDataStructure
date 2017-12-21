#include "tree.h"


template <class T>
class Forest
{
private:
    Tree<T>** ForTree;//指向树的指针的数组 
    int Number;//树数 
    int MaxNumber;
public:
    Forest(int mnum=10):MaxNumber(mnum){CreateForest();}//构造函数

    virtual ~Forest();//析构函数 删除整个森林
 	
	 //创建森林
    void CreateForest();
    
    //在以节点t为根节点的森林中查找data域为item的结点
    TreeNode<T>  *Find(TreeNode<T> *t,const T&item)const;
	
	TreeNode<T>* GetTree(int n);//获得森林中的第n棵数 
	


    //先根遍历
    void FPreOrder()const;

    //后根遍历
    void FPostOrder()const;

    //层次遍历
    void FLevelOrder()const;

   
    //其它操作
    bool IsEmpty(){return Number==0;}
    
    void output();

};


//创建森林 
template <class T>
void Forest<T>::CreateForest() {
	
	cout<<"森林中树的数量:";
	cin>>Number;
	ForTree=new Tree<T>*[MaxNumber]; 
	for(int i=0;i<Number;i++)
	{
		cout<<"创建第"<<i+1<<"棵树"<<endl; 
		ForTree[i]=new Tree<T>;
		ForTree[i]->CreateTree();
	}
	cout<<"森林创建完毕"<<endl;
	
}



template <class T>
Forest<T>::~Forest()
{
	for(int i=0;i<Number;i++)
		ForTree[i]->Del(ForTree[i]->GetRoot());
	delete[]ForTree;
}


template <class T>
void Forest<T>::output()
{
	cout<<" 森林的先根遍历的序列为：";
    FPreOrder();
    cout<<endl;
    
    
    cout<<" 森林的后根遍历的序列为：";
    FPostOrder();
    cout<<endl;
         
    cout<<" 森林的层次遍历的序列为：";
    FLevelOrder();
    cout<<endl;
}


//先根遍历
template <class T>
void Forest<T>::FPreOrder()const
{
	for(int i=0;i<Number;i++)
		ForTree[i]->PreOrder(ForTree[i]->GetRoot());
}


//后根遍历
template <class T>
void Forest<T>::FPostOrder()const
{
	for(int i=0;i<Number;i++)
		ForTree[i]->PostOrder(ForTree[i]->GetRoot());
} 


//层次遍历
template <class T>
void Forest<T>::FLevelOrder()const
{
	TreeNode<T>*root=ForTree[0]->GetRoot();//引入根结点 
	TreeNode<T>*t=NULL;
	for(int i=1;i<Number;i++)
	{
		t=ForTree[i-1]->GetRoot();
		t->SetNextBrother(ForTree[i]->GetRoot()); 
	}
	
	//遍历 
	LQueue<TreeNode<T>*> q;
	TreeNode<T>*s=NULL; 
	//所有firstchild都入队，brother立即访问 
    if(t!=NULL) {
       	q.QInsert(root);
   	}
    TreeNode<T> *node;
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
	
	//解除各树联系
	for(int i=1;i<Number;i++)
	{
		t=ForTree[i-1]->GetRoot();
		t->SetNextBrother(NULL); 
	}
	 
} 
int main()
{
	Forest<char> A;
	A.output(); 
 } 



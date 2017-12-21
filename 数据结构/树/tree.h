#include <iostream>
#include"queue.h" 
#include"stack.h"  
using namespace std;

template <class T>
class Tree;



//========================================
// ���ڵ�������
template <class T>
class TreeNode
{ 
private:
    TreeNode<T>  *firstChild,*nextBrother;
	//ָ����ӽ���ָ���ָ����ֵܽ���ָ�� 
    T data;//����
public:
	friend class Tree<T>;  
    //���캯��
    TreeNode(const T& item,TreeNode *lptr=NULL,TreeNode *rptr=NULL):
        data(item),firstChild(lptr),nextBrother(rptr){}

    TreeNode<T> * GetFirstChild()const{return firstChild;}//���ش���ӽڵ�

    void SetFirstChild(TreeNode<T> * L){firstChild=L;}//���ô���ӽ�� 

    TreeNode<T> * GetNextBrother()const{return nextBrother;}//���ش��ֵܽڵ�

    void SetNextBrother(TreeNode<T> * R){nextBrother=R;}//���ô��ֵܽڵ�

    T GetData(){return data;}

    void SetData(T item){data=item;}


};



//===============================================================
// ���������

template <class T>
class Tree
{
private:
    TreeNode<T> *root;//����������
	T stop; 
public:
	
    Tree(TreeNode<T>*t=NULL):root(t),stop('*'){}//���캯��

    virtual ~Tree(){Del(root);}//�������� ɾ������ ��

    //���Խڵ�tΪ���ڵ�������в���data��Ϊitem�Ľ��
    TreeNode<T>  *Find(TreeNode<T> *t,const T&item)const;

    //���Խڵ�tΪ���ڵ�������������ڵ�p�ĸ��ڵ�
    TreeNode<T> * Father(TreeNode<T> *t,TreeNode<T> *p)const;

	//���Խڵ�tΪ���ڵ��������ɾ���ڵ�t��������
	void DelSubTree(TreeNode<T>* t,TreeNode<T> *p);
	 
    //ɾ���ڵ�t��������
    void Del(TreeNode<T> *t);

    //�ȸ�����������Խڵ�tΪ���ڵ������
    void PreOrder( TreeNode<T> *t)const;

    //�������������Խڵ�tΪ���ڵ������
    void PostOrder(TreeNode<T> *t)const;


    //�ǵݹ��ȸ�����������Խڵ�tΪ���ڵ������
   	void NorePreOrder(TreeNode<T> *t)const;

    //�ǵݹ�������������Խڵ�tΪ���ڵ������
  	void NorePostOrder(TreeNode<T> *t)const;

    //�ǵݹ��α���������Խڵ�tΪ���ڵ������
    void NoreLevelOrder(TreeNode<T> *t)const;


    //������
    TreeNode<T>* CreateTree();
    
    
    //��������
    TreeNode<T>* GetRoot(){return root;}
    void SetRoot(TreeNode<T> * t){root=t;}
    bool IsEmpty(){return root==NULL;}
    
    void output();

};

template <class T>
void Tree<T>::output()
{
	cout<<" �����ȸ�����������Ϊ��";
    PreOrder(GetRoot());
    cout<<endl;
    
    
    cout<<" ���ĺ������������Ϊ��";
    PostOrder(GetRoot());
    cout<<endl;
         
    cout<<" ���Ĳ�α���������Ϊ��";
    NoreLevelOrder(GetRoot());
    cout<<endl;
}


//=======================================
//���Խڵ�tΪ���ڵ�������в���data��Ϊitem�Ľ��
template <class T>
TreeNode<T>* Tree<T>::Find(TreeNode<T> *t,const T&item)const
{
    TreeNode<T> * p;
    //�ݹ����
    if(t==NULL)return NULL;
    if(t->GetData()==item) return t;
    //�ݹ�
    p=Find(t->GetFirstChild(),item);
    if(p!=NULL) return p;
    
    p=Find(t->GetNextBrother(),item);
    if(p!=NULL) return p;
    
	return NULL;
}


//���Խڵ�tΪ���ڵ�������������ڵ�p�ĸ����
template <class T>
TreeNode<T>* Tree<T>::Father(TreeNode<T>* t,TreeNode<T>*p)const
{
	
	
	if(t==NULL||p==NULL)//��t��p����һ��Ϊ�� 
		return NULL;
	if(p==root) return NULL; //��t�Ǹ������û�и��ڵ� 
	
	TreeNode<T>*result=NULL;
	TreeNode<T>*q=t->GetFirstChild();//�ӵ�һ��������ʼ���� 
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
//�ǵݹ鴴���� 
template <class T>
TreeNode<T>* Tree<T>::CreateTree() {
	
	LQueue<TreeNode<T>*> Q;
	
	//��������
	//cout<<"�������㣬���س�\n"; 
	cout<<"��������\n" ;
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
		//getchar();//���˻س�
		//cout<<"����"<<node->GetData()<<"���ӽڵ�( ��*��β)�����س�\n"; 
		//item=getchar();
		cout<<"����"<<node->GetData()<<"���ӽڵ�\n";
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
//���������  
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

//���������  
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
//��α������ǵݹ� 
template <class T>
void Tree<T>::NoreLevelOrder(TreeNode<T>* t) const{
    LQueue<TreeNode<T>*> q;
	TreeNode<T>*s=NULL; 
	//����firstchild����ӣ�brother�������� 
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
//ɾ����㼰����������
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
		if(result)//���p���ڵ���� 
		{
			if(result->GetFirstChild()==p)//���p��f�Ĵ��ӽڵ� 
			{
				result->SetFirstChild(p->GetNextBrother());
				Del(p);
				return;	
			}	
			else//������Ǵ��ӽ�� 
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


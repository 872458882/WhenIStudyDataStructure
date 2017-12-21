#include <iostream>
#include"queue.h"//֮ǰд���� 
#include"stack.h" //֮ǰд���� 
using namespace std;

template <class T>
class BST;

//========================================
//�������ڵ�������
template <class T>
class BSTNode
{ 
private:
    BSTNode<T>  *left,*right;//ָ������������ָ��
    T data;//����
public:
	friend class BST<T>;  
    //���캯��
    BSTNode(const T& item,BSTNode *lptr=NULL,BSTNode *rptr=NULL):
        data(item),left(lptr),right(rptr){}

    BSTNode<T> * GetLeft()const{return left;}//�������ӽڵ�

    void SetLeft(BSTNode<T> * L){left=L;}//�������ӽڵ�

    BSTNode<T> * GetRight()const{return right;}//�������ӽڵ�

    void SetRight(BSTNode<T> * R){right=R;}//�������ӽڵ�

    T GetData(){return data;}

    void SetData(T item){data=item;}


};



//===============================================================
//��������Bindoubleree������

template <class T>
class BST
{
private:
    BSTNode<T> *root;//����������
   
    
public:int adata; int n;
    BST(BSTNode<T>*t=NULL):root(t),adata(0),n(0){}//���캯��

    virtual ~BST(){Del(root);}//�������� ɾ�����ö�����

    //���Խڵ�tΪ���ڵ�������в���data��Ϊitem�Ľ��(first)
    BSTNode<T>  *Find(BSTNode<T> *t,const T&item);

    //���Խڵ�tΪ���ڵ�������������ڵ�p�ĸ��ڵ�
    BSTNode<T> * Father(BSTNode<T> *t,BSTNode<T> *p)const;

    //ɾ���ڵ�t������������
    void Del(BSTNode<T> *t);

    //�ȸ�����������Խڵ�tΪ���ڵ������
    void PreOrder( BSTNode<T> *t)const;

    //�и�����������Խڵ�tΪ���ڵ������
    void InOrder( BSTNode<T> *t)const;

    //�������������Խڵ�tΪ���ڵ������
    void PostOrder(BSTNode<T> *t)const;

    //��α���������Խڵ�tΪ���ڵ������
    //void LevelOrder(BSTNode<T> *t)const;

    //�ǵݹ��ȸ�����������Խڵ�tΪ���ڵ������
   	void NorePreOrder(BSTNode<T> *t)const;

    //�ǵݹ��и�����������Խڵ�tΪ���ڵ������
   	void NoreInOrder(BSTNode<T> *t)const;

    //�ǵݹ�������������Խڵ�tΪ���ڵ������
  	void NorePostOrder(BSTNode<T> *t)const;

    //�ǵݹ��α���������Խڵ�tΪ���ڵ������
    void NoreLevelOrder(BSTNode<T> *t)const;
    
    void DelLarge(BSTNode<T> *t);

    //����������
    BSTNode<T>* CreateBST();
    
    
    //��������
    BSTNode<T>* GetRoot(){return root;}
    void SetRoot(BSTNode<T> * t){root=t;}
    bool IsEmpty(){return root==NULL;}
    bool IsFull(BSTNode<T>*t); 
    
    void output();

};

template <class T>
void BST<T>::output()
{
	cout<<"���������ȸ�����������Ϊ��";
    PreOrder(GetRoot());
    cout<<endl;
    
	cout<<"���������и�����������Ϊ��";
    InOrder(GetRoot());
    cout<<endl;
    
    cout<<"�������ĺ������������Ϊ��";
    PostOrder(GetRoot());
    cout<<endl;
         
    cout<<"�������Ĳ�α���������Ϊ��";
    NoreLevelOrder(GetRoot());
    cout<<endl;
}


//=======================================
//���Խڵ�tΪ���ڵ�������в���data��Ϊitem�Ľ��
template <class T>
BSTNode<T>* BST<T>::Find(BSTNode<T> *t,const T&item)
{
    BSTNode<T>*p=t;
    while(p!=NULL)
    {
    	if(p->GetData()==item) 
    	{
    		cout<<"�Ѿ��ҵ�"<<item<<endl;
			return p;
		}
		if(item<p->GetData())
		{
			if(p->GetLeft()!=NULL)
				p=p->GetLeft();
			else 
			{
				cout<<"δ�ҵ�"<<item<<endl;
				break;
			}
		}
		if(item>p->GetData())
		{
			if(p->GetRight()!=NULL)
				p=p->GetRight();
			else 
			{
				cout<<"δ�ҵ�"<<item<<endl;
				break;
			}
		}
	}
	BSTNode<T>*q=new BSTNode<T>(item,NULL,NULL); 
	//����
	if(item < p->GetData())
		p->SetLeft(q);
	else 
		p->SetRight(q);
	adata=(n*adata+p->GetData())/(n+1);
	n++;
	cout<<"new adata"<<adata;
}



//======================================
//������ 
template <class T>
BSTNode<T>* BST<T>::CreateBST() {
   	BSTNode<T>* t;
   	T data;
   	cin>>data;
   	//ÿ��Ҷ����ⲹ������Ҷ���
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
//�������������  
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

//�������������  
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
//�������������
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
//��α������ǵݹ� 
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
//ɾ����㼰����������
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
	cout<<"ɾ���ɹ�"<<endl; 
}

int main()
{
	BSTNode<int> *root;
    BST<int> *tree = new BST<int>(root);
    cout<<"������"<<endl;
    root=tree->CreateBST();
    tree->SetRoot(root);
    cout<<"�������Ѿ�������"<<endl;
    cout<<tree->adata;
	tree->output();
    BSTNode<int> *node, *temp;
    int ch; 
    cout<<"����������Ҫ���ҵĽ���ֵ";
    getchar();
	cin>>ch;
    node = tree->Find(tree->GetRoot(), ch);
    tree->output();
    cout<<"����������Ҫ���ҵĽ���ֵ";
    getchar();
	cin>>ch;
    node = tree->Find(tree->GetRoot(), ch);
    tree->output();
    cout<<"ɾ�������"<<endl;
    tree->DelLarge(tree->GetRoot());
    tree->output();
 } 


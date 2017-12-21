/*
1�� �������Ӵ洢�Ķ������ࡣ
2�� ʵ����֤�����㷨����ȷ�ԡ����ֹ��ܼ�ָ�꣺
1������һ�ö��������������ʼ����
2���ȸ����и������������������
3���ڶ������������������ĸ���㣻
4�������������з��������������Ľ�㣻
3�� �ɽ�ʦ���ָ�����ṹ��������������
*/

#include <iostream>
#include"queue.h"//֮ǰд���� 
#include"stack.h" //֮ǰд���� 
using namespace std;

template <class T>
class BinTree;

//========================================
//�������ڵ�������
template <class T>
class BinTreeNode
{ 
private:
    BinTreeNode<T>  *left,*right;//ָ������������ָ��
    T data;//����
public:
	friend class BinTree<T>;  
    //���캯��
    BinTreeNode(const T& item,BinTreeNode *lptr=NULL,BinTreeNode *rptr=NULL):
        data(item),left(lptr),right(rptr){}

    BinTreeNode<T> * GetLeft()const{return left;}//�������ӽڵ�

    void SetLeft(BinTreeNode<T> * L){left=L;}//�������ӽڵ�

    BinTreeNode<T> * GetRight()const{return right;}//�������ӽڵ�

    void SetRight(BinTreeNode<T> * R){right=R;}//�������ӽڵ�

    T GetData(){return data;}

    void SetData(T item){data=item;}


};



//===============================================================
//��������Bindoubleree������

template <class T>
class BinTree
{
private:
    BinTreeNode<T> *root;//����������
public:
    BinTree(BinTreeNode<T>*t=NULL):root(t){}//���캯��

    virtual ~BinTree(){Del(root);}//�������� ɾ�����ö�����

    //���Խڵ�tΪ���ڵ�������в���data��Ϊitem�Ľ��(first)
    BinTreeNode<T>  *Find(BinTreeNode<T> *t,const T&item)const;

    //���Խڵ�tΪ���ڵ�������������ڵ�p�ĸ��ڵ�
    BinTreeNode<T> * Father(BinTreeNode<T> *t,BinTreeNode<T> *p)const;

    //ɾ���ڵ�t������������
    void Del(BinTreeNode<T> *t);

    //�ȸ�����������Խڵ�tΪ���ڵ������
    void PreOrder( BinTreeNode<T> *t)const;

    //�и�����������Խڵ�tΪ���ڵ������
    void InOrder( BinTreeNode<T> *t)const;

    //�������������Խڵ�tΪ���ڵ������
    void PostOrder(BinTreeNode<T> *t)const;

    //��α���������Խڵ�tΪ���ڵ������
    //void LevelOrder(BinTreeNode<T> *t)const;

    //�ǵݹ��ȸ�����������Խڵ�tΪ���ڵ������
   	void NorePreOrder(BinTreeNode<T> *t)const;

    //�ǵݹ��и�����������Խڵ�tΪ���ڵ������
   	void NoreInOrder(BinTreeNode<T> *t)const;

    //�ǵݹ�������������Խڵ�tΪ���ڵ������
  	void NorePostOrder(BinTreeNode<T> *t)const;

    //�ǵݹ��α���������Խڵ�tΪ���ڵ������
    void NoreLevelOrder(BinTreeNode<T> *t)const;

    //����������
    BinTreeNode<T>* CreateBinTree();
    
    
    //��������
    BinTreeNode<T>* GetRoot(){return root;}
    void SetRoot(BinTreeNode<T> * t){root=t;}
    bool IsEmpty(){return root==NULL;}
    bool IsFull(BinTreeNode<T>*t); 
    
    void output();

};

template <class T>
void BinTree<T>::output()
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
BinTreeNode<T>* BinTree<T>::Find(BinTreeNode<T> *t,const T&item)const
{
    BinTreeNode<T> * p;
    //�ݹ����
    if(t==NULL)return NULL;
    if(t->GetData()==item) return t;
    //�ݹ�
    p=Find(t->GetLeft(),item);
    if(p!=NULL) return p;
    p=Find(t->GetRight(),item);
    if(p!=NULL) return p;
    return NULL;
}


//���Խڵ�tΪ���ڵ�������������ڵ�p�ĸ����
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
//������ 
template <class T>
BinTreeNode<T>* BinTree<T>::CreateBinTree() {
   	BinTreeNode<T>* t;
   	T data;
   	cin>>data;
   	//ÿ��Ҷ����ⲹ������Ҷ���
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
//�������������  
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

//�������������  
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
//�������������
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
//��α������ǵݹ� 
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
//ɾ����㼰����������
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
bool BinTree<T>::IsFull(BinTreeNode<T>* t)//�ж϶������Ƿ���ȫ������ ���򷵻�1,���򷵻�0
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
			cout<<"����ȫ������"<<endl;
			return 0;
      	}else{
			q.QInsert(node->GetLeft());
			q.QInsert(node->GetRight());
		}
	}
	cout<<"����ȫ������"<<endl;
	return 1;
	
}

int main()
{
	BinTreeNode<char> *root;
    BinTree<char> *tree = new BinTree<char>(root);
    root=tree->CreateBinTree();
    tree->SetRoot(root);
    cout<<"�������Ѿ�������"<<endl;
    tree->output();
    tree->NorePreOrder(root);
    tree->NoreInOrder(root);
    tree->NorePostOrder(root);
    BinTreeNode<char> *node, *temp;
    char ch; 
    cout<<"����������Ҫ���ҵĽ���ֵ";
    cin>>ch;
    node = tree->Find(tree->GetRoot(), ch);
    if(node != NULL) {
        cout<<"�ҵ����"<<endl;
    } else {
        cout<<"δ�ҵ����"<<endl;
    }
    cout<<"���ҽ��p�ĸ��ڵ�,��������p��ֵ"<<endl;
    cin>>ch;
    node = tree->Find(tree->GetRoot(), ch);
    temp = tree->Father(tree->GetRoot(), node);
    if(temp != NULL) {
        cout<<"ֵΪ"<<node->GetData()<<"�Ľ��ĸ�����ֵΪ"<<temp->GetData()<<endl;
    } else {
        cout<<"δ�ҵ�p�ĸ��ڵ�"<<endl;
    }
    tree->IsFull(tree->GetRoot()); 
    
 } 


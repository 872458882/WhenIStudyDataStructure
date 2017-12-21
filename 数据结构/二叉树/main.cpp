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
#include <memory.h>
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
    
    //���ÿ��ڵ����or��k�� 
	int getLevelNodeNum(BinTreeNode<T>*t,int k);
    
    
    //��������
    BinTreeNode<T>* GetRoot(){return root;}
    void SetRoot(BinTreeNode<T> * t){root=t;}
    bool IsEmpty(){return root==NULL;}
    
    //�ж��Ƿ���ȫ������ 
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
      		if(flag==1) break;//�����һ�����ӵ�Ҳ��NULL,���˳�ѭ�� 
      		
			//if(k==i)
      		//{cout<<"��"<<k<<"��Ľ����Ϊ��"<<num[k]<<endl; return num[k];}
    		
			cout<<"��"<<i<<"��Ľ����Ϊ"<<num[i++]<<endl; 
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
   	
   	//cout<<"��"<<k<<"��Ľ����Ϊ��"<<num[k]<<endl; 
   	return 1;
}


//�ؽ�������
template <class T>
BinTreeNode<T>* ReBuildTree(T *preOrder, T *inOrder, int n){
	if(preOrder == NULL || inOrder == NULL || n <= 0){
	   return NULL;
	}
	BinTreeNode<T> *root = new BinTreeNode<T>();
	root->value = preOrder[0];
	root->left = NULL;
	root->right = NULL;
	//�ҵ���������и��ڵ��λ��
	int index = 0;
	while(index < n && preOrder[0] != inOrder[index]){
	    ++index;
	}
	//���Ϸ�����
	if(index >= n){
	    return NULL;
	}
	root->left = ReBuildTree(preOrder+1, inOrder, index);
	root->right = ReBuildTree(preOrder+1+index, inOrder+1+index, n-index-1);
	return root;
}


void LongestPath(BiTree bt)//��������еĵ�һ���·������,������·���ϵĽڵ�
{
	BiTree p = bt, l[MaxSize], s[MaxSize]; //l, s��ջ��Ԫ���Ƕ��������ָ�룬l�б�����ǰ�·���еĽ��
	int i,top = 0, tag[MaxSize], longest = 0;
	while (p || top >0)
	{
		while (p)
		{
			s[++top] = p;
			tag[top] = 0;
			p = p->lchild;
		} //�����֦����
		if (tag[top] == 1)    //��ǰ�����ҷ�֦�ѱ���
		{
			if (!s[top]->lchild && !s[top]->rchild)  //ֻ�е�Ҷ�ӽ��ʱ���Ų鿴·������
				if (top>longest)
				{
					for (i = 1; i <= top; i++)
						l[i] = s[i];
					longest = top;
					top--;
				}//������ǰ�·����lջ����ס���ջ��ָ�룬��ջ
		}
		else if (top>0)
		{
			tag[top] = 1;
			p = s[top]->rchild;
		}   //�����ӷ�֦����
	}//while(p!=null||top>0)
	int k = 0;
	for (k = 0; k < longest; k++)
	{
		printf("%d ", l[k]->data);
	}
}//����LongestPath






int main()
{
	BinTreeNode<char> *root;
    BinTree<char> *tree = new BinTree<char>(root);
    root=tree->CreateBinTree();
    tree->SetRoot(root);
    cout<<"�������Ѿ�������"<<endl;
    tree->output();
    //tree->NorePreOrder(root);
    //tree->NoreInOrder(root);
    //tree->NorePostOrder(root);
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
    tree->getLevelNodeNum(tree->GetRoot(),3);
 } 


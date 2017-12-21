#include <iostream>
#include <memory.h>
#include "queue.h"//֮ǰд���� 
#include "stack.h" //֮ǰд���� 
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
//�������������

template <class T>
class BST
{
private:
    BSTNode<T> *root;//����������
	T Number[15];
public:
    BST():root(NULL){}//���캯��

    virtual ~BST(){Del(root);}//�������� ɾ�����ö�����

    //���Խڵ�tΪ���ڵ�������в���data��Ϊitem�Ľ��(first)
    BSTNode<T>  *Find(const T&item);

	BSTNode<T>  *Insert(const T&item);

    //���Խڵ�tΪ���ڵ�������������ڵ�p�ĸ��ڵ�
    BSTNode<T> * Father(BSTNode<T> *t,BSTNode<T> *p)const;

    //ɾ���ڵ�t������������
    void Del(BSTNode<T> *t);



    //�и�����������Խڵ�tΪ���ڵ������
    void InOrder( BSTNode<T> *t)const;


    //�ǵݹ��и�����������Խڵ�tΪ���ڵ������
   	void NoreInOrder(BSTNode<T> *t)const;


    //�ǵݹ��α���������Խڵ�tΪ���ڵ������
    void NoreLevelOrder(BSTNode<T> *t);
    
    void DelLarge(BSTNode<T> *t);

    //����������
    BSTNode<T>* CreateBST();
		

	void getRandom(); 

    //��������
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

	cout<<"���������и�����������Ϊ��";
    InOrder(GetRoot());
    cout<<endl;
    
         
    cout<<"�������Ĳ�α���������Ϊ��";
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
//���Խڵ�tΪ���ڵ�������в���data��Ϊitem�Ľ��
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
	    		//cout<<"�Ѿ��ҵ�"<<item<<endl;
				return p;
			}
			if(item<p->GetData())
			{
				if(p->GetLeft()!=NULL)
					p=p->GetLeft();
				else 
				{
					//cout<<"δ�ҵ�"<<item<<endl;
					break;
				}
			}
			if(item>p->GetData())
			{
				if(p->GetRight()!=NULL)
					p=p->GetRight();
				else 
				{
					//cout<<"δ�ҵ�"<<item<<endl;
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
	}
	else
	{
		root=q=new BSTNode<T>(item,NULL,NULL);
	}
	return q;
}



//======================================
//������ 
template <class T>
BSTNode<T>* BST<T>::CreateBST() {
	for(int i=0;i<15;i++)
	{
	    Insert(Number[i]);
	}
	return root;
}




//=======================================
//���Խڵ�tΪ���ڵ�������в���data��Ϊitem�Ľ��
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
	    		//cout<<"�Ѿ��ҵ�"<<item<<endl;
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
					//cout<<"δ�ҵ�"<<item<<endl;
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
					//cout<<"δ�ҵ�"<<item<<endl;
					error+=compare;
					break;
				}
			}
		}
	return q;
	
}



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


//======================================
//��α������ǵݹ� 
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
      		if(flag==1) break;//�����һ�����ӵ�Ҳ��NULL,���˳�ѭ�� 
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
//ɾ����㼰����������
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
 	cout<<"���ҳɹ���ƽ���Ƚϴ�����"<<endl;
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
 	cout<<"����ʧ�ܵ�ƽ���Ƚϴ���:"<<endl;
 	cout<<error/16.0<<endl;
 	
 }

int main() {
	srand((unsigned)time(NULL));
	
	BSTNode<int> *root=NULL;
    BST<int> *tree = new BST<int>();
   
	tree->getRandom(); 
	cout<<"������"<<endl;
    root=tree->CreateBST();
    cout<<"BST�����ɹ�"<<endl;
	tree->output();
	
	tree->CompareTime();
	
	return 0;
}

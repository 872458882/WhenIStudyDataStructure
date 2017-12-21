#include <iostream>
#include"queue.h"//֮ǰд���� 
#include"stack.h" //֮ǰд���� 
using namespace std;




/*
	�ö������ķ�ʽʵ��
	rootָ��ָ���һ�����ĸ��ڵ� 
*/ 





 
template <class T>
class Forest;

//========================================
// ɭ�ֽڵ�������
template <class T>
class ForestNode
{ 
private:
    ForestNode<T>  *firstChild,*nextBrother;
	//ָ����ӽ���ָ���ָ����ֵܽ���ָ�� 
    T data;//����
public:
	friend class Forest<T>;  
    //���캯��
    ForestNode(const T& item,ForestNode *lptr=NULL,ForestNode *rptr=NULL):
        data(item),firstChild(lptr),nextBrother(rptr){}
        
    ForestNode(){}

    ForestNode<T> * GetFirstChild()const{return firstChild;}//���ش���ӽڵ�

    void SetFirstChild(ForestNode<T> * L){firstChild=L;}//���ô���ӽ�� 

    ForestNode<T> * GetNextBrother()const{return nextBrother;}//���ش��ֵܽڵ�

    void SetNextBrother(ForestNode<T> * R){nextBrother=R;}//���ô��ֵܽڵ�

    T GetData(){return data;}

    void SetData(T item){data=item;}


};



//===============================================================
// ɭ���������

template <class T>
class Forest
{
private:
    ForestNode<T> *root;//�����������
    int number;//���� 
public:
    Forest(ForestNode<T>*t=NULL):root(t){}//���캯��

    virtual ~Forest(){Del(root);}//�������� ɾ������ɭ��

    //���Խڵ�tΪ���ڵ��ɭ���в���data��Ϊitem�Ľ��
    ForestNode<T>  *Find(ForestNode<T> *t,const T&item)const;

	ForestNode<T>* CreateNewTree(); //ɭ��������һ���� 
	
	ForestNode<T>* CreateTree(); //������ 
	 
	ForestNode<T>* GetTree(int n);//���ɭ���еĵ�n���� 
	
    //ɾ���ڵ�t������ɭ��
    void Del(ForestNode<T> *t);
    

    //�ȸ�����������Խڵ�tΪ���ڵ����ɭ��
    void PreOrder( ForestNode<T> *t)const;

    //�������������Խڵ�tΪ���ڵ����ɭ��
    void PostOrder(ForestNode<T> *t)const;


    //�ǵݹ��ȸ�����������Խڵ�tΪ���ڵ����ɭ��
   	void NorePreOrder(ForestNode<T> *t)const;

    //�ǵݹ�������������Խڵ�tΪ���ڵ����ɭ��
  	void NorePostOrder(ForestNode<T> *t)const;

    //�ݹ��α���������Խڵ�tΪ���ڵ����ɭ��
    void LevelOrder(ForestNode<T> *t)const;


    //����ɭ��
    ForestNode<T>* CreateForest();
    
    
    //��������
    ForestNode<T>* GetRoot(){return root;}
    void SetRoot(ForestNode<T> * t){root=t;}
    bool IsEmpty(){return root==NULL;}
    
    void output();

};

template <class T>
void Forest<T>::output()
{
	cout<<" ɭ�ֵ��ȸ�����������Ϊ��";
    PreOrder(GetRoot());
    cout<<endl;
    
    
    cout<<" ɭ�ֵĺ������������Ϊ��";
    PostOrder(GetRoot());
    cout<<endl;
         
    cout<<" ɭ�ֵĲ�α���������Ϊ��";
    LevelOrder(GetRoot());
    cout<<endl;
}


//=======================================
//���Խڵ�tΪ���ڵ����ɭ���в���data��Ϊitem�Ľ��
template <class T>
ForestNode<T>* Forest<T>::Find(ForestNode<T> *t,const T&item)const
{
    ForestNode<T> * p;
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



//======================================
//����ɭ�� 
template <class T>
ForestNode<T>* Forest<T>::CreateForest() {
	ForestNode<T>*p,*t;
	
	cout<<"ɭ������������:";
	cin>>number;
	int i=1;
	if(number!=0)
	{
		cout<<"������"<<i<<"����"<<endl; 
		t=root=CreateTree();
		i++; 
		while(i<=number)
		{
			cout<<"������"<<i<<"����"<<endl;
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
	cout<<"����ڵ��ֵ";
	ForestNode<T>* currptr;
   	T data;
   	cin>>data;
   	currptr=new ForestNode<T>(data,NULL,NULL); 
   	cout<<"����ý���������";
   	int n;
	cin>>n;
	int i=1;
	if(n!=0)
	{
		cout<<"����"<<data<<"�ĵ�1������"<<endl; 
		ForestNode<T>* temp1 = CreateTree();
		currptr->SetFirstChild(temp1);
		i++;
		while(i<=n)
		{
			cout<<"����"<<data<<"�ĵ�"<<i<<"������"<<endl;
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
ForestNode<T>* Forest<T>::CreateNewTree()//��ɭ��������һ���� 
{
	ForestNode<T>* p=CreateTree();
	ForestNode<T>* t=root;
	while(t->GetNextBrother()!=NULL) t=t->GetNextBrother();
	t->SetNextBrother(p); 
	return p;
} 



template <class T>
ForestNode<T>* Forest<T>::GetTree(int k)//���ص�k���� 
{
	if(k>number&&k<1) return NULL;//Խ�� 
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
//�������ɭ��  
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

//�������ɭ�� 
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
//��α��� 
template <class T>
void Forest<T>::LevelOrder(ForestNode<T>* t) const
{ 
	LQueue<ForestNode<T>*> q;
	ForestNode<T>*s=NULL; 
	//����firstchild����ӣ�brother�������� 
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
//ɾ��ɭ�� 
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
    cout<<" ɭ���Ѿ�������"<<endl;
    tree->output();
    ForestNode<char> *node, *temp;
    char ch; 
    cout<<"\n����������Ҫ���ҵĽ���ֵ\n";
    cin>>ch;
    node = tree->Find(tree->GetRoot(), ch);
    if(node != NULL) {
        cout<<"�ҵ����"<<endl;
    } else {
        cout<<"δ�ҵ����"<<endl;
    }

 } 




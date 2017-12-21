#include "tree.h"


template <class T>
class Forest
{
private:
    Tree<T>** ForTree;//ָ������ָ������� 
    int Number;//���� 
    int MaxNumber;
public:
    Forest(int mnum=10):MaxNumber(mnum){CreateForest();}//���캯��

    virtual ~Forest();//�������� ɾ������ɭ��
 	
	 //����ɭ��
    void CreateForest();
    
    //���Խڵ�tΪ���ڵ��ɭ���в���data��Ϊitem�Ľ��
    TreeNode<T>  *Find(TreeNode<T> *t,const T&item)const;
	
	TreeNode<T>* GetTree(int n);//���ɭ���еĵ�n���� 
	


    //�ȸ�����
    void FPreOrder()const;

    //�������
    void FPostOrder()const;

    //��α���
    void FLevelOrder()const;

   
    //��������
    bool IsEmpty(){return Number==0;}
    
    void output();

};


//����ɭ�� 
template <class T>
void Forest<T>::CreateForest() {
	
	cout<<"ɭ������������:";
	cin>>Number;
	ForTree=new Tree<T>*[MaxNumber]; 
	for(int i=0;i<Number;i++)
	{
		cout<<"������"<<i+1<<"����"<<endl; 
		ForTree[i]=new Tree<T>;
		ForTree[i]->CreateTree();
	}
	cout<<"ɭ�ִ������"<<endl;
	
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
	cout<<" ɭ�ֵ��ȸ�����������Ϊ��";
    FPreOrder();
    cout<<endl;
    
    
    cout<<" ɭ�ֵĺ������������Ϊ��";
    FPostOrder();
    cout<<endl;
         
    cout<<" ɭ�ֵĲ�α���������Ϊ��";
    FLevelOrder();
    cout<<endl;
}


//�ȸ�����
template <class T>
void Forest<T>::FPreOrder()const
{
	for(int i=0;i<Number;i++)
		ForTree[i]->PreOrder(ForTree[i]->GetRoot());
}


//�������
template <class T>
void Forest<T>::FPostOrder()const
{
	for(int i=0;i<Number;i++)
		ForTree[i]->PostOrder(ForTree[i]->GetRoot());
} 


//��α���
template <class T>
void Forest<T>::FLevelOrder()const
{
	TreeNode<T>*root=ForTree[0]->GetRoot();//�������� 
	TreeNode<T>*t=NULL;
	for(int i=1;i<Number;i++)
	{
		t=ForTree[i-1]->GetRoot();
		t->SetNextBrother(ForTree[i]->GetRoot()); 
	}
	
	//���� 
	LQueue<TreeNode<T>*> q;
	TreeNode<T>*s=NULL; 
	//����firstchild����ӣ�brother�������� 
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
	
	//���������ϵ
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



#include <iostream>
using namespace std;


template<class T>
class Node
{
public:
    int row;
    int col;
    T val;
    Node<T>*left;
    Node<T>*up;
    Node(int r,int c,T v,Node*l,Node*u):row(r),col(c),val(v),left(l),up(u){}//���캯��
    Node()//Ĭ�Ϲ��캯��
    {
        row=col=-1;
        val=0;
        left=up=NULL;
    }

};

template<class T>
class CrossLink
{
private:
    Node<T>**BaseRow;
    Node<T>**BaseCol;
    int rows;
    int cols;
    int counts;
public:
    CrossLink(int r,int c,int co);
    ~CrossLink();
    CrossLink<T>& pivotOp(int I0,int J0);//���������
    void Insert(int r,int c,int val);
    void set(int r,int c,int val); 
};


//���캯��
template<class T>
CrossLink<T>::CrossLink(int r,int c,int co)
:rows(r),cols(c),counts(co)
{
    int i=0;
    BaseCol=new Node<T>*[cols];
    BaseRow=new Node<T>*[rows];
    for(i=0;i<cols;i++)
    {
        BaseCol[i]=new Node<T>;
        BaseCol[i]->col=i;
    }
    for(i=0;i<rows;i++)
    {
        BaseRow[i]=new Node<T>;
        BaseRow[i]->row=i;
    }
    cout<<"����ɹ�"<<endl; 
}
//��������
template<class T>
CrossLink<T>::~CrossLink()
{
    Node<T>*p,*q;
    for(int i=0;i<rows;i++)
    {
        p=BaseRow[i]->left;
        if(p->col==-1)
        	delete BaseRow[i];
		else while(p->col!=-1)
		{
       	   	q=p->left;
            delete p;
            p=q;
        	delete BaseRow[i]; 
        }
    }
    delete []BaseRow;
    for(int i=0;i<cols;i++)
    {
        delete BaseCol[i];
    }
    delete[]BaseCol;
    cout<<"�����ɹ�"<<endl; 
}

template<class T>
CrossLink<T>& CrossLink<T>::pivotOp(int I0,int J0)
{
    //SP1:��ʼ�����õ�������
    Node<T>*temp=BaseRow[I0]->left;
    while(temp->col!=J0)
    {
        temp=temp->left;
    }
    const int a=1.0/(temp->val);
    temp->val=a;

    Node<T>*R0=BaseRow[I0];
    Node<T>*C0=BaseCol[J0];
    Node<T>*PTR[100];

    //SP2:��������I0
    R0=R0->left;
    int J=R0->col;
    while(J!=-1)
    {
        PTR[J]=BaseCol[J];
        R0->val*=a;
        R0=R0->left;
        J=R0->col;
    }
    //����״��R0�����е��׽ڵ㡡�ã������е��׽ڵ�
    //����һ�����顡ֻҪ���У���������ָ�����ͷ�ڵ�

    //sp3:�����Уɣ���ָ��R1
    while(1)
    {
        C0=C0->up;//������β�ڵ㿪ʼ����
        int I=C0->row;
        if(I<0)
            return*this;
        if(I==I0)
            continue; //��������
        Node<T>*R=BaseRow[I];//Rָ��ǰ���׽ڵ�
        Node<T>*R1=R->left;//R1ָ��ǰ��β�ڵ�
        //SP4:ȷ�����У�
        do
        {          //�������������е���Ϊ��
            R0=R0->left;//�ң�������β�ڵ㿪ʼ����
            J=R0->col;//J��¼������ָ��R0������
            if(J<0) break;
            if(J==J0) continue;
            //SP5:R1��ָԪ�����ڵ�������бȽ�
            while(R1->col>J)//ʼ�ձ���R1=R->LEFT
            //����ʹR1λ��J�С����ߡ��б�J�����J����
            {
                R=R1;
                R1=R->left;
            }


            if(R1->col==J)
            {
                //SP7:���������
                R1->val-=C0->val*R0->val;
                if(R1->val==0)//ɾ�������ң�
                {
                    PTR[J]->up=R1->up;//ʹPTR[J]->UPʼ���ǣ��д��������һ���ڵ� PTR[J]Ϊ�Ѵ�������һ��
                    R->left=R1->left;
                    delete R1;
                    R1=R->left;
                }
                else//
                {
                    PTR[J]=R1;
                    R=R1;
                    R1=R->left;
                }
            }
            else
            {
                //SP6:������Ԫ��
                Node<T>*X=new Node<T>;
                X->val=-C0->val*R0->val;
                X->row=I;
                X->col=J;
                X->left=R1;
                X->up=PTR[J]->up;
                R->left=X;
                R=X;
                PTR[J]->up=X;
                PTR[J]=X;
            }
        }
        while(J>=0);
        C0->val*=-a;//�Ը������н��д���
    }
}

template<class T>
void CrossLink<T>::set(int r,int c,int val)
{
	Node<T>*p0=BaseRow[r-1]->up;
	Node<T>*p=BaseRow[r-1];
	Node<T>*q=BaseCol[c-1];
	Node<T>*q0=BaseCol[c-1]->left;
	
	if(p0->col!=-1)
	{
		while(p0->col>c)
		{
			p0=p0->up;
			p->p->up;
		}
		if(p->col!=r)
		{
			X=new Node<T>(r,c,val,NULL,p0);
			p->up=X;
		}
		else
		{
			p0->row=rk
			p0->val=val;
		}
	}
	else
	{
		
	}
	if(q->row!=-1)
	{
		while(p0->col>c)
		{
			p0=p0->up;
			p->p->up;
		}
		if(p->col!=r)
		{
			X=new Node<T>(r,c,val,NULL,p0);
			p->up=X;
		}
		else
		{
			p0->row=rk
			p0->val=val;
		}
	}
}

int main() {
    CrossLink<int> A(3,5,3);

	return 0;
}

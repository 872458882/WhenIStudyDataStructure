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
    Node(int r,int c,T v,Node*l,Node*u):row(r),col(c),val(v),left(l),up(u){}//构造函数
    Node()//默认构造函数
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
    CrossLink<T>& pivotOp(int I0,int J0);//主步骤操作
    void Insert(int r,int c,int val);
    void set(int r,int c,int val); 
};


//构造函数
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
    cout<<"构造成功"<<endl; 
}
//析构函数
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
    cout<<"析构成功"<<endl; 
}

template<class T>
CrossLink<T>& CrossLink<T>::pivotOp(int I0,int J0)
{
    //SP1:初始化　得到１／ａ
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

    //SP2:处理主行I0
    R0=R0->left;
    int J=R0->col;
    while(J!=-1)
    {
        PTR[J]=BaseCol[J];
        R0->val*=a;
        R0=R0->left;
        J=R0->col;
    }
    //现在状况R0在主行的首节点　Ｃ０在主列的首节点
    //建立一个数组　只要主行Ｊ列有数就指向Ｊ列头节点

    //sp3:找新行Ｉ，并指定R1
    while(1)
    {
        C0=C0->up;//从主列尾节点开始左移
        int I=C0->row;
        if(I<0)
            return*this;
        if(I==I0)
            continue; //主行跳过
        Node<T>*R=BaseRow[I];//R指向当前行首节点
        Node<T>*R1=R->left;//R1指向当前行尾节点
        //SP4:确定新列Ｊ
        do
        {          //这是以主行上有的数为主
            R0=R0->left;//Ｒ０从主行尾节点开始左移
            J=R0->col;//J记录主行上指针R0所在列
            if(J<0) break;
            if(J==J0) continue;
            //SP5:R1所指元素所在的列与Ｊ列比较
            while(R1->col>J)//始终保持R1=R->LEFT
            //最终使R1位于J列　或者　列比J大但最靠近J的列
            {
                R=R1;
                R1=R->left;
            }


            if(R1->col==J)
            {
                //SP7:主步骤操作
                R1->val-=C0->val*R0->val;
                if(R1->val==0)//删除０　Ｒ１
                {
                    PTR[J]->up=R1->up;//使PTR[J]->UP始终是Ｊ列待处理的下一个节点 PTR[J]为已处理的最后一个
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
                //SP6:插入新元素
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
        C0->val*=-a;//对该行主列进行处理
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

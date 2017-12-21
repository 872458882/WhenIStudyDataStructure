#include <iostream>
#include <memory.h>
#include <fstream>
#include <stack>
#include <queue> 
#include <bitset>

using namespace std;

#define m 128

//哈夫曼树结点 
struct HuffmanNode
{
	string code;
	int weight;
	char data; 
	HuffmanNode*left;
	HuffmanNode*right;
};

int part(HuffmanNode* H[],int low,int high)
{
	
	//STEP1:选中间值元素 
	swap(H[(low+high)/2], H[low+1]);
	if(H[low+1]->weight > H[high]->weight) swap(H[low+1],H[high]);
	if(H[low+1]->weight > H[high]->weight) swap(H[low],H[high]);
	if(H[low+1]->weight > H[low]->weight)  swap(H[low],H[low+1]);

	//STEP2:
	int i=low;
	int j=high+1;
	HuffmanNode* pivot=H[low];
	while(i<j)
	{
		i++;
		while(H[i]->weight < pivot->weight) i++;
		j--;
		while(H[j]->weight > pivot->weight) j--;
		if(i<j)
			swap(H[i],H[j]);
	}
	swap(H[low],H[j]);
	return j;	
} 



void insertsort(HuffmanNode*H[],int n)
{
	for(int i=1;i<n;i++)
	{
		int j=i;
		HuffmanNode* temp=H[i];
		while(i>0 && temp->weight < H[j-1]->weight)
		{
			H[j]=H[j-1];
			j--;
		}
		H[j]=temp;
	}
}

void quicksort(HuffmanNode*H[],int low,int high,int M)
{
	stack<int>s;
	//int temp;
	int n=high-low+1;
	s.push(0);
	s.push(0);
	while(low < high)
	{
		int mid=part(H,low,high);
		if((mid-low<M) && (high-mid<M))
		{
			low=s.top(); s.pop();
			high=s.top();s.pop();
			continue;
		}
		if((mid-low<M)&&(high-mid>=M))
		{
			low=mid+1;continue;
		}
		if((mid-low>=M)&&(high-mid<M))
		{
			high=mid-1;continue;
		}
		if((mid-low>=M)&&(high-mid>=M))
		{
			if(mid-low>high-mid)
			{
				s.push(mid-1);s.push(low);
				low=mid+1;
			}
			else
			{
				s.push(high);s.push(mid+1);
				high=mid-1;
			}
		}
	}
	insertsort(H,n);
}



//哈夫曼树 
class Huffman
{
public:
	Huffman();
	~Huffman(){Del(root);}
	
	void GetAllWeight(string txtname);//读取文件中每个字符的次数
	
	void WritetoNode(HuffmanNode*H[]);//将次数和字符写入结点 
	
	void CodeNode();//给每个字符生成编码 
	
	void CodeFile(string filename);//给文件编码 
	
	void DecodeFile(string filename);//文件解码 
	
	void Del(HuffmanNode *t);
	
	HuffmanNode* FindC(HuffmanNode*t,char item);//huffman树中查找 
	
	
private: 
	int weight[m];//记录从ASCII码0-127的所有字符出现的次数 
	HuffmanNode* root; 
};


void Huffman::GetAllWeight(string txtname)
{	
	ifstream infile(txtname);
	memset(weight,0,sizeof(weight));
	char c;
	//统计每个字符出现的次数 
	if(infile.is_open())
	{ 
		
		while(infile.good() && !infile.eof())
		{
			c=infile.get();
			weight[c]++;
		}
	}
	else cout<<"读取文件失败!"<<endl;
	infile.close();
	
}

void Huffman::WritetoNode(HuffmanNode*H[])//将次数和字符写入结点 
{
	for(int i=0;i<m;i++)
	{
		H[i]->data=i;
		H[i]->weight=weight[i];
        H[i]->left=H[i]->right=NULL; 
	}
	//for(int i=0;i<m;i++)
	//	cout<<H[i]->data<<" "<<H[i]->weight<<endl;
} 

Huffman::Huffman()
{
	cout<<"请输入要编码的文件名"<<endl; 
    string txtname;
	cin>>txtname;
 	
    HuffmanNode* H[m];
	HuffmanNode*p1=NULL,*p2=NULL,*p,*t;
    //初始化 
    for(int i=0;i<m;i++)  
		H[i]=new HuffmanNode;
    //计算次数 
	GetAllWeight(txtname);
	
	//写入结点 
	WritetoNode(H);

    //排序
	quicksort(H,0,m-1,5); 
	 
	//for(int i=0;i<m;i++)
	//{
	//	cout<<H[i]->data<<" "<<H[i]->weight<<endl;
	//}
  	
	  //建树 
    for(int i=0;i<m-1;i++)
    {
   		t =new HuffmanNode;
		t->weight=H[i]->weight+H[i+1]->weight;
		t->left=H[i];
		t->right=H[i+1];
		//t->data='h';
		
		//cout<<"i="<<i<<"  d="<<t->data<<" w="<<t->weight<<" "<<"z="<<t->left->data<<t->left->weight<<" y="<<t->right->data<<t->right->weight<<endl;
		/*把新节点插入到H中*/ 
		int j=i+2;
		while(j<m && t->weight > H[j]->weight)
		{
			H[j-1]=H[j];
			j++;
		}
		H[j-1]=t;
	}
	root=H[m-1]; 
}


void Huffman::CodeNode() //每个节点生成huffman编码 
{
	cout<<"生成每个Huffman编码：\n"; 
	queue<HuffmanNode*> q;
	HuffmanNode*temp;
	q.push(root);
	root->code="";
	while(!q.empty())
	{
		temp=q.front();
		q.pop();
		if(temp->left==NULL&&temp->right==NULL)
			cout<<"字符\'"<<temp->data<<"\'的出现次数："<<temp->weight<<"  编码:"<<temp->code<<endl;
		if(temp->left!=NULL)
		{
			(temp->left)->code=temp->code+"0"; 
			q.push(temp->left);
		}
		
		if(temp->right!=NULL)
		{
			(temp->right)->code=temp->code+"1";
			q.push(temp->right);
		}
	}
	cout<<"生成编码完毕"<<endl; 
}

void Huffman::DecodeFile(string filename)
{
	ifstream infile(filename);
	ofstream outfile(filename+"decode.txt");

	if(infile.is_open()&&outfile.is_open())
	{ 
		HuffmanNode*t=root;
		char c;
		
		while(infile.good() &&(c=infile.get())!=infile.eof())
		{
			
			if(c=='0') t=t->left;
			else t=t->right;
			
			if(t->left==NULL && t->right==NULL)//检查是否可以编码成字符 
			{
				outfile<<t->data; 
				t=root; //重置t为根节点 
			}
		}
	}
	else cout<<"打开文件失败!"<<endl;
	infile.close();
	outfile.close();
} 

void Huffman::CodeFile(string filename)
{
	ifstream infile(filename);
	ofstream outfile(filename+"code.txt");
	char c;
	
	if(infile.is_open()&&outfile.is_open())
	{ 
		while(infile.good() && (c=infile.get())!=EOF&&outfile.good())
		{
			HuffmanNode*t=FindC(root,c); 
			outfile<<t->code;
		}
	}
	else cout<<"打开文件失败!"<<endl;
	cout<<"编码成功"<<endl;
	outfile.close();
	infile.close();
	
} 

HuffmanNode* Huffman::FindC(HuffmanNode*t,char item)
{
	HuffmanNode *p;
    
	//递归出口
    if(t==NULL) return t;
    if(t->data==item) return t;
    
	//递归
    p=FindC(t->left,item);
    if(p!=NULL) return p;
    p=FindC(t->right,item);
    if(p!=NULL) return p;
    
    return NULL;
}

void Huffman::Del(HuffmanNode *t)
{
	if(t != NULL)
	{
    	Del(t->left);
    	Del(t->right);
    	delete t;
	}
}	 

int main()
{
	Huffman A;
	A.CodeNode(); 
	A.CodeFile("yigewenjian.txt");
	A.DecodeFile("yigewenjian.txtcode.txt") ;
 } 


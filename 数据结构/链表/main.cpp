#include"SLList.h" 


int main()
{
	SLList<int> A(5);
	cout<<"建立一个第一个节点data值为5的链表"<<endl; 
	A.output();
	cout<<"在尾结点插入一个节点，data值为6"<<endl; 
	A.InsertFromTail(6);
	cout<<"在首结点后插入一个节点，data值为2"<<endl; 
	A.InsertFromHead(2);
	A.SetCH();
	cout<<"把当前指针指向头节点"<<endl; 
	A.Insert(9);
	cout<<"当前指针后插入9"<<endl; 
	A.Insert(10);
	cout<<"当前指针后插入10"<<endl; 
	A.Insert(11);
	cout<<"当前指针后插入11"<<endl; 
	A.output();
	A.SetCK(2);
	cout<<"把当前结点设为第二个结点，并分别用两个取数函数输出第二个结点的值："<<endl; 
	int tmp;
	A.Findc(tmp);
	cout<<tmp<<endl;
	A.Findk(2,tmp);
	cout<<tmp<<endl;
	cout<<"把当前结点设为第三个结点，并分别用两个存数函数把第三个第四个结点的值变为7和8："<<endl; 
	A.SetCK(3);
	A.Storec(7);
	A.Storek(4,8);
	A.output(); 
	cout<<"6在第"<<A.Search(6)<<"个结点"<<endl; 
	A.output();

	A.SetCK(3);
	cout<<"删除第三个结点,它的data域为：";
	A.Delete(tmp);
	cout<<tmp<<endl;
	A.output(); 
	cout<<"删除第一个结点,它的data域为：";
	A.DeleteFromHead(tmp);
	cout<<tmp<<endl;
	cout<<"链表中还剩下：" ; 
	A.output();
	cout<<"从表尾删除结点，它的data域为："; 
	A.DeleteFromTail(tmp);
	cout<<tmp<<endl;
	A.Reverse();A.output();
	
}


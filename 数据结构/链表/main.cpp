#include"SLList.h" 


int main()
{
	SLList<int> A(5);
	cout<<"����һ����һ���ڵ�dataֵΪ5������"<<endl; 
	A.output();
	cout<<"��β������һ���ڵ㣬dataֵΪ6"<<endl; 
	A.InsertFromTail(6);
	cout<<"���׽������һ���ڵ㣬dataֵΪ2"<<endl; 
	A.InsertFromHead(2);
	A.SetCH();
	cout<<"�ѵ�ǰָ��ָ��ͷ�ڵ�"<<endl; 
	A.Insert(9);
	cout<<"��ǰָ������9"<<endl; 
	A.Insert(10);
	cout<<"��ǰָ������10"<<endl; 
	A.Insert(11);
	cout<<"��ǰָ������11"<<endl; 
	A.output();
	A.SetCK(2);
	cout<<"�ѵ�ǰ�����Ϊ�ڶ�����㣬���ֱ�������ȡ����������ڶ�������ֵ��"<<endl; 
	int tmp;
	A.Findc(tmp);
	cout<<tmp<<endl;
	A.Findk(2,tmp);
	cout<<tmp<<endl;
	cout<<"�ѵ�ǰ�����Ϊ��������㣬���ֱ����������������ѵ��������ĸ�����ֵ��Ϊ7��8��"<<endl; 
	A.SetCK(3);
	A.Storec(7);
	A.Storek(4,8);
	A.output(); 
	cout<<"6�ڵ�"<<A.Search(6)<<"�����"<<endl; 
	A.output();

	A.SetCK(3);
	cout<<"ɾ�����������,����data��Ϊ��";
	A.Delete(tmp);
	cout<<tmp<<endl;
	A.output(); 
	cout<<"ɾ����һ�����,����data��Ϊ��";
	A.DeleteFromHead(tmp);
	cout<<tmp<<endl;
	cout<<"�����л�ʣ�£�" ; 
	A.output();
	cout<<"�ӱ�βɾ����㣬����data��Ϊ��"; 
	A.DeleteFromTail(tmp);
	cout<<tmp<<endl;
	A.Reverse();A.output();
	
}


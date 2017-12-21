#include <iostream>
#include "CList.h"
using namespace std; 



int main() {
/*
	//Ñ­»·Á´±í²âÊÔ´úÂë 
	int TMP;
	CList<int> A(5);
	A.InsertFromHead(7);
	A.InsertFromHead(9);
	A.Findc(TMP);
	cout<<TMP;
	A.SetCK(2);
	A.Insert(4);
	A.output();
	A.DeleteFromHead(TMP);
*/

	CList<char> bracket;
	char read_in=cin.get();
	bool is_matched=true;
	while(is_matched&&read_in!='\n')
	{
		if(read_in=='{'||read_in=='['||read_in=='(')
			bracket.InsertFromHead(read_in);
		if(read_in=='}'||read_in==']'||read_in==')')
		{
			if(bracket.IsEmpty())
			{
				cout<<"Unmatched closing bracket"<<read_in<<"is detected"<<endl;
				is_matched=false;
				return 0;
			}
			char open_bracket;
			bracket.DeleteFromHead(open_bracket);
			is_matched=(open_bracket=='('&&read_in==')')||(open_bracket=='['&&read_in==']')||(open_bracket=='{'&&read_in=='}');
			if(!is_matched)
			{
				cout<<"Bad match"<<open_bracket<<read_in<<endl;
				return 0;
			}
		}
		read_in=cin.get();
	}
	cout<<"Good match"<<endl;

	return 0;
}

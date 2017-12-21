#include <iostream>
#include <map>
#include <set>
#include <vector>
using namespace std; 

map<int,int> MAP[3];
set<int> SET;
int main() {
	int a,b;
	int i=0;
	while(i<2)
	{
		cout<<"the first/second"<<endl;
		while(scanf("%d %d",&b,&a)&&(a||b))
		{
			MAP[i][a]+=b;
			SET.insert(a); 
		}
		i++;
	}
	for(set<int>::iterator it=SET.begin();it!=SET.end();it++)
	{
		MAP[2][*it]=MAP[0][*it]+ MAP[1][*it]; cout<<2333<<endl; 
	}
	for(map<int,int>::iterator it2=MAP[2].begin();it2!=MAP[2].end();it2++)
	{
		cout<<it2->second<<"x^"<<it2->first<<" ";
		
	}
	return 0;
}

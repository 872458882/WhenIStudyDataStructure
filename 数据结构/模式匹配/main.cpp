#include<iostream>
#include<string>
using namespace std;


int fun(string A,string B)//用模式首字母和尾字母匹配的算法
{

    char temp1=B[0],temp2=B[B.length()];
    int i=0,j=1;
    int i1=i+B.length()-1;
    int j1=j+B.length()-1;
    while(j<B.length()&&i<(A.length()-B.length()))
    {
        if(A[i]!=B[j-1]&&A[i1]!=b[j1-1])
        {
            i++;
            j=1;
            continue;
        }
        else
        {
            string A1=assign(A,int i+1,int i1-1);
            string B1=assign(B,1,B.length()-2)
            if(fun(A1,B1)==-1)
            {
                i++;j=1;
                continue;
            }
        }
    }
}
int KMP(string A,string B)//KMP模式匹配算法
{

}
int fail(string A)//模式A的失败算法
{

}
int main()
{
    string A="happy23333";
    string B="py2";

    return 0;
}
int main()
{
    string A="happy";
    string B="pp";
    cout<<fun(A,B)<<endl;
    return;
}

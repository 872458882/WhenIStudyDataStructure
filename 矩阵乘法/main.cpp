#include <iostream>

using namespace std;

void multi(int*A,int*B,int*C,int m,int n,int p)
{
    int ca=0,cb=0,cc=0;
    C[cc]=0;
    for(int i=0;i<m;i++)
    {
        ca=i*n;
        for(int j=0;j<p;j++)
        {
            cb=j;
            for(int k=0;k<n;k++)
            {
                C[cc]+=C[cc]+A[ca]*B[cb];
                cout<<C[cc]<<" "<<cc<<endl;
                ca+=1;
                cb+=p;
            }

        }
    }
}
int main()
{
    int A[2]={1,2};
    int B[2]={1,2};
    int C[1];
    multi(A,B,C,1,2,1);
    cout<<C[0]<<endl;
}

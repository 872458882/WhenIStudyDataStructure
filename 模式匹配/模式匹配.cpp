#include<iostream>
#include<string>
using namespace std;

void get_nextval(const char *T, int next[])
{
    // 求模式串T的next函数值并存入数组 next。
    int j = 0, k = -1;
    next[0] = -1;
    while ( T[j] != '\0' )
    {
        if (k == -1 || T[j] == T[k])
        {
            ++j; ++k;
            if (T[j]!=T[k])
                next[j] = k;
            else
                next[j] = next[k];
        }
        else
            k = next[k];
    }
    cout<<"FAIL:"<<endl; 
    for(int j=0;T[j]!='\0';j++)
	{
		cout<<"t["<<j<<"]="<<(char)T[j]<<"   "<<(int)next[j]<<endl;
	 } 
}
int KMP(const char *Text,const char* Pattern)//const 表示函数内部不会改变这个参数的值。
{
    //SP1:判断是否为空指针或空串
    if(Text==NULL||Pattern==NULL||Text[0]=='\0'||Pattern[0]=='\0') return -1;

    //SP2:得到模式串的长度
    const char* p=Pattern;
    int len=0;
    while(*p++) len++;

    //SP3:求Pattern的next函数值
    int next[len+1];
    get_nextval(Pattern,next);

    //SP4:模式匹配
    int index=0,i=0,j=0;
    while(Text[i]!='\0'&& Pattern[j]!='\0')
    {
        if(Text[i]== Pattern[j])// 若匹配继续比较后继字符
        {
        	cout<<"匹配，继续比较后继字符"<<endl;
            ++i;
            ++j;
        }
        else
        {
            index += (j-next[j]);
            cout<<"intdex+= (j-next[j]);"<<endl;
            if(next[j]!=-1)
                {j=next[j];cout<<"if next[j]!=-1;模式串右移.j=next[j]"<<endl;}// 模式串向右移动
            else
            {
            	cout<<"从0开始"<<endl; 
                j=0;
                ++i;
                
            }
        }
    }
    if(Pattern[j]=='\0')
        return index;// 匹配成功
    else
        return -1;
}

int main()//abCabCad
{
    char text[100]="bababCabCadcaabcaababcbaaaabaaacababcaabc";
    char pattern[100]="abCad";
    cout<<KMP(text,pattern)<<endl;
    return 0;
}


#include<iostream>
#include<string>
using namespace std;

void get_nextval(const char *T, int next[])
{
    // ��ģʽ��T��next����ֵ���������� next��
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
int KMP(const char *Text,const char* Pattern)//const ��ʾ�����ڲ�����ı����������ֵ��
{
    //SP1:�ж��Ƿ�Ϊ��ָ���մ�
    if(Text==NULL||Pattern==NULL||Text[0]=='\0'||Pattern[0]=='\0') return -1;

    //SP2:�õ�ģʽ���ĳ���
    const char* p=Pattern;
    int len=0;
    while(*p++) len++;

    //SP3:��Pattern��next����ֵ
    int next[len+1];
    get_nextval(Pattern,next);

    //SP4:ģʽƥ��
    int index=0,i=0,j=0;
    while(Text[i]!='\0'&& Pattern[j]!='\0')
    {
        if(Text[i]== Pattern[j])// ��ƥ������ȽϺ���ַ�
        {
        	cout<<"ƥ�䣬�����ȽϺ���ַ�"<<endl;
            ++i;
            ++j;
        }
        else
        {
            index += (j-next[j]);
            cout<<"intdex+= (j-next[j]);"<<endl;
            if(next[j]!=-1)
                {j=next[j];cout<<"if next[j]!=-1;ģʽ������.j=next[j]"<<endl;}// ģʽ�������ƶ�
            else
            {
            	cout<<"��0��ʼ"<<endl; 
                j=0;
                ++i;
                
            }
        }
    }
    if(Pattern[j]=='\0')
        return index;// ƥ��ɹ�
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


#include <iostream>
#include <fstream>
#include <queue>
#include <stack>
#include <cmath>
#include <string> 
#include <time.h> 
#include <sys/timeb.h>
using namespace std;
class ComNet;
class NetLine;
class Menu
{
public:
	Menu():numofnet(0){} 
	void MainMenu();
	void Welcome();
	void CreateNewNet();
	void ReadNet(int which);
	void NetsMenu();
	void CreateNewNet0();
	void DeleteNet(int which);
	int numofnet;
	ComNet* COMNET[100];
	NetLine* templine[1000];
	int cities[100];
}menu; 
 
class NetLine
{
public:
	int x;
	int y;
	NetLine(int tempx,int tempy):x(tempx),y(tempy){}
};


class ComNet
{
	public:
		friend class Menu;
		
		ComNet();
	
		ComNet(const ComNet& obj);
	
		~ComNet();
		
		void getTestData(NetLine**path,int which); //���ɲ������� 

		bool loadTestData(NetLine**path,int which); //���������ļ�		
		
		void ConstructSecond(NetLine**path); //����2 
		
		void ConstructFirst(NetLine**path); //����1 
		
		int CityCenterTest(int *x,bool Out=0);//�ؼ����м��  
		
		int LineReliableCheck(bool Out=0);  //��·�ɿ���� 
		
		bool IsExcess(int x,int y);//�����·(x,y)�Ƿ����� 
		
		static bool IsConnectAccord(const ComNet& before,const ComNet& after,int a=0/*��ѡ*/);//��⣨���a!=0�����a�㣩����ͨ����ͬ 
		
		bool Insert(int from, int to)
		{ 
			if(from>0 && to>0 && from<=iCityNum && to<=iCityNum)
			{Line[from-1][to-1]=Line[to-1][from-1]=1;return 1;}
			else return 0;
		} 
		bool Insert(NetLine* line)
		{
		 	int from=line->x;int to=line->y;
			if(from>0 && to>0 && from<=iCityNum && to<=iCityNum)
			{	Line[from-1][to-1]=Line[to-1][from-1]=1;return 1;}
			else return 0;
		} 
		
		bool Delete(int from, int to)
		{ 
			if(from>0 && to>0 && from<=iCityNum && to<=iCityNum)
			{Line[from-1][to-1]=Line[to-1][from-1]=0;return 1;}
			else return 0;
		}
		bool Delete(NetLine* line)
		{ 
			int from=line->x;int to=line->y;
			if(from>0 && to>0 && from<=iCityNum && to<=iCityNum)
			{Line[from-1][to-1]=Line[to-1][from-1]=0;return 1;}
			else return 0;
		}
		
		
		//���ظ�ֵ����� 
		ComNet* operator=(const ComNet& obj);
		 
		int getCityNum(){return iCityNum;}
		int getLineNum(){return iLineNum;}
		
		void DrawInWindows();//��ͼ 
		void Output();//��� 
		
	private:
		int maxCityNum;
		int maxLineNum;
		int iCityNum;//������ 
		int iLineNum;//��·��	
		int **Line;
};


//���캯��
ComNet::ComNet():maxCityNum(100),maxLineNum(1000)
{
	int i=0,j=0;
	Line = new int*[maxCityNum];
	for(i=0; i<maxCityNum; i++)
		Line[i] = new int[maxCityNum];
	for(i=0;i<maxCityNum;i++)
		for(int j=0;j<maxCityNum;j++)
			Line[i][j]=0;
} 


ComNet::ComNet(const ComNet& obj) //�������캯�� 
:maxCityNum(obj.maxCityNum),maxLineNum(obj.maxLineNum),iCityNum(obj.iCityNum),iLineNum(obj.iLineNum)
{
	int i=0,j=0;
	Line = new int*[maxCityNum];
	for(i=0; i<maxCityNum; i++)
		Line[i] = new int[maxCityNum];
	for(i=0; i<iCityNum; i++)
		for(j=0; j<iCityNum ;j++)
			Line[i][j]=obj.Line[i][j];
}

//�������� 
bool ComNet::loadTestData(NetLine**path,int index)
{
	char atxt[4]; 
	itoa(index,atxt,10);
	string ttxt="text";
	ttxt+=atxt;
	ttxt+=".txt";
	FILE*fp;
	if((fp=fopen(ttxt.c_str(),"r"))==NULL){printf("�ļ��򲻿��������Ƿ��������\n");system("pause");return 0;}
	int tempx=0,tempy=0;
	cout<<"=========================================================="<<endl;
	cout<<"\n������ɳ��м��ͨѶ��·Ϊ��\n"; 
	fscanf(fp,"%d %d\n",&iCityNum,&iLineNum);
	for(int i=0;i<iLineNum&&!feof(fp);i++)
	{
				
		fscanf(fp,"(%d,%d) ",&tempx,&tempy);
		
		if(tempx == tempy) //����Ƿ�tempX=tempY
		{ 
			cout<<"�ļ������ݲ���ȷ�������ļ��Ƿ����Ҫ��"<<endl; 
			return 0;
		}		
			
		int j;
		for(j=0;j<i;j++) //����Ƿ���Ѿ����ɵ��ظ� 
			if((tempx==path[j]->x && tempy==path[j]->y)||(tempx==path[j]->y&&tempy==path[j]->x))
			{
				cout<<"�ļ������ݲ���ȷ�������ļ��Ƿ����Ҫ��"<<endl; 
				return 0;
			}
					
		path[i]=new NetLine(tempx,tempy);
		printf("(% 3d,% 3d) ",path[i]->x,path[i]->y);
		if(i%8==7) printf("\n"); 
	}
	cout<<"\n�ļ��������"<<endl; 
	fclose(fp);
	system("pause");
	return 1;
}


//���ɲ�������
void ComNet::getTestData(NetLine **path,int which)
{
	printf("\n");
	printf("   \n");  
	cout<<"=========================================================="<<endl;
	printf("\n");  
	printf("��������и�����ͨѶ��·���� \n");  
	printf("(��������ͨѶ��·��Ӧ�ں���Χ��) ");
	printf("\n");
	cin>> iCityNum >> iLineNum; 
	while(iCityNum<1||iLineNum<1||iCityNum>100||iCityNum*(iCityNum-1)/2 < iLineNum||iLineNum>1000)
	{
		cout<<"���벻����, ����������.\n";
		cin>>iCityNum>>iLineNum; 
	} 
	char atxt[4]; 
	itoa(which,atxt,10);
	int tempx=0,tempy=0; 
	string ttxt="text";
	ttxt+=atxt;
	ttxt+=".txt";
	ofstream fout(ttxt);
	fout<<iCityNum<<" "<<iLineNum<<endl;
	cout<<"=========================================================="<<endl;
	cout<<"\n������ɳ��м��ͨѶ��·Ϊ��\n"; 
	for(int i=0;i<iLineNum&&fout.is_open();i++)
	{
		//�������һ����ͬ��(tempx,tempy)�� 
 		bool flag=0; //flag==1������� 
		while(!flag) //��鲻�������� 
		{
			tempx = rand()%iCityNum + 1;
			tempy = rand()%iCityNum + 1; 
			
			if(tempx == tempy) //����Ƿ�tempX=tempY
				continue; 
				
			int j;
			for(j=0;j<i;j++) //����Ƿ���Ѿ����ɵ��ظ� 
				if((tempx==path[j]->x && tempy==path[j]->y)||(tempx==path[j]->y&&tempy==path[j]->x))
					break;
					
			if(j==i) {flag=1;}//�����˳�ѭ����û���ظ� 
		
		}
	
		path[i]=new NetLine(tempx,tempy);
		
		printf("(% 3d,% 3d) ",path[i]->x,path[i]->y);
		fout<<"("<<path[i]->x<<","<<path[i]->y<<") ";
		if(i%8==7) {printf("\n");} 
	}
	
	cout<<endl;
	
	fout.close();
	cout<<"���ݹ̻����ļ�\""<<ttxt<<"\"��"<<endl; 
 
	cout<<"=========================================================="<<endl;
	system("pause");
}


void ComNet::ConstructSecond(NetLine**path)//���ɸ������� 
{
	cout<<"====================================================="<<endl; 
	cout<<"�������ɵڶ�������"<<endl;
	for(int i=0;i<iLineNum;i++)
	{
		Insert(path[i]->x,path[i]->y); 
	}
	cout<<"�������"<<endl;
	system("pause");
}



void ComNet::ConstructFirst(NetLine** path)//���ɼ����� 
{
	cout<<"======================================================"<<endl;
	cout<<"���ڸ������ݹ���������"<<endl; 
	for(int i=0;i<iLineNum;i++)
	{
		bool t=IsExcess(path[i]->x, path[i]->y);
		if(t)
			printf("   (% 3d,% 3d)��������·����������·��\n",path[i]->x, path[i]->y); 	
	
		else
		{
			printf("   (% 3d,% 3d)����������·��������·��\n",path[i]->x, path[i]->y); 	
			Insert(path[i]); 
		}
	}
	system("pause");
} 


int ComNet::CityCenterTest(int *CenterCity, bool Out)//�ɿ��Լ�鲢����ؼ�����(��ѡ) ,���عؼ�������Ŀ 
{
	int i=0,j=0; 
	ComNet tempobj(*this);
	int num=0;
	for(i=0;i<iCityNum;i++)//ÿ�����б��� 
	{
		ComNet tempobj(*this);
		for(j=0;j<iCityNum;j++) //ɾ��ֱ�������� 
		{ 
			tempobj.Delete(i+1,j+1);
		}
		//cout<<"i=="<<i+1<<endl;
		if(!IsConnectAccord(*this,tempobj,i+1))
		{
			CenterCity[num++]=i+1;
		}
	}
	if(Out)
	{
		if(num) 
		{	
			cout<<"�ؼ�����(��Ҫ���佻����)��"<<endl;
			for(int i=0;i<num;i++)
				cout<<CenterCity[i]<<" ";
			cout<<endl; 
		}
		else cout<<"û�йؼ�����,����Ҫ���佻����!"<<endl; 
	}
	system("pause");
	return num;
}



int ComNet::LineReliableCheck(bool Out)//�ɿ��Լ�鲢������ɿ���·����ѡ�� 
{
	ComNet tempobj(*this);
	int i=0;//��ʱ 
	int j=0;//���� 
	int k=0;
	int x[iLineNum],y[iLineNum];
	NetLine* UnRe[iLineNum]; 
	for(int a=0;a<iCityNum;a++)
		for(int b=0;b<a;b++)
			if(Line[a][b]){x[k]=a+1;y[k++]=b+1;}
	for(i=0;i<iLineNum;i++)
	{
		ComNet tempobj(*this);
		tempobj.Delete(x[i],y[i]);
		if(!IsConnectAccord(*this,tempobj))
		{
			UnRe[j++] = new NetLine(x[i],y[i]);
		}
	}
	
	if(Out)
	{
		if(!j) 
		{
			cout<<"�޲��ɿ���·,����ɿ�"<<endl; 
			return 0;
		}
		else
		{
			cout<<"���ɿ���·��:"<<endl; 
			for(i=0;i<j;i++)
			{	
				cout<<"("<<UnRe[i]->x<<","<<UnRe[i]->y<<") ";
				if(i%8==7) cout<<endl;
			}
		}
	}
	system("pause");
	for(i=0;i<j;i++) delete UnRe[i];
	if(!j) return 0; 
	return 1; 
	
}


bool ComNet::IsExcess(int x,int y)               //����Ƿ����� 
{
	int i=0,j=0,k=0;
	bool Connect[iCityNum][iCityNum];
	for(int i=0;i<iCityNum;i++)
	{
		for(int j=0;j<iCityNum;j++)
		{
			Connect[i][j]=Line[i][j];
		}
	}		
	for(k=0; k<iCityNum; k++) 
		for(i=0; i<iCityNum; i++)
			if(k!=i)
			{
				for(j=0;j<iCityNum;j++)
					if(j!=k && j!=i && (Connect[i][k]||Connect[k][i]) && (Connect[k][j]||Connect[j][k]))
					{
						Connect[i][j]=Connect[j][i]=1;
					}
			}
	
	if(Connect[x-1][y-1]) return 1;
	return 0;
}


bool ComNet::IsConnectAccord(const ComNet& before,const ComNet& after,int a)      //����Ƿ�ɼ���һ�� 
{
	int i=0,j=0,k=0;
	if(before.iCityNum!=after.iCityNum) {cout<<"������������"<<endl;return 0;} 
	bool Connectb[before.iCityNum][before.iCityNum];
	bool Connecta[after.iCityNum][after.iCityNum];
	for(i=0;i<before.iCityNum;i++)
	{
		for(j=0;j<before.iCityNum;j++)
		{
			Connectb[i][j]=before.Line[i][j];
			Connecta[i][j]=after.Line[i][j];
		}
	}
		
	for(k=0; k<before.iCityNum; k++) 
		for(i=0; i<before.iCityNum; i++)
			if(k!=i)
			{
				for(j=0;j<before.iCityNum;j++)
					if(j!=k &&i!=j&& (Connecta[i][k]||Connecta[k][i]) && (Connecta[k][j]||Connecta[j][k]))
						Connecta[i][j]=Connecta[j][i]=1;
			}
	
	for(k=0; k<before.iCityNum; k++) 
		for(i=0; i<before.iCityNum; i++)
			if(k!=i)
			{
				for(j=0;j<before.iCityNum;j++)
					if(j!=k &&i!=j&& (Connectb[i][k]||Connectb[k][i]) && (Connectb[k][j]||Connectb[j][k]))
						Connectb[i][j]=Connectb[j][i]=1;
			}
	
/*	for(j=0; j<before.iCityNum; j++) 
	{
		for(i=0; i<before.iCityNum; i++)
			cout<<"c"<<Connecta[j][i]<<" ";
		cout<<endl;
	}
*/	
	if(a==0)
	{
		for(i=0;i<before.iCityNum;i++)
			for(j=0;j<i;j++)
				if(Connecta[i][j]!=Connectb[i][j])//��ԭ���ɼ��Ծ����пɼ�,��ɾ��һֱ�ӱߺ󲻿ɼ��ˣ���Ϊ���ɿ���
					return 0;			
	}
	else for(i=0;i<before.iCityNum;i++)
		for(j=0;j<i;j++)
		{
			if(i!=a-1&&j!=a-1&&Connecta[i][j]!=Connectb[i][j])//��ԭ���ɼ��Ծ����пɼ�,��ɾ��һ��󲻿ɼ��ˣ���Ϊ���ɿ��� ,���Ա�ɾ���ĵ� 
				return 0;
		}
	return 1; 
}

void ComNet::Output()
{
	for(int i=0;i<iCityNum;i++)
	{
		for(int j=0;j<iCityNum;j++)
			cout<<Line[i][j]<<" ";
	}
	system("pause");
}


void ComNet::DrawInWindows()
{
	//����ÿ��������� 
	//4������[0,200][200,400] 
	int pos[2] ={0,200}; 
	int posx[iCityNum];
	int posy[iCityNum];
	for(int i=0;i<iCityNum;i++)
	{
		int part = i%4; 
		posx[i] = rand()%200 +pos[i%2];
		posy[i] = rand()%200 +pos[i/2];
	}
	//����============================================================================ 
	//����============================================================================ 
	//����============================================================================ 
	//����============================================================================ 
	//����============================================================================ 
	//����============================================================================ 
	//����============================================================================ 
	//����============================================================================ 
	//����============================================================================ 
	//����============================================================================ 
	//����============================================================================ 
	//����============================================================================ 
	//����============================================================================ 
	//����============================================================================ 
	//����============================================================================ 
	//����============================================================================ 
	//����============================================================================ 
	//����============================================================================ 
	//����============================================================================ 
	//����============================================================================ 
	//����============================================================================ 
	//����============================================================================ 
	//����============================================================================ 
	//����============================================================================ 
	//����============================================================================ 
	system("pause");
}





ComNet* ComNet::operator=(const ComNet& obj)
{
	int i=0,j=0; 
	iCityNum = obj.iCityNum;
	iLineNum = obj.iLineNum;
	Line = new int*[iCityNum];
	for(i=0; i<iCityNum; i++)
		Line[i] = new int[iCityNum];
	for(i=0; i<iCityNum; i++)
		for(j=0; j<iCityNum ;j++)
			Line[i][j]=obj.Line[i][j];
	return this;
} 


ComNet::~ComNet()         //�������� 
{
	for(int i=0;i<iCityNum;i++)
		delete []Line[i];
	delete [] Line;
}


void Menu::Welcome()     //��ӭ����
{
	printf("\n");
	printf("                            \n");  
	printf("����������������������������������������������������������������\n");  
	printf("��                                                            ��\n");  
	printf("��                      ���ݽṹ�γ����                      ��\n");  
	printf("��                       ��������������                       ��\n");
	printf("��                                                            ��\n");
	printf("��                     ����˵ʲô��                           ��\n"); 
	printf("��                                                            ��\n"); 
	printf("����������������������������������������������������������������\n");  
	printf("\n"); 
	system("pause");
} 



void Menu::CreateNewNet()
{
	system("CLS");
	printf("\n");

	int order=-1;        //��ʾ�˵�
	printf("\n");
	printf("                      ��������������������                   \n");  
	printf("������������������������������% 4d�����穧����������������������\n",numofnet+1);  
	printf("��                    ��������������������                    ��\n");  
	printf("��                                                            ��\n");  
	printf("��           ��1����ȡ�����ļ�����                            ��\n");  
	printf("��                                                            ��\n");  
	printf("��           ��2������ȫ������                                ��\n");
	printf("��                                                            ��\n");
	printf("��           ��3���鿴����������                              ��\n");
	printf("��                                                            ��\n");   
	printf("��           ��3���ص����˵�                                  ��\n");        
	printf("��                                                            ��\n");  
	printf("����������������������������������������������������������������\n");  
	printf("\n");
	printf("���������:��   ��\b\b\b");  
	for(;;)                     //ѡ����
	{
		scanf("%d",&order);
		switch(order) 
		{  
			case 1: 	
				COMNET[numofnet] = new ComNet;
				numofnet++; 
				int index;
				cout<<"�������ļ�����"<<endl;
				cin>>index;
				COMNET[numofnet-1]->loadTestData(templine,index); 
				CreateNewNet0(); 
				break;
			case 2:
				COMNET[numofnet] = new ComNet;
				numofnet++; 
				COMNET[numofnet-1]->getTestData(templine,numofnet-1);
				CreateNewNet0();
				break;
			case 3: NetsMenu();break; 
			case 4: MainMenu();break;
			default: printf("��������ȷ����ţ���"); break; 
		} 
		
	}	
}

void Menu::CreateNewNet0()
{
	system("CLS");
	printf("\n");

	int order=-1;        //��ʾ�˵�
	printf("\n");
	printf("                      ��������������������                   \n");  
	printf("������������������������������% 4d�����穧����������������������\n",numofnet+1);  
	printf("��                    ��������������������                    ��\n");  
	printf("��                                                            ��\n");  
	printf("��           ��1���������෽ʽ����                            ��\n");  
	printf("��                                                            ��\n");  
	printf("��           ��2���Կ����෽ʽ����                            ��\n");
	printf("��                                                            ��\n");
	printf("��           ��3���鿴����������                              ��\n");
	printf("��                                                            ��\n");   
	printf("��           ��3���ص����˵�                                  ��\n");        
	printf("��                                                            ��\n");  
	printf("����������������������������������������������������������������\n");  
	printf("\n");
	printf("���������:��   ��\b\b\b");  
	for(;;)                     //ѡ����
	{
		scanf("%d",&order);
		switch(order) 
		{  
			case 1: 	
				COMNET[numofnet-1]->ConstructFirst(templine); 
				ReadNet(numofnet-1);
				break;
			case 2:
				COMNET[numofnet-1]->ConstructSecond(templine);
				ReadNet(numofnet-1);
				break;
			case 3:
				printf("ȷ��ֹͣ������ ��1��ȷ�� ��2����������\n"); 
				scanf("%d",&order);
				if(order==1)
				{
					COMNET[numofnet-1]=NULL;
					numofnet--; 
					NetsMenu();
				}
				if(order==2)
					CreateNewNet0(); 
				break; 
			case 4: 
				printf("ȷ��ֹͣ������ ��1��ȷ�� ��2����������\n"); 
				scanf("%d",&order);
				if(order==1)
				{
					COMNET[numofnet-1]=NULL;
					numofnet--; 
					MainMenu();
				}
				if(order==2)
					CreateNewNet0(); 
				MainMenu();
				break;
			default: printf("��������ȷ����ţ���"); break; 
		} 
		
	}	
}
void Menu::ReadNet(int which)
{
	system("CLS");
	int order=-1;        //��ʾ�˵�
	printf("\n");
	printf("                      ��������������������                   \n");  
	printf("������������������������������% 4d�Ĳ���������������������������\n",which+1);  
	printf("��                    ��������������������                    ��\n");  
	printf("��                                                            ��\n");  
	printf("��           ��1����ʾ������                                  ��\n");  
	printf("��                                                            ��\n");  
	printf("��           ��2���ɿ��Լ��                                  ��\n");
	printf("��                                                            ��\n");    
	printf("��           ��3���鿴�������䱸����                          ��\n");
	printf("��                                                            ��\n");  
	printf("��           ��4��ɾ��������                                  ��\n");  
	printf("��                                                            ��\n");  
	printf("��           ��5���鿴��������                                ��\n");  
	printf("��                                                            ��\n");  
	printf("����������������������������������������������������������������\n");  
	printf("\n");
	printf("���������:��   ��\b\b\b");  
	
	for(;;)                     //ѡ����
	{
		scanf("%d",&order);
		switch(order) 
		{  
			case 1: COMNET[which]->DrawInWindows(); ReadNet(which);break;
			case 2: COMNET[which]->LineReliableCheck(1);ReadNet(which);break;
			case 3: COMNET[which]->CityCenterTest(cities,1);ReadNet(which); break;
			case 5: NetsMenu();break;
			case 4: DeleteNet(which);break; 
			default: printf("��������ȷ����ţ���"); break; 
		} 
		
	}
}


void Menu::NetsMenu()
{
	system("CLS");
	int order=-1;        //��ʾ�˵�
	printf("\n");
	printf("                      ��������������������                   \n");  
	printf("������������������������   ��ǰ����     ������������������������\n");  
	printf("��                    ��������������������                    ��\n");  
	printf("��                                                            ��\n");  
	if(numofnet==0){
	printf("��           ��ǰû�����������                               ��\n");
	printf("��                                                            ��\n"); 
	printf("��                                                            ��\n"); 
	printf("����������������������������������������������������������������\n"); 
	system("pause");
	MainMenu();
	}
	
	printf("��                                                            ��\n"); 
	printf("��           ��ǰ������%4d������                              ��\n",numofnet);
	printf("��                                                            ��\n");  
	
	
	printf("��                                                            ��\n");  
	printf("����������������������������������������������������������������\n");  
	printf("\n");
	printf("�����������������(1~%4d),����0����������,����999�ص����˵�:��   ��\b\b\b",numofnet);  
	
	cin>>order;
	while((order<0||order>numofnet)&&order!=999)
	{
		cout<<"��������ȷ���������\n";
		cin>>order; 
	}
	if(order==0) CreateNewNet();
	else if(order==999) MainMenu();
	else ReadNet(order-1);
}

 

void Menu::MainMenu()    //���˵�
{
	system("CLS");
	int order=-1;        //��ʾ�˵�
	printf("\n");
	printf("                      ��������������������                   \n");  
	printf("������������������������     ���˵�     ������������������������\n");  
	printf("��                    ��������������������                    ��\n");  
	printf("��                                                            ��\n");  
	printf("��           ��1��������������в���                          ��\n");  
	printf("��                                                            ��\n");  
	printf("��           ��2������һ��������                              ��\n");  
	printf("��                                                            ��\n");
	printf("��                                                            ��\n");  
	printf("��                                                            ��\n");  
	printf("����������������������������������������������������������������\n");  
	printf("\n");
	printf("���������:��   ��\b\b\b");  
	
	for(;;)                     //ѡ����
	{
		scanf("%d",&order);
		switch(order) 
		{  
			case 1: NetsMenu(); break;
			case 2: CreateNewNet(); break;
			default: printf("��������ȷ����ţ���"); break; 
		} 
		
	}
	 
} 

void Menu::DeleteNet(int which)
{
	printf("��û������������\n");
	MainMenu(); 
	//�޸��ļ�����
	//�޸������ڵ����� 
}

int main() {
	srand((unsigned)time(NULL));
	ComNet* COMNET[100];
	NetLine* templine[10000];
	int cities[100];
	int n=0;

	system("color 3");
	system("mode con cols=100");
	Menu menu; 
	menu.Welcome(); 
	menu.MainMenu();
	
	return 0;
}

#include <iostream>
#include <fstream>
#include <queue>
#include <stack>
#include <cmath>
#include <string> 
#include <time.h> 
#include <sys/timeb.h>
#include <graphics.h> 
#include <conio.h>
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
		
		void getTestData(NetLine**path,int which); //生成测试数据 

		bool loadTestData(NetLine**path,int which); //载入文件
		
		bool loadData(NetLine**path,string filename,int which);//载入文件		
		
		void ConstructSecond(NetLine**path); //创建2 
		
		void ConstructFirst(NetLine**path,int which,char* txt1); //创建1 
		
		int CityCenterCheck(int *x,bool Out=0);//关键城市检测  
		
		int LineReliableCheck(bool Out=0);  //线路可靠检测 
		
		bool IsExcess(int x,int y);//检测线路(x,y)是否冗余 
		
		static bool IsConnectAccord(const ComNet& before,const ComNet& after,int a=0/*可选*/);//检测（如果a!=0则除了a点）外连通性相同 
		
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
		
		
		//重载赋值运算符 
		ComNet* operator=(const ComNet& obj);
		 
		int getCityNum(){return iCityNum;}
		int getLineNum(){return iLineNum;}
		
		void DrawInWindows(int which);//画图 
		void Output();//输出 
		
	private:
		int maxCityNum;
		int maxLineNum;
		int iCityNum;//城市数 
		int iLineNum;//线路数	
		int **Line;
};


//构造函数
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


ComNet::ComNet(const ComNet& obj) //拷贝构造函数 
:maxCityNum(obj.maxCityNum),maxLineNum(obj.maxLineNum),iCityNum(obj.iCityNum),iLineNum(obj.iLineNum)
{
	int i=0,j=0;
	Line = new int*[100];
	for(i=0; i<maxCityNum; i++)
		Line[i] = new int[100];
	for(i=0; i<iCityNum; i++)
		for(j=0; j<iCityNum ;j++)
			Line[i][j]=obj.Line[i][j];
}

//载入数据 
bool ComNet::loadTestData(NetLine**path,int index)
{
	char atxt[10]; 
	itoa(index,atxt,10);
	string ttxt="text";
	ttxt+=atxt;
	ttxt+=".txt";
	FILE*fp;
	if((fp=fopen(ttxt.c_str(),"r"))==NULL){printf("文件打不开，请检查是否输入错误\n");system("pause");return 0;}
	int tempx=0,tempy=0;
	cout<<"=========================================================="<<endl;
	fscanf(fp,"%d %d\n",&iCityNum,&iLineNum);
	for(int i=0;i<iLineNum&&!feof(fp);i++)
	{
				
		fscanf(fp,"(%d,%d) ",&tempx,&tempy);
		
		if(tempx == tempy) //检查是否tempX=tempY
		{ 
			cout<<"文件中数据不正确，请检查文件是否符合要求"<<endl; 
			return 0;
		}		
			
		int j;
		for(j=0;j<i;j++) //检查是否和已经生成的重复 
			if((tempx==path[j]->x && tempy==path[j]->y)||(tempx==path[j]->y&&tempy==path[j]->x))
			{
				cout<<"文件中数据不正确，请检查文件是否符合要求"<<endl; 
				return 0;
			}
					
		path[i]=new NetLine(tempx,tempy);
		printf("(% 3d,% 3d) ",path[i]->x,path[i]->y);
		if(i%8==7) printf("\n"); 
	}
	cout<<"\n文件载入完毕"<<endl; 
	fclose(fp);
	system("pause");
	return 1;
}


//载入数据 
bool ComNet::loadData(NetLine**path,string filename,int which)
{
	FILE*fp;
	FILE*fin;
	char atxt[10]; 
	itoa(which,atxt,10);
	int tempx=0,tempy=0; 
	string ttxt="text";
	ttxt+=atxt;
	ttxt+=".txt";
	if((fp=fopen(filename.c_str(),"r"))==NULL){printf("文件打不开，请检查是否输入错误\n");return 0;}
	cout<<"=========================================================="<<endl;
	fscanf(fp,"%d %d\n",&iCityNum,&iLineNum);
	for(int i=0;i<iLineNum&&!feof(fp);i++)
	{
				
		fscanf(fp,"(%d,%d) ",&tempx,&tempy);
		
		if(tempx == tempy) //检查是否tempX=tempY
		{ 
			cout<<"文件中数据不正确，请检查文件是否符合要求"<<endl; 
			return 0;
		}		
			
		int j;
		for(j=0;j<i;j++) //检查是否和已经生成的重复 
			if((tempx==path[j]->x && tempy==path[j]->y)||(tempx==path[j]->y&&tempy==path[j]->x))
			{
				cout<<"文件中数据不正确，请检查文件是否符合要求"<<endl; 
				return 0;
			}
					
		path[i]=new NetLine(tempx,tempy);
		printf("(% 3d,% 3d) ",path[i]->x,path[i]->y);
		if(i%8==7) printf("\n"); 
	}
	cout<<"\n文件载入完毕"<<endl; 
	fclose(fp);
	if((fin=fopen(ttxt.c_str(),"w"))==NULL){printf("文件打不开，请检查是否输入错误\n");system("pause");return 0;}
	fprintf(fin,"%d %d\n",iCityNum,iLineNum);
	for(int j=0;j<iLineNum&&!feof(fin);j++)
	{
		fprintf(fin,"(% 3d,% 3d) ",path[j]->x,path[j]->y); 
	}
	cout<<"数据固化于文件\""<<ttxt<<"\"中"<<endl; 
	cout<<"========================================================="<<endl;
	system("pause");
	fclose(fin);
	return 1;
}

//生成测试数据
void ComNet::getTestData(NetLine **path,int which)
{
	printf("\n");
	printf("   \n");  
	cout<<"=========================================================="<<endl;
	printf("\n");  
	printf("请输入城市个数和通讯线路条数 \n");  
	printf("(城市数与通讯线路数应在合理范围内) ");
	printf("\n");
	cin>> iCityNum >> iLineNum; 
	while(iCityNum<1||iLineNum<1||iCityNum>100||iCityNum*(iCityNum-1)/2 < iLineNum||iLineNum>1000)
	{
		cout<<"输入不合理, 请重新输入.\n";
		cin>>iCityNum>>iLineNum; 
	} 
	char atxt[10]; 
	itoa(which,atxt,10);
	int tempx=0,tempy=0; 
	string ttxt="text";
	ttxt+=atxt;
	ttxt+=".txt";
	ofstream fout(ttxt.c_str());
	fout<<iCityNum<<" "<<iLineNum<<endl;
	cout<<"=========================================================="<<endl;
	cout<<"\n随机生成城市间的通讯线路为：\n"; 
	for(int i=0;i<iLineNum&&fout.is_open();i++)
	{
		//随机生成一个不同的(tempx,tempy)对 
 		bool flag=0; //flag==1则检测合理 
		while(!flag) //检查不合理输入 
		{
			tempx = rand()%iCityNum + 1;
			tempy = rand()%iCityNum + 1; 
			
			if(tempx == tempy) //检查是否tempX=tempY
				continue; 
				
			int j;
			for(j=0;j<i;j++) //检查是否和已经生成的重复 
				if((tempx==path[j]->x && tempy==path[j]->y)||(tempx==path[j]->y&&tempy==path[j]->x))
					break;
					
			if(j==i) {flag=1;}//正常退出循环则没有重复 
		
		}
	
		path[i]=new NetLine(tempx,tempy);
		
		printf("(% 3d,% 3d) ",path[i]->x,path[i]->y);
		fout<<"("<<path[i]->x<<","<<path[i]->y<<") ";
		if(i%8==7) {printf("\n");} 
	}
	
	cout<<endl;
	
	fout.close();
	cout<<"数据固化于文件\""<<ttxt<<"\"中"<<endl; 
 
	cout<<"=========================================================="<<endl;
	system("pause");
}


void ComNet::ConstructSecond(NetLine**path)//生成复杂网络 
{
	cout<<"====================================================="<<endl; 
	cout<<"正在生成第二种网络"<<endl;
	for(int i=0;i<iLineNum;i++)
	{
		Insert(path[i]->x,path[i]->y); 
	}
	cout<<"生成完毕"<<endl;
	system("pause");
}



void ComNet::ConstructFirst(NetLine** path,int which,char* txt1=NULL)//生成简单网络 
{	
	cout<<"======================================================"<<endl;
	cout<<"正在根据数据构建简单网络"<<endl; 
	if(!txt1)	
	{
		for(int i=0;i<iLineNum;i++)
		{
			bool t=IsExcess(path[i]->x, path[i]->y);
		
		
			if(t)
				printf("   (% 3d,% 3d)是冗余线路，不加入线路网\n",path[i]->x, path[i]->y); 	
	
			else
			{
				printf("   (% 3d,% 3d)不是冗余线路，加入线路网\n",path[i]->x, path[i]->y); 	
				Insert(path[i]); 
			}
		}
	}
	else
	{
			FILE*fp;
			if((fp=fopen(txt1,"w"))==NULL){printf("文件打不开，请检查是否错误\n");system("pause");return;}
			for(int i=0;i<iLineNum;i++)
			{
				bool t=IsExcess(path[i]->x, path[i]->y);
		
		
				if(t)
				{
					printf("   (% 3d,% 3d)是冗余线路，不加入线路网\n",path[i]->x, path[i]->y); 	
					fprintf(fp,"   (% 3d,% 3d)冗余\n",path[i]->x, path[i]->y);
				}
				else
				{
					printf("   (% 3d,% 3d)不是冗余线路，加入线路网\n",path[i]->x, path[i]->y); 	
					fprintf(fp,"   (% 3d,% 3d)不冗余\n",path[i]->x, path[i]->y); 
					Insert(path[i]); 
				}
				fclose(fp);
			}
	}
	
	
	NetLine**temppath;
	temppath=new NetLine*[1000];
	int num=0;//无冗余网络中点数
	
	for(int i=0;i<iCityNum;i++)
	{
		if(!IsExcess(path[i]->x, path[i]->y))
		{
			temppath[num++]=new NetLine(path[i]->x,path[i]->y);
		};
	}
	iLineNum=num;
	FILE*fin;
	char atxt[10]; 
	itoa(which,atxt,10);
	int tempx=0,tempy=0; 
	string ttxt="text";
	ttxt+=atxt;
	ttxt+=".txt";
	if((fin=fopen(ttxt.c_str(),"w"))==NULL){printf("文件打不开，请检查是否输入错误\n");system("pause");return ;}
	fprintf(fin,"%d %d\n",iCityNum,iLineNum);
	for(int j=0;j<iLineNum&&!feof(fin);j++)
	{
		fprintf(fin,"(% 3d,% 3d) ",temppath[j]->x,temppath[j]->y); 
	}
	cout<<"删除冗余线路数据固化于文件\""<<ttxt<<"\"中"<<endl; 
	cout<<"========================================================="<<endl;
	system("pause");
	fclose(fin);
	system("pause");
} 


int ComNet::CityCenterCheck(int *CenterCity, bool Out)//可靠性检查并输出关键城市(可选) ,返回关键城市数目 
{
	int i=0,j=0; 
	ComNet tempobj(*this);
	int num=0;
	for(i=0;i<iCityNum;i++)//每个城市遍历 
	{
		ComNet tempobj(*this);
		for(j=0;j<iCityNum;j++) //删除直接相连边 
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
			cout<<"关键城市(需要分配交换机)："<<endl;
			for(int i=0;i<num;i++)
				cout<<CenterCity[i]<<" ";
			cout<<endl; 
		}
		else cout<<"没有关键城市,不需要分配交换机!"<<endl; 
	}
	system("pause");
	return num;
}



int ComNet::LineReliableCheck(bool Out)//可靠性检查并输出不可靠线路（可选） 
{
	ComNet tempobj(*this);
	int i=0;//临时 
	int j=0;//计数 
	int k=0;
	int x[1000],y[1000];
	NetLine* UnRe[1000]; 
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
			cout<<"无不可靠线路,网络可靠"<<endl; 
			system("pause");
			return 0;
		}
		else
		{
			cout<<"不可靠线路有:"<<endl; 
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


bool ComNet::IsExcess(int x,int y)               //检查是否冗余 
{
	int i=0,j=0,k=0;
	bool Connect[100][100];
	for(i=0;i<iCityNum;i++)
	{
		for(j=0;j<iCityNum;j++)
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


bool ComNet::IsConnectAccord(const ComNet& before,const ComNet& after,int a)      //检测是否可及性一致 
{
	int i=0,j=0,k=0;
	if(before.iCityNum!=after.iCityNum) {cout<<"操作有误，请检查"<<endl;return 0;} 
	bool Connectb[100][100];
	bool Connecta[100][100];
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
	

	if(a==0)
	{
		for(i=0;i<before.iCityNum;i++)
			for(j=0;j<i;j++)
				if(Connecta[i][j]!=Connectb[i][j])//在原来可及性矩阵中可及,但删掉一直接边后不可及了，则为不可靠的
					return 0;			
	}
	else for(i=0;i<before.iCityNum;i++)
		for(j=0;j<i;j++)
		{
			if(i!=a-1&&j!=a-1&&Connecta[i][j]!=Connectb[i][j])//在原来可及性矩阵中可及,但删掉一点后不可及了，则为不可靠的 ,忽略被删掉的点 
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



void ComNet::DrawInWindows(int which)
{
	//生成每个点的坐标 
	int pos[2] ={0,300}; 
	int posx[100];
	int posy[100];
	int i;
	for(i=0;i<iCityNum;i++)
	{
		int part = i%4; 
		posx[i] = rand()%300 +pos[i%2];
		posy[i] = rand()%300 +pos[(i/2)%2];
	}

	initgraph(600,600,SHOWCONSOLE);
	setbkcolor(WHITE);
	cleardevice();
	
	setcolor(RGB(200,0,0));
	//settextstyle(10,0);
	char strr[100];
	for(i=0;i<iCityNum;i++)
	{
		itoa(i+1,strr,10);
		circle(posx[i],posy[i],5);
		outtextxy(posx[i], posy[i], strr);

	}
	setcolor(RGB(0,200,0));

	for(i=0;i<iCityNum;i++)
	{
		for(int j=0;j<iCityNum;j++)
		{
			if(Line[i][j]==1)
				line(posx[i],posy[i],posx[j],posy[j]);
		}
	}
	getch();
	char atxt[10]; 
	itoa(which,atxt,10);
	int tempx=0,tempy=0; 
	string ttxt="text";
	ttxt+=atxt;
	ttxt+="image.jpg";	
	saveimage(ttxt.c_str());
	closegraph(); 
	system("pause");
}





ComNet* ComNet::operator=(const ComNet& obj)
{
	int i=0,j=0; 
	iCityNum = obj.iCityNum;
	iLineNum = obj.iLineNum;
	Line = new int*[maxCityNum];
	for(i=0; i<maxCityNum; i++)
		Line[i] = new int[maxCityNum];
	for(i=0; i<iCityNum; i++)
		for(j=0; j<iCityNum ;j++)
			Line[i][j]=obj.Line[i][j];
	return this;
} 


ComNet::~ComNet()         //析构函数 
{
	for(int i=0;i<maxCityNum;i++)
		delete []Line[i];
	delete [] Line;
}


void Menu::Welcome()     //欢迎界面
{
	printf("\n");
	printf("                            \n");  
	printf("┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓\n");  
	printf("┃                                                            ┃\n");  
	printf("┃                      数据结构课程设计                      ┃\n");  
	printf("┃                                                            ┃\n");
	printf("┃                                                            ┃\n");
	printf("┃                   by 万蔓芊 丁笑维 于子桓                  ┃\n"); 
	printf("┃                                                            ┃\n"); 
	printf("┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛\n");  
	printf("\n"); 
	system("pause");
} 



void Menu::CreateNewNet()
{
	 string filename;
	system("CLS");
	printf("\n");

	int order=-1;        //显示菜单
	printf("\n");
	printf("                      ┏━━━━━━━━┓                   \n");  
	printf("┏━━━━━━━━━━┃创建第% 4d个网络┃━━━━━━━━━━┓\n",numofnet+1);  
	printf("┃                    ┗━━━━━━━━┛                    ┃\n");  
	printf("┃                                                            ┃\n");  
	printf("┃                                                            ┃\n");  
	printf("┃           【1】创建网络                                    ┃\n");
	printf("┃                                                            ┃\n");
	printf("┃           【2】查看已载入网络                              ┃\n");
	printf("┃                                                            ┃\n");      	
	printf("┃           【3】载入其他网络                                ┃\n");      
	printf("┃                                                            ┃\n");   
	printf("┃           【4】回到主菜单                                  ┃\n");        
	printf("┃                                                            ┃\n");  
	printf("┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛\n");  
	printf("\n");
	printf("请输入序号:【   】\b\b\b");  
	for(;;)                     //选择功能
	{
		scanf("%d",&order);
		switch(order) 
		{  
			case 1: 	
				COMNET[numofnet] = new ComNet;
				numofnet++; 
				COMNET[numofnet-1]->getTestData(templine,numofnet-1);
				CreateNewNet0();
				break;
			case 2: NetsMenu();break; 
			case 3:
				COMNET[numofnet] = new ComNet;
				numofnet++; 
				printf("请输入完整文件名\n");
				cin>>filename; 
				while(!COMNET[numofnet-1]->loadData(templine,filename,numofnet-1))
				{
					printf("请输入完整文件名\n");
					cin>>filename; 
				}
				CreateNewNet0();
				break;
			case 4: MainMenu();break;
			default: printf("请输入正确的序号！！"); break; 
		} 
		
	}	
}

void Menu::CreateNewNet0()
{
	system("CLS");
	printf("\n");
	char atxt[100];string ttxt;
	int order=-1;        //显示菜单
	printf("\n");
	printf("                      ┏━━━━━━━━┓                   \n");  
	printf("┏━━━━━━━━━━┃创建第% 4d个网络┃━━━━━━━━━━┓\n",numofnet);  
	printf("┃                    ┗━━━━━━━━┛                    ┃\n");  
	printf("┃                                                            ┃\n");  
	printf("┃           【1】以无冗余方式创建                            ┃\n");  
	printf("┃                                                            ┃\n");  
	printf("┃           【2】以可冗余方式创建                            ┃\n");
	printf("┃                                                            ┃\n");
	printf("┃           【3】查看已载入网络                              ┃\n");
	printf("┃                                                            ┃\n");   
	printf("┃           【4】回到主菜单                                  ┃\n");        
	printf("┃                                                            ┃\n");  
	printf("┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛\n");  
	printf("\n");
	printf("请输入序号:【   】\b\b\b");  
	for(;;)                     //选择功能
	{
		scanf("%d",&order);
		switch(order) 
		{  
			case 1: 	
				itoa(numofnet-1,atxt,10);
				ttxt="text";
				ttxt+=atxt;
				ttxt+="-e.txt";
				atxt[0]='\0';
				strcpy(atxt,ttxt.c_str());
				
				COMNET[numofnet-1]->ConstructFirst(templine,numofnet-1,atxt); 
				ReadNet(numofnet-1);
				break;
			case 2:
				COMNET[numofnet-1]->ConstructSecond(templine);
				ReadNet(numofnet-1);
				break;
			case 3:
				printf("确定停止创建吗？ 【1】确定 【2】继续创建\n"); 
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
				printf("确定停止创建吗？ 【1】确定 【2】继续创建\n"); 
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
			default: printf("请输入正确的序号！！"); break; 
		} 
		
	}	
}
void Menu::ReadNet(int which)
{
	system("CLS");
	int order=-1;        //显示菜单
	printf("\n");
	printf("                      ┏━━━━━━━━┓                   \n");  
	printf("┏━━━━━━━━━━┃对网络% 4d的操作┃━━━━━━━━━━┓\n",which+1);  
	printf("┃                    ┗━━━━━━━━┛                    ┃\n");  
	printf("┃                                                            ┃\n");  
	printf("┃           【1】显示该网络                                  ┃\n");  
	printf("┃                                                            ┃\n");  
	printf("┃           【2】可靠性检查                                  ┃\n");
	printf("┃                                                            ┃\n");    
	printf("┃           【3】查看交换机配备建议                          ┃\n");
	printf("┃                                                            ┃\n");  
	printf("┃           【4】查看其他网络                                ┃\n");  
	printf("┃                                                            ┃\n");  
	printf("┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛\n");  
	printf("\n");
	printf("请输入序号:【   】\b\b\b");  
	
	for(;;)                     //选择功能
	{
		scanf("%d",&order);
		switch(order) 
		{  
			case 1: COMNET[which]->DrawInWindows(which); ReadNet(which);break;
			case 2: COMNET[which]->LineReliableCheck(1);ReadNet(which);break;
			case 3: COMNET[which]->CityCenterCheck(cities,1);ReadNet(which); break;
			case 4: NetsMenu();break;
			default: printf("请输入正确的序号！！"); break; 
		} 
		
	}
}


void Menu::NetsMenu()
{
	system("CLS");
	int order=-1;        //显示菜单
	printf("\n");
	printf("                      ┏━━━━━━━━┓                   \n");  
	printf("┏━━━━━━━━━━┃   当前网络     ┃━━━━━━━━━━┓\n");  
	printf("┃                    ┗━━━━━━━━┛                    ┃\n");  
	printf("┃                                                            ┃\n");  
	if(numofnet==0){
	printf("┃           当前没有载入的网络                               ┃\n");
	printf("┃                                                            ┃\n"); 
	printf("┃                                                            ┃\n"); 
	printf("┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛\n"); 
	system("pause");
	MainMenu();
	}
	
	printf("┃                                                            ┃\n"); 
	printf("┃           当前已知%4d个网络                                ┃\n",numofnet);
	printf("┃                                                            ┃\n");  
	
	
	printf("┃                                                            ┃\n");  
	printf("┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛\n");  
	printf("\n");
	printf("请输入想操作的网络文件索引(0~% 4d),输入% 4d创建新网络,输入999回到主菜单:【   】\b\b\b",numofnet-1,numofnet);  
	
	cin>>order;
	while((order<0||order>numofnet)&&order!=999)
	{
		cout<<"请输入正确的网络序号\n";
		cin>>order; 
	}
	if(order==numofnet) CreateNewNet();
	else if(order==999) MainMenu();
	else {system("CLS");COMNET[order]->loadTestData(templine,order);ReadNet(order);}
}

 

void Menu::MainMenu()    //主菜单
{
	system("CLS");
	int order=-1;        //显示菜单
	printf("\n");
	printf("                      ┏━━━━━━━━┓                   \n");  
	printf("┏━━━━━━━━━━┃     主菜单     ┃━━━━━━━━━━┓\n");  
	printf("┃                    ┗━━━━━━━━┛                    ┃\n");  
	printf("┃                                                            ┃\n");  
	printf("┃           【1】对已有网络进行操作                          ┃\n");  
	printf("┃                                                            ┃\n");  
	printf("┃           【2】创建一个新网络                              ┃\n");  
	printf("┃                                                            ┃\n");
	printf("┃                                                            ┃\n");  
	printf("┃                                                            ┃\n");  
	printf("┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛\n");  
	printf("\n");
	printf("请输入序号:【   】\b\b\b");  
	
	for(;;)                     //选择功能
	{
		scanf("%d",&order);
		switch(order) 
		{  
			case 1: NetsMenu(); break;
			case 2: CreateNewNet(); break;
			default: printf("请输入正确的序号！！"); break; 
		} 
		
	}
	 
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

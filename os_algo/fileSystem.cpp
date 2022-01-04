#include<algorithm>
#include<random>
#include<iostream>
#include<vector>
#include<list>
using namespace std;
#define USER 10
#define MAXFILE 10
#define OPENMAX 5

struct mfd{//主文件目录结构体
    char user;//用户
    int dirp;//目录区指针
    mfd(char user,int dirp)
    {
        this->user = user;
        this->dirp = dirp;
    }
};
struct ufd{//用户文件目录
    char fileName;//文件名
    char user;
    int proctectCode[3];//保护码
    int fileLength;//文件长度
    ufd(char fileName,int* proctectCode,int fileLength)
    {
        this->fileName = fileName;
        for(int i=0;i<3;i++)
        {
            this->proctectCode[i]=proctectCode[i];
        }
        this->fileLength=fileLength;
    }
};
struct afd{//运行文件目录
    int fid;//文件号
    int fileName;//文件名
    int proctectCode[3];//保护码
    int ROrW;//读写指针, 0 for open, 1 for r, 2 for w
    afd(int fid,char fileName,int* proctectCode,int ROrW)
    {
        this->fid = fid;
        this->fileName = fileName;
        for(int i=0;i<3;i++)
        {
            this->proctectCode[i]=proctectCode[i];
        }
        this->ROrW=ROrW;
    }   
};

vector<mfd> mfds;
vector<ufd> fds;
vector<afd> afds;

void front(){//初始化
    int i;
    for(i=0;i<USER*MAXFILE;i++)
    {
        int pc[3];
        for(int j=0;j<3;j++)
        {
            pc[j]=rand()%2;
        }
        ufd newFile(char(i+1),pc,rand()%100+1);//文件名从1排,地址从0排
        fds.push_back(newFile);
    }
    for(i=0;i<USER;i++)
    {
        char user;
        user=char(int('a')+i);
        mfd newmfd(user,i*MAXFILE); 
        mfds.push_back(newmfd); 
        for(int j=0;j<MAXFILE;j++)
        {
            fds[i*MAXFILE+j].user=user;
        }      
    }
}

int checkUser(char chooseUser)//检查选择用户是否合法
{
    for(int i=0;i<USER;i++)
    {
        if(mfds[i].user==chooseUser)
            return i;
    }
    return -1;
}

void printDir(int num)//打印用户文件目录
{
    cout<<"USER: "<<mfds[num].user<<endl;
    // int filenum=mfds[num+1].dirp-mfds[num].dirp;
    int dirp=mfds[num].dirp;
    cout<<"YOUR FILE DIRECTORY: "<<endl;
    for(int i=dirp;i<fds.size();i++)
    {
        if(fds[i].user==mfds[num].user)
        {
            cout<<int(fds[dirp+i].fileName)<<"  ";
            for(int j=0;j<3;j++)
                cout<<fds[dirp+i].proctectCode[j];
            cout<<"  "<<fds[dirp+i].fileLength<<"  "<<endl;
        }
    }
}

void printAfd()//打印打开文件目录
{
    cout<<"OPEN FILE DIRECTORY: "<<endl;
    for(int i=0;i<afds.size();i++)
    {
        cout<<afds[i].fid<<"  "<<afds[i].fileName<<"  ";
        for(int j=0;j<3;j++)
            cout<<afds[i].proctectCode[j];
        cout<<"  "<<afds[i].ROrW<<"  "<<endl;
    }
}

void create(char chooseUser)//新建文件
{
    int filename;
    cout<<"CREATE A NEW FILE!"<<endl;
    cout<<"INPUT FILE INFO: "<<endl;
    cout<<"FILENAME: ";cin>>filename;
    cout<<"PROCECTCODE: ";
    int pc[3];
    for(int j=0;j<3;j++)
    {
        cin>>pc[j];
    }
    int index=fds.size();
    ufd newFile(char(filename),pc,rand()%100+1);
    fds.push_back(newFile);
    fds.back().user=chooseUser;
    cout<<"THE NEW FILE IS CREATED!"<<endl;
}

void dele(char chooseUser)//删除文件
{
    int filename;
    cout<<"DELETE A FILE!"<<endl;
    cout<<"FILENAME: ";cin>>filename;
    int i;
    int fg=0;
    for(i=0;i<fds.size();i++)
    {
        if(fds[i].fileName==filename&&fds[i].user==chooseUser)
        {
            fg=1;
            break;
        }
    }
    if (!fg) cout<<"NO SUCH FILE!"<<endl;
    else{//文件打开的情况，不可直接删除，需要提醒
        for(i=0;i<afds.size();i++)
        {
            if(afds[i].fileName==filename)
            {
                fg=1;
                break;
            }
        }
        if (!fg) cout<<"FILE IS OPENING"<<endl;
        else{
            fds.erase(fds.begin()+i);
            for(int j=0;j<USER;j++)
            {
                if(mfds[i].user==chooseUser&&mfds[i].dirp==i)//若删除的文件处理程序恰为目录区头部指针，需要后移
                {
                    int flag=0;
                    for(int k=i;k<fds.size();k++)
                    {
                        if(fds[k].user==chooseUser)
                        {
                            mfds[i].dirp=k;
                            flag=1;
                            break;
                        }
                    }
                    if(!flag)
                    {
                        mfds[i].dirp=-1;//代表目录区指针为空，此时该用户无目录文件
                    }
                }
            }
            cout<<"THE FILE IS DELETED!"<<endl;
        }
    }
}

void open(char chooseUser)//打开文件
{
    int filename;
    if(afds.size()==OPENMAX)//考虑到最多能打开的文件数量
    {
        cout<<"OPEN FILE IS UP TO MAX!"<<endl;
        return;
    }
    cout<<"OPEN A FILE!"<<endl;
    cout<<"FILENAME: ";cin>>filename;
    int i;
    int fg=0;
    for(i=0;i<fds.size();i++)
    {
        if(fds[i].fileName==filename&&fds[i].user==chooseUser)
        {
            fg=1;
            break;
        }
    }
    if (!fg) cout<<"NO SUCH FILE!"<<endl;//处理所需文件不在系统中情况
    else
    {
        cout<<"PROCECTCODE: ";
        int pc;
        for(int j=0;j<3;j++)
        {
            cin>>pc;
            fds[i].proctectCode[j]=pc;
        }
        afd newFile(afds.size()+1,fds[i].fileName,fds[i].proctectCode,0);
        afds.push_back(newFile);
        cout<<"FILE IS OPENED!"<<endl;
    }
}

void close()//关闭文件
{
    int filename;
    cout<<"CLOSE A FILE!"<<endl;
    cout<<"FILENAME: ";cin>>filename;
    int i;
    int fg=0;
    for(i=0;i<afds.size();i++)
    {
        if(afds[i].fileName==filename)
        {
            fg=1;
            break;
        }
    }
    if (!fg) cout<<"NO SUCH FILE!"<<endl;//处理所需文件未打开的情况
    else
    {
        afds.erase(afds.begin()+i);
        cout<<"FILE IS CLOSED!"<<endl;
    }
}

void read()//读文件
{
    int filename;
    cout<<"READ A FILE!"<<endl;
    cout<<"FILENAME: ";cin>>filename;
    int i;
    int fg=0;
    for(i=0;i<afds.size();i++)
    {
        if(afds[i].fileName==filename)
        {
            fg=1;
            break;
        }
    }
    if (!fg) cout<<"FILE IS NOT OPENING!"<<endl;//处理所需文件未打开的情况
    else if(afds[i].proctectCode[0]==0)
    {
        cout<<"ERROR MESSAGE:IT IS NOT ALLOWED TO READ THIS FILE!"<<endl;
    }
    else
    {
        afds[i].ROrW=1;
        cout<<"FILE READ!"<<endl;
    }    
}

void write()//写文件
{
    int filename;
    cout<<"WRITE A FILE!"<<endl;
    cout<<"FILENAME: ";cin>>filename;
    int i;
    int fg=0;
    for(i=0;i<afds.size();i++)
    {
        if(afds[i].fileName==filename)
        {
            fg=1;
            break;
        }
    }
    if (!fg) cout<<"FILE IS NOT OPENING!"<<endl;//处理所需文件未打开的情况
    else if(afds[i].proctectCode[0]==0)
    {
        cout<<"ERROR MESSAGE:IT IS NOT ALLOWED TO WRITE THIS FILE!"<<endl;
    }
    else
    {
        afds[i].ROrW=2;
        cout<<"FILE WROTE!"<<endl;
    }    
}

void bye(int num)//关闭系统
{
    printDir(num);
    printAfd();
    cout<<"EXIT, BYE!"<<endl;
}

int main(){
    front();
    cout<<"USER NAME: ";
    for(int i=0;i<USER;i++)
    {
        cout<<mfds[i].user;
        cout<<" ";
    }
    cout<<endl<<"YOUR NAME PLEASE?  ";
    int num=-1;
    char chooseUser;
    cin>>chooseUser;
    while(num=checkUser(chooseUser)&&num==-1)
    {
        cout<<"YOUR NAME IS NOT IN THE USER NAME TABLE,TRY AGAIN.";
        cin>>chooseUser;
    }
    printDir(num);
    int option;
    cout<<"INPUT OPTION: (1 FOR CREATE, 2 FOR DELETE, 
    3 FOR OPEN, 4 FOR CLOSE. 5 FOR READ, 6 FOR WRITE, 7 FOR QUIT)  ";
    while(cin>>option)
    {
        switch(option)
        {
            case 1://添加文件
            {
                create(chooseUser);
                printDir(num);
                break;
            }
            case 2://删除文件
            {
                dele(chooseUser);
                printDir(num);
                break;
            }
            case 3://打开文件
            {
                open(chooseUser);
                printAfd();
                break;
            }
            case 4://关闭文件
            {
                close();
                printAfd();
                break;
            }
            case 5://读文件
            {
                read();
                printAfd();
                break;
            }
            case 6://写文件
            {
                write();
                printAfd();
                break;
            }
            case 7://退出系统
            {
                bye(num);
                return 0;
            }
            default:
            {
                cout<<"OPTION USELESS!"<<endl;
                break;
            }
        }
        cout<<"INPUT OPTION: (1 FOR CREATE, 2 FOR DELETE, 
        3 FOR OPEN, 4 FOR CLOSE. 5 FOR READ, 6 FOR WRITE, 7 FOR QUIT)  ";
    }
}
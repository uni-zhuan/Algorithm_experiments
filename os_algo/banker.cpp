#include<algorithm>
#include<random>
#include<iostream>
#include<vector>
#include<queue>
#include<iomanip>
#define NP 3
#define NT 6
using namespace std;

struct proc{
    int pid;//进程号
    int maxp;//进程的最大需求量
    int allocationp;//进程已分配到的资源数
    int needp;//进程还需要的资源数
    int finishp;//进程完成请求标志，为1时表示已完成各次请求
    int workp;//进程请求次数计数器
    proc(int pid,int maxp,int allocationp,int need,int finishp,int workp)
    {
        this->pid=pid;
        this->maxp=maxp;
        this->allocationp=allocationp;
        this->needp=needp;
        this->finishp=finishp;
        this->workp=workp;
    }
    bool operator<(const proc & p1)  const
    {
        return needp < p1.needp;
    }
    bool operator>(const proc & p1)  const
    {
        return needp > p1.needp;
    }
};//头文件定义的结构体后面要加；

vector<proc> process;
int option;
int available;//可利用资源
int nowprocess;//现在运行的进程号
int resource;//系统资源数
queue<int> procid;//假定分配的进程
queue<int> request;//假定分配的资源数

void front()//初始化
{
    int i;
    for(i=0;i<NP;i++)
    {
        proc newproc(i+1,0,0,0,0,0);
        //用质数作生成范围内随机数得到的结果会好些
        process.push_back(newproc);
    }
}

void printerror(int errornb)//打印出错信息
{
    switch(errornb)
    {
        case 1:
            cout<<"Max claim of this resource is greater than all resources"<<endl;
            break;
        case 2:
            cout<<"Request is greater than need"<<endl;
            break;
        case 3:
            cout<<"Request is greater than available"<<endl;
            break;
    }
}
void printprocdata()//打印资源数据
{
    cout<<"The data of processes is as follows:"<<endl;
    cout<<"   Process"<<"       Max"<<" Alloction"<<"      Need"<<" Available"<<endl;
    for(int i=0;i<NP;i++)//输入进程资源分配数
    {
        cout.setf(ios::right);
        if(i==0)
            cout<<setw(10)<<process[i].pid<<setw(10)<<process[i].maxp<<setw(10)<<process[i].allocationp<<setw(10)<<process[i].needp<<setw(10)<<available<<endl;
        else
            cout<<setw(10)<<process[i].pid<<setw(10)<<process[i].maxp<<setw(10)<<process[i].allocationp<<setw(10)<<process[i].needp<<endl;
    }
}
void printsafe()//打印资源数据
{
    cout<<"The security sequence is as follows:"<<endl;
    cout<<"   Process"<<"       Max"<<" Alloction"<<"      Need"<<" Available"<<endl;
    for(int i=0;i<NP;i++)//输入进程资源分配数
    {
        cout.setf(ios::right);
        if(i==0)
            cout<<setw(10)<<process[i].pid<<setw(10)<<process[i].workp<<setw(10)<<process[i].allocationp<<setw(10)<<process[i].needp<<setw(10)<<process[i].workp+process[i].allocationp<<endl;
        else
            cout<<setw(10)<<process[i].pid<<setw(10)<<process[i].workp<<setw(10)<<process[i].allocationp<<setw(10)<<process[i].needp<<setw(10)<<process[i].workp+process[i].allocationp<<endl;
    }
}

bool safe()//安全性，测试当前分配状况下是否产生死锁
{
    int work=available;
    for(int i=0;i<NP;i++)
        process[i].finishp=0;//先全置0
    cout<<"The security sequence is as follows:"<<endl;
    cout<<"   Process"<<"      Work"<<" Alloction"<<"      Need"<<"       W+A"<<"    Finish"<<endl;
    cout.setf(ios::right);
    for(int i=0;i<NP;i++)
    {
        for(int j=0;j<NP;j++)
            if(process[j].finishp==0&&process[j].needp<=work)
            {
                process[j].workp=work;
                work+=process[j].allocationp;
                process[j].finishp=1;
                cout<<setw(10)<<process[j].pid<<setw(10)<<process[j].workp<<setw(10)<<process[j].allocationp<<setw(10)<<process[j].needp<<setw(10)<<process[j].workp+process[j].allocationp<<setw(10)<<process[j].finishp<<endl;
            }
    }
    bool issafe=1;
    for(int i=0;i<NP;i++)
    {
        if(process[i].finishp==0)
            issafe=0;
    }
    return issafe;
}

void banker()//银行家算法
{
    bool sf;
    int tempcin;
    int thispid;
    int thisrequest;
    while(true)
    {
        cout<<"Process id: ";
        cin>>tempcin;
        procid.push(tempcin-1);
        cout<<"Try to allocate: ";
        cin>>tempcin;
        request.push(tempcin);
        for(int j=procid.size();j>0;j--)
        {
            thispid=procid.front();
            thisrequest=request.front();
            procid.pop();
            request.pop();
            //检查需要的资源数是否超过
            if(thisrequest>process[thispid].needp)
            {
                printerror(2);
                j--;
                break;
            }
            else if(thisrequest>available)
            {
                printerror(3);
                j--;
                break;
            }
            else
            {
                available-=thisrequest;
                process[thispid].allocationp+=thisrequest;
                process[thispid].needp-=thisrequest;
                printprocdata();
                sf=safe();
                if(sf)
                {
                    if(process[thispid].needp==0)
                    {
                        available+=process[thispid].allocationp;
                        process[thispid].allocationp=0;
                    }
                    cout<<"This allocation can be completed"<<endl;
                    printprocdata();
                }
                else
                {   
                    cout<<"This allocation can't be completed"<<endl;
                    available+=thisrequest;
                    process[thispid].allocationp-=thisrequest;
                    process[thispid].needp+=thisrequest;
                    procid.push(thispid);
                    request.push(thisrequest);
                }
            }
        }
    }
}

void deadlock()
{
    bool sf;
    int tempcin;
    int thispid;
    int thisrequest;
    while(true)
    {
        cout<<"Process id: ";
        cin>>tempcin;
        procid.push(tempcin-1);
        cout<<"Try to allocate: ";
        cin>>tempcin;
        request.push(tempcin);
        thispid=procid.front();
        thisrequest=request.front();
        procid.pop();
        request.pop();
        if(thisrequest>process[thispid].needp)
        {
            printerror(2);
            // break;
        }
        else if(thisrequest>available)
        {
            printerror(4);
            cout<<"Process "<<process[thispid].pid<<" in deadlock."<<endl;
            // system("pause");
            getchar();
        }
        else
        {
            available-=thisrequest;
            process[thispid].allocationp+=thisrequest;
            process[thispid].needp-=thisrequest;
            printprocdata();  
            if(process[thispid].needp==0)//若进程结束，将资源释放
            {
                available+=process[thispid].allocationp;
                process[thispid].allocationp=0;
            }        
        }
    }
}

void sortprevent()
{
    bool sf;
    int tempcin;
    int thispid;
    int thisrequest;
    int emptyindex=0;
    while(true)
    {
        sort(process.begin(), process.end(),less<proc>());
        procid.push(tempcin-1);
        cout<<"Process "<<process[emptyindex].pid<<": try to allocate: ";
        cin>>tempcin;
        request.push(tempcin);
        thisrequest=request.front();
        request.pop();
        if(thisrequest>process[emptyindex].needp)
        {
            printerror(2);
            // break;
        }
        else if(thisrequest>available)
        {
            printerror(4);
            cout<<"Process "<<process[emptyindex].pid<<" in deadlock."<<endl;
            getchar();
        }
        else
        {
            available-=thisrequest;
            process[emptyindex].allocationp+=thisrequest;
            process[emptyindex].needp-=thisrequest;
            if(process[emptyindex].needp==0)//若进程结束，将资源释放
            {
                available+=process[emptyindex].allocationp;
                process[emptyindex].allocationp=0;
                emptyindex+=1;
            }      
            printprocdata();   
        }
    }
}

main()
{
    cout<<"Option = (1 for banker, 2 for deadlock, 3 for sortprevent)";
    cin>>option;
    cout<<"Resource Num= ";
    cin>>resource;
    int tempcin;
    cout<<"Max Claim of process: ";
    front();
    for(int i=0;i<NP;i++)//输入进程最大资源需求数
    {
        cin>>tempcin;
        if(!(tempcin>resource))//最大资源需求量不超过系统资源数
            process[i].maxp=tempcin;
        else//最大资源需求量超过系统资源数
        {
            printerror(1);
            i-=1;
        }
    }
    cout<<"Alloction of process: ";
    for(int i=0;i<NP;i++)//输入进程资源分配数
    {
        cin>>tempcin;
        process[i].allocationp=tempcin;
    }
    cout<<"Need of process is: ";
    for(int i=0;i<NP;i++)//输入进程资源分配数
    {
        cin>>tempcin;
        process[i].needp=tempcin;
    }
    available=resource;
    for(int i=0;i<NP;i++)
        available-=process[i].allocationp;
    cout<<endl;
    printprocdata();
    if(option==1)
    {
        if(!safe())
            cout<<"This system is not safe!"<<endl;
        banker();
    }
    else if(option==2)
        deadlock();
    else if(option==3)
        sortprevent();
}
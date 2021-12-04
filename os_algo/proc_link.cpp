#include<algorithm>
#include<random>
#include<iostream>
#include<vector>
#include<queue>
using namespace std;

enum processStatus{//枚举进程状态
    run=0,
    wait=1,
    finish=2
};

struct pcb{
    int pid;//进程标识数
    int cputime;//占用CPU时间片数
    int alltime;//进程所需时间片数
    processStatus ps;//进程状态
    int queueNum;//处在哪个队列
    pcb()
    {
        ;
    }
    pcb( int pid,int cputime,int alltime,
    processStatus ps,int queueNum)
    {
        this->pid=pid;
        this->cputime=cputime;
        this->alltime=alltime;
        this->ps=ps;
        this->queueNum=queueNum;
    }
};//头文件定义的结构体后面要加；

struct waitqueue{
    int qpri;//队列优先级
    int qtime;//时间片长度
    queue<pcb> pcbs;//队列中进程
    waitqueue()
    {
        ;
    }
    waitqueue(int qpri,int qtime,queue<pcb> pcbs)
    {
        this->qpri=qpri;
        this->qtime=qtime;
        this->pcbs=pcbs;
    }
};

vector<pcb> finishpcbs;
vector<waitqueue> waitqueues;
// (3,queue<pcb> pcbqueue)
int pnum=1;
int runpcb=0;
pcb thispcb;
int procTime;
waitqueue thisqueue;

//初始化多级队列
void newqueues()
{
    int i;
    for(i=1;i<=3;i++)//设定共有三级队列
    {
        queue<pcb> thisqueue;
        waitqueue pcbqueue(i,i,thisqueue);
        waitqueues.push_back(pcbqueue);
    }
}

//产生进程用以投入多级队列
void newpcbs()
{
    pcb newpcb(pnum,rand()%10+1,0,processStatus(1),1);
    waitqueues[0].pcbs.push(newpcb);
    pnum++;
}

void Fb()
{
    if(runpcb==0)
    {
        int i=0;
        while(!waitqueues[i].pcbs.empty())
            i++;
        thispcb=waitqueues[i].pcbs.front();
        waitqueues[i].pcbs.pop();
        thispcb.ps=processStatus(0);
        procTime=waitqueues[i].qtime;
        thisqueue=waitqueues[i];
        runpcb=1;
    }
    if(procTime>0)
    {
        thispcb.cputime-=1;
        thispcb.alltime+=1;
        procTime-=1;
        // if(thispcb.cputime<0) //如果结束且超出的情况
        // {
        //     thispcb.alltime+=thispcb.cputime;
        //     thispcb.cputime=0;
        // }
        if(thispcb.cputime==0)
        {
            thispcb.ps=processStatus(1);
            finishpcbs.push_back(thispcb);
            runpcb=0;
        }
    }
    if(procTime=0)
    {
        if(thisqueue.qpri<3)//除最后一级队列以外往下面一级的队尾放
        {
            thispcb.ps=processStatus(1);
            waitqueues[thisqueue.qpri].pcbs.push(thispcb);
            thisqueue=waitqueues[thisqueue.qpri];
            procTime=thisqueue.qtime;
            runpcb=0;
        }
        else//最后一级队列放在自己的队尾
        {
            waitqueues[thisqueue.qpri-1].pcbs.push(thispcb);
            procTime=thisqueue.qtime;
            runpcb=0;
        }
    }    
}

void FBProc()
{
    int choose;
    cout<<"CHOOSE THE ACTION (1 TO GO ON, 2 TO ADD A NEW PROCESS)   ";
    while(cin>>choose)
    {
        if(choose==1)
            Fb();
        else if(choose==2)
        {
            newpcbs();
            thispcb.ps=processStatus(1);
            thisqueue.pcbs.push(thispcb);
            runpcb=0;
            Fb();
        }    
    }
}

main()
{
    newqueues();
    FBProc();
    // for(int i=finishpcbs.size()-1;i>=0;i--)
    //     cout<<finishpcbs[i].pid<<"    ";
    cout<<endl;
}

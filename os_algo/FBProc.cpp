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
int pnum=0;
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
    pcb newpcb(pnum+1,rand()%10+1,0,processStatus(1),1);
    waitqueues[0].pcbs.push(newpcb);
    pnum++;
}

void printqueue()
{
    if(pnum==finishpcbs.size())
    {
        cout<<"ALL QUEUE EMPTY!"<<endl;
        return;
    }
    cout<<"pid   cputime  alltime  ps  queueNum"<<endl;
    cout<<"now running:"<<endl;
    cout << thispcb.pid<<"      "<<thispcb.cputime<<"      "<<thispcb.alltime<<"      "<<thispcb.ps<<"      "<<thispcb.queueNum<<"      "<<endl;
    cout<<"now waiting:"<<endl;
    for(int i=0;i<3;i++)
    {   
        queue<pcb> tempqueue;
        if(!waitqueues[i].pcbs.empty())
        {
            tempqueue=waitqueues[i].pcbs;
            while (!tempqueue.empty())
            {
                cout << tempqueue.front().pid<<"      "<<tempqueue.front().cputime<<"      "<<tempqueue.front().alltime<<"      "<<tempqueue.front().ps<<"      "<<tempqueue.front().queueNum<<"      "<<endl;
                tempqueue.pop();  // Delete the 1st element
            }
        }
    }
    if(!finishpcbs.empty())
    {
        // cout<<pnum<<"  "<<finishpcbs.size();
        cout<<endl<<"FINISHED PROC"<<"           ";
        for(int i=finishpcbs.size()-1;i>=0;i--)
            cout<<finishpcbs[i].pid<<"    ";
    }
    cout<<endl;
}

void Fb()
{
    
    if(runpcb==0)//当前没有进程在运行（有一优先级更高进程进入、上一进程运行刚结束）
    {
        //队列为空，返回FBProc等待新进程进入
        int i=0;
        while(waitqueues[i].pcbs.empty()&&i<3)
            i++;
        if(i==3) return;
        //队列不为空，从优先级最高的队列开始调度
        thispcb=waitqueues[i].pcbs.front();
        waitqueues[i].pcbs.pop();
        thispcb.ps=processStatus(0);
        procTime=waitqueues[i].qtime;
        thisqueue=waitqueues[i];
        runpcb=1;
        printqueue();
    }
    if(procTime>0)
    {
        thispcb.cputime-=1;
        thispcb.alltime+=1;
        procTime-=1;
        if(thispcb.cputime==0)
        {
            thispcb.ps=processStatus(2);
            finishpcbs.push_back(thispcb);
            runpcb=0;
        }
    }
    if(procTime==0)
    {
        if(thisqueue.qpri<3)//除最后一级队列以外往下面一级的队尾放
        {
            thispcb.ps=processStatus(1);
            thispcb.queueNum+=1;
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
        if(choose==1)//选择1，则不产生新进程
            Fb();
        else if(choose==2)//选择2，产生新进程进入第一个队列，现有进程停止运行
        {
            newpcbs();
            runpcb=0;
            Fb();
        }
        // printqueue();
        cout<<"=========================================="<<endl;    
        cout<<"CHOOSE THE ACTION (1 TO GO ON, 2 TO ADD A NEW PROCESS)   " ;
    }
}



main()
{
    newqueues();
    FBProc();
    for(int i=finishpcbs.size()-1;i>=0;i--)
        cout<<finishpcbs[i].pid<<"    ";
    cout<<endl;
}

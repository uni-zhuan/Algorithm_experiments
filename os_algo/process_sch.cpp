#include<algorithm>
#include<random>
#include<iostream>
#include<vector>
#include<queue>
#include <iomanip>
using namespace std;

enum processStatus{//枚举进程状态
    run=0,
    wait=1,
    finish=2
};

struct pcb{
    int pid;//进程标识数
    int priority;//优先数/轮转时间片数
    int cputime;//占用CPU时间片数
    int alltime;//进程所需时间片数
    processStatus ps;//进程状态
    int passtime;
    int next;//就绪队列中：下一进程pid,最后一个是-1；结束队列中为-1；运行队列中为就绪队列首
    pcb( int pid,int priority,int cputime,int alltime,
    processStatus ps,int passtime,int next)
    {
        this->pid=pid;
        this->priority=priority;
        this->cputime=cputime;
        this->alltime=alltime;
        this->ps=ps;
        this->passtime;
        this->next=next;
    }
    bool operator<(const pcb & p1)  const
    {
        return priority < p1.priority;
    }
    bool operator>(const pcb & p1)  const
    {
        return priority > p1.priority;
    }
};//头文件定义的结构体后面要加；

vector<pcb> waitpcbs;
vector<pcb> runpcbs;
vector<pcb> finishpcbs;
int nowtime=0;

void newpcbs1()
{
    int i;
    for(i=1;i<=4;i++)
    {
        pcb newpcb(i,rand()%83+1,0,rand()%8+1,processStatus(1),0,i+1);
        //用质数作生成范围内随机数得到的结果会好些
        waitpcbs.push_back(newpcb);
    }
    pcb newpcb(i,rand()%40+1,0,rand()%10+1,processStatus(1),0,-1);
    waitpcbs.push_back(newpcb);
}

void newpcbs2()
{
    int i;
    for(i=1;i<=4;i++)
    {
        pcb newpcb(i,rand()%5+1,0,rand()%10+1,processStatus(1),0,i+1);
        waitpcbs.push_back(newpcb);
    }
    pcb newpcb(i,rand()%5+1,0,rand()%10+1,processStatus(1),0,-1);   
    waitpcbs.push_back(newpcb);     
}

void printProcess()//进程信息打印
{
    int i;
    cout<<"=========================================="<<endl; 
    cout<<"RUNNING PROC"<<"             "<<"WAITING PROC"<<endl;
    if(runpcbs.empty()) cout<<"                       ";
    else cout<<runpcbs[0].pid<<"                       ";
    for(i=0;i<waitpcbs.size();i++)
        cout<<waitpcbs[i].pid<<"   ";
    cout<<endl<<"=========================================="<<endl;
    cout<<"ID"<<"                      ";
    if(!runpcbs.empty()) cout<<runpcbs[0].pid<<"   ";
    for(i=0;i<waitpcbs.size();i++)
        cout<<waitpcbs[i].pid<<"   ";
    cout<<endl<<"PRIORITY"<<"                ";
    if(!runpcbs.empty()) cout<<runpcbs[0].priority<<"   ";
    for(i=0;i<waitpcbs.size();i++)
        cout<<waitpcbs[i].priority<<"   ";
    cout<<endl<<"CPUTIME"<<"                 ";
    if(!runpcbs.empty()) cout<<runpcbs[0].cputime<<"   ";
    for(i=0;i<waitpcbs.size();i++)
        cout<<waitpcbs[i].cputime<<"   ";
    cout<<endl<<"ALLTIME"<<"                 ";
    if(!runpcbs.empty()) cout<<runpcbs[0].alltime<<"   ";
    for(i=0;i<waitpcbs.size();i++)
        cout<<waitpcbs[i].alltime<<"   ";
    cout<<endl<<"STATE"<<"                   ";
    if(!runpcbs.empty()) cout<<runpcbs[0].ps<<"   ";
    for(i=0;i<waitpcbs.size();i++)
        cout<<waitpcbs[i].ps<<"   ";
    cout<<endl<<"NEXT"<<"                    ";
    if(!runpcbs.empty()) cout<<runpcbs[0].next<<"   ";
    for(i=0;i<waitpcbs.size();i++)
        cout<<waitpcbs[i].next<<"   ";

    cout<<endl<<"FINISHED PROC"<<"           ";
    if(!finishpcbs.empty())
        for(i=finishpcbs.size()-1;i>=0;i--)
            cout<<finishpcbs[i].pid<<"    ";
    cout<<endl;
}

void priorityProc()//优先数法
{
    sort(waitpcbs.begin(), waitpcbs.end(),greater<pcb>()); //优先数高优先级高
    printProcess();
    while(!waitpcbs.empty())
    {
        sort(waitpcbs.begin(), waitpcbs.end(),less<pcb>());
        runpcbs.push_back(waitpcbs.back());
        waitpcbs.pop_back();
        runpcbs[0].ps=processStatus(0);
        sort(waitpcbs.begin(), waitpcbs.end(),greater<pcb>());
        ////////////////////
        if(!waitpcbs.empty())
        {
            for(int i=0;i<waitpcbs.size()-1;i++)
            {
                waitpcbs[i].next=waitpcbs[i+1].pid;
            }
            waitpcbs.back().next=-1;
        }
        //等待队列不为空，直到优先数顺序发生变化时再进行调度
        while(!waitpcbs.empty()&&runpcbs[0].priority>=waitpcbs.front().priority)
        {

            runpcbs[0].priority-=3;
            runpcbs[0].alltime-=1;
            runpcbs[0].cputime+=1;  
            runpcbs[0].next=waitpcbs.front().pid; 
            nowtime+=1;
            printProcess();         
        }
        if(waitpcbs.empty())//等待队列中已经为空
        {
            while(runpcbs[0].alltime>0)
            {
                runpcbs[0].priority-=3;
                runpcbs[0].alltime-=1;
                runpcbs[0].cputime+=1;
                nowtime+=1;
                printProcess();           
            }
            runpcbs[0].passtime=nowtime;
            finishpcbs.push_back(runpcbs[0]);
            runpcbs.pop_back();
        }
        //若这里使用if会使runpcbs不能释放
        else if(runpcbs[0].alltime<=0)//判断当前运行进程是否执行完毕，是则放入结束进程
        {
            runpcbs[0].passtime=nowtime;
            runpcbs[0].ps=processStatus(2);
            finishpcbs.push_back(runpcbs[0]);
            runpcbs.pop_back();            
        }
        else//否则放入就绪队列末尾
        {
            waitpcbs.push_back(runpcbs[0]);
            runpcbs.pop_back(); 
            waitpcbs.back().ps=processStatus(1);
        }
    }
    cout<<endl;
}

void RRProc()//简单轮转法
{
    printProcess();
    while(!waitpcbs.empty())
    {
        //拿出队列首个进程占领处理机
        runpcbs.push_back(waitpcbs.front());
        for(int i=0;i<waitpcbs.size()-1;i++)
            waitpcbs[i]=waitpcbs[i+1];
        waitpcbs.pop_back();
        runpcbs[0].ps=processStatus(0);
        int occupytime=runpcbs[0].priority;
        //重置next指针
        if(!waitpcbs.empty())
        {
            for(int i=0;i<waitpcbs.size()-1;i++)
            {
                waitpcbs[i].next=waitpcbs[i+1].pid;
            }
            waitpcbs.back().next=-1;
        }
        //链首进程投入运行，占用处理机时间片到或进程时间片到停止
        while(runpcbs[0].priority>0)
        {
            runpcbs[0].alltime-=1;
            runpcbs[0].cputime+=1; 
            runpcbs[0].next=waitpcbs.front().pid; 
            runpcbs[0].priority-=1;
            nowtime+=1;
            printProcess();  
            //进程时间片到，加finish，跳出循环 
            if(runpcbs[0].alltime==0)
            {
                runpcbs[0].passtime=nowtime;
                runpcbs[0].ps=processStatus(2);
                finishpcbs.push_back(runpcbs[0]);
                runpcbs.pop_back(); 
                break;
            }
        }
        if(!runpcbs.empty())//占用处理机时间片到，排到末尾
        {
            runpcbs[0].priority=occupytime;
            waitpcbs.push_back(runpcbs[0]);
            runpcbs.pop_back(); 
            waitpcbs.back().ps=processStatus(1);
        }
    }
    cout<<endl;
}

main()
{
    int choose;
    cout<<"CHOOSE THE ALGORTITHM: (1 FOR PRIORITY, 2 FOR ROUND BOBIN)  ";
    cin>>choose;
    if(choose==1){
        newpcbs1();
        cout<<"OUTPUT OF PRIORITY"<<endl;
        priorityProc();
    }
    else
    {
        newpcbs2();
        cout<<"OUTPUT OF ROUND BOBIN"<<endl;
        RRProc();
    }
    cout<<"=========================================="<<endl<<"FINISH       "; 
    for(int i=0;i<finishpcbs.size();i++)
        cout<<finishpcbs[i].pid<<setw(8)<< setfill(' ');
    cout<<endl<<"TURNTIME     "; 
    for(int i=0;i<finishpcbs.size();i++)
        cout<<finishpcbs[i].passtime<<setw(8)<< setfill(' ');
    cout<<endl<<"WEIGHTTIME   "; 
    for(int i=0;i<finishpcbs.size();i++)
        cout<<double(finishpcbs[i].passtime)/double(finishpcbs[i].cputime)<<setw(8)<< setfill(' ');
    cout<<endl<<"MEANWEIGHTTIME   "; 
    double sum=0;
    for(int i=0;i<finishpcbs.size();i++)
        sum+=double(finishpcbs[i].passtime)/double(finishpcbs[i].cputime);
    sum/=5.0;
    cout<<sum<<endl;
}

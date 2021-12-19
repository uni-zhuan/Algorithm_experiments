#include<random>
#include<iostream>
#include<vector>
#include<queue>
#include<iomanip>
#include<algorithm>
// #include<Eigen/Dense>
#define NP 3//不同进程数
#define NR 4//不同资源数
using namespace std;
// using namespace Eigen;
struct res{
    int rid;//资源号
    int remiander;//总共需要的资源数量
    res(int rid,int remiander)
    {
        this->rid=rid;
        this->remiander=remiander;
    }
    bool operator<(const res & p1)  const
    {
        return remiander < p1.remiander;
    }
    bool operator>(const res & p1)  const
    {
        return remiander > p1.remiander;
    }
};
struct proc{
    int pid;//进程号
    bool free;//该进程是否已经释放所有资源
    vector<res> resource;
    proc(int pid,bool free)
    {
        this->pid=pid;
        this->free=free;
    }
};//头文件定义的结构体后面要加；

vector<proc> process;
vector<res> priresource;

vector<int> procid;//假定分配的进程
vector<int> request;//假定分配的资源数

void front()//初始化
{
    for(int i=0;i<NR;i++)
    {
        res newres(i+1,rand()%10+10);
        priresource.push_back(newres);
    }
    for(int i=0;i<NP;i++)
    {
        proc newproc(i+1,0);
        for(int j=0;j<NR;j++)
        {
            res newres(j+1,rand()%5+4);
            newproc.resource.push_back(newres);
        }
        process.push_back(newproc);
    }
    for(int i=0;i<10;i++)
    {
        procid.push_back(rand()%3);
        request.push_back(rand()%8);
    }
}

void print()
{
    cout<<endl<<"Remain resource"<<endl;
    for(int j=0;j<NR;j++)
    {
        cout<<setw(3)<<setfill(' ')<<priresource[j].remiander;
    }
    cout<<endl;
}

void alloction()
{
    while(!procid.empty())
    {
        sort(priresource.begin(), priresource.end(),less<res>());//按照资源紧缺程度排序
        int i=0;
        for(;procid[i]==priresource[0].rid;i++)//资源最紧缺的首个rid与procid一致
        {
            ;
        }
        int temp=i;
        process[procid[i]].resource[i].remiander-=request[i];
        swap(*(begin(procid)+i),*(end(procid)-1));
        procid.pop_back();
        swap(*(begin(request)+i),*(end(request)-1));
        request.pop_back();
        if(priresource[procid[i]].remiander>0)
        {
            priresource[procid[i]].remiander-=request[i];
            if(priresource[procid[i]].remiander<0)
                priresource[procid[i]].remiander=0;
        }
        else
        {
            cout<<"deadlock occour!";
            break;
        }
        print();

    }
}

main()
{
    front();
    print();
    alloction();
}
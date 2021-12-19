#include <random>
#include <iostream>
#include <vector>
#include <queue>
#include <iomanip>
#define NP 3 //不同进程数
#define NR 4 //不同资源数
using namespace std;

struct proc
{
    int pid;   //进程号
    bool free; //该进程是否已经释放所有资源
    proc(int pid, bool free)
    {
        this->pid = pid;
        this->free = free;
    }
}; //头文件定义的结构体后面要加；

struct res
{
    int rid;       //进程号
    int remiander; //进程完成请求标志，为1时表示已完成各次请求
    res(int rid, int remiander)
    {
        this->rid = rid;
        this->remiander = remiander;
    }
}; //头文件定义的结构体后面要加；
vector<proc> process;
vector<res> resource;
vector<vector<int>> A(NP, vector<int>(NR));
vector<vector<int>> B(NP, vector<int>(NR));

void add(vector<vector<int>> a1, vector<vector<int>> a2)
{
    for (int i = 0; i < NP; i++) //随机生成资源图分配矩阵和请求矩阵
    {
        for (int j = 0; j < NR; j++)
        {
            a1[i][j] += a2[i][j];
        }
    }
}

void subtract(vector<vector<int>> a1, vector<vector<int>> a2)
{
    for (int i = 0; i < NP; i++) //随机生成资源图分配矩阵和请求矩阵
    {
        for (int j = 0; j < NR; j++)
        {
            a1[i][j] -= a2[i][j];
        }
    }
}

void front() //初始化
{
    for (int i = 0; i < NP; i++) //随机生成资源图分配矩阵和请求矩阵
    {
        for (int j = 0; j < NR; j++)
        {
            A[i][j] = rand() % 4;
            B[i][j] = rand() % 4;
        }
    }
    for (int i = 0; i < NP; i++)
    {
        proc newproc(i + 1, 0);
        process.push_back(newproc);
    }
    for (int i = 0; i < NR; i++)
    {
        res newres(i + 1, rand() % 6);
        resource.push_back(newres);
    }
}

void print()
{
    cout << "Matrix A (alloction): " << endl;
    for (int i = 0; i < NP; i++) //随机生成资源图分配矩阵和请求矩阵
    {
        for (int j = 0; j < NR; j++)
        {
            cout << setw(3) << setfill(' ') << A[i][j];
        }
        cout << endl;
    }
    cout << endl
         << "Matrix B (request): " << endl;
    for (int i = 0; i < NP; i++) //随机生成资源图分配矩阵和请求矩阵
    {
        for (int j = 0; j < NR; j++)
        {
            cout << setw(3) << setfill(' ') << B[i][j];
        }
        cout << endl;
    }
    cout << endl
         << "Remain resource" << endl;
    for (int j = 0; j < NR; j++)
    {
        cout << setw(3) << setfill(' ') << resource[j].remiander;
    }
    cout << endl;
}

bool alloction()
{
    int flag;
    for (int k = 0; k < NP; k++)
    {
        for (int i = 0; i < NP && !(process[i].free); i++)
        {
            flag = 1;
            for (int j = 0; j < NR; j++)
            {
                if (B[i][j] > resource[j].remiander) //某个进程各种资源的请求数都小于当前剩余数
                {
                    flag = 0;
                    break;
                }
            }
            if (flag == 1)
            {
                add(A, B);                   //将该进程的请求量全部分配
                for (int j = 0; j < NR; j++) //将该进程的所有资源全部释放
                    B[i][j] = 0;
                print();
                for (int j = 0; j < NR; j++) //将该进程的所有资源全部释放
                {
                    resource[j].remiander += A[i][j];
                    A[i][j] = 0;
                }
                process[i].free = 1;
                print();
                cout << "====================" << endl;
            }
        }
    }
    flag = 1;
    for (int i = 0; i < NP; i++)
        for (int j = 0; j < NR; j++)
        {
            if (B[i][j] != 0 || A[i][j] != 0) //某个进程各种资源的请求数都小于当前剩余数
                flag = 0;
        }
    if (flag == 0)
    {
        cout << "Can't be simplify completely" << endl;
        return 0;
    }
    else
    {
        cout << "Can be simplify completely" << endl;
        return 1;
    }
}

main()
{
    front();
    print();
    bool dl;
    dl = alloction();
    if (dl)
        cout << "No deadlock!";
}
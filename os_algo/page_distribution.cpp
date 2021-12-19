#include <algorithm>
#include <random>
#include <iostream>
#include <vector>
#include <deque>
#include <iomanip>

#define INF 32767
#define ADDRNB 200
#define RANDADDR 12
#define BLOCK 3
#define RAND 5

using namespace std;

vector<int> addr;//指令地址流
vector<int> pagenb;//页号
vector<int> randpage;//随机生成页面一些
vector<vector<char>> result(RANDADDR, vector<char>(BLOCK));
int emptyflag=0;
deque<int> pagedeque;
double missingrate;

void front()
{
//     本程序是按下述原则生成指令序列的：
// （1） 50%的指令是顺序执行的。
// （2） 25%的指令均匀散布在前地址部分。
// （3） 25%的指令均匀散布在后地址部分。
    int order=rand()%(INF/2);
    for(int i=0;i<ADDRNB/2;i++)
        addr.push_back(order+i);
    for(int i=0;i<ADDRNB/4;i++)
    {
        addr.insert(addr.begin()+rand()%addr.size(),rand()%(INF/2));
        addr.insert(addr.begin()+rand()%addr.size(),rand()%(INF/2)+(INF/2));
    } 
    for(int i=0;i<ADDRNB;i++)
        cout<<"addr["<<i<<"]="<<addr[i]<<" "; 
}

void transpage(int page)
{
    for(int i=0;i<ADDRNB;i++)
    {
        pagenb.push_back(addr[i]/(page*1024));
    }
    cout<<endl;
    for(int i=0;i<ADDRNB;i++)
    {
        cout<<"page["<<i<<"]="<<pagenb[i]<<" "; 
    }
    cout<<endl;
}

void front2()
{
    cout<<"页面序列："<<endl;
    for(int i=0;i<RANDADDR;i++)
        randpage.push_back(rand()%RAND+1);
    for(int i=0;i<RANDADDR;i++)
        cout<<randpage[i]<<" ";
    for(int i=0;i<RANDADDR;i++)
        for(int j=0;j<BLOCK;j++)
            result[i][j]=('_');
}

void print()
{
    cout<<endl<<"结果序列："<<endl;
    for(int i=0;i<BLOCK;i++)
    {
        for(int j=0;j<RANDADDR;j++)//若直接cout会乱码
            if(result[j][i]=='_')
                cout<<'_'<<' ';
            else
                cout<<int(result[j][i])<<' ';
        cout<<endl;
    }
}

void missing()
{
    double sum=0;
    for(int i=0;i<RANDADDR-1;i++)
        for(int j=0;j<BLOCK;j++)
            if(result[i][j]!=result[i+1][j])
            {
                sum++;
                break;
            }
    missingrate=sum/RANDADDR;
    cout<<"缺页次数: "<<sum<<endl;
    cout<<"缺页率: "<<missingrate<<endl;
}

void OPT()
{
    int j;
    for(int i=0;i<RANDADDR;i++)
    {
        for(j=0;j<BLOCK;j++)
        {
            if(result[i][j]=='_')
            {
                result[i][j]=randpage[i];
                // emptyflag=1;
                break;
            }
            if(result[i][j]==randpage[i])
            {
                break;
            }
        }
        if(j==BLOCK)
        {
            //找最迟访问页面
            int tempaddr=i;
            vector<int> fin(RAND);//存放地址的最近一次出现index
            for(int p=0;p<RAND;p++)
            {
                for(int k=i;k<RANDADDR;k++)
                {
                    if(randpage[k]==p+1)
                    {
                        fin[p]=k;
                        break;
                    }
                }
            }
            int tempmax=0;
            while(randpage[tempmax+1]==i|| find(result[i].begin(),result[i].end(),tempmax+1)== result[i].end())
            {
                tempmax++;
            }
            for(int p=1;p<BLOCK;p++)//找最大的最后一次地址值
            {
                if(fin[tempmax]<fin[p]&&randpage[p+1]!=i&& find(result[i].begin(),result[i].end(),p+1)!= result[i].end())
                    tempmax=p;
            }
            for(int p=0;p<BLOCK;p++)
            {
                if(result[i][p]==tempmax+1)
                {
                    result[i][p]=randpage[i];
                }
            }
        }
        for(int k=0;k<BLOCK;k++)
        {
            if(i<RANDADDR-1 && result[i+1][k]=='_')
                result[i+1][k]=result[i][k];
        }
    }
    print();
    missing();
}

void LRU()
{
    for(int i=0;i<RANDADDR;i++)
    {
        if(pagedeque.size()<BLOCK)
            pagedeque.push_back(randpage[i]);
        else if(find(pagedeque.begin(),pagedeque.end(),randpage[i])==pagedeque.end())
        {
            pagedeque.pop_front();
            pagedeque.push_back(randpage[i]);
        }
        else
        {
            pagedeque.erase(find(pagedeque.begin(),pagedeque.end(),randpage[i]));
            pagedeque.push_back(randpage[i]);   
        }
        for(int j=0;j<pagedeque.size();j++)
        {
            result[i][j]=pagedeque[j];
        }
    }
    print();
    missing();
}

void FIFO()
{
    for(int i=0;i<RANDADDR;i++)
    {
        if(pagedeque.size()<BLOCK)
            pagedeque.push_back(randpage[i]);
        else if(find(pagedeque.begin(),pagedeque.end(),randpage[i])!=pagedeque.end())
            ;
        else
        {
            pagedeque.pop_front();
            pagedeque.push_back(randpage[i]); 
        }
        for(int j=0;j<pagedeque.size();j++)
        {
            result[i][j]=pagedeque[j];
        }
    }
    print();
    missing();
}

main()
{
    //要求1
    int page=1;
    int option;
    // front();
    // transpage(page);

    //要求2
    cout << "Option = (1 for OPT, 2 for LRU, 3 for FIFO) ";
    cin >> option;
    front2();
    switch (option)
    {
        case 1:
        {
            OPT();
            break;
        }
        case 2:
        {
            LRU();
            break;
        }
        case 3:
        {
            FIFO();
            break;
        }
    }
}
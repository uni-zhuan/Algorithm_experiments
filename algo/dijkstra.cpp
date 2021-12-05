#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
using namespace std;

#define INF 1e9 // int范围约为 (-2.15e9, 2.15e9)

/*Dijkstra算法解决的是单源最短路径问题，即给定图G(V,E)和起点s(起点又称为源点),边的权值为非负，
求从起点s到达其它顶点的最短距离，并将最短距离存储在矩阵d中*/
void Dijkstra(int n, int s, vector<vector<int>> x, vector<bool> &vis, vector<int> &d, vector<int> *pre)
{
    // 初始化
    fill(vis.begin(), vis.end(), false);//节点都没被访问
    fill(d.begin(), d.end(), INF);//距离无穷大
    d[s] = 0;//起点到自身距离为0
    for (int i = 0; i < n; ++i)//初始化,所有前驱结点都存成0
    {
        pre[i].push_back(s);
    }
    // n次循环,确定d[n]数组
    for (int i = 0; i < n; i++)
    {
        // 找到距离s最短且还未被访问的点u,和最短距离d[u]
        int u = -1;
        int min = INF;
        for (int j = 0; j < n; j++)
        {
            if (!vis[j] && d[j] < min)
            {
                u = j;
                min = d[j];
            }
        }
        // 找不到小于INF的d[u],说明剩下的顶点与起点s不连通
        if (u == -1)
        {
            return;
        }
        vis[u] = true;//标记u被访问
        for (int v = 0; v < n; ++v)
        {
            // 遍历所有顶点，如果v未被访问 && 可以达到v
            if (!vis[v] && x[u][v] != INF)
            {
                if(d[u] + x[u][v] < d[v]) // 以u为中介点使d[v]更小
                {
                    d[v] = d[u] + x[u][v];   // 更新d[v]
                    pre[v].clear();     // 清空前驱节点
                    pre[v].push_back(u);//只保留当前这一个前驱
                }
                else if(d[u] + x[u][v] == d[v]) // 以u为中介点时,d[v]最小距离的路径不止之前的
                {
                    pre[v].push_back(u);//向数组中存入目前的节点作为其他前驱
                }
            }
        }
    }
}


void searchPath(int v, int u, vector<int> *pre,vector<int> sta, int len,vector<int> &path) 
{
    if (u == v) //输出并存 p1节点
    {
        path.push_back(v+1);
        cout<<v+1;
        return ;
    }
    sta[len] = u;
    for (int i = 0 ; i < pre[u].size(); ++i ) {
        if (i > 0) {
            for (int j = len - 1  ; j >= 0 ; --j) {//输出并存前驱节点
                path.push_back(sta[j]+1);
                cout << " -> " << sta[j]+1;
            }
            cout<<endl;
        }
        searchPath( v, pre[u][i], pre, sta, len + 1,path);
        path.push_back(u+1);
        cout << " -> " << u+1;
    }
}

main()
{
    int num=0,p1,p2,n;
    while(cin>>n)
    {
        vector<vector<int>> x(n,vector<int>(n));//x为存放矩阵的二维数组
        for(int i=0;i<n;i++)//输入数据
        {
            for(int j=0;j<n;j++)
            {
                cin>>x[i][j];
                if(x[i][j]==-1)
                    x[i][j]=INF;//INF表示两点间不联通
            }
        }
        cin>>p1>>p2;

        vector<bool> vis(n);//标记顶点是否已经被访问
        vector<int> dist(n);//存储源点到其他顶点的最短距离
        vector<int> pre[n];//最短路径中v的前驱节点
        vector<int> sta(n);//
        vector<int> path(1);//所有最短路径的节点号
        Dijkstra(n, 0, x, vis, dist, pre);
       
        cout<<"Case "<<++num<<endl;
        cout<<"The least distance from "<< p1 <<"->"<<p2<<" is "<<dist[p2-1]<<endl;
        // DFSPrint(p1-1,p2-1,pre);
        int len=0;
        searchPath(p1-1,p2-1,pre,sta,len,path);
        //从顶点s到顶点t有不止一条最短路径，那么输出路段数最少者
        //具有最短路径并且路段数也是最少的路径至少有2条，那么输出按顶点编号的字典序最小者
        int temp=1;int shorter=INF;int shortest=0;int shorttemp;
        path.push_back(INF);
for(int i=2;i<=path.size();i++)
{
    if(path[i]==p1&&shorter>temp)
    //逐个比较,找到最小路段数源点下标
    {   
        shortest=i+1-temp;
        swap(shorter,temp);
        temp=1;
    }
    else if(path[i]==p1&&shorter==temp)
    //路径和路段都最小时比较字典序并找最小的源点下标
    {  
        shorttemp=shortest;
        for(int j=i-temp;j<i;j++)
        {
            if(path[j]==path[shorttemp-1])
                shorttemp++;
            else if(path[j]<path[shorttemp-1])
            {
                int swapdata=i+1-temp;
                swap(shortest,swapdata);
                break;
                temp=1;
            }
        }
    }
    else if(path[i]==p1)
        temp=1;
    else
        temp++;
}
        if(shortest==0)
            cout<<endl<<"there have only one least distance.";
        else
        {
            cout<<endl<<"the least section:"<<p1;
            for(int i=shortest;path[i]!=p1;i++)
                cout<<"->"<<path[i];
        }
        cout<<endl;
    }
}
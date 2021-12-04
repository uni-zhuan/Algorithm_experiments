#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
using namespace std;

#define INF 1e9 // int范围约为 (-2.15e9, 2.15e9)

/*Dijkstra算法解决的是单源最短路径问题，即给定图G(V,E)和起点s(起点又称为源点),边的权值为非负，
求从起点s到达其它顶点的最短距离，并将最短距离存储在矩阵d中*/
void Dijkstra(int n, int s, vector<vector<int>> x, vector<bool> &vis, vector<int> &d, vector<int> &pre)
{
    // 初始化
    fill(vis.begin(), vis.end(), false);//节点都没被访问
    fill(d.begin(), d.end(), INF);//距离无穷大
    d[s] = 0;//起点到自身距离为0
    for (int i = 0; i < n; ++i)
    {
        pre[i] = i;
    }
    // n次循环,确定d[n]数组
    for (int i = 0; i < n; i++)
    {
        // 找到距离s最短且还未被访问的点u,和最短距离d[u]
        int u = -1;
        int MIN = INF;
        for (int j = 0; j < n; j++)
        {
            if (!vis[j] && d[j] < MIN)
            {
                u = j;
                MIN = d[j];
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
            // 遍历所有顶点，如果v未被访问 && 可以达到v && 以u为中介点使d[v]更小
            if (!vis[v] && x[u][v] != INF && d[u] + x[u][v] < d[v])
            {
                d[v] = d[u] + x[u][v];   // 更新d[v]
                pre[v] = u;              // 记录v的前驱顶点为u（新添加）
            }
        }
    }
}


void DFSPrint(int s, int v, vector<int> pre)//深度搜索算法打路径
{
       if (v == s) {
              cout << "the path is "<<s+1;
              return;
       }
       DFSPrint(s, pre[v], pre);
       cout <<"->"<< v+1 ;
}

main()
{
    int num=0,p1,p2,n;
    while(cin>>n)
    {
        vector<vector<int>> x(n+1,vector<int>(n+1));//x为存放矩阵的二维数组
        for(int i=0;i<n;i++)//从第二行第二列开始的
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
        vector<int> pre(n);//最短路径中v的前驱节点
        Dijkstra(n, 0, x, vis, dist, pre);
       
        cout<<"Case "<<++num<<endl;
        cout<<"The least distance from "<< p1 <<"->"<<p2<<" is "<<dist[p2-1]<<endl;
        DFSPrint(p1-1,p2-1,pre);
    }
}
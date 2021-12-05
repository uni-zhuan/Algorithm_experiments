// 回溯、搜索剪枝、使用子集树
//在子集树的第j+1层的结点z处，用cw记当前的装载重量
//当cw>c1时，以结点z为根的子树中所有结点都不满足约束条件，故可将该子树剪去
//引入一个上界函数，用于剪去不含最优解的子树

#include <iostream>
#include<vector>
using namespace std;
int c1, c2;         //分别载重量
int n;              //集装箱数量
int w[10];         //集装箱重量
int cw;             //c1当前载重量
int bestw;          //c1当前最优载重量
int r;              //剩余集装箱重量
int x[10];         //当前解
int bestx[10];      //当前最优解

void Backtrack(int i)
{
    if(i > n)//到达叶子节点时
    {
        //当前解优于最优解，更新
        if(cw > bestw)
        {
            for(int j = 1; j <= n; j++)//更新存储的最优载重量
                bestx[j] = x[j];
            bestw = cw;//更新c1当前最优载重量
        }
        return;
    }
 
    //搜索子树,放入或不放入
    r -= w[i];              //剩余容量集合去掉w[i]
    if(cw + w[i] <= c1)     //可放入，且放入
    {
        x[i] = 1;           //放入,子树节点置为1
        cw += w[i];         //当前重量加上他
        Backtrack(i+1);     //判断下一个物品
        cw -= w[i];         //再减掉当前重量,为进行是否有新的最优载重量的判断
    }
	//如果当前c1的载重量+当前节点的子树的最大重量都没有betsw（最优载重量）大，不放入当前的重量
	//就不再向当前节点的右子树移动了，即剪枝。
    if(cw + r > bestw)      //有可能有新的最优载重量
    {
        x[i] = 0;//向右子树移动,这个物品不放入
        Backtrack(i+1);//判断下一个物品
    }
    r += w[i];              //回溯
}
 main()
{
    int num=1;
    while(cin>>n)
    {
        cw = 0;             //每组样例初始化
        r = 0;
        bestw = 0;
        for(int i = 1; i <= n; i++)
        {
            cin >> w[i];
            r += w[i];
        }
        cin>>c1>>c2;
        Backtrack(1);
        cout<<"Case "<<num<<endl;
        if(r-bestw <= c2)
        {
            cout << bestw <<" ";
            for(int i=1;i<=n;i++)
                cout<<bestx[i];
            cout << endl;
        }
        else
            cout << "No" << endl;
        num++;
    }
}
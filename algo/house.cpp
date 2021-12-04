#include<iostream>
#include<queue>
using namespace std;

struct point
{
    int x;//坐标
	int y;
    int step;//当前步数
};
int dir[8][2]={{1,2},{2,1},{1,-2},{-2,1},{-1,2},{2,-1},{-2,-1},{-1,-2}};//列举所有可能的跳步情况
int vis[8][8]={0};//记录该点是否访问过
queue<point> q;
point S,E;

int bfs()
{
	//清空队列
    while(!q.empty()) 
        q.pop();
    S.step=0;
    q.push(S);
    vis[S.x][S.y]=1;//标记开始地址
    while(!q.empty())
    {//依次将队列里的元素出队查看是否到达终点，如是则return，否就将该点8个方向上的点依次入队
        point cur=q.front();//放置一个指向当前队尾的旗标
		vis[cur.x][cur.y]=1;
        q.pop();
        if(cur.x==E.x&&cur.y==E.y)//到达中点则return当前步
            return cur.step;
        for(int i=0;i<8;i++)//逐个探查是否能到
        {
            point nxt;
            nxt.x=cur.x+dir[i][0];
            nxt.y=cur.y+dir[i][1];
            nxt.step=cur.step+1;
			vis[nxt.x][nxt.y]=1;
            if(nxt.x<1||nxt.x>8||nxt.y<1||nxt.y>8)  //超出棋盘边界
                continue;
			if(vis[nxt.x][nxt.y]==1) //该点已经访问过
                continue;
            q.push(nxt);//无法到达终点,依次入队进行下一轮bfs
        }
    }
    return -1;
}

int main()
{
    int x1,y1;
    string a,b;
    while(cin>>a)
          {
              cin>>b;
              //cout<<a<<" "<<b<<endl;
              S.x=a[1]-'0';
              S.y=a[0]-'a'+1;
              E.x=b[1]-'0';
              E.y=b[0]-'a'+1;
              //cout<<x2<<" "<<y2<<endl;
              if(a==b)
                cout<<a<<"==>"<<b<<": "<<0<<" moves"<<endl;
              else
              {
				int step=bfs();
				if(step>0)
                	cout<<a<<"==>"<<b<<": "<<step<<" moves"<<endl;
				else
					cout<<a<<"==>"<<b<<": "<<"fail"<<endl;
              }
          }
    return 0;
}
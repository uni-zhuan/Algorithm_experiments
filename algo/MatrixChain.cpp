#include<iostream>
#include<cstring>
#include<vector>
#include<iomanip>
using namespace std;
using std::vector;

#define SIZE 100
void MatrixChain(vector<int> &p,int n,vector<vector<int>> &m,vector<vector<int>> &s)
//p:输入参数p0-pn n:矩阵数目 m:存储最小次数 s:存储分割位置
{
    for(int i=1;i<=n;i++)
    //单个矩阵乘法次数赋值为0
    {
        m[i][i]=0;
    }
    for(int r=2;r<=n;r++)//r表示当前问题的规模,有r个矩阵相乘
    {
        for(int i=1;i<=n-r+1;i++)
        {
            int j=i+r-1;
            m[i][j]=m[i+1][j]+p[i-1]*p[i]*p[j];
            s[i][j]=i;
            for(int k=i+1;k<j;k++)
            //移动寻找最优解
            {
                int temp=m[i][k]+m[k+1][j]+p[i-1]*p[k]*p[j];
                if(temp<m[i][j])
                {
                    m[i][j]=temp;
                    s[i][j]=k;
                }
            }
        }
    }
}

void print(const vector<vector<int>> &s,const vector<vector<int>> &m,const int n)
{
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=n;j++)
        {
            cout<<left<<setw(5)<<s[i][j]<<" ";
        }
        cout<<endl;
    }
    cout<<endl;
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=n;j++)
        {
            cout<<left<<setw(5)<<m[i][j]<<" ";
        }
        cout<<endl;
    }
}

void Traceback(int i,int j,const vector<vector<int>> &s,const int n)
{
	if(i == j)//递归出口
	{
		cout<<"A"<<i;
		return;
	}
    //递归输出左边
    if(i!=1||j!=n)
	    cout<<"(";
	Traceback(i,s[i][j],s,n);
    //递归输出右边
	Traceback(s[i][j]+1,j,s,n);
    if(i!=1||j!=n)
	    cout<<")";
}

main()
{
    vector<vector<int>> m(SIZE,vector<int>(SIZE)),s(SIZE,vector<int>(SIZE));
    int n;
    int num=1;
    vector<int> p;
    while(cin>>n)
    {
        // cout<<"start:";
        // cin>>n;
        for(int i=0;i<=n;i++)
        {
            int pn;
            cin>>pn;
            p.push_back(pn);
        }
        cout<<"Case "<<num<<endl;
        num++;
        MatrixChain(p,n,m,s);
        cout<<m[1][n]<<" ";
        Traceback(1,n,s,n);        
        cout<<endl;    
        print(s,m,n);
        cout<<endl;
    }  
    
}
// X = “ABCBDAB”、Y = “BDCABA”
#include<iostream>
#include<vector>
#include<set>
#include<iomanip>
#include<math.h>
// #include<string.h>
#include<algorithm>
using namespace std;
set<string> allLCS; //使用集合保存所有lcs序列保证不重复
#define SIZE 10
int length;
void LCSLength(int m,int n,vector<char> &x,vector<char> &y,vector<vector<int>> &c,vector<vector<int>> &b)
{
    //c:记录最长公共子序列的长度、b：记录最长公共子序列的路径
    //初始化空序列
    for(int i=1;i<=m;i++)
    {
        c[i][0]=0;
    }
    for(int i=1;i<=n;i++)
    {
        c[0][i]=0;
    }
    for(int i=1;i<=m;++i)
    {
        for(int j=1;j<=n;++j)
        {
            //当前最后一个元素相同时
            if(x[i]==y[j])
            {
                c[i][j]=c[i-1][j-1]+1;  
                b[i][j]=1;
            }
            //当前最后一个元素不相同时
            else if(c[i-1][j]>=c[i][j-1]){
                c[i][j]=c[i-1][j];
                b[i][j]=2;
            }
            else
            {
                c[i][j]=c[i][j-1];
                b[i][j]=3;
            }
        }
    }
}
void LCS(int i,int j,const vector<char> &x,const vector<vector<int>> &b)
{
    if(i==0||j==0)
    {
        return;
    }
    if(b[i][j]==1)
    {
        LCS(i-1,j-1,x,b);
        cout<<x[i];
    }
    else if(b[i][j]==2)
    {
        LCS(i-1,j,x,b);
    }
    else
    {
        LCS(i,j-1,x,b);
    }
}

void print(const vector<vector<int>> &cn,const vector<vector<int>> &bn,int m,int n)
{
    cout<<endl;
    cout<<"b("<<m<<","<<n<<"):"<<endl;
    for(int i=0;i<=m;i++)
    {
       for(int j=0;j<=n;j++)
        {
            cout<<bn[i][j]<<" ";
        }
        cout<<endl;
    }
    cout<<endl<<"c("<<m<<","<<n<<"):"<<endl;
    for(int i=0;i<=m;i++)
    {
       for(int j=0;j<=n;j++)
        {
            // cout<<cn[i][j]<<" ";
            cout<<cn[i][j]<<" ";
        }
        cout<<endl;
    }
    cout<<endl;
}

void allInSet(const vector<char> &x,const vector<char> &y,const vector<vector<int>> &c,int i,int j,string LCS_str)
{
    while(i>0&&j>0)
    {
        if(x[i]==y[j])
        {
            LCS_str.push_back(x[i]);
            --i;
            --j;
        }
        else
        {
            if(c[i-1][j]>c[i][j-1])
            {
                i--;
            }
            else if(c[i-1][j]<c[i][j-1])
            {
                j--;
            }
            else
            {
                allInSet(x,y,c,i-1,j,LCS_str);
                allInSet(x,y,c,i,j-1,LCS_str);
                return;
            }
        }
    }
    reverse(LCS_str.begin(),LCS_str.end());
    allLCS.insert(LCS_str);
}


main()
{
    vector<vector<int>> c(SIZE,vector<int>(SIZE)),b(SIZE,vector<int>(SIZE));
    int m,n;
    int num;
    int casenum=1;
    vector<char> x,y;
    int length;
    string LCS_str;
    cin>>num;
    while(num--)
    {
        // cout<<"start:";
        cin>>m>>n;
        x.push_back('x');
        for(int i=0;i<m;i++)
        {
            char xn;
            cin>>xn;
            x.push_back(xn);
        }
        y.push_back('x');
        for(int i=0;i<n;i++)
        {
            char yn;
            cin>>yn;
            y.push_back(yn);
        }
        cout<<endl<<"Case "<<casenum<<endl;
        LCSLength(m,n,x,y,c,b);
        length=c[m][n];
        // LCS(m,n,x,b);

        allInSet(x,y,c,m,n,LCS_str);
        set<string>::iterator it = allLCS.begin();//迭代集合中所有的LCS序列
	    for( ; it!=allLCS.end(); ++it)
		    cout << *it << endl;
        allLCS.clear();
        print(c,b,m,n);
        casenum++;
        x.clear();
        y.clear();
    }
}
#include <iostream>
#include <math.h>
using namespace std;

//（1）n是偶数，x，y均为素数，给n,x,y赋初值
int n = 2;
int x = 2;
int y = 2; // n是偶数，x，y均为素数
int q = 0;
int sushu(int a)
{ //确定a是否为素数
    int k = 1;
    if (a != 2)
    {
        for (int i = 2; i < a; i++)
        {
            if (a % i == 0)
                k = 0;
        }
    }
    else
        k = 1;
    return k;
}
//（2）寻找素数x,y，使得偶数n=x+y；
main()
{
    for (n = 4; n <= 100; n = n + 2)
    {
        //（2.1）找到在2~n之间的所有素数对的组合；
        q = 0;
        for (x = 2; x < n; x++)
        {
            if (sushu(x) == 1)
            {
                for (y = 2; y < n; y++)
                {
                    if (sushu(y) == 1)
                    {
                        // （2 .2）判断x + y是否等于n ，是输出结果 if (x + y == n && q == 0)
                        {
                            //（3）按要求输出结果
                            if (x + y == n && q == 0)
                            {
                                cout << n << '=' << x << '+' << y << endl;
                                q = 1;
                            }
                        }
                    }
                }
            }
        }
    }
}
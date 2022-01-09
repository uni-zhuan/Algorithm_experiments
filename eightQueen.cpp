#include <stdio.h>
#include <iostream>
#include <iomanip>
using namespace std;
int a[8], b[16], c[16], s[8]; //声明全局变量
int sum = 0;
//打印结果
void print()
{
    cout << "Row: 1 2 3 4 5 6 7 8 " << endl;
    cout << "Col:";
    for (int i = 0; i < 8; i++)
    {
        cout << setw(2) << s[i];
    }
    cout << endl;
}
//移走(i,j)上的皇后
void Queen(int i, int j)
{
    a[j] = 1;
    b[i + j + 1] = 1;
    c[i - j + 8] = 1;
}
//八皇后算法
void eightQueen()
{
    int i, j;
    for (int i = 1; i < 16; i++)
    {
        if (i > 0 && i <= 8)
        {
            a[i - 1] = 1;
        }
        b[i] = 1;
        c[i] = 1;
    }
    i = 0;
    j = 0;
    while (i >= 0)//i<0时终止循环
    {
        while (j < 8)//在i行寻找安全位置
        {
            if (a[j] && b[i + j + 1] && c[i - j + 8])
            {
                break;
            }
            j++;
        }
        if (j < 8)
        {
            a[j] = 0;
            b[i + j + 1] = 0;
            c[i - j + 8] = 0;
            s[i] = j;
            if (i == 7)//找到解
            {
                print();
                sum++;
                Queen(i, j);
                i--;
                j = s[i];
                Queen(i, j);
                j++;
            }
            else//防止下一皇后
            {
                i++;
                j = 0;
            }
        }
        else//退栈
        {
            i--;
            if (i >= 0)
            {
                j = s[i];
                Queen(i, j);
                j++;
            }
        }
    }
}
main()
{
    eightQueen();
    cout << "Number: " << sum << endl;
}

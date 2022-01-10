#include <iostream>
#include <math.h>
using namespace std;
int x, y; // x为客人使用钞票的张数，y为售货员找出钞票的张数
main()
{
    //（1）给x和y赋初值
    x = 10;
    y = 1;
    //（2）寻找方案使19=2*x-5*y
    //（2.1）寻找使19=2*x-5*y成立的最小的x；
    for (x = 10; x < 50; x++)
    {
        //（2.2）寻找使19=2*x-5*y成立的最小的x；
        for (y = 1; y < 50; y++)
            if (2 * x - 5 * y == 19)
                break;
        if (2 * x - 5 * y == 19)
            break;
    }
    //（3）打印付款方法
    cout << "顾客付";
    cout << x;
    cout << "张2元钞票" << endl;
    cout << "售货员找";
    cout << y;
    cout << "张5元钞票" << endl;
}

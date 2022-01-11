#include <iostream>
#include <string>
using namespace std;

int p3(int ih)
{
    return ih*ih*ih;
}

int p4(int ih)
{
    return ih*ih*ih*ih;
}

int main()
{
    int i, il, ih, min, a, b, k;
    int j[200], s[200], p[200];
    //s[k]表示第k行中已经生成的最后一个候选者
    //j[k]表示k行中已经生成的最后一个候选者的下标j
    //p[k]为避免多余计算,将p(i)保留起来
    i = 1;
    ih = 2;//界限，即只对k<=ih的进行挑选和赋初值
    il = 1;//i的下界
    j[1] = 1;
    p[1] = 1;
    s[1] = 1;
    j[2] = 1;
    p[2] = 8;
    s[2] = 9;
    // p[2] = 16;
    // s[2] = 17;
    do
    {
        min = s[i];//已生成的候选者
        a = i;
        b = j[i];
        if (j[i] == i)
        //第i行候选者已全部生成，执行后续语句是不需考虑i行，下界增加
            il = il + 1;
        else
        {
            if (j[i] == 1)//增大ih，且给s[ih]置初值
            {
                ih = ih + 1;
                p[ih] = p3(ih);
                // p[ih] = p4(ih);
                j[ih] = 1;
                s[ih] = p[ih] + 1;
            }
            j[i] = j[i] + 1;//增大j[i],且用第i行中下一个候选者替换s[i]
            s[i] = p[i] + p[j[i]];
        }
        // 确定i，使得s[i]=min(s[1],…,s[ih])
        i = il;
        k = i;
        while (k < ih)
        {
            k = k + 1;
            if (s[k] < s[i])
                i = k;
        }
    } while (s[i] != min);
    cout<< "s = " << min << " = " << a << "^3 + " << b << "^3 = " << i << "^3 + " << j[i] << "^3" << endl;
    // cout<< "s = " << min << " = " << a << "^4 + " << b << "^4 = " << i << "^4 + " << j[i] << "^4" << endl;
    return 0;
}

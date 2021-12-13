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
    int j[13], s[13], p[13];
    //s[k]表示第k行中已经生成的最后一个候选者
    //j[k]表示k行中已经生成的最后一个候选者的下标j
    i = 1;
    ih = 2;
    il = 1;
    j[1] = 1;
    p[1] = 1;
    s[1] = 1;
    j[2] = 1;
    p[2] = 8;
    s[2] = 9;
    do
    {
        min = s[i];
        a = i;
        b = j[i];
        if (j[i] == i)
            il = il + 1;
        else
        {
            if (j[i] == 1)
            {
                ih = ih + 1;
                p[ih] = ih * ih * ih;
                j[ih] = 1;
                s[ih] = p[ih] + 1;
            }
            j[i] = j[i] + 1;
            s[i] = p[i] + p[j[i]];
        }
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
    return 0;
}

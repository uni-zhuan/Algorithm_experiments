#include <iostream>
#include <math.h>
using namespace std;
int x,y,z;
release1()
{
    if(x>=y)
        z=x;
}
release2()
{
    if(x>=y)
        z=x;
    if(y>=x)
        z=y;
}
final()
{
    if(x>=y)
        z=x;
    else
        z=y;
}
main()
{
    cout<<"Input x,y: ";
    cin>>x;cin>>y;
    final();
    cout<<"Max: "<<z;
}
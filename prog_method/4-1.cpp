#include <iostream>
#include <math.h>
using namespace std;

main()
{
    int size = 10;
    int l = 1, max = 1;
    int b[10] = {1, 1, 2, 2, 2, 2, 4, 5, 5, 6};
    int i = 1; // Begin
    do
    {
        if (b[i] == b[i - 1])
        {
            l++;
            i++; // Recur
            if (max < l)
                max = l;
        }
        else //
        {
            i++;
            l = 1;
        }
    } while (i != size); // Termination
    cout << "MaxLength: " << max;
}


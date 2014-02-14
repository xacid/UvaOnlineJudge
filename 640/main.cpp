#include <iostream>
#include <vector>
#include <cstdio>
using namespace std;

int _digitation(int n)
{
    int ret = n;
    while(n > 0)
    {
        ret += n % 10;
        n /= 10;
    }
    return ret;
}

void _printSelfNum()
{
    const int MAX = 1000001;
    vector<bool> vSelf(MAX, true);
    for(int i = 0; i < MAX; ++i)
    {
        int d = _digitation(i);
        if(d < MAX)
        {
            vSelf[d] = false;
        }
    }
    for(int i = 0; i < MAX; ++i)
    {
        if(true == vSelf[i])
        {
            printf("%ld\n", i);
        }
    }
}

int main()
{
    _printSelfNum();
    return 0;
}

#include <iostream>
#include <vector>
#include <cstdio>
using namespace std;

const int MAX = 1000001;
int D[MAX] = {0};

void _buildTable()
{
    // D(n) = nk + n[k-1] + ... + n1 + n0
    // D(0) = 0
    // D(n) = D(n / 10) + (n % 10)
    for(int i = 0; i < MAX; ++i)
    {
        D[i] = D[i / 10] + (i % 10);
    }
}

void _printSelfNum()
{
    const int MAX = 1000001;
    vector<bool> vSelf(MAX, true);
    for(int i = 0; i < MAX; ++i)
    {
        int d = D[i] + i;
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
    _buildTable();
    _printSelfNum();
    return 0;
}

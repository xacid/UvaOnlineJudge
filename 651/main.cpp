/********************************************************************
 * 651 - Deck, OVa Online Judge
 * http://uva.onlinejudge.org/external/6/651.html
 * Remark:
 * 1. Compute recursively:
 *        L[1] = 0.5
 *        L[n] = L[n-1] + x,
 *    where x is overall center of mass that
 *        (0.5 - x) * 1 = x * (n - 1).
 *    =>  L[n] = L[n-1] + 0.5 / n
 ********************************************************************/
#include <iostream>
#include <vector>
#include <cstdio>
using namespace std;

double _length(int n)
{
    static vector<double> s_vL(100000, 0);
    static int s_iMax = 1;
    s_vL[1] = 0.5;
    if(n <= s_iMax)
    {
        return s_vL[n];
    }
    for(int i = s_iMax + 1; i <= n; ++i)
    {
        s_vL[i] = s_vL[i - 1] + 0.5 / (double) i;
    }
    s_iMax = n;
    return s_vL[n];
}

int main()
{
    puts("# Cards Overhang");
    int iCard = 0;
    while(cin >> iCard)
    {
        printf("%5ld     %.3f\n", iCard, _length(iCard));
    }
    return 0;
}
#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <cmath>
using namespace std;

bool _isSquare(unsigned long n)
{
    unsigned long est = (unsigned long) sqrt((double) n);
    unsigned long b = est + 1;
    if(est * est == n) return true;
    if(b * b == n) return true;

    return false;
}

unsigned long _calcBase(const vector<int>& in, int base)
{
    unsigned long ret = (unsigned int)in[0];
    for(int i = 1; i < in.size(); ++i)
    {
        // check overflow here.
        ret *= base;
        ret += in[i];
    }
    return ret;
}

int _findBase(const vector<int>& in)
{
    int minBase = 0;
    for(int i = 0; i < in.size(); ++i)
    {
        minBase = max(minBase, in[i]);
    }
    for(int i = minBase + 1; i < 100; ++i)
    {
        unsigned long decimal = _calcBase(in, i);
        if(decimal == 0)
        {
            return 0; // overflow & not found.
        }
        if(_isSquare(decimal) == true)
        {
            return i;
        }
    }
    // not found, return 0.
    return 0;
}

int main()
{
    char buf[100];
    memset(buf, 0, sizeof(buf));
    cin.getline(buf, 100);
    while('0' != buf[0])
    {
        // format input
        vector<int> input;
        int idx = 0;
        while('\0' != buf[idx])
        {
            input.push_back((unsigned char)(buf[idx] - '0'));
            ++idx;
        }
        printf("%u\n", _findBase(input));
        memset(buf, 0, sizeof(buf));
        cin.getline(buf, 100);
    }
    return 0;
}
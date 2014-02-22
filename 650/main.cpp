#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <cstdio>
using namespace std;

void _printDigit(int val)
{
    char c = '0';
    if(10 == val)
    {
        c = 'X';
    }
    else if(0 == val)
    {
        c = '-';
    }
    else
    {
        c = '0' + val;
    }
    printf("%c", c);
}

bool _printTwo(const vector<int>& v, int i)
{
    _printDigit(10 - v[i]);
    if(i + 1 < v.size())
    {
        if(0 == v[i])
        {
            _printDigit(10 - v[i + 1]);
            return true;
        }
        if(0 == v[i + 1])
        {
            fputs("/", stdout);
            return true;
        }
        _printDigit(v[i] - v[i + 1]);
    }
    return false;
}

int main()
{
    int iCase = 0;
    char buf[80];
    while(cin.getline(buf, 80))
    {
        // Input
        stringstream ss(buf);
        string sName;
        ss >> sName;
        sName += string(12 - sName.size(), ' ');
        vector<int> vStand;
        int iStand = 0;
        while(ss >> iStand)
        {
            vStand.push_back(iStand);
        }
        // Output
        if(iCase > 0)
        {
            puts("");
        }
        ++iCase;
        printf("%s", sName.c_str());
        int iBall = 0;
        int iFrame = 0;
        while(iBall < vStand.size())
        {
            iFrame += 1;
            fputs(" ", stdout);
            if(0 == vStand[iBall])
            {
                // Strike
                _printDigit(10 - vStand[iBall]);
                if(iFrame < 10)
                {
                    fputs("  ", stdout);
                    iBall += 1;
                    continue;
                }
                if(iBall + 1 < vStand.size())
                {
                    _printTwo(vStand, iBall + 1);
                }
                break;
            }
            bool bSpare = _printTwo(vStand, iBall);
            if(10 == iFrame)
            {
                if((bSpare == true) && (iBall + 2 < vStand.size()))
                {
                    _printDigit(10 - vStand[iBall + 2]);
                }
                break;
            }
            fputs(" ", stdout);
            iBall += 2;
        }
        fputs("\n            ", stdout);
        // Print scores
        bool bFirst = true;
        iFrame = 1;
        int iTotal = 0;
        for(int i = 0; (i < vStand.size()) && (iFrame <= 10); ++i)
        {
            if(true == bFirst)
            {
                // Strike
                if(0 == vStand[i])
                {
                    if(i + 2 >= vStand.size())
                    {
                        break;
                    }
                    iTotal += 10 +
                        (0 == vStand[i + 1] ? 20 - vStand[i + 2] : 10 - vStand[i + 2]);
                }
                else
                {
                    bFirst = false;
                    continue;
                }
            }
            else
            {
                iTotal += 10 - vStand[i];
                // Spare
                if(0 == vStand[i])
                {
                    if(i + 1 >= vStand.size())
                    {
                        break;
                    }
                    iTotal += 10 - vStand[i + 1];
                }
            }
            printf("%4ld", iTotal);
            bFirst = true;
            ++iFrame;
        }
        puts("");
    }
    return 0;
}

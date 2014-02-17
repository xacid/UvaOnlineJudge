#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cstdio>
using namespace std;

struct StringIdx
{
    string s;
    int idx;

    StringIdx(int n, char c) :
        s(n, c),
        idx(0)
    {}
    char& operator[](int i)
    {
        return s[i];
    }
    bool operator<(const StringIdx& rhs) const
    {
        return (s < rhs.s);
    }
};

string _BWT(const string& s, int& oiS1)
{
    const int len = s.size();
    string ret("");
    if(len < 2)
    {
        oiS1 = 0;
        return s;
    }

    vector<StringIdx> v(len, StringIdx(len, ' '));
    v[0].s = s;
    v[0].idx = 0;
    for(int i = 1; i < len; ++i)
    {
        for(int j = 0; j < len - 1; ++j)
        {
            v[i][j] = v[i - 1][j + 1];
        }
        v[i][len - 1] = v[i - 1][0];
        v[i].idx = i;
    }
    sort(v.begin(), v.end());
    ret.resize(len);
    for(int i = 0; i < len; ++i)
    {
        ret[i] = v[i][len - 1];
        if(1 == v[i].idx)
        {
            oiS1 = i;
        }
    }
    return ret;
}

int main()
{
    int iNumSet = 0;
    cin >> iNumSet;
    for(int iSet = 0; iSet < iNumSet; ++iSet)
    {
        int iChar = 0;
        cin >> iChar;
        string sIn(iChar, ' ');
        char buf[80];
        cin.getline(buf, 51);
        for(int i = 0; i < (iChar + 49) / 50; ++i)
        {
            cin.getline(buf, 51);
            for(int j = 0; (j + i * 50 < sIn.size()) && (j < 50); ++j)
            {
                sIn[j + i * 50] = buf[j];
            }
        }
        int iS1 = 0;
        string sOut = _BWT(sIn, iS1);
        // Print
        printf("%ld", iS1);
        for(int i = 0; i < sOut.size(); ++i)
        {
            if(i % 50 == 0)
            {
                puts("");
            }
            printf("%c", sOut[i]);
        }
        puts("");
        if(iSet < iNumSet - 1)
        {
            puts("");
        }
    }
    return 0;
}

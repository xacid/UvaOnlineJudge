#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cstdio>
#include <cctype>
using namespace std;

struct Bundle
{
    string sZip;
    int iLetter;
    int iBundle;

    bool operator<(const Bundle& rhs) const
    {
        return (sZip < rhs.sZip);
    }
};

template<class T>
class OrderedSet
{
public:
    OrderedSet(){}
    void push_back(const T& v)
    {
        for(int i = 0; i < m_vData.size(); ++i)
        {
            if(v == m_vData[i])
            {
                return;
            }
        }
        m_vData.push_back(v);
    }
    int size() const
    {
        return m_vData.size();
    }
    T& operator[](int i)
    {
        return m_vData[i];
    }

private:
    vector<T> m_vData;
};

struct TotalLetter
{
    int iTotal;

    explicit TotalLetter() :
        iTotal(0)
    {}
    void operator()(const Bundle& b)
    {
        iTotal += b.iLetter;
    }
};

struct TotalBundle
{
    int iTotal;

    explicit TotalBundle() :
        iTotal(0)
    {}
    void operator()(const Bundle& b)
    {
        iTotal += b.iBundle;
    }
};

bool _checkZip(const string& s)
{
    if(s.size() != 5)
    {
        return false;
    }
    if("00000" == s)
    {
        return false;
    }
    for(int i = 0; i < 5; ++i)
    {
        if((s[i] < '0') || (s[i] > '9'))
        {
            return false;
        }
    }
    return true;
}

Bundle _packBundle(vector<string>& v, int a, int b, int n)
{
    Bundle ret;
    ret.sZip = v[a].substr(0, n) + string(5 - n, 'x');
    ret.iLetter = b - a;
    ret.iBundle = (b - a + 14) / 15;
    v.erase(v.begin() + a, v.begin() + b);
    return ret;
}

vector<Bundle> _getBundle(vector<string>& v, const int n)
{
    vector<Bundle> ret;
    int iBegin = 0;
    for(int i = 1; i < v.size(); ++i)
    {
        if(v[i].substr(0, n) != v[i - 1].substr(0, n))
        {
            if(i - iBegin < 10)
            {
                iBegin = i;
            }
            else // if(i - iBegin >= 10)
            {
                Bundle b = _packBundle(v, iBegin, i, n);
                ret.push_back(b);
                i = iBegin;
            }
        }
    }
    if(v.size() - iBegin >= 10)
    {
        Bundle b = _packBundle(v, iBegin, v.size(), n);
        ret.push_back(b);
    }
    return ret;
}

vector<Bundle> _getBundle1(vector<string>& v)
{
    vector<Bundle> ret;
    for(int i = 0; i < v.size(); ++i)
    {
        if((0 == i) || (v[i] != v[i - 1]))
        {
            Bundle b;
            b.sZip = v[i];
            b.iLetter = 1;
            b.iBundle = 0;
            ret.push_back(b);
        }
        else // if(v[i] == v[i-1])
        {
            ret.back().iLetter += 1;
        }
    }
    return ret;
}

template<class T, class U>
void _forEach(T first, T last, U& action)
{
    while(first != last)
    {
        action(*first);
        ++first;
    }
}

int main()
{
    vector<string> zipList;
    OrderedSet<string> invalidSet;
    string sIn;
    while(cin >> sIn)
    {
        if(_checkZip(sIn) == false)
        {
            invalidSet.push_back(sIn);
            continue;
        }
        zipList.push_back(sIn);
    }
    // Get bundles
    sort(zipList.begin(), zipList.end());
    vector<Bundle> bundle5 = _getBundle(zipList, 5);
    vector<Bundle> bundle3 = _getBundle(zipList, 3);
    vector<Bundle> bundle1 = _getBundle1(zipList);
    sort(bundle5.begin(), bundle5.end());
    sort(bundle3.begin(), bundle3.end());
    sort(bundle1.begin(), bundle1.end());
    //Calc totals
    TotalLetter totalLetter;
    TotalBundle totalBundle;
    _forEach(bundle5.begin(), bundle5.end(), totalLetter);
    _forEach(bundle3.begin(), bundle3.end(), totalLetter);
    _forEach(bundle1.begin(), bundle1.end(), totalLetter);
    _forEach(bundle5.begin(), bundle5.end(), totalBundle);
    _forEach(bundle3.begin(), bundle3.end(), totalBundle);
    _forEach(bundle1.begin(), bundle1.end(), totalBundle);
    // Print
    printf("ZIP         LETTERS     BUNDLES\n\n");
    for(int i = 0; i < bundle5.size(); ++i)
    {
        printf("%s %10ld  %10ld\n", bundle5[i].sZip.c_str(), bundle5[i].iLetter, bundle5[i].iBundle);
    }
    puts("");
    for(int i = 0; i < bundle3.size(); ++i)
    {
        printf("%s %10ld  %10ld\n", bundle3[i].sZip.c_str(), bundle3[i].iLetter, bundle3[i].iBundle);
    }
    puts("");
    for(int i = 0; i < bundle1.size(); ++i)
    {
        printf("%s %10ld  %10ld\n", bundle1[i].sZip.c_str(), bundle1[i].iLetter, bundle1[i].iBundle);
    }
    puts("");
    printf("TOTALS%10ld  %10ld\n", totalLetter.iTotal, totalBundle.iTotal);
    puts("");
    puts("INVALID ZIP CODES");
    for(int i = 0; i < invalidSet.size(); ++i)
    {
        printf("%s\n", invalidSet[i].c_str());
    }

    return 0;
}

/********************************************************************
 * 648 - Stamps (II), OVa Online Judge
 * http://uva.onlinejudge.org/external/6/648.html
 ********************************************************************/
#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdio>
using namespace std;

class Dfs
{
public:
    explicit Dfs(const vector<int>& vStamp) :
        m_vStamp(vStamp),
        m_vFound(4, 0),
        m_Rlt(),
        m_bTie(false),
        m_bFound(false)
    {}
    void search(int val, int depth, int stampIdx)
    {
        if(0 == val)
        {
            m_bFound = true;
            Combination c;
            _setCombination(c, m_vFound, depth);
            if(c == m_Rlt)
            {
                m_bTie = true;
            }
            else
            {
                if(m_Rlt < c)
                {
                    m_bTie = false;
                    m_Rlt = c;
//print(0);
                }
            }
            return;
        }
        if(depth == 4)
        {
            return;
        }

        for(int i = stampIdx; i < m_vStamp.size(); ++i)
        {
            if(m_vStamp[i] > val)
            {
                continue;
            }
            m_vFound[depth] = i;
            search(val - m_vStamp[i], depth + 1, i);
        }
    }
    void print(int val) const
    {
        if(false == m_bFound)
        {
            printf("%ld ---- none\n", val);
            return;
        }

        printf("%ld (%ld):", val, m_Rlt.numType);
        if(true == m_bTie)
        {
            printf(" tie\n");
            return;
        }

        vector<int> vStamp;
        for(int i = 0; i < m_Rlt.num; ++i)
        {
            vStamp.push_back(m_vStamp[m_Rlt.soln[i]]);
        }
        sort(vStamp.begin(), vStamp.end());
        for(int i = 0; i < vStamp.size(); ++i)
        {
            printf(" %ld", vStamp[i]);
        }
        puts("");
    }

private:
    typedef vector<int> Solution;
    struct Combination
    {
        Solution soln;
        int numType;
        int num;
        int stampMax;

        Combination() :
            soln(),
            numType(0),
            num(0),
            stampMax(0)
        {}
        bool operator<(const Combination& rhs) const
        {
            if(numType < rhs.numType)
            {
                return true;
            }
            if((numType == rhs.numType) && (num > rhs.num))
            {
                return true;
            }
            if((numType == rhs.numType) && (num == rhs.num) && (stampMax < rhs.stampMax))
            {
                return true;
            }
            return false;
        }
        bool operator==(const Combination& rhs) const
        {
            return ((numType == rhs.numType) && (num == rhs.num) && (stampMax == rhs.stampMax));
        }
    };

    const vector<int>& m_vStamp;
    Solution m_vFound;
    Combination m_Rlt;
    bool m_bTie;
    bool m_bFound;

    void _setCombination(Combination& c, const Solution& s, int n)
    {
        c.soln = s;
        c.num = n;
        vector<int> vType;
        for(int i = 0; i < c.num; ++i)
        {
            if(find(vType.begin(), vType.end(), c.soln[i]) == vType.end())
            {
                vType.push_back(c.soln[i]);
            }
            if(m_vStamp[c.soln[i]] > c.stampMax)
            {
                c.stampMax = m_vStamp[c.soln[i]];
            }
        }
        c.numType = vType.size();
    }
};

int main()
{
    int iStamp = 0;
    while(cin >> iStamp)
    {
        // Input stamps
        vector<int> vStamp;
        while(iStamp > 0)
        {
            vStamp.push_back(iStamp);
            cin >> iStamp;
        }
        // Input customers
        vector<int> vCus;
        int iCus = 0;
        cin >> iCus;
        while(iCus > 0)
        {
            vCus.push_back(iCus);
            cin >> iCus;
        }
        for(int i = 0; i < vCus.size(); ++i)
        {
            Dfs d(vStamp);
            d.search(vCus[i], 0, 0);
            d.print(vCus[i]);
        }
    }
    return 0;
}


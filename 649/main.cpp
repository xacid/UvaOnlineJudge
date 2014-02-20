/********************************************************************
 * 649 - You Who?, OVa Online Judge
 * http://uva.onlinejudge.org/external/6/649.html
 ********************************************************************/
#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdio>
using namespace std;

int s_iCalcTimeCount = 0;

class Graph
{
public:
    typedef vector<bool> Point;

    Graph(int n, bool hasEdge) :
        m_vEdge(n, Point(n, hasEdge)),
        m_iSize(n),
        m_vAsgn(n, false),
        m_iMin(n)
    {}
    Point& operator[](int idx)
    {
        return m_vEdge[idx];
    }
    void search(int depth, vector<bool>& vAsgn, int iNumAsgn)
    {
#if 0
        int iT1 = _calcTime(vAsgn, true);
        if(iT1 > m_iMin)
        {
            return;
        }
#endif
        if(((iNumAsgn + m_iSize - depth) < (m_iSize / 2)) ||
            (iNumAsgn > (m_iSize / 2)))
        {
            return;
        }
        if(m_iSize == depth)
        {
            int iT1 = _calcTime(vAsgn, true);
            int iT2 = _calcTime(vAsgn, false);
            if(max(iT1, iT2) < m_iMin)
            {
                m_vAsgn = vAsgn;
                m_iMin = max(iT1, iT2);
            }
            return;
        }

        vAsgn[depth] = true;
        search(depth + 1, vAsgn, iNumAsgn + 1);
        vAsgn[depth] = false;
        search(depth + 1, vAsgn, iNumAsgn);
    }
    void search2()
    {
        // Assign first half
        vector<bool> vAsgn(m_iSize, false);
        for(int i = 0; i < m_iSize / 2; ++i)
        {
            vAsgn[i] = true;
        }
        _checkMin(vAsgn);
        // Swap to find min
        while(true)
        {
            bool bFound = false;
            for(int iT = 0; iT < m_iSize; ++iT)
            {
                if(true != vAsgn[iT])
                {
                    continue;
                }
                for(int iF = 0; iF < m_iSize; ++iF)
                {
                    if(false != vAsgn[iF])
                    {
                        continue;
                    }
                    vAsgn[iT] = false;
                    vAsgn[iF] = true;
                    if(_checkMin(vAsgn) == true)
                    {
                        bFound = true;
                    }
                    vAsgn[iT] = true;
                    vAsgn[iF] = false;
                }
            }
            if(false == bFound)
            {
                break;
            }
        }
    }
    void print() const
    {
        printf("%ld\n", m_iMin);
        printf("%ld", m_iSize / 2);
        for(int i = 0; i < m_iSize; ++i)
        {
            if(true == m_vAsgn[i])
            {
                printf(" %ld", i + 1);
            }
        }
        printf("\n%ld", m_iSize - (m_iSize / 2));
        for(int i = 0; i < m_iSize; ++i)
        {
            if(false == m_vAsgn[i])
            {
                printf(" %ld", i + 1);
            }
        }
        puts("");
//printf("s_iCalcTimeCount %ld\n", s_iCalcTimeCount);
    }

private:
    typedef vector<int> ConnectedVertice;

    vector<Point> m_vEdge;
    int m_iSize;
    vector<bool> m_vAsgn;
    int m_iMin;

    bool _checkMin(const vector<bool>& asgn)
    {
        int iT1 = _calcTime(asgn, true);
        int iT2 = _calcTime(asgn, false);
        if(max(iT1, iT2) < m_iMin)
        {
            m_vAsgn = asgn;
            m_iMin = max(iT1, iT2);
            return true;
        }
        return false;
    }

    int _calcTime(const vector<bool>& asgn, const bool val) const
    {
        // Find all connected in inverse graph
        ConnectedVertice cAllVertice;
        for(int i = 0; i < m_iSize; ++i)
        {
            if(val == asgn[i])
            {
                cAllVertice.push_back(i);
            }
        }
        vector<ConnectedVertice> vCon;
        while(cAllVertice.size() > 0)
        {
            ConnectedVertice c;
            c.push_back(cAllVertice[0]);
            cAllVertice.erase(cAllVertice.begin());
            int iCon = 0;
            while(iCon < c.size())
            {
                int iChk = 0;
                while(iChk < cAllVertice.size())
                {
                    if(true == m_vEdge[c[iCon]][cAllVertice[iChk]])
                    {
                        ++iChk;
                        continue;
                    }
                    c.push_back(cAllVertice[iChk]);
                    cAllVertice.erase(cAllVertice.begin() + iChk);
                }
                ++iCon;
            }
            vCon.push_back(c);
        }
        // Find the max time for each connected graph
        int iMax = 0;
        for(int i = 0; i < vCon.size(); ++i)
        {
            int iTime = _calcTimeConnect(vCon[i]);
            if(iTime > iMax)
            {
                iMax = iTime;
            }
        }
        return iMax;
    }
    int _calcTimeConnect(const ConnectedVertice& vCon) const
    {
        if(vCon.size() < 2)
        {
            return 0;
        }
        // Find max degree and edge count
        int iMaxDeg = 0;
        int iEdgeCnt = 0;
        for(int i = 0; i < vCon.size(); ++i)
        {
            int iDeg = 0;
            for(int j = i + 1; j < vCon.size(); ++j)
            {
                if(false == m_vEdge[vCon[i]][vCon[j]])
                {
                    ++iEdgeCnt;
                }
            }
            for(int j = 0; j < vCon.size(); ++j)
            {
                if((i != j) && (false == m_vEdge[vCon[i]][vCon[j]]))
                {
                    ++iDeg;
                }
            }
            if(iDeg > iMaxDeg)
            {
                iMaxDeg = iDeg;
            }
        }
        int iAddNum = vCon.size() / 2;
        return max(iMaxDeg, (iEdgeCnt + iAddNum - 1) / iAddNum);
    }
};

int main()
{
    int iNum = 0;
    int iCount = 0;
    while(cin >> iNum)
    {
        Graph graph(iNum, false);
        for(int i = 0; i < iNum; ++i)
        {
            int a = 0, b = 0;
            int numFnd = 0;
            cin >> a >> numFnd;
            for(int j = 0; j < numFnd; ++j)
            {
                cin >> b;
                graph[a - 1][b - 1] = true;
            }
        }
s_iCalcTimeCount = 0;
        vector<bool> vAsgn(iNum, false);
        //graph.search(0, vAsgn, 0);
        graph.search2();

        if(iCount > 0)
        {
            puts("");
        }
        graph.print();
        ++iCount;
    }
    return 0;
}

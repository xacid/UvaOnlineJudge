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
    void print() const
    {
        printf("%ld\n", m_iMin);
        printf("1");
        for(int i = 0; i < m_iSize; ++i)
        {
            if(true == m_vAsgn[i])
            {
                printf(" %ld", i + 1);
            }
        }
        puts("");
        printf("2");
        for(int i = 0; i < m_iSize; ++i)
        {
            if(false == m_vAsgn[i])
            {
                printf(" %ld", i + 1);
            }
        }
        puts("");
printf("s_iCalcTimeCount %ld\n", s_iCalcTimeCount);
    }

private:
    vector<Point> m_vEdge;
    int m_iSize;
    vector<bool> m_vAsgn;
    int m_iMin;

    int _calcTime(const vector<bool>& asgn, const bool val)
    {
#if 0
++s_iCalcTimeCount;
return 0;
#endif
        int iMinDegree = m_iSize;
        int iNumPerson = _getNumPerson(asgn, val);
        if(iNumPerson < 2)
        {
            return 0;
        }
        int iNeedEdge = 0;
        for(int i = 0; i < m_iSize; ++i)
        {
            if(val != asgn[i])
            {
                continue;
            }

            int iDeg = 0;
            for(int j = 0; j < m_iSize; ++j)
            {
                if(val != asgn[j])
                {
                    continue;
                }
                if(m_vEdge[i][j])
                {
                    ++iDeg;
                }
                else if(i < j)
                {
                    ++iNeedEdge;
                }
            }
            if(iDeg < iMinDegree)
            {
                iMinDegree = iDeg;
            }
        }
        int addEdegNum = iNumPerson / 2;
        return max(iNumPerson - iMinDegree - 1, (iNeedEdge + addEdegNum - 1) / addEdegNum);
    }
    int _getNumPerson(const vector<bool>& asgn, const bool val)
    {
        int iRet = 0;
        for(int i = 0; i < m_iSize; ++i)
        {
            if(val == asgn[i])
            {
                ++iRet;
            }
        }
        return iRet;
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
        graph.search(0, vAsgn, 0);

        if(iCount > 0)
        {
            puts("");
        }
        graph.print();
        ++iCount;
    }
    return 0;
}

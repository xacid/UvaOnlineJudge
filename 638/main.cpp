#include <iostream>
#include <map>
#include <vector>
#include <algorithm>
#include <string>
#include <cstring>
#include <cstdio>
#include <cassert>

using namespace std;

struct Point
{
    char c;
    int x;
    int y;
};

struct Rect
{
    string sAbcd;
    Rect(const Point* a, const Point* b, const Point* c, const Point* d) :
        sAbcd(5, '\0')
    {
        sAbcd[0] = a->c;
        sAbcd[1] = b->c;
        sAbcd[2] = c->c;
        sAbcd[3] = d->c;
    }

    struct CompareStr
    {
        bool operator()(const Rect& l, const Rect& r)
        {
            return l.sAbcd < r.sAbcd;
        }
    };
};

class Line
{
public:
    typedef typename vector<Point*>::iterator iterator;

    explicit Line(int iSize) :
        m_vPoint(iSize, NULL)
    {
    }
    Point*& operator[](int n)
    {
        assert(n < m_vPoint.size());
        return m_vPoint[n];
    }
    iterator begin()
    {
        iterator begin = m_vPoint.begin();
        if(*begin == NULL)
        {
            begin = getNext(begin);
        }
        return begin;
    }
    iterator end()
    {
        return m_vPoint.end();
    }
    iterator getNext(iterator itr)
    {
        while(itr != m_vPoint.end())
        {
            ++itr;
            if((itr != m_vPoint.end()) && (*itr != NULL))
            {
                break;
            }
        }
        return itr;
    }
    iterator getNext(const Point* p)
    {
        int i = 0;
        for(i = 0; i < m_vPoint.size(); ++i)
        {
            if(p == m_vPoint[i])
            {
                break;
            }
        }
        return getNext(m_vPoint.begin() + i);
    }
    bool empty() const
    {
        for(int i = 0; i < m_vPoint.size(); ++i)
        {
            if(m_vPoint[i] != NULL)
            {
                return false;
            }
        }
        return true;
    }

private:
    vector<Point*> m_vPoint;
};

class PointMap
{
public:
    typedef typename vector<Line>::iterator iterator;

    PointMap(int iSizeA, int iSizeB) :
        m_vLine(iSizeA, Line(iSizeB))
    {
    }
    Line& operator[](int n)
    {
        assert(n < m_vLine.size());
        return m_vLine[n];
    }
    iterator begin()
    {
        iterator begin = m_vLine.begin();
        if(begin->empty())
        {
            begin = getNext(begin);
        }
        return begin;
    }
    iterator end()
    {
        return m_vLine.end();
    }
    iterator getNext(iterator itr)
    {
        while(itr != m_vLine.end())
        {
            ++itr;
            if((itr != m_vLine.end()) && (itr->empty() == false))
            {
                break;
            }
        }
        return itr;
    }

private:
    vector<Line> m_vLine;
};

void _calcRects(vector<Point>& p)
{
    // Sort input in row and col.
    PointMap row(51, 51);
    PointMap col(51, 51);
    for(int i = 0; i < p.size(); ++i)
    {
        row[p[i].y][p[i].x] = &p[i];
        col[p[i].x][p[i].y] = &p[i];
    }
    // Find rect for each point
    vector<Rect> ans;
    for(PointMap::iterator itr = row.begin(); itr < row.end(); itr = row.getNext(itr))
    {
        Line& lineY = *itr;
        for(Line::iterator itrP = lineY.begin(); itrP < lineY.end(); itrP = lineY.getNext(itrP))
        {
            Point* p4 = *itrP;
            Line& lineX = col[p4->x];
            for(Line::iterator pp3 = lineY.getNext(p4); pp3 < lineY.end(); pp3 = lineY.getNext(pp3))
            {
                for(Line::iterator pp1 = lineX.getNext(p4); pp1 < lineX.end(); pp1 = lineY.getNext(pp1))
                {
                    if(row[(*pp1)->y][(*pp3)->x] != NULL)
                    {
                        //Found rect.
                        Point* p2 = row[(*pp1)->y][(*pp3)->x];
                        ans.push_back(Rect(*pp1, p2, *pp3, p4));
                    }
                }
            }
        }
    }
    //Sort ans
    sort(ans.begin(), ans.end(), Rect::CompareStr());
    // Print, no ans
    if(ans.size() == 0)
    {
        printf(" No rectangles\n");
        return;
    }
    // Print ans
    for(int i = 0; i < ans.size(); ++i)
    {
        if((i % 10) == 0)
        {
            puts("");
        }
        printf(" %s", ans[i].sAbcd.c_str());
    }
    puts("");
}

int main()
{
    int iNumPoint = 0;
    int iSetCount = 1;
    cin >> iNumPoint;
    while(0 < iNumPoint)
    {
        // Get points
        vector<Point> vP(iNumPoint);
        for(int i = 0; i < iNumPoint; ++i)
        {
            cin >> vP[i].c >> vP[i].x >> vP[i].y;
        }
        // Print
        printf("Point set %ld:", iSetCount);
        _calcRects(vP);
        // Next set
        ++iSetCount;
        cin >> iNumPoint;
    }
    return 0;
}

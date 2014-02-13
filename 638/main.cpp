#include <iostream>
#include <map>
#include <vector>
#include <algorithm>
#include <string>
#include <cstring>
#include <cstdio>

using namespace std;

struct Point
{
    char c;
    int x;
    int y;
    int ix, iy;

    struct CompareX
    {
        bool operator()(const Point* l, const Point* r)
        {
            return (l->x) < (r->x);
        }
    };

    struct CompareY
    {
        bool operator()(const Point* l, const Point* r)
        {
            return (l->y) < (r->y);
        }
    };
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

void _calcRects(vector<Point>& p)
{
    // Sort input in row and col.
    typedef map<int, vector<Point*> > PointMap;
    PointMap row, col;
    for(int i = 0; i < p.size(); ++i)
    {
        row[p[i].y].push_back(&p[i]);
        col[p[i].x].push_back(&p[i]);
    }
    for(PointMap::iterator itr = row.begin(); itr != row.end(); ++itr)
    {
        sort(itr->second.begin(), itr->second.end(), Point::CompareX());
        for(int i = 0; i < itr->second.size(); ++i)
        {
            itr->second[i]->ix = i;
        }
    }
    for(PointMap::iterator itr = col.begin(); itr != col.end(); ++itr)
    {
        sort(itr->second.begin(), itr->second.end(), Point::CompareY());
        for(int i = 0; i < itr->second.size(); ++i)
        {
            itr->second[i]->iy = i;
        }
    }
    // Find rect for each point
    vector<Rect> ans;
    for(PointMap::iterator itr = row.begin(); itr != row.end(); ++itr)
    {
        vector<Point*>& vRow = itr->second;
        for(int i = 0; i < vRow.size(); ++i)
        {
            Point* p4 = vRow[i];
            vector<Point*>& vCol = col[p4->x];
            for(int j = p4->ix + 1; j < vRow.size(); ++j)
            {
                Point* p3 = vRow[j];
                for(int k = p4->iy + 1; k < vCol.size(); ++k)
                {
                    Point* p1 = vCol[k];
                    if((row.find(p1->y) != row.end()) && (col.find(p3->x) != col.end()))
                    {
                        //Found rect.
                        for(int ip = 0; ip < row[p1->y].size(); ++ip)
                        {
                            if(row[p1->y][ip]->x == p3->x)
                            {
                                Point* p2 = row[p1->y][ip];
                                ans.push_back(Rect(p1, p2, p3, p4));
                            }
                        }
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

#include <string>
#include <vector>
#include <algorithm>
#include <cstdio>
using namespace std;

typedef vector<int> Table;

void _printTable(const Table& t)
{
    for(int i = 0; i < t.size(); ++i)
    {
        printf("%c", t[i] + 'A');
    }
}

void _printDay(const vector<Table>& d)
{
    for(int i = 0; i < d.size(); ++i)
    {
        _printTable(d[i]);
        fputs("\t", stdout);
    }
    puts("");
}

class Graph
{
public:
    Graph() :
        m_bHasEdge(16, vector<bool>(16, false))
    {}
    bool generate(vector< vector<Table> >& sched, int day, int tab, int per, vector<bool>& vAssign, int asn)
    {
        if(5 == day)
        {
_printDay(sched[0]);
_printDay(sched[1]);
_printDay(sched[2]);
_printDay(sched[3]);
_printDay(sched[4]);
puts("");
            return false;
        }
//printf("d %ld t %ld per %ld a %ld\n", day, tab, per, asn);
if(4 == day)
{
    //return true;
}
        vector<bool> origAssign(vAssign);
        int iAssign = 0;
        if(0 != per)
        {
            iAssign = asn + 1;
        }
        if((0 == tab) && (0 == per))
        {
            vAssign = vector<bool>(16, false);
        }
        for(int i = iAssign; i < 16; ++i)
        {
            if(true == vAssign[i])
            {
                continue;
            }
            if(_addEdge(sched[day][tab], per, i) == false)
            {
                continue;
            }
            sched[day][tab][per] = i;
            // Iterate
            int newPer = per + 1;
            int newTab = tab;
            int newDay = day;
            if(4 == newPer)
            {
                newPer = 0;
                newTab += 1;
            }
            if(4 == newTab)
            {
                newTab = 0;
                newDay += 1;
            }
            // Find next person ercursively
            vAssign[i] = true;
            if(generate(sched, newDay, newTab, newPer, vAssign, i))
            {
                return true;
            }
            _removeEdge(sched[day][tab], per, i);
            vAssign[i] = false;
        }
        vAssign = origAssign;
        return false;
    }

private:
    vector< vector<bool> > m_bHasEdge;

    bool _addEdge(const Table& tab, int numPer, int per)
    {
        for(int i = 0; i < numPer; ++i)
        {
            if(_getEdge(tab[i], per))
            {
                return false;
            }
        }
        for(int i = 0; i < numPer; ++i)
        {
            _setEdge(tab[i], per, true);
        }
        return true;
    }
    bool _removeEdge(const Table& tab, int numPer, int per)
    {
        for(int i = 0; i < numPer; ++i)
        {
            _setEdge(tab[i], per, false);
        }
        return true;
    }
    bool _getEdge(int a, int b)
    {
        return m_bHasEdge[min(a, b)][max(a, b)];
    }
    void _setEdge(int a, int b, bool val)
    {
        m_bHasEdge[min(a, b)][max(a, b)] = val;
    }
};

int main()
{
    vector< vector<Table> > sched(5, vector<Table>(4, Table(4, 0)));
    vector<bool> vAssign(16, false);
    Graph g;
    g.generate(sched, 0, 0, 0, vAssign, 0);
printf("DONE\n");
    return 0;
}

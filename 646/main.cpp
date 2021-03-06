/********************************************************************
 * 646 - The Gourmet Club, OVa Online Judge
 * http://uva.onlinejudge.org/external/6/646.html
 * Remark:
 * 1. "Echo the input" must be exactly the same. Use getline().
 * 2. The input is always valid, no any pair of person eat twice.
 ********************************************************************/

#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <cassert>
#include <cstdio>

using namespace std;

typedef vector< vector<bool> >      Graph;
typedef vector<int>                 Table;
typedef vector< vector<Table> >     Schedule;

void _printTable(const Table& table)
{
    for(int i = 0; i < table.size(); ++i)
    {
        printf("%c", table[i] + 'A');
    }
}

bool _setAllEdge(Graph& graph, const Table& tab, int numPer, int per, const bool val)
{
    for(int i = 0; i < numPer; ++i)
    {
        if(val == graph[tab[i]][per])
        {
            return false;
        }
    }
    for(int i = 0; i < numPer; ++i)
    {
        graph[tab[i]][per] = val;
    }
    return true;
}

bool _make(Graph& graph, Schedule& sched, vector<bool>& vAssign, int iD, int iT, int iE, int iA)
{
    if(5 == iD)
    {
        return true;
    }

    vector<bool> origAssign(vAssign);
    if(0 == iE)
    {
        iA = 0;
    }
    if((0 == iT) && (0 == iE))
    {
        vAssign = vector<bool>(16, false);
    }
    for(int i = iA; i < vAssign.size(); ++i)
    {
        if(vAssign[i] ||
            (_setAllEdge(graph, sched[iD][iT], iE, i, true) == false))
        {
            continue;
        }
        sched[iD][iT][iE] = i;

        int nE = iE + 1;
        int nT = iT;
        int nD = iD;
        if(4 == nE)
        {
            nE = 0;
            nT += 1;
        }
        if(4 == nT)
        {
            nT = 0;
            nD += 1;
        }
        vAssign[i] = true;
        if(_make(graph, sched, vAssign, nD, nT, nE, i))
        {
            return true;
        }
        _setAllEdge(graph, sched[iD][iT], iE, i, false);
        vAssign[i] = false;
    }

    vAssign = origAssign;
    return false;
}

int main()
{
    int idx = 0;
    string sIn;
    char buf[80];
    while(cin.getline(buf, 80))
    {
        // Input
        vector<string> vEcho;
        vEcho.push_back(string(buf));
        for(int i = 1; i < 3; ++i)
        {
            cin.getline(buf, 80);
            vEcho.push_back(string(buf));
        }
        cin.getline(buf, 80);
        // Reformat
        vector<string> vIn;
        for(int i = 0; i < 3; ++i)
        {
            stringstream ss;
            ss.str(vEcho[i]);
            for(int j = 0; j < 4; ++j)
            {
                string s;
                ss >> s;
                vIn.push_back(s);
            }
        }
        Graph graph(16, vector<bool>(16, false));
        Schedule sched(5, vector<Table>(4, Table(4, 0)));
        bool bInputError = false;
        for(int i = 0; i < 12; ++i)
        {
            vector<int> vertice(4, 0);
            for(int j = 0; j < vIn[i].size(); ++j)
            {
                sched[i / 4][i % 4][j] = vIn[i][j] - 'A';
                if(_setAllEdge(graph, sched[i / 4][i % 4], j, vIn[i][j] - 'A', true) == false)
                {
                    bInputError = true;
                }
            }
        }
        // Print
        if(idx > 0)
        {
            puts("");
        }
        vector<bool> vAssigned(16, false);
        if((true == bInputError) ||
            (_make(graph, sched, vAssigned, 3, 0, 0, 0) == false))
        {
            puts("It is not possible to complete this schedule.");
        }
        else
        {
            for(int i = 0; i < 3; ++i)
            {
                puts(vEcho[i].c_str());
            }
            for(int i = 3; i < 5; ++i)
            {
                for(int j = 0; j < 4; ++j)
                {
                    if(j > 0)
                    {
                        fputs("\t", stdout);
                    }
                    _printTable(sched[i][j]);
                }
                puts("");
            }
        }
        ++idx;
    }
    return 0;
}

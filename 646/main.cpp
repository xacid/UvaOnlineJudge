#include <iostream>
#include <string>
#include <vector>
#include <cassert>
#include <cstdio>

using namespace std;

void _printTable(const vector<int>& table)
{
    for(int i = 0; i < table.size(); ++i)
    {
        printf("%c", table[i] + 'A');
    }
}

bool _removeEdge(vector< vector<bool> >& graph, const vector<int>& v4)
{
    for(int i = 0; i < 4; ++i)
    {
        for(int j = i + 1; j < 4; ++j)
        {
            int a = v4[i];
            int b = v4[j];
            if(false == graph[a][b])
            {
printf("remove %c%c fail\n", a + 'A', b + 'A');
                return false;
            }
            graph[a][b] = false;
            graph[b][a] = false;
        }
    }
    return true;
}

bool _checkAllK4(const vector< vector<bool> >& graph, vector< vector<int> >& d5)
{
    vector< vector<bool> > newGraph(graph);
    for(int i = 0; i < 16; ++i)
    {
        vector<int> k4;
        k4.push_back(i);
        for(int j = i + 1; j < 16; ++j)
        {
            if(newGraph[i][j] == true)
            {
                k4.push_back(j);
            }
        }
        if((k4.size() == 4) && (_removeEdge(newGraph, k4) == true))
        {
            d5.push_back(k4);
_printTable(k4);
printf("\t");
        }
    }
puts("");
    if(d5.size() == 4)
    {
        return true;
    }
    return false;
}

int _getFirstV(const vector< vector<int> >& d, int iTable)
{
    vector<bool> used(16, false);
    for(int i = 0; i < iTable; ++i)
    {
        for(int j = 0; j < 4; ++j)
        {
            used[d[i][j]] = true;
        }
    }
    for(int i = 0; i < 16; ++i)
    {
        if(false == used[i])
        {
            return i;
        }
    }

    assert(0);
    return 0;
}

bool _make(vector< vector<bool> >& graph, vector< vector<int> >& d4, int iTable)
{
printf("%s, %d\n", __FILE__, __LINE__);
    if(iTable == 4)
    {
        vector< vector<int> > dummy;
        if(_checkAllK4(graph, dummy) == true)
        {
            return true;
        }
        return false;
    }

    vector< vector<bool> > origGraph(graph);
    vector<int>& k4 = d4[iTable];
    k4[0] = _getFirstV(d4, iTable);
    for(int i = k4[0] + 1; i < 16; ++i)
    {
        if(origGraph[k4[0]][i] == false)
        {
            continue;
        }
        for(int j = i + 1; j < 16; ++j)
        {
            if(origGraph[k4[0]][j] == false)
            {
                continue;
            }
            for(int k = j + 1; k < 16; ++k)
            {
                if(origGraph[k4[0]][k] == false)
                {
                    continue;
                }
                k4[1] = i;
                k4[2] = j;
                k4[3] = k;
_printTable(k4); printf("\n");
                graph = origGraph;
                if(_removeEdge(graph, k4) &&_make(graph, d4, iTable + 1))
                {
                    return true;
                }
            }
        }
    }
    return false;
}

int main()
{
    int idx = 0;
    string sIn;
    while(cin >> sIn)
    {
        // Input
        vector<string> vIn(12, string(4, 'A'));
        vIn[0] = sIn;
        for(int i = 1; i < 12; ++i)
        {
            cin >> vIn[i];
        }
        vector< vector<bool> > graph(16, vector<bool>(16, true));
        for(int i = 0; i < 12; ++i)
        {
            vector<int> vertice(4, 0);
            for(int j = 0; j < vIn[i].size(); ++j)
            {
                vertice[j] = vIn[i][j] - 'A';
            }
            _removeEdge(graph, vertice);
        }
        // Print
        if(idx > 0)
        {
            puts("");
        }
        vector< vector<int> > d4(4, vector<int>(4, 0));
        if(_make(graph, d4, 0) == false)
        {
            puts("It is not possible to complete this schedule.");
        }
        else
        {
            vector< vector<int> > d5;
            _checkAllK4(graph, d5);
            puts("Impossible?");
        }
        ++idx;
    }
    return 0;
}

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
//printf("remove %c%c fail\n", a + 'A', b + 'A');
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
//_printTable(k4);
//printf("\t");
        }
    }
//puts("");
    if(d5.size() == 4)
    {
        return true;
    }
    return false;
}

bool _noEdge(const vector< vector<bool> >& graph, const vector<int>& v, int end, int p)
{
    for(int i = 0; i < end; ++i)
    {
        if(false == graph[v[i]][p])
        {
            return true;
        }
    }
    return false;
}

bool _make(const vector< vector<bool> >& graph, vector< vector<int> >& d4, vector<bool>& vAssigned, int iT, int iE, int iA)
{
    if(iT == 4)
    {
        vector< vector<int> > dummy;
        if(_checkAllK4(graph, dummy) == true)
        {
            return true;
        }
        return false;
    }

    for(int i = iA; i < vAssigned.size(); ++i)
    {
        if(false == vAssigned[i])
        {
            if(_noEdge(graph, d4[iT], iE, i))
            {
                continue;
            }

            vAssigned[i] = true;
            d4[iT][iE] = i;
            if(3 == iE)
            {
                if(_make(graph, d4, vAssigned, iT + 1, 0, 0))
                {
                    return true;
                }
            }
            else
            {
                if(_make(graph, d4, vAssigned, iT, iE + 1, i + 1))
                {
                    return true;
                }
            }

            vAssigned[i] = false;
            if(0 == iE)
            {
                break;
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
        vector<bool> vAssigned(16, false);
        if(_make(graph, d4, vAssigned, 0, 0, 0) == false)
        {
            puts("It is not possible to complete this schedule.");
        }
        else
        {
            vector< vector<int> > d5;
            _checkAllK4(graph, d5);
            for(int i = 0; i < 12; ++i)
            {
                printf("%s", vIn[i].c_str());
                if(i % 4 == 3)
                {
                    puts("\n");
                }
                else
                {
                    printf("\t");
                }
            }
            for(int i = 0; i < 4; ++i)
            {
                if(i > 0)
                {
                    printf("\t");
                }
                _printTable(d4[i]);
            }
            for(int i = 0; i < 4; ++i)
            {
                if(i > 0)
                {
                    printf("\t");
                }
                _printTable(d5[i]);
            }
        }
        ++idx;
    }
    return 0;
}

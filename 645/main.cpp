#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cstdio>
using namespace std;

void _indent(const int num)
{
    for(int i = 0; i < num; ++i)
    {
        fputs("|     ", stdout);
    }
}

void _parseDir(const int depth, const string& sFirst)
{
    vector<string> vFiles;
    char cEnd = '*';
    string sIn;
    if(depth == 0)
    {
        sIn = sFirst;
    }
    else //if(depth != 0)
    {
        cEnd = ']';
        cin >> sIn;
    }

    while(cEnd != sIn[0])
    {
        if('f' == sIn[0])
        {
            vFiles.push_back(sIn);
        }
        if('d' == sIn[0])
        {
            _indent(depth + 1);
            printf("%s\n", sIn.c_str());
            _parseDir(depth + 1, "");
        }
        cin >> sIn;
    }
    sort(vFiles.begin(), vFiles.end());
    for(int i = 0; i < vFiles.size(); ++i)
    {
        _indent(depth);
        printf("%s\n", vFiles[i].c_str());
    }
}

int main()
{
    int idx = 1;
    string sIn;
    cin >> sIn;
    while(sIn[0] != '#')
    {
        if(1 != idx)
        {
            puts("");
        }
        printf("DATA SET %ld:\n", idx);
        printf("ROOT\n");
        _parseDir(0, sIn);
        ++idx;
        cin >> sIn;
    }
    return 0;
}

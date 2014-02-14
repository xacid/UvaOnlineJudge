#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <cstdio>
using namespace std;

struct DictChecker
{
    map< string, int >& dict;
    vector<string> ans;

    DictChecker(map< string, int >& d) :
        dict(d),
        ans()
    {}
    void operator()(const string& s)
    {
//printf("check %s\n", s.c_str());
        if(dict.find(s) != dict.end())
        {
            ans.push_back(s);
        }
    }
};

static const string INPUT_SEP("XXXXXX");

template<class T>
void _forEachPerMute(string& s, int idx, T& checker)
{
//printf("_forEachPerMute %s %ld\n", s.c_str(), idx);
    if(idx == s.size() - 1)
    {
        checker(s);
        return;
    }

    string sOrig(s);
    for(int i = idx; i < sOrig.size(); ++i)
    {
        string sWork(sOrig);
        swap(sWork[idx], sWork[i]);
        _forEachPerMute(sWork, idx + 1, checker);
    }
}

void _printValid(map< string, int >& dict, string& s)
{

    DictChecker c(dict);
    _forEachPerMute(s, 0, c);
    sort(c.ans.begin(), c.ans.end());
    for(int i = 0; i < c.ans.size(); i++)
    {
        if((i > 0) && (c.ans[i] == c.ans[i-1]))
        {
            continue;
        }
        printf("%s\n", c.ans[i].c_str());
    }
    if(c.ans.empty())
    {
        printf("NOT A VALID WORD\n");
    }
}

int main()
{
    // Build dict
    map< string, int > dict;
    string sWord;
    cin >> sWord;
    while(sWord != INPUT_SEP)
    {
        dict[sWord] = 1;
        cin >> sWord;
    }
    // Get letters
    string sLetters;
    cin >> sLetters;
    while(sLetters != INPUT_SEP)
    {
        _printValid(dict, sLetters);
        printf("******\n");
        cin >> sLetters;
    }
    return 0;
}

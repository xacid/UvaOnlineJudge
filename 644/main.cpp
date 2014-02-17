#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cstdio>

using namespace std;

bool _compareStringLength(const string& lhs, const string& rhs)
{
    if(lhs.size() == rhs.size())
    {
        return (lhs < rhs);
    }

    return (lhs.size() < rhs.size());
}

bool _isImmediatelyDecodable(vector<string>& code)
{
    sort(code.begin(), code.end(), _compareStringLength);
    for(int i = 1; i < code.size(); ++i)
    {
        for(int j = 0; j < i; ++j)
        {
            if(code[i].substr(0, code[j].size()) == code[j])
            {
                return false;
            }
        }
    }
    return true;
}

int main()
{
    string sIn;
    int idx = 1;
    while(cin >> sIn)
    {
        vector<string> vCode;
        while(sIn[0] != '9')
        {
            vCode.push_back(sIn);
            cin >> sIn;
        }

        if(_isImmediatelyDecodable(vCode))
        {
            printf("Set %ld is immediately decodable\n", idx);
        }
        else
        {
            printf("Set %ld is not immediately decodable\n", idx);
        }

        ++idx;
    }
    return 0;
}

#include <iostream>
#include <string>
#include <vector>
#include <cstdio>
using namespace std;

vector<int> TO_NUM(128, 0);
vector<char> TO_CHAR(28, '0');

string _untwist(string& c, int k)
{
    int len = c.size();
    // Char to num
    for(int i = 0; i < len; ++i)
    {
        c[i] = TO_NUM[c[i]];
    }
    // p[k * i mod len] = (c[i] + i) mod 28
    string ret(len, '0');
    for(int i = 0; i < len; ++i)
    {
        ret[(k * i) % len] = (c[i] + i) % 28;
    }
    // Num to char
    for(int i = 0; i < len; ++i)
    {
        ret[i] = TO_CHAR[ret[i]];
    }
    return ret;
}

int main()
{
    // Build converter.
    TO_NUM['_'] = 0;
    for(int i = 'a'; i <= 'z'; ++i)
    {
        TO_NUM[i] = i - 'a' + 1;
    }
    TO_NUM['.'] = 27;
    TO_CHAR[0] = '_';
    for(int i = 1; i <= 26; ++i)
    {
        TO_CHAR[i] = i + 'a' - 1;
    }
    TO_CHAR[27] = '.';
    // Input
    int iKey = 0;
    cin >> iKey;
    while(iKey > 0)
    {
        string sCipher;
        cin >> sCipher;
        string sPlain = _untwist(sCipher, iKey);
        printf("%s\n", sPlain.c_str());
        cin >> iKey;
    }
    return 0;
}

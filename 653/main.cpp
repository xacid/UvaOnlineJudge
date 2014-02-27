#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdio>
using namespace std;

typedef long long unsigned U64;
typedef vector<U64> Factor;

void _print(const Factor& fact)
{
    for(int i = 0; i < fact.size(); ++i)
    {
        printf("%llu ", fact[i]);
    }
    puts("");
}

bool _factorHas(const Factor& fact, U64 val)
{
    return (find(fact.begin(), fact.end(), val) != fact.end());
}

vector<Factor> _FindFactor(U64 val)
{
    vector<Factor> vRet;
    for(int i = 1; i <= 100; ++i)
    {
        if(val % i != 0)
        {
            continue;
        }
        Factor fact;
        U64 v = val;
        for(int j = i; j <= 100; ++j)
        {
            if(v % j == 0)
            {
                fact.push_back(j);
                v /= j;
            }
        }
        if(1 == v)
        {
            vRet.push_back(fact);
        }
    }
printf("Factor %llu\n", val);
for(int i = 0; i < vRet.size(); ++i) _print(vRet[i]);
    return vRet;
}

Factor _getIntersect(const vector<Factor>& vFact)
{
    Factor fRet;
    if(vFact.empty() == true)
    {
        return fRet;
    }
    for(int i = 0; i < vFact[0].size(); ++i)
    {
        bool bAllExist = true;
        for(int j = 1; j < vFact.size(); ++j)
        {
            if(_factorHas(vFact[j], vFact[0][i]) == false)
            {
                bAllExist = false;
                break;
            }
        }
        if(true == bAllExist)
        {
            fRet.push_back(vFact[0][i]);
        }
    }
    return fRet;
}

int main()
{
    U64 uA = 0, uB = 0;
    while(cin >> uA)
    {
        cin >> uB;
        // Let A be larger one
        if(uA < uB)
        {
            swap(uA, uB);
        }
        // Find factor of B
        vector<Factor> vFactB = _FindFactor(uB);
        if(vFactB.empty() == true)
        {
            printf("%llu\n", uA);
            continue;
        }
        // Find factor of A
        vector<Factor> vFactA = _FindFactor(uA);
        if(vFactA.empty() == true)
        {
            printf("%llu\n", uB);
            continue;
        }
        Factor vB = _getIntersect(vFactB);
        vector<bool> vbPossible(vFactA.size(), true);
        for(int i = 0; i < vB.size(); ++i)
        {
            for(int j = 0; j < vFactA.size(); ++j)
            {
                if(_factorHas(vFactA[j], vB[i]) == true)
                {
                    vbPossible[j] = false;
                }
            }
        }
        bool bIsAPossible = false;
        for(int i = 0; i < vbPossible.size(); ++i)
        {
            if(true == vbPossible[i])
            {
                bIsAPossible = true;
            }
        }
        if(true == bIsAPossible)
        {
            printf("%llu\n", uA);
        }
        else
        {
            printf("%llu\n", uB);
        }
    }
    return 0;
}

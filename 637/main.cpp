#include <iostream>
#include <vector>
#include <cstdio>

using namespace std;

struct Side
{
    int l;
    int r;

    void print(int max) const
    {
        if(l <= max)
        {
            printf("%ld, ", l);
        }
        else
        {
            printf("Blank, ");
        }

        if(r <= max)
        {
            printf("%ld\n", r);
        }
        else
        {
            printf("Blank\n");
        }
    }
};

void _printBook(int n)
{
    printf("Printing order for %ld pages:\n", n);
    int nSheet = (n + 3) / 4;
    vector<Side> book(nSheet * 2);
    for(int i = 0; i < book.size(); i++)
    {
        if((i % 2) == 0)
        {
            book[i].l = nSheet * 4 - i;
            book[i].r = i + 1;
        }
        else
        {
            book[i].l = i + 1;
            book[i].r = nSheet * 4 - i;
        }
    }

    for(int i = 0; i < book.size(); i++)
    {
        if((i % 2) == 0)
        {
            printf("Sheet %ld, front: ", i / 2 + 1);
            book[i].print(n);
            if(1 == n)
            {
                break;
            }
        }
        else
        {
            printf("Sheet %ld, back : ", i / 2 + 1);
            book[i].print(n);
        }
    }
}

int main()
{
    int iNumPage = 0;
    cin >> iNumPage;
    while(iNumPage > 0)
    {
        _printBook(iNumPage);
        cin >> iNumPage;
    }
    return 0;
}

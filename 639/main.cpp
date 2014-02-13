#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdio>

using namespace std;

class Board
{
public:
    explicit Board(int iSize) :
        m_vState(iSize, vector<EN_STATE>(iSize, E_WALL)),
        m_iSize(iSize)
    {}
    int getMax(int x, int y)
    {
        if(_getEmpty(x, y) == false)
        {
            return 0;
        }
        vector< vector<EN_STATE> > vOrig(m_vState);
        // Add Rook
        _addRook(x, y);
        int numRook = getMax(x, y) + 1;
        // No Rook
        m_vState.swap(vOrig);
        int numRook2 = 0;
        if(_getNext(x, y) == true)
        {
            numRook2 = getMax(x, y);
        }

        return max(numRook, numRook2);
    }

    void print()
    {
        for(int i = 0; i < m_iSize; ++i)
        {
            for(int j = 0; j < m_iSize; ++j)
            {
                printf("%ld", m_vState[i][j]);
            }
            puts("");
        }
    }

private:
    enum EN_STATE
    {
        E_WALL,
        E_EMPTY,
        E_ROOK,
        E_ILLEGAL,
    };

    vector< vector<EN_STATE> > m_vState;
    int m_iSize;

    friend istream& operator>>(istream& in, Board& rhs);
    // Get the next position of [x, y].
    // Return false if no next.
    bool _getNext(int& x, int& y) const
    {
        if(x + 1 < m_iSize)
        {
            ++x;
            return true;
        }
        if(y + 1 < m_iSize)
        {
            ++y;
            x = 0;
            return true;
        }

        return false;
    }
    // Get the next empty position, including [x, y].
    // Return false if no next or no empty.
    bool _getEmpty(int& x, int& y) const
    {
        while(E_EMPTY != m_vState[x][y])
        {
            if(_getNext(x, y) == false)
            {
                return false;
            }
        }
        return true;
    }
    void _addRook(int x, int y)
    {
        m_vState[x][y] = E_ROOK;
        int l = x - 1;
        while((l >= 0) && (m_vState[l][y] != E_WALL))
        {
            m_vState[l][y] = E_ILLEGAL;
            --l;
        }
        int r = x + 1;
        while((r < m_iSize) && (m_vState[r][y] != E_WALL))
        {
            m_vState[r][y] = E_ILLEGAL;
            ++r;
        }
        int u = y - 1;
        while((y >= 0) && (m_vState[x][u] != E_WALL))
        {
            m_vState[x][u] = E_ILLEGAL;
            --u;
        }
        int d = y + 1;
        while((d < m_iSize) && (m_vState[x][d] != E_WALL))
        {
            m_vState[x][d] = E_ILLEGAL;
            ++d;
        }
    }
};

istream& operator>>(istream& in, Board& rhs)
{
    for(int i = 0; i < rhs.m_iSize; ++i)
    {
        char buf[10];
        in >> buf;
        for(int j = 0; j < rhs.m_iSize; ++j)
        {
            if('.' == buf[j])
            {
                rhs.m_vState[i][j] = Board::E_EMPTY;
            }
        }
    }
    return in;
}

int main()
{
    int iBoardSize = 0;
    cin >> iBoardSize;
    while(iBoardSize > 0)
    {
        Board b(iBoardSize);
        cin >> b;
        printf("%ld\n", b.getMax(0, 0));
        cin >> iBoardSize;
    }
    return 0;
}

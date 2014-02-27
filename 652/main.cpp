/********************************************************************
 * 652 - Eight, OVa Online Judge
 * http://uva.onlinejudge.org/external/6/652.html
 * Remark:
 * 1. For unsolvable-checking, see
 *    http://mathworld.wolfram.com/15Puzzle.html
 ********************************************************************/
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cstdio>
using namespace std;

template<unsigned int N>
struct Factory
{
    static const unsigned int VALUE = N * Factory<N - 1>::VALUE;
};
template<>
struct Factory<0>
{
    static const unsigned int VALUE = 1;
};

static const unsigned int s_auFact[10] = 
{
    Factory<0>::VALUE,
    Factory<1>::VALUE,
    Factory<2>::VALUE,
    Factory<3>::VALUE,
    Factory<4>::VALUE,
    Factory<5>::VALUE,
    Factory<6>::VALUE,
    Factory<7>::VALUE,
    Factory<8>::VALUE,
    Factory<9>::VALUE
};

template<unsigned int N, class T>
class Permutation
{
public:
    static unsigned int calcIndex(const vector<T>& vSeq)
    {
        unsigned int iRet = 0;
        for(unsigned int i = 0; i < N; ++i)
        {
            iRet += s_auFact[N - i - 1] *
                _getGtCount(vSeq[i], vSeq.begin() + i + 1, vSeq.end());
        }
        return iRet;
    }
private:
    typedef typename vector<T>::const_iterator Iterator;
    static unsigned int _getGtCount(const T& val, Iterator first, Iterator last)
    {
        unsigned int iRet = 0;
        while(first < last)
        {
            if(val > *(first++))
            {
                ++iRet;
            }
        }
        return iRet;
    }
};

class Puzzle
{
public:
    typedef vector< vector< char> > Board;
    explicit Puzzle() :
        m_vEnd(3, vector<char>(3, '0')),
        m_vBoardStep(),
        m_vParent(Factory<9>::VALUE, -1),
        m_vDir(Factory<9>::VALUE, E_DIR_MAX)
    {
        for(int i = 0; i < 3; ++i)
        {
            for(int j = 0; j < 3; ++j)
            {
                m_vEnd[i][j] = i * 3 + j + '1';
            }
        }
        m_vEnd[2][2] = 'x';
    }
    void build()
    {
        // Init
        m_vBoardStep.reserve(Factory<9>::VALUE);
        m_vBoardStep.push_back(m_vEnd);

        // BFS
        int iCur = 0;
        int iRootIdx = _calcBoardIdx(m_vBoardStep[0]);
        m_vParent[iRootIdx] = iRootIdx;
        m_vDir[iRootIdx] = E_DIR_MAX;
        while(iCur < m_vBoardStep.size())
        {
            Board board(m_vBoardStep[iCur]);
            int iX = 0, iY = 0;
            int iParentIdx = _calcBoardIdx(board);
            _findX(board, iX, iY);
//_print(board);
//printf("iCur %ld x %ld y %ld iBoardIdx %ld\n", iCur, iX, iY, _calcBoardIdx(board));
            for(int d = E_UP; d < E_DIR_MAX; ++d)
            {
                int iX2 = iX + aiDir[d][0];
                int iY2 = iY + aiDir[d][1];
                if((iX2 >= 0) && (iX2 < 3) && (iY2 >= 0) && (iY2 < 3))
                {
                    swap(board[iX][iY], board[iX2][iY2]);
                    int iBoardIdx = _calcBoardIdx(board);
                    if(-1 == m_vParent[iBoardIdx])
                    {
                        m_vBoardStep.push_back(board);
                        m_vParent[iBoardIdx] = iParentIdx;
                        m_vDir[iBoardIdx] = (EN_DIR)d;
                    }
                    swap(board[iX][iY], board[iX2][iY2]);
                }
            }
            ++iCur;
        }
//printf("iCur %ld size %ld\n", iCur, m_vBoardStep.size());
    }
    void print(const Board& board) const
    {
        int iBoardIdx = _calcBoardIdx(board);
        if(-1 == m_vParent[iBoardIdx])
        {
            puts("unsolvable");
            return;
        }
        // Back-tracking
        string sAns;
        while(iBoardIdx != m_vParent[iBoardIdx])
        {
            sAns += acUrdl[m_vDir[iBoardIdx]];
            iBoardIdx = m_vParent[iBoardIdx];
        }
        reverse(sAns.begin(), sAns.end() - 1);
        puts(sAns.c_str());
    }

private:
    enum EN_DIR
    {
        E_UP = 0,
        E_RIGHT,
        E_DOWN,
        E_LEFT,
        E_DIR_MAX
    };

    static const char acUrdl[];
    static const int aiDir[][2];
    Board m_vEnd;
    vector<Board> m_vBoardStep;
    vector<int> m_vParent;
    vector<EN_DIR> m_vDir;

    void _findX(const Board& board, int& iX, int& iY) const
    {
        for(iX = 0; iX < 3; ++iX)
        {
            for(iY = 0; iY < 3; ++iY)
            {
                if('x' == board[iX][iY])
                {
                    return;
                }
            }
        }
    }
    int _calcBoardIdx(const Board& board) const
    {
        vector<char> vList(9, '0');
        for(int i = 0; i < 3; ++i)
        {
            for(int j = 0; j < 3; ++j)
            {
                vList[i * 3 + j] = board[i][j];
            }
        }
        return Permutation<9, char>::calcIndex(vList);
    }
    void _print(const Board& board) const
    {
        for(int i = 0; i < 3; ++i)
        {
            for(int j = 0; j < 3; ++j)
            {
                printf("%c", board[i][j]);
            }
            puts("");
        }
    }
};

const char Puzzle::acUrdl[] = {'u', 'r', 'd', 'l'};
const int Puzzle::aiDir[][2] = { {-1, 0}, {0, 1}, {1, 0}, {0, -1}};

int main()
{
    Puzzle pzl;
    pzl.build();
    int iNumCase = 0;
    cin >> iNumCase;
    for(int i = 0; i < iNumCase; ++i)
    {
        vector< vector<char> > vPzl(3, vector<char>(3, '0'));
        for(int j = 0; j < 3; ++j)
        {
            for(int k = 0; k < 3; ++k)
            {
                cin >> vPzl[j][k];
            }
        }
        if(i > 0)
        {
            puts("");
        }
        pzl.print(vPzl);
    }
    return 0;
}

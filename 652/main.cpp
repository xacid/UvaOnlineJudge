/********************************************************************
 * 652 - Eight, OVa Online Judge
 * http://uva.onlinejudge.org/external/6/652.html
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
    static unsigned int calcInversion(const vector<T>& vSeq)
    {
        unsigned int iRet = 0;
        for(unsigned int i = 0; i < N; ++i)
        {
            iRet += _getGtCount(vSeq[i], vSeq.begin() + i + 1, vSeq.end());
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
    explicit Puzzle(const vector<char>& vIn) :
        m_vOrig(3, vector<char>(3, '0')),
        m_bFound(false),
        m_vBoardStep(),
        m_vParent(),
        m_vDir(),
        m_bVisited(Factory<9>::VALUE, false)
    {
        for(int i = 0; i < 3; ++i)
        {
            for(int j = 0; j < 3; ++j)
            {
                m_vOrig[i][j] = vIn[i * 3 + j];
            }
        }
    }
    bool solveBfs()
    {
        // Init
        m_vBoardStep.resize(1);
        m_vParent.resize(1);
        m_vDir.resize(1);
        m_vBoardStep[0] = m_vOrig;
        m_vParent[0] = -1;
        m_vDir[0] = E_DIR_MAX;
        m_bFound = false;
        // BFS
        int iCur = 0;
        while(iCur < m_vBoardStep.size())
        {
            Board board(m_vBoardStep[iCur]);
            int iX = 0, iY = 0;
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
                    if(false == m_bVisited[iBoardIdx])
                    {
                        m_vBoardStep.push_back(board);
                        m_vParent.push_back(iCur);
                        m_vDir.push_back((EN_DIR)d);
                        m_bVisited[iBoardIdx] = true;
                        if(0 == iBoardIdx)
                        {
//_print(board);
//printf("iCur %ld size %ld iBoardIdx %ld\n", iCur, m_vParent.size(), iBoardIdx);
                            m_bFound = true;
                            return true;
                        }
                    }
                    swap(board[iX][iY], board[iX2][iY2]);
                }
            }
            ++iCur;
        }
//printf("iCur %ld size %ld\n", iCur, m_vParent.size());
        return false;
    }
    void print() const
    {
        if(false == m_bFound)
        {
            puts("unsolvable");
            return;
        }
        // Back-tracking
        int iCur = m_vBoardStep.size() - 1;
        string sAns;
        while(iCur >= 0)
        {
            sAns += acUrdl[m_vDir[iCur]];
            iCur = m_vParent[iCur];
        }
        reverse(sAns.begin(), sAns.end() - 1);
        puts(sAns.c_str());
    }
    bool isSolvable() const
    {
        vector<char> vList;
        vList.reserve(8);
        for(int i = 0; i < 3; ++i)
        {
            for(int j = 0; j < 3; ++j)
            {
                if('x' != m_vOrig[i][j])
                {
                    vList.push_back(m_vOrig[i][j]);
                }
            }
        }
        if((Permutation<8, char>::calcInversion(vList) % 2) == 0)
        {
            return true;
        }
        return false;
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
    Board m_vOrig;
    bool m_bFound;
    vector<Board> m_vBoardStep;
    vector<int> m_vParent;
    vector<EN_DIR> m_vDir;
    vector<bool> m_bVisited;

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
    int _calcBoardIdx(const Board& board)
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
    int iNumCase = 0;
    cin >> iNumCase;
    for(int i = 0; i < iNumCase; ++i)
    {
        vector<char> vPzl(9, '0');
        for(int j = 0; j < 9; ++j)
        {
            cin >> vPzl[j];
        }
        if(i > 0)
        {
            puts("");
        }
        Puzzle pzl(vPzl);
        if(pzl.isSolvable() == false)
        {
            puts("unsolvable");
            continue;
        }
        pzl.solveBfs();
        pzl.print();
    }
    return 0;
}

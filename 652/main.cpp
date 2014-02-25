/********************************************************************
 * 652 - Eight, OVa Online Judge
 * http://uva.onlinejudge.org/external/6/652.html
 ********************************************************************/
#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdio>
using namespace std;

class Puzzle
{
public:
    typedef vector< vector< char> > Board;
    explicit Puzzle(const vector<char>& vIn) :
        m_vOrig(3, vector<char>(3, '0')),
        m_vSolution(),
        m_bFound(false)
    {
        for(int i = 0; i < 3; ++i)
        {
            for(int j = 0; j < 3; ++j)
            {
                m_vOrig[i][j] = vIn[i * 3 + j];
            }
        }
    }
    void solve()
    {
        int iX = 0, iY = 0;
        for(iX = 0; iX < 3; ++iX)
        {
            for(iY = 0; iY < 3; ++iY)
            {
                if('x' == m_vOrig[iX][iY])
                {
                    goto FOUND_X;
                }
            }
        }
FOUND_X:
printf("char %c x %ld y %ld\n", m_vOrig[iX][iY], iX, iY);
        m_vBoardStep.resize(10);
        m_vBoardStep[0] = m_vOrig;
        if(solve(0, iX, iY) == true)
        {
            m_bFound = true;
        }
    }
    bool solve(int depth, int iX, int iY)
    {
        static const char acUrdl[] = {'u', 'r', 'd', 'l'};
        static const int aiDir[][2] = { {-1, 0}, {0, 1}, {1, 0}, {0, -1}};
        vector<Board> vBoard(E_DIR_MAX, Board(3, vector<char>(3, '0')));
        vector<Priority> vScore;
        Board board(m_vBoardStep[depth]);
printf("depth %ld x %ld y %ld\n", depth, iX, iY);
_print(board);
        for(int d = E_UP; d < E_DIR_MAX; ++d)
        {
            int iX2 = iX + aiDir[d][0];
            int iY2 = iY + aiDir[d][1];
            if((iX2 >= 0) && (iX2 < 3) && (iY2 >= 0) && (iY2 < 3))
            {
                swap(board[iX][iY], board[iX2][iY2]);
                if(_checkCycle(board, depth) == false)
                {
                    Priority p;
                    vBoard[d] = board;
                    p.pBoard = &vBoard[d];
                    p.iScore = _calcScore(board);
                    p.enDir = (EN_DIR)d;
                    vScore.push_back(p);
                    if(8 == p.iScore)
                    {
                        m_vSolution.push_back(acUrdl[d]);
                        return true;
                    }
                }
                swap(board[iX][iY], board[iX2][iY2]);
            }
        }
        if(vScore.empty() == true)
        {
            return false;
        }
        sort(vScore.begin(), vScore.end());
        for(int i = 0; i < vScore.size(); ++i)
        {
            int iX2 = iX + aiDir[vScore[i].enDir][0];
            int iY2 = iY + aiDir[vScore[i].enDir][1];
            m_vBoardStep.resize(depth + 2);
            m_vBoardStep[depth + 1] = *(vScore[i].pBoard);
            if(solve(depth + 1, iX2, iY2) == true)
            {
                m_vSolution.push_back(acUrdl[vScore[i].enDir]);
                return true;
            }
        }
        return false;
    }
    void print() const
    {
        if(false == m_bFound)
        {
            puts("unsolvable");
            return;
        }
        for(int i = m_vSolution.size() - 1; i >= 0; --i)
        {
            printf("%c", m_vSolution[i]);
        }
        puts("");
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
    struct Priority
    {
        EN_DIR enDir;
        int iScore;
        Board* pBoard;
        bool operator<(const Priority& rhs) const
        {
            return (iScore > rhs.iScore);
        }
    };

    Board m_vOrig;
    vector<char> m_vSolution;
    bool m_bFound;
    vector<Board> m_vBoardStep;

    bool _checkCycle(const Board& board, int depth) const
    {
        for(int i = 0; i <= depth; ++i)
        {
            if(m_vBoardStep[i] == board)
            {
                return true;
            }
        }
        return false;
    }
    int _calcScore(const Board& board) const
    {
        int iRet = 0;
        for(int i = 0; i < 3; ++i)
        {
            for(int j = 0; j < 3; ++j)
            {
                if((i * 3 + j + '1') == board[i][j])
                {
                    ++iRet;
                }
            }
        }
        return iRet;
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
        Puzzle pzl(vPzl);
        pzl.solve();
        if(i > 0)
        {
            puts("");
        }
        pzl.print();
    }
    return 0;
}

#include <iostream>
#include <vector>
#include <cstdio>
using namespace std;

struct Game
{
    static const int BOARD_SIZE = 101;
    int numPlayer;
    vector<int> vLadder;
    vector<bool> vRepeat;
    vector<bool> vSkip;

    explicit Game(int nP) :
        numPlayer(nP),
        vLadder(BOARD_SIZE, -1),
        vRepeat(BOARD_SIZE, false),
        vSkip(BOARD_SIZE, false)
    {}
    int play(const vector<int>& dice)
    {
        int player = 0;
        vector<int> pos(numPlayer, 0);
        vector<bool> skip(numPlayer, false);
        int i = 0;
        while(i < dice.size())
        {
//printf("P %ld: %ld\n", player, pos[player]);
            if(skip[player])
            {
                skip[player] = false;
                player = _nextPlayer(player);
                continue;
            }

            int nxtPos = _nextPos(pos[player], dice, i);
            if(nxtPos == 100)
            {
                return player;
            }
            else if(true == vSkip[nxtPos])
            {
                skip[player] = true;
            }
            pos[player] = nxtPos;
            player = _nextPlayer(player);
        }
        return 0;
    }
private:
    int _nextPos(int cur, const vector<int>& dice, int& i)
    {
        if(i >= dice.size())
        {
            return cur;
        }

        int ret = cur + dice[i];
        ++i;
        if(ret > 100)
        {
            return cur;
        }

        bool bCheck = true;
        while(bCheck)
        {
            if(true == vRepeat[ret])
            {
                return _nextPos(ret, dice, i);
            }
            if(vLadder[ret] > 0)
            {
                ret = vLadder[ret];
                continue;
            }
            bCheck = false;
        }
        return ret;
    }
    int _nextPlayer(int p)
    {
        return ((p + 1 < numPlayer) ? p + 1 : 0);
    }
};

int main()
{
    // Get dice
    vector<int> dice;
    int die = 0;
    cin >> die;
    while(die > 0)
    {
        dice.push_back(die);
        cin >> die;
    }
    // Get game
    int players = 0;
    cin >> players;
    while(players > 0)
    {
        Game game(players);
        // Get ladder
        int start = 0, end = 0;
        cin >> start >> end;
        while((start != 0) && (end != 0))
        {
            game.vLadder[start] = end;
            cin >> start >> end;
        }
        // Get repeats
        int turn = 0;
        cin >> turn;
        while(turn != 0)
        {
            if(turn > 0)
            {
                game.vRepeat[turn] = true;
            }
            else
            {
                game.vSkip[-turn] = true;
            }
            cin >> turn;
        }

        printf("%ld\n", game.play(dice) + 1);
        cin >> players;
    }
    return 0;
}

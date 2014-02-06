#include <iostream>
#include <cassert>
using namespace std;

enum MOVETYPE{
  NONE = 0,
  KNIGHT = 1,
  BISHOP = 2,
  TELE = 4
};

const int NMAX = 20;
const int STEPMAX = 100000;
const int NUMK = 8;
const int KNIGHT_X[NUMK] = {1, 2, 2, 1, -1, -2, -2, -1};
const int KNIGHT_Y[NUMK] = {-2, -1, 1, 2, 2, 1, -1, -2};
const int NUMB = 4;
const int BISHOP_X[NUMB] = {2, 2, -2, -2};
const int BISHOP_Y[NUMB] = {-2, 2, 2, -2};
int steps[NMAX*2][NMAX*2];
unsigned int stepType[NMAX*2][NMAX*2];
int N;

inline void doMark(int x, int y, int px, int py, int step, MOVETYPE type){
  if(steps[px][py] == -1 && stepType[x][y] != type){
    steps[px][py] = step;
    stepType[px][py] = type;
  }
  else if(steps[px][py] == step && stepType[x][y] != type){
    steps[px][py] = step;
    stepType[px][py] |= type;
  }
}

void markStep(int x, int y, int step){
  assert(x < N*2);
  assert(y < N*2);
  assert(step < N*N*2*2);
  // mark K
  for(int i = 0; i < NUMK; ++i){
    int px = x + KNIGHT_X[i];
    int py = y + KNIGHT_Y[i];
    if(px >= 0 && px < 2*N && py >= 0 && py < 2*N){
      doMark(x, y, px, py, step, KNIGHT);
    }
  }
  // mark B
  for(int i = 0; i < NUMB; ++i){
    int px = x + BISHOP_X[i];
    int py = y + BISHOP_Y[i];
    if(px >= 0 && px < 2*N && py >= 0 && py < 2*N){
      doMark(x, y, px, py, step, BISHOP);
    }
  }
  // mark T
  int px = N * 2 - 1 - x;
  doMark(x, y, px, y, step, TELE);
  int py = N * 2 - 1 - y;
  doMark(x, y, x, py, step, TELE);
}

void createTable(){
  int step = 0;
  bool stepFound = false;
  do{
    stepFound = false;
    for(int i = 0; i < N*2; ++i){
      for(int j = 0; j < N*2; ++j){
        if(steps[i][j] == step){
          stepFound = true;
          markStep(i, j, step + 1);
        }
      }
    }
/*
for(int i=0; i<N*2; ++i){
for(int j=0; j<N*2; ++j){
  cout << steps[i][j] << '\t';
}
  cout << "\n";
}
*/
  ++step;
  }while(stepFound);
}

int main(){
  cin >> N;
  while(N > 0){
    for(int i = 0; i < N*2; ++i)
      for(int j = 0; j < N*2; ++j)
        steps[i][j] = -1;
    for(int i = 0; i < N*2; ++i)
      for(int j = 0; j < N*2; ++j)
        stepType[i][j] = NONE;
    int Sx, Sy, Tx, Ty;
    cin >> Sx >> Sy >> Tx >> Ty;
    steps[Sx - 1][Sy - 1] = 0;
    int Ux, Uy;
    cin >> Ux >> Uy;
    while(Ux != 0 || Uy != 0){
      steps[Ux - 1][Uy - 1] = STEPMAX;
      cin >> Ux >> Uy;
    }
    createTable();
    if((steps[Tx - 1][Ty - 1] == -1) || (steps[Tx - 1][Ty - 1] == STEPMAX))
      cout << "Solution doesn't exist\n";
    else
      cout << "Result : " << steps[Tx - 1][Ty - 1] << "\n";
    cin >> N;
  }
}

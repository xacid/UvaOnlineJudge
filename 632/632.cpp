#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

const int MAX_LEN = 1998;
char input2[MAX_LEN * 2];
vector< pair<char, int> > collast;
int len;

bool cmp(pair<char, int> a, pair<char, int> b){
  for(int i = 0; i < len; i++){
    if(input2[a.second + i] < input2[b.second + i]) return true;
    if(input2[a.second + i] > input2[b.second + i]) return false;
  }
  return false;
}

int bwt(){
  stable_sort(collast.begin(), collast.end(), cmp);
  //for(int i = 0; i < len; i++) cout << collast[i].first;
  //cout << '\n';
  //for(int i = 0; i < len; i++) cout << collast[i].second << ' ';
  //cout << '\n';
  for(int i = 0; i < len; i++)
    if(collast[i].second == 1)
      return i;
}

int main(){
  int inputNum = 0;
  cin >> inputNum;
  for(int i = 0; i < inputNum; i++){
    collast.clear();
    cin >> len;
    for(int j = 0; j < len; j++){
      char c = '0';
      cin >> c;
      input2[j] = c;
      input2[j + len] = c;
    }
    collast.push_back(pair<char, int>(input2[len - 1], 0));
    for(int j = 1; j < len; j++){
      collast.push_back(pair<char, int>(input2[j - 1], j));
    }
    int s1 = bwt();
    cout << s1;
    for(int j = 0; j < len; j++){
      if(j % 50 == 0)
        cout << endl;
      cout << collast[j].first;
    }
    cout << '\n';
    if(i < inputNum - 1)
      cout << '\n';
  }
}

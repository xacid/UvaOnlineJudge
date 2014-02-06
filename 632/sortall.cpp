#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

const int MAX_LEN = 1998;
vector< pair<char *, int> > strlist;
char input[MAX_LEN];
int len;

bool cmp(pair<char *, int> a, pair<char *, int> b){
  for(int i = 0; i < len; i++){
    if(a.first[i] < b.first[i]) return true;
    if(a.first[i] > b.first[i]) return false;
  }
  return false;
}

int bwt(){
  stable_sort(strlist.begin(), strlist.end(), cmp);
  for(int i = 0; i < len; i++){
    if(strlist[i].second == 1)
        return i;
  }
  //cout << "ERROR!\n";
  return 1;
}

int main(){
  int inputNum = 0;
  cin >> inputNum;
  for(int i = 0; i < inputNum; i++){
    cin >> len;
    for(int j = 0; j < len; j++){
      char c = '0';
      cin >> c;
      input[j] = c;
    }
    for(int j = 0; j < len; j++){
      char* str = new char[len];
      for(int k = 0; k < len; k++){
        if(k + j < len)
          str[k] = input[k + j];
        else
          str[k] = input[k + j - len];
      }
      strlist.push_back(pair<char *, int>(str, j));
    }
    int s1 = bwt();
    cout << s1;
    for(int j = 0; j < len; j++){
      if(j % 50 == 0)
        cout << endl;
      cout << strlist[j].first[len - 1];
    }
    cout << '\n';
    if(i < inputNum - 1)
      cout << '\n';

    for(int j = 0; j < len; j++)
      delete [] strlist[j].first;
    strlist.clear();
  }
}

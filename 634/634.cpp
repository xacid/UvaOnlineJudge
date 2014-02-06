#include <iostream>
#include <vector>
using namespace std;

const int MIN = -10001;
vector< pair<int, int> > v;

int crossCount(int x, int y){
  int count = 0;
  for(int i = 1; i < v.size(); i++){
    if(v[i].second == v[i - 1].second
        && v[i].second < y && v[i].second > MIN
        && x > min(v[i].first, v[i -1].first)
        && x < max(v[i].first, v[i -1].first)){
      count++;
    }
  }
  return count;
}

int main(){
  int N;
  cin >> N;
  while(N > 0){
    v.clear();
    for(int i = 0; i < N; ++i){
      int x, y;
      cin >> x >> y;
      v.push_back(pair<int, int>(x, y));
    }
    if(v.size() > 0){
      v.push_back(pair<int, int>(v[0].first, v[0].second));
    }
    int x, y;
    cin >> x >> y;
    int count = crossCount(x, y);
    if(count % 2 == 1)
      cout << "T\n";
    else
      cout << "F\n";
    cin >> N;
  }
}

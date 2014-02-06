#include <iostream>
#include <vector>
using namespace std;

const int MAX_NODE = 10;
const int MAX_K = 1024;
int nodeNum;
bool choseNode[MAX_NODE];
bool adj[MAX_NODE][MAX_NODE];
vector< vector<char> > K;

void printK(vector<char>& vec){
  for(int i = 0; i < vec.size(); i++) cout << (int)vec[i] << ' ';
  cout << '\n';
}

void addK(){
  vector<char> set;
  K.push_back(set);
  for(int v = 0; v < nodeNum; v++){
    if(choseNode[v]){
      K.back().push_back((char)v);
    }
  }
  //printK(K.back());
}

void checkK(){
  bool compMax = true;
  for(int v = 0; v < nodeNum; v++){
    bool adjAll = true;
    for(int u = 0; u < nodeNum; u++){
      if(choseNode[u] && adj[v][u] == false){
        adjAll = false;
        break;
      }
    }
    if((choseNode[v] && !adjAll) || (!choseNode[v] && adjAll)){
      compMax = false;
      break;
    }
  }
  if(compMax)
    addK();
}

void findK(int nodeS){
  if(nodeS == nodeNum){
    bool hasNode = false;
    for(int v = 0; v < nodeNum; v++){
      if(choseNode[v]){
        hasNode = true;
        break;
      }
    }
    if(hasNode)
      checkK();
    return;
  }
  choseNode[nodeS] = false;
  findK(nodeS + 1);
  choseNode[nodeS] = true;
  findK(nodeS + 1);    
}

int cmpK(vector<char>& a, vector<char>& b){
  if(a.size() > b.size()) return 1;
  if(a.size() < b.size()) return -1;
  for(int i = 0; i < a.size(); i++){
    if(a[i] < b[i]) return 1;
    if(a[i] > b[i]) return -1;
  }
  return 0;
}

void sortK(){
  int numK = K.size();
  for(int i = 0; i < numK; i++)
    for(int j = i + 1; j < numK; j++)
      if(cmpK(K[i], K[j]) < 0)
        K[i].swap(K[j]);
}

int main(){
  while(cin >> nodeNum){
    K.clear();
    for(int i = 0; i < MAX_NODE; i++)
      choseNode[i] = false;

    for(int i = 0; i < nodeNum; i++){
      adj[i][i] = true;
      for(int j = 0; j < nodeNum; j++){
        char c;
        cin >> c;
        if(j <= i)
          continue;
        if('-' == c) adj[i][j] = adj[j][i] = true;
        if('*' == c) adj[i][j] = adj[j][i] = false;
        //cout << adj[i][j] << ' ';
      }
      //cout << '\n';
    }
    findK(0);
    //for(int i = 0; i < K.size(); i++) printK(K[i]);
    sortK();
    //for(int i = 0; i < K.size(); i++) printK(K[i]);
    for(int v = 0; v < nodeNum; v++){
      for(int i = 0; i < K.size(); i++){
        for(int j = 0; j < K[i].size(); j++){
          if(K[i][j] == (char)v){
            cout << (char)('a' + i);
            break;
          }
        }
      }
      cout << '\n';
    }
    cout << "-----\n";
  }
}

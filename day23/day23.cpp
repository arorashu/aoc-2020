#include <iostream>
#include <vector>
#include <deque>
#include <list>
#include <algorithm>
#include <unordered_map>

using namespace std;

template<typename T>
void print(const vector<T> &arr) {
  for(auto x: arr)
    cout << x << ' ';
  cout << endl;
}


template<typename T>
void print(const deque<T> &arr) {
  for(auto x: arr)
    cout << x << ' ';
  cout << endl;
}



template<typename T>
void print(const list<T> &arr) {
  for(auto x: arr)
    cout << x << ' ';
  cout << endl;
}



int main() {

  //vector<int> cups = {1, 2, 3, 4, 8, 7, 5, 9, 6};
  //int i=100, cur=0, dest;
  //vector<int> cups = {3, 8, 9, 1, 2, 5, 4, 6 ,7};
  
  
  //deque<long> cups = {1, 2, 3, 4, 8, 7, 5, 9, 6};
  long i=100, cur=0, dest;


  // part 1
#if 0
  deque<int> cups = {3, 8, 9, 1, 2, 5, 4, 6 ,7};
  i = 10;
  while(i--) {
    cout << "round: " << 10-i << endl;
    print(cups);
    int curVal = cups[cur];
    cout << "cur pos: " << cur << ", cur val: " << cups[cur] << endl;
    
    vector<int> pick;

    if(cur+1 < cups.size()) { 
      pick.insert(pick.begin(), cups.begin()+cur+1, min(cups.begin()+cur+4, cups.end()) );
      cups.erase(cups.begin()+cur+1, min(cups.begin()+cur+4, cups.end()) );
    }

    while(pick.size() != 3) {
      pick.push_back(cups.front());
      cups.pop_front();
    }

    //vector<int> pick(cups.begin()+cur+1, cups.begin()+cur+4);
    cout << "pick : " ; print(pick);
    //cups.erase(cups.begin()+cur+1, cups.begin()+cur+4);
    
    //vector<int> remain = cups;
    /*
    deque<int> remain = cups;
    sort(remain.begin(), remain.end());
    int temp =  find(remain.begin(), remain.end(), curVal) - remain.begin();
    if(temp==0) {
      dest =  find(cups.begin(), cups.end(), remain.back()) - cups.begin();
    } else {
      dest =  find(cups.begin(), cups.end(), remain[temp-1]) - cups.begin();
    }
    */
    // find max element less than cur
    long elemToFind = curVal-1;
    if(elemToFind==0)
      elemToFind = 9;

    while(count(pick.begin(),pick.end(), elemToFind) > 0 ) {
      elemToFind -= 1;
      if(elemToFind==0)
        elemToFind = 9;
    }
    dest = find(cups.begin(), cups.end(), elemToFind) - cups.begin();
    cout << "dest pos: " << dest << " , val: " << cups[dest] << endl;
    
    cups.insert(cups.begin() + dest + 1, pick.begin(), pick.end());
    int newCurPos = find(cups.begin(), cups.end(), curVal)-cups.begin();
    cur = (newCurPos + 1) % cups.size();
  }

  cout << "end: "; print(cups);
  // ans: 47598263
#endif


// part 2
#if 1
  unordered_map<long, list<long>::iterator> posMap; 
  //list<long> cups = {3, 8, 9, 1, 2, 5, 4, 6 ,7};
  list<long> cups = {1, 2, 3, 4, 8, 7, 5, 9, 6};
  long rounds = 1e7;
  //long rounds = 10;
  i = rounds;
  long max_elem = 1e6;
  //long max_elem = 9;
  
  for(long j=10; j<=max_elem; j++) {
    cups.push_back(j);
  }
  for(auto it = cups.begin(); it!=cups.end(); it++)
    posMap[*it] = it;
  
  auto curIt = cups.begin();

  while(i--) {
    cout << "round: " << rounds-i << endl;
    //print(cups);
    long curVal = *curIt;
    //cout << "cur val: " << curVal << endl;

    // find max element less than cur that is not picked
    vector<int> pick;
    int x = 3;
    auto pickIt = curIt;
    while(x--) {
      pickIt++;
      if(pickIt==cups.end())
        pickIt = cups.begin();

      pick.push_back(*pickIt);
    }
    
    long elemToFind = (*curIt)-1;
    if(elemToFind==0)
      elemToFind = max_elem;
    while(find(pick.begin(), pick.end(), elemToFind) != pick.end()) {
      elemToFind--;
      if(elemToFind==0)
        elemToFind = max_elem;
    }

    auto destIt = posMap[elemToFind];
    //cout << "dest val: " << *destIt << endl;
    destIt++;
   
    // move the nodes
    x = 3;
    while(x--) {
      auto toMoveIt = curIt;
      toMoveIt++;
      if(toMoveIt==cups.end())
        toMoveIt = cups.begin();

      cups.splice(destIt, cups, toMoveIt);
    }

    // update the next cur node
    auto nextCurIt = curIt;
    nextCurIt++;
    if(nextCurIt==cups.end())
      nextCurIt = cups.begin();
    curIt = nextCurIt;
  }

  // print the succeeding nodes
  auto it1 = posMap[1];
  int x=2;
  while(x--) {
    it1++;
    if(it1==cups.end())
      it1 = cups.begin();
    cout << *it1 << ' ';
  }
  cout << endl;
  //cout << "test solution\n";
  // ans: 248009574232
#endif

  return 0;
}




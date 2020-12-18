/*
  day 15 - part a and b
  compile: g++ day15.cpp
  run:     ./a.out
*/

#include <iostream>
#include <vector>
#include <map>

using namespace std;

int main() {
  vector<int> inp = {7,12,1,0,16,2};
  map<long, long> lastSpoken;
  long i=1, next;

  while(i-1<inp.size()) {
    int x = inp[i-1];
    //cout << i << " : " << x << endl;
    if(lastSpoken.find(x)==lastSpoken.end()) {
      lastSpoken[x] = i;
      next = 0;
    } else {
      next = i - lastSpoken[x];
      lastSpoken[x] = i;
    }
    i++;
  }


  // part a
  /*
  while(i<2020) {
    //cout << i << " : " << next << endl;
    if(lastSpoken.find(next)==lastSpoken.end()) {
      lastSpoken[next] = i;
      next = 0;
    } else {
      int x = next;
      next = i - lastSpoken[next]; 
      lastSpoken[x] = i;
    }
    i++;
  }

  cout << "last num is: " << next << endl;
  */
  // wrong: 0
  // right: 410


  
  // part b
  while(i<30000000) {
    //cout << i << " : " << next << endl;
    if(lastSpoken.find(next)==lastSpoken.end()) {
      lastSpoken[next] = i;
      next = 0;
    } else {
      long x = next;
      next = i - lastSpoken[next]; 
      lastSpoken[x] = i;
    }
    i++;
  }

  cout << "last num is: " << next << endl;
  // right: 238

  return 0;
}

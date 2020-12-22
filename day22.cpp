/*
  day 22 - part a and b
  compile: g++ day22.cpp
  run:     ./a.out
*/

#include <iostream>
#include <vector>
#include <deque>
#include <map>
#include <string>
#include <unordered_set>
#include <set>

using namespace std;


struct roundState {
  deque<int> p1;
  deque<int> p2;
};

bool operator< (const roundState& lhs, const roundState& rhs) {
  if(lhs.p1 !=  rhs.p1) 
    return lhs.p1 < rhs.p1;

  return lhs.p2 < rhs.p2;
}



void calculateScore(deque<int> &p1, deque<int> &p2) {
  
  // calculate and print score
  int score = 0;
  if(p1.empty()) {
    swap(p1, p2); // set player 1 as winner
  }

  int n = p1.size();
  for(int i=n-1; i>=0; i--) {
    score += p1[i] * (n-i);
  }
  cout << "score: " << score << endl;

  // part 2
  // low: 31843
  // ans: 33647
}

void printCards(deque<int> & p) {

  for(auto x: p) {
    cout << x << ' ';
  }
  cout << endl;
}

// pass by value as subgames do not affect original game
// return true - player 1 won, false - player 2 won
bool playGame2(deque<int> &p1, deque<int> &p2, int gameId) {

  /*
  cout << "playing game: " << gameId << endl;
  cout << "p1: "; printCards(p1); 
  cout << "p2: "; printCards(p2); 
  */
  int round = 1;
  set<roundState> history;

  
  while(!p1.empty() && !p2.empty()) {
  //cout << "playing round: " << round << endl;
    if(round > 1 && history.find({p1, p2}) != history.end()) { // happened before, game ends
      //cout << "found!: " << history.size() << endl;
      if(gameId==1)
        break;
      else
        return false; // p1 wins
    } else { // add to history
      history.insert({p1, p2});
    }

    bool winner = false;
    
    if(p1.front() <= p1.size()-1 && p2.front() <= p2.size()-1) {
      //cout << "go play recurse game\n";
      deque<int> p1sub(p1.begin()+1, p1.begin()+p1.front()+1);
      deque<int> p2sub(p2.begin()+1, p2.begin()+p2.front()+1);
      winner = playGame2(p1sub, p2sub, gameId+1);
    } else {
      //cout << "normal play\n";
      if(p1.front() > p2.front()) {
        winner = false;
      } else {
        winner = true;
      }
    }

    if(!winner) { // p1 wins
      p1.push_back(p1.front());
      p1.push_back(p2.front());
      p1.pop_front();
      p2.pop_front();
    } else {
      p2.push_back(p2.front());
      p2.push_back(p1.front());
      p1.pop_front();
      p2.pop_front();
    }
    //cout << "p1 deck: " << p1.size() 
    //     << " p2 deck: " << p2.size() << endl;
    round++;
  } // while ends


  if(gameId==1) {
    calculateScore(p1, p2);
  }
  //cout << "game: " << gameId << " ends\n";
  return p1.empty() ? true : false;
}


int main() {
  string playerName;  
  getline(cin, playerName);

  deque<int> player1, player2;
  int card, i=0;
  while(i<25) {
    cin >> card;
    player1.push_back(card);
    i++;
  }


  cout << "player 1 cards:\n";
  for(auto x: player1) {
    cout << x << ' ';
  }
  cout << endl;


  string empty;
  getline(cin, empty); // clear \n buffer ?
  getline(cin, empty); // new line ?
  getline(cin, playerName);


  i=0;
  while(i<25) {
    cin >> card;
    player2.push_back(card);
    i++;
  }

  cout << "player 2 cards:\n";
  for(auto x: player2) {
    cout << x << ' ';
  }
  cout << endl;

/*
  cout << "game started, part 1\n";

  i=0;
  while(!player1.empty() && !player2.empty()) {
    if(player1.front() > player2.front()) {
      player1.push_back(player1.front());
      player1.push_back(player2.front());
      player1.pop_front();
      player2.pop_front();
    } else {
      player2.push_back(player2.front());
      player2.push_back(player1.front());
      player2.pop_front();
      player1.pop_front();
    }
    cout << "round: " << i++ << " player1 deck: " << player1.size() 
                           << " player2 deck: " << player2.size() << endl;
  }*/

  
  cout << "part 2 \n";
  bool winner = playGame2(player1, player2, 1);

/*
  // calculate and print score part a
  int score = 0;
  if(player1.empty() || winner==true) {
    swap(player1, player2); // set player 1 as winner
  }

  int n = player1.size();
  for(i=n-1; i>=0; i--) {
    score += player1[i] * (n-i);
  }
  cout << "score: " << score << endl;
  // ans: 31308
*/


  return 0;
}

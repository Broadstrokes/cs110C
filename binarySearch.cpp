#include <iostream>
#include <string>
#include <fstream>
using namespace std;


    ///////////////////
    // BINARY SEARCH //
    ///////////////////

void promptUser();
void getUserInput(char &userResponse, int &start, int& end);
bool playAgain();
void playOnce();
int getMidpoint(int start, int end);
void mySwapWithReference(int &a, int &b);
void mySwapWithPointers(int *a, int *b);


int main() {
  
  cout << "Hello Player" << endl;
  int a = 5, b = 30;
  cout << a << endl;
  cout << b << endl;
  mySwapWithReference(a, b);

  cout << "after" << endl;
  cout << a << endl;
  cout << b << endl;

  do {
    playOnce();
  } while(playAgain());


}

void playOnce() {
    char userResponse;
    int start = 1;
    int end = 100;

    promptUser();
    getUserInput(userResponse, start, end);
    cout << userResponse << endl;
}

bool playAgain() {
  char userResponse;
  cout << "Play again (y/n))?: ";
  cin >> userResponse;
  return userResponse == 'y';
}

void promptUser() {
  cout << "Guess an # between 1 and 100" << endl;
}

void getUserInput(char &userResponse, int &start, int& end) {
  do {
    int midpoint = getMidpoint(start, end);
    cout << "Is it " << midpoint << "(h/l/c)?: ";
    cin >> userResponse;

    if (userResponse == 'h') {
      start = midpoint;
    } else if (userResponse == 'l') {
      end = midpoint;
    }
  } while (userResponse != 'c');

}

int getMidpoint(int start, int end) {
  return ((start + end) / 2);
}




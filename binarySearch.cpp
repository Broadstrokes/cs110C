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





    /////////////////////////
    // SWAP WITH REFERENCE //
    /////////////////////////
void mySwapWithReference(int &a, int &b) {
  int temp = a;
  a = b;
  b = temp;
}


    ////////////////////////
    // SWAP WITH POINTERS //
    ////////////////////////
void mySwapWithPointers(int *a, int *b) {
  int temp = *a; //declaring a pointer variable
  *a = *b; 
  *b = temp;
}



    ////////////////////////////////
    //using regular swap function //
    ////////////////////////////////
void swap(int *int1, int *int2);

    ////////////////////
    //using templates //
    ////////////////////
template<typename T>
T swapi(T &int1, T &int2){
  T temp = int1;
  int1 = int2;
  int2 = temp;
}


int main() {
  int int1 = 1;
  int int2 = 2;

  swap(int1, int2);
  cout<< "1: " << int1 << " 2: " << int2 << endl;
  
  swapi(int1, int2);
  cout<< "1: " << int1 << " 2: " << int2 << endl;

  void swap(int *int1, int *int2) { //* here are pointers
    int temp = *int1;  //here we are dereferencing to get value
   *int1 = *int2;
   *int2 = temp;
  }

}


/*
  Using template
  template <typename T> 

  T Swap (T &int1, T &int2) {
    T temp = int1; 
    int1 = int2; 
    int2 = temp;
  }
*/


    /////////////////////////
    // READING FROM A FILE //
    /////////////////////////

ifstream fin("order.dat");
const int SIZE=20;
int q[SIZE];
double price[SIZE];
double total=0;

if (fin.is_open()){
  for (int i=0; i<6;i++){
    fin >> q[i];
    fin >> price[i];
    total=total+(q[i]*price[i]);

  }
}
cout << total;
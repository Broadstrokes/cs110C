#include <iostream>
#include <string>
#include <math.h> // sqrt
#include <map> 		// for map operations 

using namespace std;

void testAListSearch();
void testForArrayBasedSimpleStat();

///////////////////////
// Utility functions //
///////////////////////
template <typename T>
void loopOverList(T &myList) {
	for (myList.moveToStart(); !myList.isAtEnd(); myList.next()) {
  	double it = myList.getValue();
  	cout << it << endl;
	}
}

inline bool EVEN(int x) { return (x % 2) == 0;} // Return true iff "x" is even
inline bool ODD(int x) { return (x % 2) != 0; } // Return true iff "x" is odd

// Assert: If "val" is false, print a message and terminate the program
void Assert(bool val, string s) {
  if (!val) { // Assertion failed -- close the program
      cout << "Assertion Failed: " << s << endl;
      exit(-1);
    }
}
// Swap two elements in a generic array
template<typename E>
inline void swap(E A[], int i, int j) {
  E temp = A[i];
  A[i] = A[j];
  A[j] = temp;
}
// Random number generator functions
inline void Randomize(){ srand(1); }  // Seed the generator
// Return a random value in range 0 to n-1
inline int Random(int n) { return rand() % (n); }



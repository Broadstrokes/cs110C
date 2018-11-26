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



////////////////////
// SimpleSTAT ADT //
////////////////////
class SimpleStat {
	public:
		virtual double mean() =0;
		virtual double mode() =0;
		virtual double median() =0;
		virtual double standardDeviation() =0;
};



///////////////////////////////////////////////////
// Singly linked list node with freelist support //
///////////////////////////////////////////////////

template <typename E> class Link {
private:
  static Link<E>* freelist; // Reference to freelist head
public:
  E element; // Value for this node
  Link* next; // Point to next node in list
  // Constructors
  Link(const E& elemval, Link* nextval =NULL){
    element = elemval;
    next = nextval;
  }
  Link(Link* nextval =NULL) {
    next = nextval;
  }
  void* operator new(size_t) { // Overloaded new operator
    if (freelist == NULL) return ::new Link; // Create space
    Link<E>* temp = freelist; // Can take from freelist
    freelist = freelist->next;
    return temp; // Return the link
  }
  // Overloaded delete operator
  void operator delete(void* ptr) {
    ((Link<E>*)ptr)->next = freelist; // Put on freelist
    freelist = (Link<E>*)ptr; // We need casting because we are using void pointers here
  }
};


////////////////////////////////////////////////////////
// The freelist head pointer is actually created here //
////////////////////////////////////////////////////////
template <typename E>
Link<E>* Link<E>::freelist = NULL;


//////////////
// List ADT //
//////////////

template <typename E> class List {
private:
  void operator =(const List&) {} // Protect assignment
  List(const List&) {} // Protect copy constructor
public:
  List() {} // Default constructor
  virtual ~List() {} // Base destructor
  // Clear contents from the list, to make it empty.
  virtual void clear() = 0;
  // Insert an element at the current location.
  // item: The element to be inserted
  virtual void insert(const E& item) = 0;
  // Append an element at the end of the list.
  // item: The element to be appended.
  virtual void append(const E& item) = 0;
  // Remove and return the current element.
  // Return: the element that was removed.
  virtual E remove() = 0;
  // Set the current position to the start of the list
  virtual void moveToStart() = 0;
  // Set the current position to the end of the list
  virtual void moveToEnd() = 0;
  // Move the current position one step left. No change
  // if already at beginning.
  virtual void prev() = 0;
  // Move the current position one step right. No change
  // if already at end.
  virtual void next() = 0;
  // Return: The number of elements in the list.
  virtual int length() const = 0;
  // Return: The position of the current element.
  virtual int currPos() const = 0;
  // Set current position.
  // pos: The position to make current.
  virtual void moveToPos(int pos) = 0;
  // Return: The current element.
  virtual const E& getValue() const = 0;
  // Return true if current position is at end of the list
  virtual bool isAtEnd() = 0;
};
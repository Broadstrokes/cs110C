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

inline bool EVEN(int x) { return (x % 2) == 0; } // Return true iff "x" is even
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


/////////////////////////////////////
// Array-based list implementation //
/////////////////////////////////////
template <typename E>
class AList : public List<E> {
private:
  int maxSize; // Maximum size of list
  int listSize; // Number of list items now
  int curr; // Position of current element
  E* listArray; // Array holding list elements
  int recursiveBinarySearch(double arrayToSearch[], int low, int high, int tgt) {
  	if (low <= high) {
    		int middle = (low + high) / 2;
				if (arrayToSearch[middle] == tgt) { return middle; }   
				else if (arrayToSearch[middle] < tgt) { return recursiveBinarySearch(arrayToSearch, middle + 1, high, tgt); }
        else { return recursiveBinarySearch(arrayToSearch, low, middle - 1, tgt); }
 		}

   	return -1; 
	}

public:
  AList(int size = 100) { // Constructor replace defaultSize (now 10) with the default you want otherwise leave empty
    maxSize = size;
    listSize = curr = 0;
    listArray = new E[maxSize];
  }
  ~AList() { delete [] listArray; } // Destructor
  void clear() { // Reinitialize the list
    delete [] listArray; // Remove the array
    listSize = curr = 0; // Reset the size
    listArray = new E[maxSize]; // Recreate array
  }
  // Insert "it" at current position
  void insert(const E& it) {
    Assert(listSize < maxSize, "List capacity exceeded");
    for(int i=listSize; i>curr; i--) // Shift elements up
      listArray[i] = listArray[i-1]; // to make room
    listArray[curr] = it;
    listSize++; // Increment list size
  }
  void append(const E& it) { // Append "it"
    Assert(listSize < maxSize, "List capacity exceeded");
    listArray[listSize++] = it;
  }
  // Remove and return the current element.
  E remove() {
    Assert((curr>=0) && (curr < listSize), "No element");
    E it = listArray[curr]; // Copy the element
    for(int i=curr; i<listSize-1; i++) // Shift them down
      listArray[i] = listArray[i+1];
    listSize--; // Decrement size
    return it;
  }
  void moveToStart() { curr = 0; } // Reset position
  void moveToEnd() {  curr = listSize; } // Set at end
  void prev() {  if (curr != 0) curr--; }  // Back up
  void next() {  if (curr < listSize) curr++;}
  int length() const { return listSize; } // Return list size
  int currPos() const { return curr; }  // Return current position
  // Set current list position to "pos"
  void moveToPos(int pos) {
    Assert ((pos>=0)&&(pos<=listSize), "Pos out of range");
    curr = pos;
  }
  const E& getValue() const { // Return current element
    Assert((curr>=0)&&(curr<listSize),"No current element");
    return listArray[curr];
  }
  // Return true if current position is at end of the list
  bool isAtEnd() { return curr == listSize; }

  int ssearch(double tgt) { 
  	int result = -1;

		for (moveToStart(); !isAtEnd(); next()) {
			double it = getValue();
			if (it == tgt) {
				return currPos();
			}
		}			

  	return result;
  }

  int ibsearch(double tgt) {
  	int result = -1;
  	double arrayToSearch[length()];
  	int n = sizeof(arrayToSearch)/sizeof(arrayToSearch[0]);
  	
		for (moveToStart(); !isAtEnd(); next()) {
			arrayToSearch[currPos()] = getValue();
		}

  	sort(arrayToSearch, arrayToSearch + n); 

  	int low = 0;
  	int high = n - 1; 


		while (low <= high) {
			int middle = low + (high - low) / 2;

			if (arrayToSearch[middle] == tgt) { return middle; } 
			else if (arrayToSearch[middle] < tgt) { low = middle + 1; }
			else { high = middle - 1; }
		}
  
  	return result;
  }


  int rbsearch(double tgt) {
  	double arrayToSearch[length()];
  	int n = sizeof(arrayToSearch)/sizeof(arrayToSearch[0]);
  	
		for (moveToStart(); !isAtEnd(); next()) {
			arrayToSearch[currPos()] = getValue();
		}

  	sort(arrayToSearch, arrayToSearch + n); 

  	int low = 0;
  	int high = n - 1;

  	return recursiveBinarySearch(arrayToSearch, low, high, tgt);
  }
};


/////////////////////////////////////////
// ArrayBasedSimpleStat Implementation //
/////////////////////////////////////////

class ArrayBasedSimpleStat : public SimpleStat, public AList<double> {
	public:
		// Default constructor
		ArrayBasedSimpleStat() {};
		
		double mean() {
			double sum = 0;
			double average;
					
			for (moveToStart(); !isAtEnd(); next()) {
	  		sum += getValue();
			}

			return sum/length(); 
		}

		double median() {
			int len = length();
			double term1, term2;
			double arrayToSort[len];
			int isOdd = len % 2 != 0;
			int middleIndex = ((len + 1) / 2) - 1;

			for (moveToStart(); !isAtEnd(); next()) {
	  		arrayToSort[currPos()] = getValue();
			}			 	

	  	int n = sizeof(arrayToSort)/sizeof(arrayToSort[0]);
	  	sort(arrayToSort, arrayToSort + n); 


			if (isOdd) {
				return arrayToSort[middleIndex];
			} else {
				return (arrayToSort[middleIndex] + arrayToSort[middleIndex + 1]) / 2;
			}
		}

		double mode() {
			int maxCount = 0; 
			double valueCorrespondingToMaxCount;
			map<int, int> countMap;

			// declaring iterators 
			map<int, int>::iterator it;
			map<int, int>::iterator itr;

			// store count of each value in the map
			for (moveToStart(); !isAtEnd(); next()) {
	  		double val = getValue();

	  		it = countMap.find(val);

  			if (maxCount == 0) {
  				maxCount = it->second;
  				valueCorrespondingToMaxCount = it->first;
  			}

	  		if (it == countMap.end()) {
	  			countMap.insert(pair <int, int> (val, 1));
	  		} else {
	  			it->second = it->second + 1;
  				
  				if (it->second > maxCount) {
  					maxCount = it->second;
  					valueCorrespondingToMaxCount = it->first;
	  			}
	  		}
			}		

			return valueCorrespondingToMaxCount;
		}

		double standardDeviation() { 
			double summationMeanSquaredDiff;
			double avg = this->mean();

			for (moveToStart(); !isAtEnd(); next()) {
				double it = getValue();
	  		summationMeanSquaredDiff += (it - avg) * (it - avg);
			}

			return sqrt(summationMeanSquaredDiff/length());
		}
};


//////////
// MAIN //
//////////
int main() {
	cout << "Starting HW 3 Driver" << endl;	

	cout << ">>>>>>>>>>>>>>>>>>>>>>>>" << endl;
	cout << "RUN TESTS FOR QUESTION 7" << endl;
	cout << ">>>>>>>>>>>>>>>>>>>>>>>>" << endl;
	testForArrayBasedSimpleStat();
	
	cout << ">>>>>>>>>>>>>>>>>>>>>>>>" << endl;
	cout << "RUN TESTS FOR QUESTION 8" << endl;
	cout << ">>>>>>>>>>>>>>>>>>>>>>>>" << endl;
	testAListSearch();


	////////////////
	// QUESTION 9 //
	////////////////

	/*
		Solution:
		1. I would use a linked list to store each digit in reverse order
		2. Time complexity to add O(n) time 
		3. Time complexity to multiply O(n) time 
	 */

}


//////////
// TEST //
//////////

void testAListSearch() {
	AList<double> myList;
	
	myList.insert(100);
	myList.insert(101);
	myList.insert(61);
	myList.insert(102);
	myList.insert(82);
	myList.insert(103);
	myList.insert(79);
	myList.insert(80);
	myList.insert(77);
	myList.insert(102);
	myList.insert(99);
	myList.insert(88);
	myList.insert(92);
	myList.insert(88);

	cout << "Search for 99 using ssearch: " << myList.ssearch(99) << endl;
	cout << "Search for 87 using ssearch: " << myList.ssearch(87) << endl;
	cout << "Search for 99 using ibsearch: "  << myList.ibsearch(99) << endl;
	cout << "Search for 87 using ibsearch: "  << myList.ibsearch(87) << endl;
	cout << "Search for 99 using rbsearch: "  << myList.rbsearch(99) << endl;
	cout << "Search for 97 using rbsearch: "  << myList.rbsearch(87) << endl;
}

void testForArrayBasedSimpleStat() {
		ArrayBasedSimpleStat myAABST;
		myAABST.insert(1);
		myAABST.insert(2);
		myAABST.insert(3);
		myAABST.insert(4);
		myAABST.insert(5);
		myAABST.insert(3);
		myAABST.insert(3);
		myAABST.insert(3);
		myAABST.insert(5);
		myAABST.insert(5);
		myAABST.insert(10);
		myAABST.insert(20);
		myAABST.insert(10);


		cout << "Mean: " << myAABST.mean() << endl;
		cout << "Standard Deviation: " << myAABST.standardDeviation() << endl;
		cout << "Median: " << myAABST.median() << endl;
		cout << "Mode: " << myAABST.mode() << endl;


		Assert((myAABST.median() == 4), "median calculation failed");
		Assert((myAABST.mode() == 3), "mode calculation failed");
}
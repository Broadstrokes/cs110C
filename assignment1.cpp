#include <iostream>
#include <string>
#include<vector>
#include <cmath>

using namespace std;

static const double PI = 3.14159; 

  ///////////
  // Ellipse //
  ///////////

class Ellipse {

  public:
    Ellipse();
    Ellipse(int a, int b);
    int getArea();
    int getPerimeter();
  private:
    int majorA;
    int minorB;
};


Ellipse::Ellipse() {
  majorA = 0;
  minorB = 0;
};

Ellipse::Ellipse(int majorA, int minorB) {
  this -> majorA = majorA;
  this -> minorB = minorB;
};

int Ellipse::getArea() {
  return PI * majorA * minorB;
};

int Ellipse::getPerimeter() {
  int h = pow((majorA - minorB), 2) / pow((majorA + minorB), 2);
  return PI * (majorA + minorB) * (1 + ((3 * h) / (10 + sqrt(4 - (3 * h)))));
};

    ///////////
    // Circle //
    ///////////
class Circle: public Ellipse {
  public:
    Circle();
    Circle(int radius);
};

Circle::Circle() { }
Circle::Circle(int radius) : Ellipse(radius, radius) { }



         /////////////////////////////////
          // Template To Add 2 Types //
          /////////////////////////////////


template <typename T, typename V>
T add(const T& a, const V& b) {
  return a + b;
}


void printTables(int start, int end);
bool allUniqueCharacters(string str);
bool isPanagram(string str);
void rotateLeft(int arr[], int numRotations, int arrSize);
void printArray(int arr[], int arrSize);
unsigned long long factorial(int num);


int main() {

  cout << "==========================" << endl;
  cout << "Ellipse & Circle Classes" << endl;
  cout << "==========================" << endl;
  Ellipse a = Ellipse(10, 5);
  cout << "Area of ellipse major=10, minor=5: " << a.getArea() << endl;
  Circle b = Circle(10);
  cout << "Area of circle with radius 10: " << b.getArea() << endl;

  cout << endl;
  cout << "==========================" << endl;
  cout << "Print Table" << endl;
  cout << "==========================" << endl;
  printTables(1, 12);

  cout << endl;
  cout << "==========================" << endl;
  cout << "All unique" << endl; 
  cout << "==========================" << endl;

  cout << allUniqueCharacters("hello") << endl;

  cout << endl;
  cout << "==========================" << endl;
  cout << "Is panagram" << endl; 
  cout << "==========================" << endl;
  
  cout << isPanagram("The quick brown fox jumps over the lazy dog") << endl;
  cout << isPanagram("hi there") << endl;

  cout << endl;
  cout << "==========================" << endl;
  cout << "Rotate" << endl; 
  cout << "==========================" << endl;

  int arr[] = { 1, 2, 3, 4, 5, 6};
  int size = sizeof(arr) / sizeof(arr[0]);

  rotateLeft(arr, 2, size);
  printArray(arr, size);

  cout << endl;
  cout << endl;
  cout << "==========================" << endl;
  cout << "Factorial" << endl; 
  cout << "==========================" << endl;
  
  cout << "Factorial " << factorial(1) << endl;
  cout << "Factorial " << factorial(2) << endl;
  cout << "Factorial " << factorial(3) << endl;
  cout << "Factorial " << factorial(4) << endl;
  cout << "Factorial " << factorial(5) << endl;
  cout << "Factorial " << factorial(12) << endl;
  cout << "Factorial " << factorial(30) << endl;
  cout << "Factorial " << factorial(-5) << endl;
  cout << "Factorial " << factorial(40) << endl;

  cout << endl;
  cout << "==========================" << endl;
  cout << "Add" << endl; 
  cout << "==========================" << endl;
  
  cout << add<int>(3, 5) << endl;
  cout << add<int>(10.0, 5.0) << endl;
  cout << add<string>("hat", "abb") << endl;
  cout << add<string>("abb", "hat") << endl;
}


/**
 * Calculate the the factorial of integers between
 * 0 and 30 inclusive respectively
 * @param      num        integer 0<= num <= 30
 * @return     long long  factorial of num
 */
unsigned long long factorial(int num) {
  if (num < 0 || num > 30) {
    cout << "Input outside range" << endl;
    return 0;
  } else {
    int result = 1;
    for(int i = 1; i <= num; i++) {
      result = result * i;
    }

    return result;
  }
}


/**
 * Rotates an array left by a given number of rotations
 * @param arr          int array that needs to be rotated
 * @param numRotations int indicating the # of left rotations 
 * @param arrSize      int size of the give array
 */
void rotateLeft(int arr[], int numRotations, int arrSize) {
  for (int i = 0; i < numRotations; i++) {
    int temp = arr[0];
    int j;
    for (j = 0; j < arrSize - 1; j++) {
        arr[j] = arr[j + 1];
    }
    arr[j] = temp;
  }
}
 
/**
 * Prints a given array
 * @param arr     int array that needs to be printed
 * @param arrSize int size of the give array
 */
void printArray(int arr[], int arrSize) {
  for (int i = 0; i < arrSize; i++) {
    cout << arr[i] << " ";
  }
}


/**
 * Given a string returns a boolean indicated if the string has
 * all unique characters
 * @param  str string to test
 * @return     bool true indicating all characters are unquie
 */
bool allUniqueCharacters(string str){
  cout << str.size() << endl;
  for (int i = 0; i < str.size(); i++) {
    for(int j = i+1; j < str.size(); j++) {
      if(str[i] == str[j]) {
        return false;
      }
    }
  }
 
  return true;
}


/**
 * Given a string returns a boolean indicated if the string has
 * all characters in the english alphabet i.e. it is a panagram
 * @param  str string to test
 * @return     bool true/false indicating the string is/not a panagram
 */
bool isPanagram(string str) {
  int len = 26;
  int idx;
  vector<bool> map(len, false);


  for(int i = 0; i < str.size(); i++) {
    if (str[i] >= 'A' && str[i] <= 'Z') { idx = str[i] - 'A'; } 
    else if (str[i] >= 'a' && str[i] <= 'z') { idx = str[i] - 'a'; }

    map[idx] = true;
  }

  for(int i = 0; i < len; i++) {
    if (map[i] == false) {
      return false;
    }
  }
  return true;  
}


/**
 * Prints a multiplication table for a given range
 * @param start start of the range
 * @param end   end of the range
 */
void printTables(int start, int end) {
  int multiple;
  
  for(int row = 1; row <= end; row++) {
    if (row < 10) {
      cout << " ";
    }

    cout << row << ' ';
    
    for(int col  = 1; col  <= end; col ++) {
      if (col  == 1) {
        cout << '|';
      }

      int multiple = col * row;
      if(multiple < 10) {
        cout << "  ";
      }
      if(multiple < 100 && multiple >= 10) { 
        cout << " ";
      }
      
      cout << multiple << ' ';
    }
    if(row == 1) {
      cout << endl;
      cout << "---------------------------------------------------";
    }
    cout << endl;
  }
}


/*
Sound understanding about iterators in C++ is very important as access to a
data structure is enabled through an iterator. Learn more about C++ iterators here.
(Links to an external site.)Links to an external site.

Imagine you are writing a wrapper class to make a container out of a fixed array.
You are doing this because you want to access every multiple of 3 elements in the array. 
That means you want to iterate over the array in steps of 3 through a dedicated iterator.
For example ++ would give you the next integer multiple of 3 elements.
Your iterator should start from the beginning of the array (0 index) and ends with
the maximum index that is a multiple of 3. 

Write your wrapper class for an array size 100 and use it to write your iterator class.
Write a driver program to print out an example array in steps of 3 using the iterator 
you designed.
*/

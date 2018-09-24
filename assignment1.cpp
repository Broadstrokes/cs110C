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
    int area;
    int perimeter;
};


Ellipse::Ellipse() {
  area = 0;
  perimeter = 0;
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
  cout << "Hello World!\n";

  printTables(1, 12);
  cout << allUniqueCharacters("hello") << endl;
  cout << isPanagram("The quick brown fox jumps over the lazy dog") << endl;
  cout << isPanagram("hi there") << endl;



  int arr[] = { 1, 2, 3, 4, 5, 6};
  int size = sizeof(arr) / sizeof(arr[0]);

  rotateLeft(arr, 2, size);
  printArray(arr, size);


  cout << endl;
  cout << "Factorial " << factorial(1) << endl;
  cout << "Factorial " << factorial(2) << endl;
  cout << "Factorial " << factorial(3) << endl;
  cout << "Factorial " << factorial(4) << endl;
  cout << "Factorial " << factorial(5) << endl;
  cout << "Factorial " << factorial(12) << endl;
  cout << "Factorial " << factorial(30) << endl;
  cout << "Factorial " << factorial(-5) << endl;
  cout << "Factorial " << factorial(40) << endl;



  cout << add<int>(3, 5) << endl;
  cout << add<int>(10.0, 5.0) << endl;
  cout << add<string>("hat", "abb") << endl;
  cout << add<string>("abb", "hat") << endl;
}


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

void rotateLeft(int arr[], int numRotations, int arrSize) {
  cout << "==========================" << endl;
  cout << "Rotate" << endl; 
  cout << "==========================" << endl;

    for (int i = 0; i < numRotations; i++) {
      int temp = arr[0];
      int j;
      for (j = 0; j < arrSize - 1; j++) {
          arr[j] = arr[j + 1];
      }
      arr[j] = temp;
    }
}
 
void printArray(int arr[], int n) {
    for (int i = 0; i < n; i++) {
      cout << arr[i] << " ";
    }
}

bool allUniqueCharacters(string str){
  cout << "==========================" << endl;
  cout << "All unique" << endl; 
  cout << "==========================" << endl;

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

bool isPanagram(string str) {
  cout << "==========================" << endl;
  cout << "Is panagram" << endl; 
  cout << "==========================" << endl;
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

void printTables(int start, int end) {
  int multiple;    
  cout << "==========================" << endl;
  cout << "Print Table" << endl;
  cout << "==========================" << endl;
  
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

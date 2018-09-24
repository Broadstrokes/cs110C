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

int main {

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
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



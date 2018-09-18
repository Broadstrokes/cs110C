#include <iostream>
using namespace std;

/*
  Student class with overloaded << to print student name and age
 */

          /////////////
          // Student //
          /////////////
class Student {
  public:
    Student();
    Student(string name, int age);
    friend ostream& operator<<(ostream& out, const Student& right);

  private: 
    string name;
    int age;
};

Student::Student() {};

Student::Student(string nameInput, int ageInput) {
  name = nameInput;
  age = ageInput;
};


ostream& operator<<(ostream& out, const Student& right) {
  out << "Name: " << right.name << endl;
  out <<"Age: " << right.age << endl;
  return out;
}


              ///////////
              // Shape //
              ///////////
class Shape {
  public:
    Shape();
    int getArea();
  private:  
    int area;
    int perimeter;
};

Shape::Shape() {
  area = 0;
  perimeter = 0;
};


                //////////////
                // Triangle //
                //////////////

class Triangle: public Shape {
  public:
    Triangle();
    Triangle(int b, int h);
    int getArea();
  private:
    int base;
    int height;
};


Triangle::Triangle() {};

Triangle::Triangle(int base, int height) {
  this -> base = base;
  this -> height = height;
};

int Triangle::getArea() {
  return 0.5 * base * height;
};




int main() {
  Triangle x(2, 4);
  Student a("Jimmy", 30);

  cout << a;
  cout << x.getArea() << endl;
}
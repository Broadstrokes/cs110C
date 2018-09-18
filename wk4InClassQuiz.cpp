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





int main() {
  // Triangle x(2, 4);
  Student a("Jimmy", 30);

  cout << a;
  cout << x.getArea() << endl;
}
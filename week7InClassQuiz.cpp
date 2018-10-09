#include <iostream>
using namespace std;

int fib(int n);

int main() {
  cout << (fib(0) == 0)  << endl;
  cout << (fib(1) == 1) << endl;
  cout << (fib(2) == 1) << endl;
  cout << (fib(3) == 2) << endl;
  cout << (fib(4) == 3) << endl;
  cout << (fib(5) == 5) << endl;
  cout << (fib(10) == 55) << endl;
  cout << (fib(15) == 610) << endl;
  cout << (fib(20) == 6765) << endl;
  cout << (fib(25) == 75025)<< endl;
  cout << (fib(30) == 832040) << endl;
}

int fib(int n) {
    if (n <= 2)
      return 1;
    else
      return fib(n-1) + fib(n-2);
}

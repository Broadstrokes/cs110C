#include <iostream>
#include <string>
using namespace std;


int main() {
 cout << GCD(18, 24) << endl;	// 6
 cout << GCD(42, 35) << endl;	// 7 
}


//Q6 GCD recursive
int GCD(int x, int y) {
 if (y == 0)
   return x;
 return GCD(y, x % y);
} 
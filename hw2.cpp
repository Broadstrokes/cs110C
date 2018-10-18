#include <iostream>
#include <string>
#include <math.h>       /* sqrt */
using namespace std;

int GCD(int x, int y);
bool isPalindrome(string str);
int powOfn(int n, double m);
bool isPrime(int n, int count = 2);

int main() {
	cout << GCD(18, 24) << endl;	// 6
	cout << GCD(42, 35) << endl;	// 7
	cout << isPalindrome("madam") << endl;
	cout << isPalindrome("maa") << endl;


	cout << powOfn(2, 0) << endl;
	cout << powOfn(2, 1) << endl;
	cout << powOfn(2, 2) << endl;
	cout << powOfn(2, 3) << endl;
	cout << powOfn(2, 4) << endl;
	cout << powOfn(2, 5) << endl;



	cout << isPrime(1) << endl;
	cout << isPrime(2) << endl;
	cout << isPrime(3) << endl;
	cout << isPrime(4) << endl;
	cout << isPrime(5) << endl;
	cout << isPrime(6) << endl;
	cout << isPrime(7) << endl;
	cout << isPrime(8) << endl;
	cout << isPrime(9) << endl;
}


// Q6 GCD recursive
int GCD(int x, int y) {
	if (y == 0)
		return x;
	return GCD(y, x % y);
} 

// Q13 Palindrome recursive
bool isPalindrome(string str) {
	int start = 0;
	int end = str.size() - 1;

	if (start >= end)
		return true;
	else if (str[start] != str[end])
		return false;
	return isPalindrome(str.substr(1, str.size() -2));
}


// Q14 Power of N
int powOfn(int n, double m) {
  if (m == 0)
    return 1;
  return n * powOfn(n, m - 1);
}

// Q15 is prime recursive
bool isPrime(int n, int count) {
	if (n == 1)
		return false;
	else if (n == 2)
		return true;
	else if (n % count == 0)
		return false;
	else if (count > sqrt(n))
		return true;

	return isPrime(n, count + 1);
}
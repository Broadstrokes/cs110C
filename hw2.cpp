#include <iostream>
#include <string>
using namespace std;

int GCD(int x, int y);
bool isPalindrome(string str);


int main() {
	cout << GCD(18, 24) << endl;	// 6
	cout << GCD(42, 35) << endl;	// 7
	cout << isPalindrome("madam") << endl;
	cout << isPalindrome("maa") << endl;
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
	return isPalindrome(str.substr (1, str.size() -2));
}

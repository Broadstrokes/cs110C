#include <algorithm>
#include <iostream>
#include <time.h> // C library


unsigned int long long factorial(int num);
void testTimeUsingTimeHLibrary(int num);

int main() {
  testTimeUsingTimeHLibrary(5);
  return 0;
}


/////////////////////////
// Calculate factorial //
/////////////////////////
unsigned int long long factorial(int num) {
	int result = 1;
	
	for (int i = 1; i <= num; i++) {
	  result = result * i;
  }

	return result;
}

///////////////////////
// Time using time.h //
///////////////////////
void testTimeUsingTimeHLibrary(int num) {
  // using time.h from C library
  clock_t start, end;
  double cpu_time_used;

  start = clock();
  cout << "factorial(" << num << ") " << factorial(num) << endl;
  end = clock();
  cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC; // in seconds

  cout << cpu_time_used * 1000 << " milliseconds";
}
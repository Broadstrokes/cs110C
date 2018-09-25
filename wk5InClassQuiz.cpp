#include <algorithm>
#include <iostream>
#include <time.h> // C library
#include <chrono> // C++ library
using namespace std;
using namespace std::chrono;

unsigned int long long factorial(int num);
void testTimeUsingTimeHLibrary(int num);
void testTimeUsingChronoLibrary(int num);

int main() {
  testTimeUsingTimeHLibrary(5);
  testTimeUsingChronoLibrary(5);
  return 0;
}


unsigned int long long factorial(int num) {
	int result = 1;
	
	for (int i = 1; i <= num; i++) {
	  result = result * i;
  }

	return result;
}

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


/*
  For clean and robust C++ programs we should strive
  to use C++ specific language constructs only.
*/
void testTimeUsingChronoLibrary(int num) {
  // using chrono from C++ library

  // Use auto keyword to avoid typing long 
  // type definitions to get the timepoint 
  // at this instant use function now() 
  auto start = high_resolution_clock::now();
  cout << "factorial(" << num << ") " << factorial(num) << endl;
  auto stop = high_resolution_clock::now();


  // Subtract stop and start timepoints and 
  // cast it to required unit. Predefined units 
  // are nanoseconds, microseconds, milliseconds, 
  // seconds, minutes, hours. Use duration_cast() 
  // function. 
  auto duration = duration_cast<microseconds>(stop - start);

   cout << "Time taken by function: "
        << duration.count() * 0.001 << " milliseconds" << endl;
}
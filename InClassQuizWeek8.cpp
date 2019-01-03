// Solutions to the coding question of practice exam on week 8, In-Class Quiz 8


//#include <QCoreApplication> // a QT thing
#include <iostream>
#include <set>
#include<cstdlib>
#include<ctime>
#include <string>
#include <algorithm>

// Q10: You are give the series sum,
//S(n) = 1^2 + 2^2 + 3^2 + 4^2 + .....+ (n-2)^2 +  (n-1)^2 + n^2 . Propose a recurrence relation to solve this sum recursively. Predict the running time for the above sum using the master theorem. Note that you will have to assume an alternative recurrence relation to apply master theorem. Use your original recurrence relation and write a recursive function to return the sum of first 50 terms. Use mathematical induction to prove that above sum simplifies to n(n+1)(2n+1)/6. Verify your recursive answer above with the direct result.

//Hint: Draw the recursive tree diagram for small n like n = 5 and try to predict the running time. Then work backward to see how you can use master theorem to prove the same.


long seriesSum(int n){
  if (n == 1){
      return 1; // Base case
    }
  else{
      return seriesSum(n-1) + n*n; // recursion relation is S(n) = S(n-1) + n^2
    }
}


// Q11, 12, 13:
// Q12: Pretending as the vendor in above question, write your solution as C++ code. Copy paste your answer here and select the formatting to "preformated". Anything we bake constitutes three operations, setTemperature, setTime, and bake.

class BakedGood{
public:
  virtual ~BakedGood();
  void virtual bake() = 0;
  void virtual setTemperature(double temperature) = 0;
  void virtual setTime(double time) = 0; // in minutes

};

//Q 13:
//Imagine you are the client of above company who make household stoves and you are going to use the above vendors interface for baking. Write a C++ class to represent a Stove. In addition to above operations, A stove has a model number, model name, a unique random integer serial number between 100 and 1000 and a count of how many Stoves that has been created. For the bake operation you can simply print a message of acknowledgement.
// 1. Draw the UML class diagram for this class
// 2. Implement the above class


class Stove: public BakedGood{
private:
  using BakedGood::setTemperature; // tell the compiler we want actualy overriding not hiding
  using BakedGood::bake; // keeps out a warning about hiding
  using BakedGood::setTime; // without this compiler warns that we are hiding above virtual method

  static std::set<int> myset;
  static unsigned long count; // had to make this type to avoid a down-cast to int because set use the same type as size
  static unsigned long size; // had to make this type to avoid a down-cast to int because set use the same type as size
  int serial_number;
  double temperature = 0;
  double bakeTime = 0;

  std::string name ="";
  std::string model_number ="";

public:
  Stove(int min, int max, std::string name, std::string model_number){
    int output = 0;
    unsigned int t = static_cast<unsigned int>(std::time(nullptr));// t is an int coresponding to current time
    std::srand(t); //If you don't use this the default is srand(1) so if you run the program twise you get same set of random numbers!
    while(count == Stove::myset.size()){ // How to add unique SN? We can check the size and count before and after
                                                       // Before add a new value the sizes are equal
        output = min + (std::rand() % static_cast<int>(max - min + 1)); // A randome int between min and max
        Stove::myset.insert(output); // insert. If this process is a sucess now the loop conditon is fails and we exit
      }
    // while loop fails when the insert is succesfull
    count = Stove::myset.size(); // Now we make the two sizes equal again so in the next constructor call we go into the while loop

    this->model_number = model_number;
    this->name = name;
    serial_number = output;
    //count += 1; // now theat at the end of the constructing we can increase the count by one safly
  }

  // Destructor
  ~Stove(){}

  void bake();
  void setTemperature(double temperature);
  void setTime(double bakeTime);

  // Getters
  static unsigned long getCount(){ // getter for count
    return Stove::count;
  }

  static unsigned long getProductCount(){ // getter for size
    return Stove::myset.size();
  }
  int getSerialNumber(){
    return this->serial_number;
  }
  double getTemperature(){
    return this->temperature;
  }

  // Setters
  void setCount(unsigned long count){ // in any case if we wants to reset the counter
    Stove::count = count;
  }
};

// if we are to provide a seperate className.cpp file then the lines between here and main() would go in there

void Stove::bake(){
  std::cout << "Please press the bake button" << "\n";
}
void Stove::setTemperature(double temperature){
  this->temperature = temperature;
}
void Stove::setTime(double bakeTime){
  this->bakeTime = bakeTime;
}

BakedGood::~BakedGood(){ } // Needed to be declaired outside
unsigned long Stove::count = 0; // static varibles need to be initilized outside of the class declaration
unsigned long Stove::size = 0;
std::set<int> Stove::myset; // static varibles need to be initilized outside of the clas declaration

//Q17: Write a c++ function to check whether a given phrase an English Pangram (Links to an external site.)Links to an external site.. A Pangram has all the letters of the alphabet. Here only consider a word phrase consist of all lower case letters.

bool isPangram(std::string phrase){
  std::set<std::string> myset;
  phrase += " "; // Adding a space by default so I will not miss on the word abcdefghijklmnopqrstuvwxyz
  transform(phrase.begin(), phrase.end(), phrase.begin(), ::tolower); // Transfrom all letters to lower case

  for (char c : phrase){
      //std::cout << c << "\n";
      myset.insert(std::string{c}); // iterator of a string is a char so need to convert it back to a string just before adding
    }
  return myset.size() == 27; // I am accomodating phrases with only spaces and english alphabatical charcters. So if the phrase is as such the length of the set by its definition is 27 (alphabatical characters +  1 space)

}

// The main driver or the client prgoram
int main()
{
  //QCoreApplication a(argc, argv); // Qt thing

  // Testing Q 10

  int n;
  std::cout << "Enter your integer number of terms, n for the series in the form 1^2 + 2^2 + 3^2 + 4^2 + ..... +  (n-2)^2 +  (n-1)^2 + n^2  " << '\n';
  std::cin >> n;
  std::cin.ignore(); // otherwise hitting enter key above will be the next input which is not
  std::cout << "series sum for n = " << n << " is " << seriesSum(n) << '\n';
  std::cout << "the direct sum is " << n*(n+1)*(2*n+1)/6 << '\n' << '\n';

  // Testing Q 12, 13

  Stove test1 (100, 1000, "Kenmore super1", "6N546"); // calling BakedGood(int min, int max)
  Stove test2 (100, 1000, "Kenmore super2", "6N548"); // calling BakedGood(int min, int max)
  Stove test3 (100, 1000, "Kenmore super4", "6N5463");

// To demostarte C++ sub-type polymorephisum you can also do below
// we still creates stove1/3 with Stove not BackedGood as we can't use an abstract class constructor
// But notice we can use it as a type! in particuar as the declaired type (= BakedGood)
// For example with the help of this, we can create an array of objects created out of multiple Stove or Kiln classes beacuse the declaired type is just one type, BackedGood

  BakedGood * stove1 = new Stove (100, 1000, "Kenmore super3", "6N5462");
  BakedGood * stove3 = &test3;

  std::cout << "Total number of Stoves is " <<  Stove::getProductCount() << '\n'; // Should be 4 above 4 objects
  std::cout << "test1 SN is " <<test1.getSerialNumber() << '\n';  // Should be whatever uniq random number
  std::cout << "test2 SN is " <<test2.getSerialNumber() << '\n' << '\n'; // Should be whatever uniq random number
  stove1->bake();  // Should be whatever uniq random number
  stove3->setTemperature(450);  // Should be whatever uniq random number
  stove3->setTime(120);  // Should be whatever uniq random number
  std::cout <<  "test3 SN is " << test3.getSerialNumber() << '\n';  // Should be whatever uniq random number
  std::cout <<  "test3 SN is " << test3.getTemperature() << '\n'<< '\n';  // Should be whatever uniq random number

  delete stove1; // only stove1 resides in heap so witout this its a memory leak


  // Testing Q 17:
  std::string phrase; // The phrase we are checking

  std::cout << "Please enter your phrase to check isPangram: just try \"abcdefghijklmnopqrstuvwxyz   \"  " << "\n";
 // std::cin >> phrase;
  getline (std::cin, phrase); // cin wouldn't work because of space
  std::cout << "pangram status of  "   << phrase << " is "  << '\n' << isPangram(phrase) << '\n';

  std::cout << "Please enter your phrase to check is Pangram: just try \"Pack my box with five dozen liquor jugs\"  " << "\n";
 // std::cin >> phrase;
  getline (std::cin, phrase); // cin wouldn't work because of space
  std::cout << "pangram status of  "   << phrase << " is "  << '\n' << isPangram(phrase) << '\n';

  std::cout << "Please enter your phrase to check is Pangram: just try \"not a pangram\"  " << "\n";
 // std::cin >> phrase;
  getline (std::cin, phrase); // cin wouldn't work because of space
  std::cout << "pangram status of  "   << phrase << " is "  << '\n' << isPangram(phrase) << '\n';

  //return a.exec();// a QT thing
  return 0;
}

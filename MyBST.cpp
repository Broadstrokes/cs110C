// Binary Search Tree imlementation for any nonw-dictionary
// data type. This should work with any data type that overloades
// >, = or < operators

// This is eveything in a sigle file. If you want it as seperate
// please put every major comphonent in seperate header file

#include <iostream>
#include <set>
using namespace std;




//////////////////////////////////////
// ABSTRACT CLASS: Binary Tree Node //
//////////////////////////////////////

template <typename E> class BinNode {
public:
  virtual ~BinNode() {}                   // Base destructor
  virtual E &element() = 0;               // Return the node’s value
  virtual void setElement(const E &) = 0; // Set the node’s value
  virtual BinNode *left() const = 0;      // Return the node’s left child
  virtual void setLeft(BinNode *) = 0;    // Set the node’s left child
  virtual BinNode *right() const = 0;     // Return the node’s right child
  virtual void setRight(BinNode *) = 0;   // Set the node’s right child
  virtual bool
  isLeaf() = 0; // Return true if the node is a leaf, false otherwise
}; // End of class BinNode




//////////////////////////////////////
// IMPLEMENTATION: Binary Tree Node //
//////////////////////////////////////
template <typename E> class BSTNode : public BinNode<E> {
private:
  E it;        // The node’s value
  BSTNode *lc; // Pointer to left child
  BSTNode *rc; // Pointer to right child

public:
  // Two constructors -- with and without initial values
  BSTNode() { lc = rc = NULL; } // set both nodes to null
  BSTNode(E e, BSTNode *l = NULL, BSTNode *r = NULL) {
    it = e;
    lc = l;
    rc = r;
  }
  ~BSTNode() {}

  // Destructor
  // Functions to set and return the value and key
  E &element() { return it; }
  void setElement(const E &e) { it = e; }

  // Functions to set and return the children
  inline BSTNode *left() const { return lc; }
  void setLeft(BinNode<E> *b) { lc = (BSTNode *)b; }
  inline BSTNode *right() const { return rc; }
  void setRight(BinNode<E> *b) { rc = (BSTNode *)b; }
  // Return true if it is a leaf, false otherwise
  bool isLeaf() { return (lc == NULL) && (rc == NULL); }
}; // End of class BSTNode




////////////////
// CLASS: BST //
////////////////

// This has to be a class template so that we write one class for
// all the types and to enforce compile time type safety
// this is equivalent of Java's generics
template <typename E> class BST {

private:
  BSTNode<E> *root; // Root of the BST
  int nodecount;    // Number of nodes in the BST

  // Private "helper" functions

  // Helper function for clear implementation taken from section 5.4
  template <typename E1> void clearhelp(BSTNode<E1> *root) {
    if (root == NULL)
      return;
    clearhelp(root->left());
    clearhelp(root->right());
    delete root;
  }

  // Helper function for insert implementation taken from section 5.4
  template <typename E1>
  BSTNode<E1> *inserthelp(BSTNode<E1> *root, const E1 &it) {
    if (root == NULL) // Empty tree: create node
      return new BSTNode<E1>(it, NULL, NULL);
    if (it < root->element())
      root->setLeft(inserthelp(root->left(), it));
    else
      root->setRight(inserthelp(root->right(), it));
    return root; // Return tree with node inserted
  }

  // Helper function for insert implementation taken from section 5.4
  // This was also for Rectagle. C++ doesn't allow passing an object
  // as const and accessing its member unless the members too are
  // const. So I simply removed const
  template <typename E1> BSTNode<E1> *inserthelp2(BSTNode<E1> *root, E1 &it) {
    if (root == NULL) // Empty tree: create node
      return new BSTNode<E1>(it, NULL, NULL);
    if (it < root->element())
      root->setLeft(inserthelp2(root->left(), it));
    else
      root->setRight(inserthelp2(root->right(), it));
    return root; // Return tree with node inserted
  }

  // Helper function for deletemin implementation taken from section 5.4
  template <typename E1> BSTNode<E1> *deletemin(BSTNode<E1> *rt) {
    if (rt->left() == NULL) // Found min
      return rt->right();
    else {
      // Continue left
      rt->setLeft(deletemin(rt->left()));
      return rt;
    }
  }

  // Helper function for getmin implementation taken from section 5.4
  template <typename E1> BSTNode<E1> *getmin(BSTNode<E1> *rt) {
    if (rt->left() == NULL)
      return rt;
    else
      return getmin(rt->left());
  }

  // Helper function for remove implementation taken from section 5.4
  // Remove a node with element e
  // Return: The tree with the node removed
  template <typename E1> BSTNode<E1> *removehelp(BSTNode<E1> *rt, const E1 &e) {
    if (rt == NULL)
      return NULL;
    // k is not in tree
    else if (e < rt->element())
      rt->setLeft(removehelp(rt->left(), e));
    else if (e > rt->element())
      rt->setRight(removehelp(rt->right(), e));
    else { // Found: remove it
      BSTNode<E1> *temp = rt;
      if (rt->left() == NULL) { // Only a right child
        rt = rt->right();       // so point to right
        delete temp;
      } else if (rt->right() == NULL) { // Only a left child
        rt = rt->left();                // so point to left
        delete temp;
      } else { // Both children are non-empty
        BSTNode<E1> *temp = getmin(rt->right());
        rt->setElement(temp->element());
        rt->setRight(deletemin(rt->right()));
        delete temp;
      }
    }
    return rt;
  }

  // Helper function for find implementation taken from section 5.4
  template <typename E1> E findhelp(BSTNode<E1> *root, const E1 &e) const {
    if (root == NULL)
      return NULL; // Empty tree
    if (e < root->value())
      return findhelp(root->left(), e); // Check left
    else if (e > root->value())
      return findhelp(root->right(), e); // Check right
    else
      return root->element(); // Found it
  }

  // Helper function for print implementation taken from section 5.4
  template <typename Key1, typename E1>
  void printhelp(BSTNode<E1> *root, int level) const {
    if (root == NULL)
      return;                           // Empty tree
    printhelp(root->left(), level + 1); // Do left subtree
    for (int i = 0; i < level; i++)     // Indent to level
      cout << "  ";
    cout << root->value() << "\n";       // Print node value
    printhelp(root->right(), level + 1); // Do right subtree
  }

  // Helper function for print implementation taken from section 5.4
  template <typename E1> void printhelp2(BSTNode<E1> *root, int level) const {
    if (root == NULL)
      return;                            // Empty tree
    printhelp2(root->left(), level + 1); // Do left subtree
    for (int i = 0; i < level; i++) {    // Indent to level
      cout << "           ";
    }
    cout << root->element() << "\n";      // Print node value
    printhelp2(root->right(), level + 1); // Do right subtree
  }

  // Helper function for print implementation taken from section 5.4
  template <typename E1> void printhelp3(BSTNode<E1> *root, int level) const {
    if (root == NULL)
      return;                            // Empty tree
    printhelp3(root->left(), level + 1); // Do left subtree
    for (int i = 0; i < level; i++)      // Indent to level
      cout << "       ";
    cout << root->element() << "\n";      // Print node value
    printhelp3(root->right(), level + 1); // Do right subtree
  }

  // Helper function to return root
  // I added this as all 3 traversal methods require access to root
  // so we need a getter for root
  template <typename E11> BSTNode<E11> *getroot(BSTNode<E11> *rt) { return rt; }

public:
  BST() { // Constructor
    root = NULL;
    nodecount = 0;
  }                           
  ~BST() { clearhelp(root); } // Destructor
  void clear() { // Reinitialize tree
    clearhelp(root);
    root = NULL;
    nodecount = 0;
  }

  // Insert a record into the tree.
  // e The record to insert.
  void insert(const E &e) {
    root = inserthelp(root, e);
    nodecount++;
  }

  // This was also for Rectagle. C++ doesn't allow passing an object
  // as const and accessing its member unless the members too are
  // const. So I simply removed const
  void insert2(E &e) {
    root = inserthelp2(root, e);
    nodecount++;
  }
  // Remove a record from the tree.
  // e record to remove.
  // Return: The record removed, or NULL if there is none.
  E remove(const E &e) {
    E temp = findhelp(root, e);
    // First find it
    if (temp != NULL) {
      root = removehelp(root, e);
      nodecount--;
    }
    return temp;
  }

  // Remove and return the root node from the dictionary.
  // Return: The record removed, null if tree is empty.
  E removeAny() { // Delete min value
    if (root != NULL) {
      E temp = root->element();
      root = removehelp(root, root->element());
      nodecount--;
      return temp;
    } else
      return NULL;
  }
  // Return Record element e, NULL if none exist.
  // e the element value to find. */
  // Return some record matching "e".
  // Return true if such exists, false otherwise. If
  // multiple records match "e", return an arbitrary one.
  E find(const E &e) const { return findhelp(root, e); }
  // Return the number of records in the dictionary.
  int size() { return nodecount; }
  void print() const { // Print the contents of the BST
    if (root == NULL)
      cout << "The BST is empty.\n";
    else
      printhelp(root, 0);
  }

  void print_value() const { // Print the contents of the BST
    if (root == NULL)
      cout << "The BST is empty.\n";
    else
      printhelp2(root, 0);
  }

  // I added this as all 3 traversal methods require access to root
  // so we need a getter for root
  BSTNode<E> *get_root() const { return root; }
}; // End of BST class BST




/////////////////////////
// TRAVERSAL FUNCTIONS //
/////////////////////////

// Implementation of three traversals. Though may be little bit tricky
// you can also incorporate these into the BST class above itself
// my thought was that an external client frequently do this independent of
// the BST. So that means they are client programs. This is probably
// the exact reason why the book also didn't do it

// preorder traversal
template <typename E1> void preorder(BSTNode<E1> *root) {
  if (root == NULL)
    return;           // Nothing to visit
  if (root->isLeaf()) // Do leaf node
    cout << "Leaf: " << root->element() << endl;
  else {                                             // Do internal nodes
    cout << "Internal: " << root->element() << endl; // We access root first
    preorder(root->left());
    preorder(root->right());
  }
}

// postorder traversal
template <typename E1> void postorder(BSTNode<E1> *root) {
  if (root == NULL)
    return;           // Nothing to visit
  if (root->isLeaf()) // Do leaf node
    cout << "Leaf: " << root->element() << endl;
  else { // Do internal nodes
    postorder(root->left());
    postorder(root->right());
    cout << "Internal: " << root->element() << endl; // We access root last
  }
}

// inorder traversal
template <typename E1> void inorder(BSTNode<E1> *root) {
  if (root == NULL)
    return;           // Nothing to visit
  if (root->isLeaf()) // Do leaf node
    cout << "Leaf: " << root->element() << endl;
  else { // Do internal node
    inorder(root->left());
    cout << "Internal: " << root->element()
         << endl; // We access root in between
    inorder(root->right());
  }
}

// inorder traversal
// I did this solely for rectangle class as i haven't overloaded
// << operator in the original so it was breaking; notice the use of
// .area(). I was lasy to do the overloading. But in your case please
// add << overload to your class definition
template <typename E1> void inorder2(BSTNode<E1> *root) {
  if (root == NULL)
    return;           // Nothing to visit
  if (root->isLeaf()) // Do leaf node
    cout << "Leaf: " << root->element().area() << endl;
  else { // Do internal node
    inorder2(root->left());
    cout << "Internal: " << root->element().area()
         << endl; // We access root in between
    inorder2(root->right());
  }
}


/////////////////////////////////////////
// SOLUTION QUESTION 15 - FINAL REVIEW //
/////////////////////////////////////////

template <typename E1> void descending_inorder(BSTNode<E1> *root) {
  if (root == NULL)
    return;           // Nothing to visit
  if (root->isLeaf()) // Do leaf node
    cout << root->element() << endl;
  else { // Do internal node
    descending_inorder(root->right());
    cout << root->element() << endl;
    descending_inorder(root->left());
  }
}


// inorder traversal
template <typename E1> void descending_inorder2(BSTNode<E1> *root) {
  if (root == NULL)
    return;           // Nothing to visit
  if (root->isLeaf()) // Do leaf node
    cout << "Leaf: " << root->element().area() << endl;
  else { // Do internal node
    descending_inorder2(root->right());
    cout << "Internal: " << root->element().area() << ")" << endl;
    descending_inorder2(root->left());
  }
}




//////////////////////////
// SOLUTION QUESTION 18 //
//////////////////////////
/**
 * Traverses down the left side and prints all nodes (does not print inner nodes on the left only outer)
 * @param root root of the binary search tree
 *
 * Time complexity: 
 * In the worst case the last node could be at the deepest level, 
 * thus time complexity in terms of height is O(h), where h is the height of the tree
 * In the best case, there is only a single node, thus best case is O(1)
 */
template <typename E1> void printLeft(BSTNode<E1> *root) {
    if (root == NULL) return;
    cout << root->element() << "\n"; // Print node value
    printLeft(root->left()); // Keep traversing left to print left side
}


/**
 * Traverses down the right side and prints all nodes (does not print inner nodes on the right only outer)
 * @param root root of the binary search tree
 *
 * Time complexity: 
 * In the worst case the last node could be at the deepest level, 
 * thus worst case time complexity in terms of height is O(h), where h is the height of the tree
 * In the best case, there is only a single node, thus best case is O(1)
 */
template <typename E1> void printRight(BSTNode<E1> *root) {
    if (root == NULL) return;
    cout << root->element() << "\n"; // Print node value
    printRight(root->right()); // Keep traversing right to print right side
}


/**
 * Traverses the whole tree to find all the leafs and prints the leafs
 * @param root root of the binary search tree
 *
 * Time complexity: 
 * In the worst case every node must be visited, thus the worst case
 * time complexity is O(n), where n is the number of nodes.
 * In the best case, there is only a single node, thus best case is O(1)
 */
template <typename E1> void printLeaves(BSTNode<E1> *root) {
    if (root == NULL) return;
    if (root->isLeaf()) cout << root->element() << endl; // Print node value
    printLeaves(root->left()); // Keep traversing left
    printLeaves(root->right()); // Keep traversing right
}




//////////////////////////
// SOLUTION QUESTION 19 //
//////////////////////////


/**
 * Takes binary tree and using inorder traversal prints each nodes value
 * Helper method for BTSort
 * @param root pointer to the root node
 */
template <typename E1> void printAscending(BSTNode<E1> *root) {
  if (root == NULL) return; // Nothing to visit
  if (root->isLeaf()) cout << root->element() << endl; // Please leaf
  else { // Do internal node
    printAscending(root->left());
    cout << root->element() << endl; // Print node
    printAscending(root->right());
  }
}

/**
 * Takes an array of integers and prints out the values in a sorted (ascending) order
 * @param unsortedArray an array of integers
 * @param size          length of the unsorted array
 *
 * TIME COMPLEXITY: 
 * Inserting into a BST if the given array was in reverse order O(n^2)
 * Traversing the tree: O(n)
 *
 * Worst case time complexity O(n^2)
 *
 */
template <typename E1> void BTSort(int unsortedArray[], int size) {
  BST<int> newBST;

  // Build a Binary Search Tree using the unsorted array
  for (int i = 0; i < size; i++) {
    newBST.insert(unsortedArray[i]);
  }

  // Traverse the newly create binary search tree using inorder traversal & print node value
  printAscending<int>(newBST.get_root());
}




//////////////////////////
// SOLUTION QUESTION 20 //
//////////////////////////

/**
 * Returns true if given tree is BST
 * @param  root pointer to the root node
 * @param  min  min value for the range that the current node value should be between
 * @param  max  max value for that range that the current value should be between
 * @return      true if a BST otherwise return false
 *
 * TIME COMPLEXITY: 
 * Worst case scenario Traversing the tree: O(n) because in the worst case each node might 
 * be visited
 *
 */
template <typename E1> bool isBST(BSTNode<E1> *root, int min = INT_MIN, int max = INT_MAX) {
  if (root == NULL) return true;
  // if value of current node is outside the min & max range return false;
  if (root->element() < min || root->element() > max) return false;
  // Recursively call isBST on each node with the correct range to check against
  return isBST(root->left(), min, root->element()) && isBST(root->right(), root->element(), max);
}



//////////////////////////
// SOLUTION QUESTION 21 //
//////////////////////////

/**
 * Helper for countDuplicatesInBST - Checks for duplicates in a BST against a set 
 * and updates the variable count, which is returned by countDuplicatesInBST
 * @param root       the root node of a binary tree
 * @param count      the count of duplicates found in binary tree, to be returned by countDuplicatesInBST 
 * @param setToCheck the set containing values that have been seen
 */
template <typename E1> void traverseAndAddToSet(BSTNode<E1> *root, int &count, set<int> &setToCheck) {
  if (root == NULL) return;
  set<int>::iterator it = setToCheck.find(root->element());
  if (it != setToCheck.end()) { count++; } 
  else { setToCheck.insert(root->element()); }

  if (root->isLeaf()) root->element();
  else {
    traverseAndAddToSet(root->left(), count, setToCheck);
    traverseAndAddToSet(root->right(), count, setToCheck);
  }
}


/**
 * Counts the number of duplicates in a binary tree
 * Uses the helper function traverseAndAddToSet
 * @param  root root node of a binary tree
 * @return      the number of duplicates in a given binary tree
 */
template <typename E1> int countDuplicatesInBST(BSTNode<E1> *root) {
  int count = 0;
  set<int> setOfNumbers;

  traverseAndAddToSet(root, count, setOfNumbers);
  return count;  
}






/////////////////////
// Rectangle Class //
/////////////////////

// Class definition for a Rectangle to test with user defined type
class Rectangle {

private:
  double length;
  double width;

public:
  Rectangle(double length = 0, double width = 0) // constructor
  {
    this->length = length;
    this->width = width;
  }
  ~Rectangle(){}; // Destructor

  // gettors
  double get_length() { return length; }

  double get_width() { return width; }

  // Settors

  void set_length(double new_length) { this->length = new_length; }

  void set_width(double new_width) { this->width = new_width; }

  // Area
  double area() { return length * width; }
  double perimeter() { return 2 * (length + width); }
  // Overloading <, >, <=, >=, == operators so that I can compare
  // two rectangles
  // here I am going to use area to distinguish two rectangles
  bool friend operator<(Rectangle &rect1, Rectangle &rect2) {
    return rect1.area() < rect2.area(); // keep the same order
  }
  bool friend operator==(Rectangle &rect1, Rectangle &rect2) {
    return rect1.area() == rect2.area(); // keep the same order
  }
  // Once < and == are done I can semply use them for the rest
  inline bool friend operator>(Rectangle &rect1, Rectangle &rect2) {
    return rect2 < rect1;
  }
  inline bool friend operator<=(Rectangle &rect1, Rectangle &rect2) {
    return !(rect1 > rect2);
  }
  inline bool friend operator>=(Rectangle &rect1, Rectangle &rect2) {
    return !(rect1 < rect2);
  }
  inline bool friend operator!=(Rectangle &rect1, Rectangle &rect2) {
    return !(rect1 == rect2);
  }
};



///////////////////
// MAIN FUNCTION //
///////////////////



#include <algorithm> // I used this for random_shuffle
// However it is removed in c++17. So please use std::shuffle instead

int main(int argc, char *argv[]) {
  // int values[15] = {1, 2, 3, 3, 4, 4, 5, 6, 7, 7, 7, 8, 9, 10, 10};

  // srand(time(0));
  // // Shuffling randomly.
  // // Otherwise if we follow sequential order of the array and we gonna get
  // // a skewed BST
  // random_shuffle(begin(values), end(values)); // This is removed in c++17.
  // // So please use std::shuffle instead

  // // Inserting randomly shuffled above array taking the index(unique)
  // // as keys
  // cout << "printing the shuffled array" << endl;

  // for (int i = 0; i <= 15; i++) {
  //   cout << values[i] << endl; // key is i and value is input[i]
  // }

  // BST<int> testBst;
  // // Inserting randomly shuffled above array taking the index(unique)
  // // as keys
  // for (int i = 0; i <= 15; i++) {
  //   testBst.insert(values[i]); // key is i and value is input[i]
  // }

  // testBst.print_value();

  // cout << endl;

  // preorder<int>(testBst.get_root());
  // cout << endl;
  // postorder<int>(testBst.get_root());
  // cout << endl;
  // inorder<int>(testBst.get_root());

  // char chval[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I'};

  // srand(time(0));
  // random_shuffle(begin(chval), end(chval)); // Shuffling randomly.
  // // Otherwise if we follow sequential order of the array and we gonna get
  // // a skewed BST
  // cout << endl;
  // cout << endl;

  // cout << "printing the insert order" << endl;

  // for (int i = 0; i <= 8; i++) {
  //   cout << chval[i] << endl; // key is i and value is input[i]
  // }
  // cout << endl;

  // BST<char> charBst; // Initialization

  // for (int i = 0; i <= 8; i++)  { // insert shuffled array
  //   charBst.insert(chval[i]); // key is i and value is input[i]
  // }

  // charBst.print_value(); // Printing the BST

  // cout << endl;

  // cout << "printing the preorder traversal visits of nodes" << endl;

  // preorder<char>(charBst.get_root());
  // cout << endl;
  // cout << "printing the postorder traversal visits of nodes" << endl;

  // postorder<char>(charBst.get_root());
  // cout << endl;
  // cout << "printing the inorder traversal visits of nodes" << endl;

  // inorder<char>(charBst.get_root());
  // cout << endl;

  // Rectangle R1(10, 10);
  // Rectangle R2(8, 10);
  // Rectangle R3(6, 20);
  // Rectangle R4(30, 30);
  // Rectangle R5(5, 5);
  // Rectangle R6(40, 20);

  // Rectangle bunch_of_rectangles[] = {R1, R2, R3, R4, R5, R6};

  // BST<Rectangle> rectBst;     // Initialization
  // for (int i = 0; i < 6; i++)  { // insert the array of rectangles
  //   rectBst.insert2(bunch_of_rectangles[i]); //
  // }

  // cout << "printing the inorder traversal visits of nodes" << endl;

  // descending_inorder2<Rectangle>(
  //     rectBst.get_root()); // in order traversal see if the areas are orderd



////////////////////////////////////////////////////////////////
// >>>>>>>> TESTING FOR THE ASSIGNMENT QUESTONS >>>>>>>>>>    //
////////////////////////////////////////////////////////////////

  cout << endl;
  cout << "====================================================" << endl;
  cout << "   BEGIN TESTING FOR THE ASSIGNMENT QUESTONS   " << endl;
    cout << "====================================================" << endl;



  /////////////////////////
  // TESTING QUESTION 18 //
  /////////////////////////
  cout << endl;
  cout << "====================================================" << endl;
  cout << "   TESTING FOR printLeft, printRight, printLeaves   " << endl;
  cout << "====================================================" << endl << endl;
  
  int unsortedTestArray[] = {4, 1, 5, 2, 9, 8, 7, 0, 3, 6};
  BST<int> myTestBST;


  // Generate a BST from the unsorted array
  for (int j = 0; j < 10; j++) {
    myTestBST.insert(unsortedTestArray[j]); // key is i and value is input[i]
  }

  /*
  
  Shape of BST build from unsortedTestArray

           4
        /      \
       1        5 
      / \        \ 
    0    2        9
          \      /
           3    8
               /
              7
             /
            6  

  Leafs: 0, 3, 6

  */
 


  cout << ">>>>>>>>> printLeft - should print 4, 1, 0 >>>>>>>>>" << endl;
  printLeft<int>(myTestBST.get_root());

  cout << ">>>>>>>>> printRight - should print 4, 5, 9 >>>>>>>>>" << endl;
  printRight<int>(myTestBST.get_root());
  
  cout << ">>>>>>>>> printLeaves - should print 0, 3, 6 >>>>>>>>>" << endl;
  printLeaves<int>(myTestBST.get_root());




  /////////////////////////
  // TESTING QUESTION 19 //
  /////////////////////////
  cout << endl;
  cout << "======================================" << endl;
  cout << "          TESTING FOR BTSort          " << endl;
  cout << "======================================" << endl << endl;
  cout << ">>>>>>>>> should print 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 >>>>>>>>>" << endl;
  BTSort<int>(unsortedTestArray, 10);

  cout << ">>>>>>>>> should print 9, 8, 7, 6, 5, 4, 3, 2, 1, 0 >>>>>>>>>" << endl;
  descending_inorder<int>(myTestBST.get_root());



  /////////////////////////
  // TESTING QUESTION 20 //
  /////////////////////////
  cout << endl;
  cout << "=====================================" << endl;
  cout << "          TESTING FOR isBST          " << endl;
  cout << "=====================================" << endl << endl;


/*
           10
        /      \
       0       25 
      / \      / \ 
    -1  21    16  32
*/

  // Create a tree that is not a BST to test isBST function
  BSTNode<int> notBST;
  notBST.setElement(10);
  
  BSTNode<int> leftChild;
  leftChild.setElement(0);
  notBST.setLeft(&leftChild);

  BSTNode<int> leftLeftChild;
  leftLeftChild.setElement(-1);
  leftChild.setLeft(&leftLeftChild);

  BSTNode<int> leftRightChild;
  leftRightChild.setElement(21);
  leftChild.setLeft(&leftRightChild);


  BSTNode<int> rightChild;
  rightChild.setElement(25);
  notBST.setRight(&rightChild);

  BSTNode<int> rightLeftChild;
  rightLeftChild.setElement(-1);
  rightChild.setLeft(&rightLeftChild);

  BSTNode<int> rightRightChild;
  rightRightChild.setElement(21);
  rightChild.setRight(&rightRightChild);


  cout << ">>>>>>>>> isBST -- should return true >>>>>>>>>" << endl;
  cout << isBST<int>(myTestBST.get_root()) << endl;  // Should return true
  cout << ">>>>>>>>> isBST -- should return false >>>>>>>>>" << endl;
  cout << isBST<int>(&notBST) << endl;   // Should return false


  /////////////////////////
  // TESTING QUESTION 21 //
  /////////////////////////
  cout << endl;
  cout << "================================================" << endl;
  cout << "          TESTING FOR COUNT DUPLICATES          " << endl;
  cout << "================================================" << endl << endl;

  cout << ">>>>>>>>> Count Duplicates in a BST  -- Should return 0 >>>>>>>>>" << endl;
  cout << countDuplicatesInBST<int>(myTestBST.get_root()) << endl;  // Should return true


  // Using the dummy tree on lines 730 and adding in 2 duplicate values
  BSTNode<int> rightRightRightChild;
  rightRightRightChild.setElement(0);
  rightRightChild.setRight(&rightRightRightChild);


  BSTNode<int> rightRightLeftChild;
  rightRightLeftChild.setElement(21);
  rightRightChild.setRight(&rightRightLeftChild);

  cout << ">>>>>>>>> Count Duplicates in a BST -- Should return 2 >>>>>>>>>" << endl;
  cout << countDuplicatesInBST<int>(&notBST) << endl;  // Should return false


  return 0;
}

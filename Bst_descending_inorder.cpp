// Binary Search Tree imlementation for any nonw-dictionary
// data type. This should work with any data type that overloades
// >, = or < operators

// This is eveything in a sigle file. If you want it as seperate
// please put every major comphonent in seperate header file

#include <iostream>
using namespace std;




    //////////////////////////////////////
    // ABSTRACT CLASS: Binary Tree Node //
    //////////////////////////////////////

template <typename E> class BinNode {
public:
  virtual ~BinNode() {} // Base destructor  
  virtual E& element() = 0; // Return the node’s value
  virtual void setElement(const E&) = 0; // Set the node’s value
  virtual BinNode* left() const = 0; // Return the node’s left child
  virtual void setLeft(BinNode*) = 0; // Set the node’s left child
  virtual BinNode* right() const = 0; // Return the node’s right child
  virtual void setRight(BinNode*) = 0; // Set the node’s right child
  virtual bool isLeaf() = 0; // Return true if the node is a leaf, false otherwise
}; 

// End of class BinNode


//////////////////////////////////////
// IMPLEMENTATION: Binary Tree Node //
//////////////////////////////////////
template <typename E>
class BSTNode : public BinNode<E> {
private:
  E it; // The node’s value
  BSTNode* lc;  // Pointer to left child
  BSTNode* rc; // Pointer to right child
  
public:
  // Two constructors -- with and without initial values
  BSTNode() { lc = rc = NULL; } // set both nodes to null
  BSTNode(E e, BSTNode* l =NULL, BSTNode* r =NULL)
  { it = e; lc = l; rc = r; }
  ~BSTNode() {}

  // Destructor
  // Functions to set and return the value and key
  E& element() { return it; }
  void setElement(const E& e) { it = e; }

  // Functions to set and return the children
  inline BSTNode* left() const { return lc; }
  void setLeft(BinNode<E>* b) { lc = (BSTNode*)b; }
  inline BSTNode* right() const { return rc; }
  void setRight(BinNode<E>* b) { rc = (BSTNode*)b; }
  // Return true if it is a leaf, false otherwise
  bool isLeaf() { return (lc == NULL) && (rc == NULL); }
}; // End of class BSTNode


// This has to be a class template so that we write one class for
// all the types and to enforce compile time type safety
// this is equivalent of Java's generics
template <typename E>
class BST{

private:
  BSTNode<E>* root; // Root of the BST
  int nodecount; // Number of nodes in the BST

// Private "helper" functions

// Helper function for clear implementation taken from section 5.4
  template <typename E1>
  void clearhelp(BSTNode<E1>* root) {
    if (root == NULL) return;
    clearhelp(root->left());
    clearhelp(root->right());
    delete root;
  }

  // Helper function for insert implementation taken from section 5.4
  template <typename E1>
  BSTNode<E1>* inserthelp(BSTNode<E1>* root, const E1& it) {
    if (root == NULL) // Empty tree: create node
      return new BSTNode<E1>(it, NULL, NULL);
    if (it < root->element())
      root->setLeft(inserthelp(root->left(), it));
    else root->setRight(inserthelp(root->right(), it));
    return root; // Return tree with node inserted
  }

  // Helper function for insert implementation taken from section 5.4
  // This was also for Rectagle. C++ doesn't allow passing an object
  // as const and accessing its member unless the members too are
  // const. So I simply removed const
  template <typename E1>
  BSTNode<E1>* inserthelp2(BSTNode<E1>* root, E1& it) {
    if (root == NULL) // Empty tree: create node
      return new BSTNode<E1>(it, NULL, NULL);
    if (it < root->element())
      root->setLeft(inserthelp2(root->left(), it));
    else root->setRight(inserthelp2(root->right(), it));
    return root; // Return tree with node inserted
  }

  // Helper function for deletemin implementation taken from section 5.4
  template <typename E1>
  BSTNode<E1>* deletemin(BSTNode<E1>* rt) {
    if (rt->left() == NULL) // Found min
      return rt->right();
    else {
        // Continue left
        rt->setLeft(deletemin(rt->left()));
        return rt;
      }
  }

  // Helper function for getmin implementation taken from section 5.4
  template <typename E1>
  BSTNode<E1>* getmin(BSTNode<E1>* rt) {
    if (rt->left() == NULL)
      return rt;
    else return getmin(rt->left());
  }

  // Helper function for remove implementation taken from section 5.4
  // Remove a node with element e
  // Return: The tree with the node removed
  template <typename E1>
  BSTNode<E1>* removehelp(BSTNode<E1>* rt, const E1& e) {
    if (rt == NULL) return NULL;
    // k is not in tree
    else if (e < rt->element())
      rt->setLeft(removehelp(rt->left(), e));
    else if (e > rt->element())
      rt->setRight(removehelp(rt->right(), e));
    else { // Found: remove it
        BSTNode<E1>* temp = rt;
        if (rt->left() == NULL) { // Only a right child
            rt = rt->right(); // so point to right
            delete temp;
          }
        else if (rt->right() == NULL) { // Only a left child
            rt = rt->left(); // so point to left
            delete temp;
          }
        else { // Both children are non-empty
            BSTNode<E1>* temp = getmin(rt->right());
            rt->setElement(temp->element());
            rt->setRight(deletemin(rt->right()));
            delete temp;
          }
      }
    return rt;
  }

  // Helper function for find implementation taken from section 5.4
  template <typename E1>
  E findhelp(BSTNode<E1>* root, const E1& e) const {
    if (root == NULL) return NULL; // Empty tree
    if (e < root->value())
      return findhelp(root->left(), e); // Check left
    else if (e > root->value())
      return findhelp(root->right(), e); // Check right
    else return root->element(); // Found it
  }

  // Helper function for print implementation taken from section 5.4
  template <typename Key1, typename E1>
  void printhelp(BSTNode<E1>* root, int level) const {
    if (root == NULL) return; // Empty tree
    printhelp(root->left(), level+1); // Do left subtree
    for (int i=0; i<level; i++) // Indent to level
      cout << "  ";
    cout << root->value() << "\n"; // Print node value
    printhelp(root->right(), level+1); // Do right subtree
  }

// Helper function for print implementation taken from section 5.4
  template <typename E1>
  void printhelp2(BSTNode<E1>* root, int level) const {
    if (root == NULL) return; // Empty tree
    printhelp2(root->left(), level+1); // Do left subtree
    for (int i=0; i<level; i++){ // Indent to level
      cout << "           "  ;
      }
    cout << root->element() <<"\n"; // Print node value
    printhelp2(root->right(), level+1); // Do right subtree
  }

  // Helper function for print implementation taken from section 5.4
    template <typename E1>
    void printhelp3(BSTNode<E1>* root, int level) const {
      if (root == NULL) return; // Empty tree
      printhelp3(root->left(), level+1); // Do left subtree
      for (int i=0; i<level; i++) // Indent to level
        cout << "       ";
      cout << root->element() << "\n"; // Print node value
      printhelp3(root->right(), level+1); // Do right subtree
    }

    // Helper function to return root
    // I added this as all 3 traversal methods require access to root
    // so we need a getter for root
    template <typename E11>
    BSTNode<E11>* getroot(BSTNode<E11>* rt) {
      return rt;
    }

public:
  BST() { root = NULL; nodecount = 0; }// Constructor
  ~BST() { clearhelp(root); }// Destructor
  void clear() // Reinitialize tree
  { clearhelp(root); root = NULL; nodecount = 0; }

  // Insert a record into the tree.
  // e The record to insert.
  void insert(const E& e) {
    root = inserthelp(root, e);
    nodecount++;
  }

  // This was also for Rectagle. C++ doesn't allow passing an object
  // as const and accessing its member unless the members too are
  // const. So I simply removed const
  void insert2(E& e) {
    root = inserthelp2(root, e);
    nodecount++;
  }
  // Remove a record from the tree.
  // e record to remove.
  // Return: The record removed, or NULL if there is none.
  E remove(const E& e) {
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
      }
    else return NULL;
  }
  // Return Record element e, NULL if none exist.
  // e the element value to find. */
  // Return some record matching "e".
  // Return true if such exists, false otherwise. If
  // multiple records match "e", return an arbitrary one.
  E find(const E& e) const { return findhelp(root, e); }
  // Return the number of records in the dictionary.
  int size() { return nodecount; }
  void print() const { // Print the contents of the BST
    if (root == NULL) cout << "The BST is empty.\n";
    else printhelp(root, 0);
  }

  void print_value() const { // Print the contents of the BST
    if (root == NULL) cout << "The BST is empty.\n";
    else printhelp2(root, 0);
  }

// I added this as all 3 traversal methods require access to root
// so we need a getter for root
   BSTNode<E>* get_root() const {
      return root;
  }
}; // End of BST class BST

// Implementation of three traversals. Though may be little bit tricky
// you can also incorporate these into the BST class above itself
// my thought was that an external client frequently do this independent of
// the BST. So that means they are client programs. This is probably
// the exact reason why the book also didn't do it

//preorder traversal
template <typename E1>
void preorder(BSTNode<E1>* root) {
  if (root == NULL) return; // Nothing to visit
  if (root ->isLeaf()) // Do leaf node
    cout << "Leaf: " << root->element() << endl;
  else { // Do internal nodes
      cout << "Internal: " << root->element() << endl; // We access root first
      preorder(root->left());
      preorder(root->right());
    }
}

// postorder traversal
template <typename E1>
void postorder(BSTNode<E1>* root) {
  if (root == NULL) return; // Nothing to visit
  if (root ->isLeaf()) // Do leaf node
    cout << "Leaf: " << root->element() << endl;
  else { // Do internal nodes
      postorder(root->left());
      postorder(root->right());
      cout << "Internal: " << root->element() << endl; // We access root last

    }
}

// inorder traversal
template <typename E1>
void inorder(BSTNode<E1>* root) {
  if (root == NULL) return; // Nothing to visit
  if (root ->isLeaf()) // Do leaf node
    cout << "Leaf: " << root->element() << endl;
  else { // Do internal node
      inorder(root->left());
      cout << "Internal: " << root->element() << endl; // We access root in between
      inorder(root->right());

    }
}

// inorder traversal
// I did this solely for rectangle class as i haven't overloaded
// << operator in the original so it was breaking; notice the use of
// .area(). I was lasy to do the overloading. But in your case please
// add << overload to your class definition
template <typename E1>
void inorder2(BSTNode<E1>* root) {
  if (root == NULL) return; // Nothing to visit
  if (root ->isLeaf()) // Do leaf node
    cout << "Leaf: " << root->element().area() << endl;
  else { // Do internal node
      inorder2(root->left());
      cout << "Internal: " << root->element().area() << endl; // We access root in between
      inorder2(root->right());

    }
}

// inorder traversal
template <typename E1>
void descending_inorder2(BSTNode<E1>* root) {
  if (root == NULL) return; // Nothing to visit
  if (root ->isLeaf()) // Do leaf node
    cout << "Leaf: "  << root->element().area()  << endl;
  else { // Do internal node
      descending_inorder2(root->right());
      cout << "Internal: "  << root->element().area() << ")" << endl;
      descending_inorder2(root->left());

    }
}


    /////////////////////
    // Rectangle Class //
    /////////////////////

// Class definition for a Rectangle to test with user defined type
class Rectangle{

private:
  double length;
  double width;
public:
  Rectangle(double length = 0, double width = 0)// constructor
  {
    this->length = length;
    this->width = width;
  }
  ~Rectangle(){}; // Destructor

  //gettors
  double get_length(){
    return length;
  }

  double get_width(){
    return width;
  }

  // Settors

  void set_length(double new_length){
    this->length = new_length;
  }

  void set_width(double new_width){
    this->width = new_width;
  }

  // Area
  double area(){
    return length * width;
  }
  double perimeter(){
    return 2*(length + width);
  }
  // Overloading <, >, <=, >=, == operators so that I can compare
  // two rectangles
  // here I am going to use area to distinguish two rectangles
  bool friend operator<(Rectangle& rect1, Rectangle& rect2)
  {
      return rect1.area() < rect2.area(); // keep the same order
  }
  bool friend operator==( Rectangle& rect1,  Rectangle& rect2)
  {
      return rect1.area() == rect2.area(); // keep the same order
  }
  // Once < and == are done I can semply use them for the rest
  inline bool friend operator>(Rectangle& rect1, Rectangle& rect2){ return rect2 < rect1; }
  inline bool friend operator<=(Rectangle& rect1, Rectangle& rect2){ return !(rect1 > rect2); }
  inline bool friend operator>=(Rectangle& rect1, Rectangle& rect2){ return !(rect1 < rect2); }
  inline bool friend operator!=(Rectangle& rect1, Rectangle& rect2){ return !(rect1 == rect2); }

};


#include <algorithm> // I used this for random_shuffle
// However it is removed in c++17. So please use std::shuffle instead

int main(int argc, char *argv[]){
  int values[15] = {1, 2, 3, 3, 4, 4, 5, 6, 7, 7, 7, 8, 9, 10, 10};

  srand(time(0));
  // Shuffling randomly.
  // Otherwise if we follow sequential order of the array and we gonna get
  // a skewed BST
  random_shuffle(begin(values), end(values));// This is removed in c++17.
// So please use std::shuffle instead

  // Inserting randomly shuffled above array taking the index(unique)
  // as keys
  cout << "printing the shuffled array" << endl;

  for (int i = 0; i <= 15; i++)
    {
      cout << values[i]  << endl; // key is i and value is input[i]
    }

  BST <int> testBst;
  // Inserting randomly shuffled above array taking the index(unique)
  // as keys
  for (int i = 0; i <= 15; i++)
    {
      testBst.insert(values[i] ); // key is i and value is input[i]
    }

  testBst.print_value();

  cout <<  endl;

  preorder<int>(testBst.get_root());
  cout <<  endl;
  postorder<int>(testBst.get_root());
  cout <<  endl;
  inorder<int>(testBst.get_root());

  char chval[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I'};

  srand(time(0));
  random_shuffle(begin(chval), end(chval)); // Shuffling randomly.
  // Otherwise if we follow sequential order of the array and we gonna get
  // a skewed BST
  cout <<  endl;
  cout <<  endl;

  cout << "printing the insert order" << endl;

  for (int i = 0; i <= 8; i++)
    {
      cout <<  chval[i] << endl; // key is i and value is input[i]
    }
  cout <<  endl;

  BST <char> charBst; // Initialization

  for (int i = 0; i <= 8; i++) // insert shuffled array
    {
      charBst.insert(chval[i] ); // key is i and value is input[i]
    }

  charBst.print_value(); // Printing the BST

  cout <<  endl;

  cout << "printing the preorder traversal visits of nodes" << endl;

  preorder<char>(charBst.get_root());
  cout <<  endl;
  cout << "printing the postorder traversal visits of nodes" << endl;

  postorder<char>(charBst.get_root());
  cout <<  endl;
  cout << "printing the inorder traversal visits of nodes" << endl;

  inorder<char>(charBst.get_root());
  cout <<  endl;

  Rectangle R1(10, 10);
  Rectangle R2(8, 10);
  Rectangle R3(6, 20);
  Rectangle R4(30, 30);
  Rectangle R5(5, 5);
  Rectangle R6(40, 20);

  Rectangle bunch_of_rectangles[] = {R1, R2, R3, R4, R5, R6};

  BST <Rectangle> rectBst; // Initialization
  for (int i = 0; i < 6; i++) // insert the array of rectangles
    {
      rectBst.insert2(bunch_of_rectangles[i] ); //
    }

  cout << "printing the inorder traversal visits of nodes" << endl;

  descending_inorder2<Rectangle>(rectBst.get_root()); // in order traversal see if the areas are orderd


  return 0;
}

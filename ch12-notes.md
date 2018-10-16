# Ch 12 | Binary Trees | 10.14.18

## 12.1

### Tree structure applications
1. efficient access
2. efficient update

### Binary Tree applications
1. searching
2. prioritizing jobs
3. describing mathematical expressions & syntactic elements of programs
4. organizing info needed to drive data compression algorithms

## 12.2
### Binary Tree

* made up of finite set of nodes
* set is either empty or made of
  * root
  * disjoint subtrees
    * right
    * left
    * disjoint means that they right & left have no nodes in common
* roots of the subtrees are children of the root
* there is an edge from a node (parent) to each of its children
* path
  * sequence: n1, n2, ... nk, where where ni is the parent of ni + 1 & 1 <= i < k
  * this is called path from n1 to nk
  * the __length of a path__ is __k - 1__
  * if there is a path from node R to M, then
    * R is the ancestor of M
    * M is a descendant of R
* root is the ancestor of all nodes
* all nodes in a tree are descendants of the root
* __depth of a node__ M is the __length of the path from root__ to M
  * the __height of a tree__ is the __depth of the deepest node__
  * all nodes of depth d are level d
  * root is the only node at level 0 and its depth is 0
* __leaf node__ is any node with 2 empty children
* __internal node__ is any node that has at least 1 empty child
* Other types of Binary Trees
  * Full Binary Tree
    * is either
      * an internal node with exactly 2 non-empty children, or
      * a leaf node, i.e. node with 2 empty children
    * eg: Huffman coding tree
    * Do any internal nodes have only one child? If so, the tree is not full.
  * Complete Binary Tree
    * has a restricted shape obtained by starting at the root and filling
    the tree by levels from left to right
    * eg: Heap data structure
    * A complete tree fills in nodes level by level, with the bottom level filled in from left to right.
  * To remember the difference "Complete" is a wider word than "full", and complete binary trees tend to be wider than full binary trees because each level of a complete binary tree is as wide as possible.

## 12.3 - BT as a Recursive Data Structure

* a __recursive data structure__ is a ds that is partially composed of smaller or simpler instances of the same ds, eg:
  * linked lists
    * recursive ds because
      * either an empty list, or
      * a node followed by a list
  * binary trees
    * recursive ds because
      * either an empty tree, or
      * a node pointing to 2 binary trees
* You don't need to think about the details of recursion, just accept that your friends (recursive call) will return back to you the correct answer

## 12.4 - Full Binary Tree Theorem

* To analyze space requirements for a binary tree implementation, it is useful to know:
  * the min & max fraction of the nodes that are leaves in a tree containing n internal nodes
    * all full binary trees with n internal nodes have the same number of leaves
    * this fact allows us to compute the space requirements for a full binary tree implementation whose leaves require a different amount of space from its internal nodes
    * Theorem: The # of leaves in a non-empty full binary tree is 1 more than the # of internal nodes
  * how many empty subtrees a tree contains
    * in any binary tree (full or not), the # of empty subtrees is 1 more than the # of nodes in the tree

## 12.5 - Binary Tree Traversal

* traversal: process of visiting all of the nodes in some order
* __enumeration__ of a tree's nodes: any traversal that lists every node in a tree exactly once
* Pre-order traversal
  * visit node before visiting children
* Post-order traversal
  * visit node after visiting children
  * usecase: return all nodes in a tree to free store
    * we would like to delete children of node before deleting the node itself
* In-order traversal
  * first visit left child then visit the node, then visit right child
  * usecase: Binary search tree uses this to print all nodes in ascending order

#include <iostream>
#include <string>
#include "BSTNode.h"
using namespace std;

class BSTTree{
  BSTNode* root;

 public:
  BSTTree();
  ~BSTTree();
  BSTNode* getRoot();                   // return root
  BSTNode* find(string ss);             // search ss value in the BST tree. if find, return the BSTNode pointer to the node; otherwise, return nullptr
  int height(BSTNode* node);            // return the height of the subtree rooted at node
  bool insert(string ss, string na);     // insert one pair of SSN and name to the BST
  BSTNode* maxOfSubtree(BSTNode* node);    // find the node with largest value in the subtree
  BSTNode* minOfSubtree(BSTNode* node);    // find the node with smallest value in the subtree
  BSTNode* succ(BSTNode* node);            // find the successor of a given node
  BSTNode* pred(BSTNode* node);            // find the predecessor of a given node
  bool  deleteNode(string ss);             // delete the node containing ss, return true if successful; otherwise, return false
  void enumerate(BSTNode * start, BSTNode * end); // print out the values between start node and end node
  void print(BSTNode* x, int indent);
  void print();
  void levelOrder();
};

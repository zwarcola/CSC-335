#include <iostream>
#include <string>
using namespace std;

struct BSTNode{
  string ssn;
  string name;
  BSTNode *left;
  BSTNode *right;
  BSTNode *parent;
  int height;
    
  BSTNode(string ss, string na);
};

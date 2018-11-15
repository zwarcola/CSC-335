#include <iostream>
#include <string>
#include "BSTNode.h"
using namespace std;

BSTNode::BSTNode(string ss, string na){
  ssn = ss;
  name = na;
  height = 0;
  left = nullptr;
  right = nullptr;
  parent = nullptr;
}

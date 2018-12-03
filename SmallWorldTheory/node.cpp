#include <iostream>
#include "node.h"

using namespace std;

node::node(int val){ //value is initialized by user and next is initially set to nullptr
    value = val;
    next = nullptr;
}

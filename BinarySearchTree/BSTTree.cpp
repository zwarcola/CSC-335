#include <iostream>
#include <string>
#include "BSTTree.h"
#include <iomanip>
#include <queue>
using namespace std;

BSTTree::BSTTree(){
  root = nullptr;
}

BSTTree::~BSTTree(){

}

BSTNode* BSTTree::getRoot(){
  return root;
}

// search value ss in the BST tree
BSTNode* BSTTree::find(string ss){
    if (root == nullptr) {
        return root;
    }

    BSTNode* node = root;

    while (node != nullptr){
        if (ss.compare(node->ssn) == 0){ //for .compare(), result will be 0 if ss and node -> ssn are the same
            return node;
        }
        if (ss.compare(node->ssn) < 0){ //result will b less than 0 if ss is less than node -> ssn
            node = node->left;
        }
        else{
            node = node->right; //otherwise we can assume ss is larger than node -> ssn
        }
    }
    return nullptr; //if the tree exists but the node cannot be found, return null
}

// return the height of the subtree rooted at node
// if subtree is empty, height is -1
// if subtree has one node, height is 0
int BSTTree::height(BSTNode* node){
    if(node == nullptr){
        return -1;
    }
     queue<BSTNode *> q; //create a queue
     q.push(root); //push the root
     int height = 0;
     while (1){
       int counter = q.size(); //the size of the queue is the number of nodes at the current height levels
       if (counter == 0){
           return height - 1;
       }
       height++; //increase height value by 1
       while (counter > 0){ //move on to next level by removeing nodes from this level and queuing all ndoes of the next level
           BSTNode *node = q.front();
           q.pop();
           if (node->left != NULL){
               q.push(node->left);
           }
           if (node->right != NULL){
               q.push(node->right);
           }
           counter--; //decrease counter value by 1
       }
     }
}

// insert a new node with (ss, na) to the BST tree
bool BSTTree::insert(string ss, string na){

    int insertionCounter;
    BSTNode* n = new BSTNode(ss, na);

    if(find(ss)){  //if the ssn already exists, don't do anything
      return false;
    }
    //do insertion
    if(root == nullptr){ //if there is no tree, n becomes the root
      root = n;
    }
    else{
        BSTNode* current = root;
        BSTNode* parentPTR = nullptr;
        while(current != nullptr){    //while there is a node to check
            if(current -> ssn < ss){  //if the ss is larger, go to the right
              parentPTR = current;
              current = current -> right;
            }
            else{                    //if the ss is smaller, go to the left
              parentPTR = current;
              current = current -> left;
            }
        }                           //exit while loop when both children are null

        if(parentPTR -> ssn < ss){  //once we find where we need to inset it, check to see if it will be left or right leaf and insert
          parentPTR -> right = n;
          n -> parent = parentPTR;
        }
        else{
          parentPTR -> left = n;
          n -> parent = parentPTR;
        }
    }
    insertionCounter++;
    return true;
}

// return the tree node with max ssn value
// parameter "node" is the root of the subtree in question
BSTNode* BSTTree::maxOfSubtree(BSTNode* node){  //maximum value will be the node furthest to the right
    if(node == nullptr){
      return nullptr;
    }
    while(node -> right != nullptr){
      node = node -> right;
    }
    return node;
}

// return the tree node with min ssn value
// parameter "node" is the root of the subtree in question
BSTNode* BSTTree::minOfSubtree(BSTNode* node){    //minimum value will be the node furthest to the left
    if(node == NULL){
      return NULL;
    }
    while(node -> left != NULL){
      node = node -> left;
    }
    return node;
}

// return the successor of a given node
//successor is the smallest value that is larger than the input node
BSTNode* BSTTree::succ(BSTNode* node){
    BSTNode* curr = node;
    if(node == nullptr){ //if the node is null, return null
      return nullptr;
    }
    else if(node -> right != nullptr){ //if the node has a right child, succ will be the min of that subtree
        return minOfSubtree(node -> right);
    }
    else if(node -> right == nullptr){ //if the node doesn't have a right child,
      while(node != root){ //while the node doesn't reach the root
        curr = node;
        node = node -> parent; //make the node equal to it's parent
        if(node -> left == curr){ //if the node has a left child, it is the succ
          return node;
        }
      }
      return nullptr; //otherwise there is no succ
    }
    else{ //if all else fails return nullptr
      return nullptr;
    }
}

// return the predecessor of a given node
//predecessor is the largest value that is smaller than the input node
BSTNode* BSTTree::pred(BSTNode* node){

    BSTNode* curr = node;
    if(node == nullptr){ //if the node is null, return null
      return nullptr;
    }
    else if(node -> left != nullptr){ //if the node has a left child, pred will be the max of that subtree
        return maxOfSubtree(node -> left);
    }
    else if(node -> left == nullptr){ //if the node doesn't have a left child
      while(node != root){ //while the node doesn't reach the root
        curr = node;
        node = node -> parent; //make the node equal to it's parent
        if(node -> right == curr){ //if the node has a right child, it is the pred
          return node;
        }
      }
      return nullptr; //otherwise there is no pred
    }
    else{ //if all else fails return nullptr
      return nullptr;
    }
}

// delete the node containing SSN value ss
// consider all possible scenarios: no child, one child, two children
bool BSTTree::deleteNode(string ss){
    // complete the method here
    if(find(ss) == nullptr){
      return false;
    }
    BSTNode* n = find(ss);
    BSTNode* current = n;
    //if the node is a leaf, we can simply delete it
    if(n -> left == nullptr & n-> right == nullptr){
      if(n -> parent -> ssn > n -> ssn){ //deleteing a left leaf
        n -> parent -> left = nullptr;
      }
      if(n -> parent -> ssn < n -> ssn){//deleting a right leaf
        n -> parent -> right = nullptr;
      }
      return true;
    }
    //if the node has only one child we can change two pointers and remove it
    if(n -> left != nullptr & n -> right == nullptr){ //one left child
      BSTNode* temp = n -> left;
      temp -> parent = n -> parent;  //connect parent pointer
      if(n -> parent -> ssn < n -> ssn){
        n -> parent -> right = temp;
      }
      else if(n -> parent -> ssn > n -> ssn){
        n -> parent -> left = temp;    //connect left pointer
      }
      n = nullptr;
      return true;
    }
    if(n -> left == nullptr & n -> right != nullptr){ //one right child
      BSTNode* temp = n -> right;
      temp -> parent = n -> parent;  //connect parent
      if(n -> parent -> ssn < n -> ssn){
        n -> parent -> right = temp;
      }
      else if(n -> parent -> ssn > n -> ssn){
        n -> parent -> left = temp;    //connect left pointer
      }
      n = nullptr;
      return true;
    }
    //if the node has 2 children, we must manipulate the tree in a more complicated way
    if(n -> left != nullptr & n -> right != nullptr){
      BSTNode* success = succ(n); //*Note: a successor will never have a left child
      if(success -> right != nullptr){ //if the successor has a right child
        success -> right -> parent  = success -> parent; //rearrange pointers accordingly
        if(success -> parent -> ssn > success -> ssn){
          success -> parent -> left =  success -> right;
        }
        else if(success -> parent -> ssn < success -> ssn){
          success -> parent -> right = success -> right;
        }
      }
      else if(success -> right == nullptr & success -> left == nullptr){ //if the successor is a leaf
        if(success -> parent -> ssn < success -> ssn){ //rearrange pointers accordingly
          success -> parent -> right = nullptr;
          success -> parent = nullptr;
        }
        else if(success -> parent -> ssn > success -> ssn){
          success -> parent -> left = nullptr;
          success -> parent = nullptr;
        }
      }
      n -> ssn = success -> ssn; //properly assign ssn and name
      n -> name = success -> name;
      success -> parent = nullptr;
      success = nullptr;
      return true;
    }
    return false;
}

// enumerate all nodes inclusively between start and end
void BSTTree::enumerate(BSTNode * start, BSTNode * end){
    if(start == nullptr | end == nullptr){ //if either of the input nodes are null
      return;
    }
    cout << "The values between " << start -> ssn << " and " << end -> ssn << " inclusive are " << endl;
    cout << start -> ssn << endl;  //print the first value
    if(start -> ssn < end -> ssn){ //if the start is smaller than the end
      while(start -> ssn != end -> ssn){
          cout << succ(start) -> ssn << endl; //print the successor of the start
          start = succ(start);                //update the start value to be it's successor
      }
    }
    else{
      while(start -> ssn != end -> ssn){ //if the start is larger than the end
          cout << pred(start) -> ssn << endl; //print the predecessor of the start
          start = pred(start);                //update the start value to be it's predecessor
      }
    }
    return;
}

void BSTTree::print(BSTNode* x, int indent){
    if(x == nullptr) return;
    if (x->right != nullptr) {
        print(x->right, indent+4);
    }

    if (indent != 0) {
        cout << std::setw(indent) << ' ';
    }

    if(x->right != nullptr){
        cout << " /\n" << std::setw(indent) << ' ';
    }

    cout << x->ssn << endl;

    if (x->left != nullptr) {
        cout << std::setw(indent) << ' ' <<" \\\n";
        print(x->left, indent+4);
    }
}

void BSTTree::print(){
    int count = 0;
    print(root, count);
}

void BSTTree::levelOrder(){
    queue<BSTNode* > q;
    int counter =0;

    if (root != nullptr) {
        q.push(root);
    }
    while (!q.empty()) {
        BSTNode* temp = q.front();
        q.pop();

        counter++;

        if(temp->left != nullptr){
            q.push(temp->left);
        }

        if (temp->right) {
            q.push(temp->right);
        }
    }
    cout << "tree size ... " << counter << endl;
}

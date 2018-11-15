#include <iostream>
#include <fstream>
#include "BSTTree.h"
#include <string>
#include <time.h>
#include <ctime>

using namespace std;

int main(int argc, char* argv[]){
    clock_t begin = clock();
    fstream  input(argv[1]);

    char action;
    string ssn, name, first, last;
    string ssn2, ssnTemp;

    BSTTree myBST;

    int iCounter = 0;
    int dCounter = 0;
    int rCounter = 0;

    ifstream file("1000.txt"); //select file to parse through
    while(!file.eof()){
      file >> action;
      if(action == 'i'){ //if we are to insert
        file >> ssn >> first >> last;
        name = first + " " + last;
        if(myBST.insert(ssn, name)){
          myBST.insert(ssn, name);
          iCounter++;
        }
      }
      else if(action == 'd'){ //if we are to delete
        file >> ssn >> first >> last;
        name = first + " " + last;
        if(myBST.deleteNode(ssn)){
          myBST.deleteNode(ssn);
          dCounter++;
        }
      }
      else if(action == 'r'){ //if we are to retreive
        file >> ssn >> first >> last;
        if(myBST.find(ssn) != nullptr){
          myBST.find(ssn);
          rCounter++;
        }
      }
      else if(action == 's'){ //if we are to finding succesor
        file >> ssn >> first >> last;
        if(myBST.succ(myBST.find(ssn)) == nullptr){ //if there is no successor
          continue;
        }
        else{ //if there is a successor, print it as normal
          ssnTemp = myBST.succ(myBST.find(ssn)) -> ssn;
          cout << ssn << "'s successor is " << ssnTemp << endl;
        }
      }
      else if(action == 'p'){ //if we are finding predecessor
        file >> ssn >> first >> last;
        if(myBST.pred(myBST.find(ssn)) == nullptr){ //if there is no predecessor
          continue;
        }
        else{
          ssnTemp = myBST.pred(myBST.find(ssn)) -> ssn;
          cout << ssn << "'s predecessor is " << ssnTemp << endl;
        }
      }
      else if(action == 'n'){ //if we are finding min
        cout << "minimal value so far " << myBST.minOfSubtree(myBST.getRoot()) -> ssn << endl;
      }
      else if(action == 'x'){ //if we are finding max
        cout << "maximal value so far " << myBST.maxOfSubtree(myBST.getRoot()) -> ssn << endl;
      }
      else if(action == 'e'){ //if we are to enumerate, ignore.
        file >> ssn >> ssn2;
      }
    }
    cout << endl;
    clock_t end = clock();
    double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;

    cout << "The Number of Valid Insertion :" << iCounter << endl;
    cout << "The Number of Valid Deletion :" << dCounter << endl;
    cout << "The Number of Valid Retrieval :" << rCounter << endl;
    cout << "Item numbers in the list :" << (iCounter - dCounter) << endl;
    cout << "The height of the BST tree :" << myBST.height(myBST.getRoot()) << endl;


    cout << "Time elapsed :" << elapsed_secs << endl;
}

#include <iostream>
#include <stdlib.h> //for srand and rand
#include <time.h>
#include "graph.h"
#include <queue>

using namespace std;

graph::graph(){
    
}


int graph::initializeGraph(graph *g, int m){ //m is the user chosen average degree of the graph   
    srand(time(NULL));  //set seed for random generation as the time
    g -> avgDegree = m; //initialize average degree input value
    int randInt = 0;
    node* curr;
    
    for(int j = 0; j < graphLength; j++){ //assign values to all nodes in the array and give them no neighbors to start
        g -> arr[j] = new node(j);
        g -> arr[j] -> next = nullptr;
        g -> degree[j] = rand()%((m * 4/3)-(m * 2/3) + 1) + (m * 2/3);
    }
    int missedNodes = 0;
    for(int i = 0; i < graphLength; i++){
        int deathCounter = 0;
        while(!isFull(g, g -> arr[i])){
            if (deathCounter > 100000){    //deathCounter checks to see if there are no other options to add as a neighbor
                missedNodes++;             //after checking 100,000 times we assume there are no possibilities and stop trying
                break;
            }
            deathCounter++;
            
            curr = g -> arr[i];             //at i, curr will be the node we are currently working with
            
            randInt = rand()%(graphLength); //pick a new random number every time we go back through the loop;
            
            if(inList(g, curr, g -> arr[randInt])){             //if the randomly selected node is already in our target list,
                continue;                                       //pick a new random number. OR if the target node is in the randomly
            }                                                   //selected number's list, pick a new random number
            if(inList(g, g -> arr[randInt], curr)){
                continue;
            }
            
            if(isFull(g, g -> arr[randInt])){ //if the randomly selected node is full, pick a new random number
                continue;
            }
            
            //if we get through these checks, we can make a mutual connection
            addConnection(g, curr, g -> arr[randInt]);
            addConnection(g, g -> arr[randInt], curr);
        }
    }
    return missedNodes; //returns the number of nodes with missed connections
}

void graph::addConnection(graph *g, node* node1, node* node2){ //function to build a ONE WAY connection between two nodes
    node* add = new node(node2 -> value);
    
    while(node1 -> next != nullptr){
        node1 = node1 -> next;
    }
    node1 -> next = add;
}

bool graph::isFull(graph* g, node *target){ //function to check if a target node has proper amount of neighbors
    int size = g -> degree[target -> value];
    int count = 0;
    while(target -> next != nullptr){ //add 1 to count when we visit a neighbor
        target = target -> next;
        count++;
    }
    if(count == size){ //if the node has the right amount in it, return true
        return true;
    }
    else{ //otherwise it is not full, we can return false
        return false;
    }
}

bool graph::inList(graph *g, node *target, node *node){ //function to check if a node is already a neighbor with a target node
    while(target != nullptr){
        if(node -> value != target -> value){
            target = target -> next;
        }
        else{
            return true; //if the node is in the list return true
        }
    }
    return false; //if we exit the while loop, the node is not in the list, we can return false
}

int graph::diameter(graph *g){
    int maxDist = 0;
    int currDist = 0;
    int rand1 = 0;
    int rand2 = 0;
    
    for(int i = 0; i < 1000; i++){ //estimate diameter with 1000 iterations of BFS
        rand1 = rand()%(graphLength);
        rand2 = rand()%(graphLength);
        
        currDist = BFS(g, g -> arr[rand1], g -> arr[rand2]);
        if (currDist > maxDist) maxDist = currDist;
    }
    return maxDist;
}

int graph::BFS(graph *g, node *src, node *dst){ //BFS to find total number of edges between two nodes
    
    if (src -> value == dst -> value) return 0;
    bool visited[graphLength] = {false}; //create an array to know if a node has been visited
    
    node *v;
    node *parents[graphLength] ={nullptr};
    node *neighbor;
    
    if (src -> value >= graphLength || dst -> value >= graphLength) return -1; //if the node is not in the graph, return -1
    else{
        queue<node *> q;
        
        q.push(src);
        
        while(!q.empty()){ //go until queue is empty
            v = q.front();
            if (v -> value == dst -> value){
                return backTrack(g, parents, src, dst); //when we reach our destination node, backtrack will will give us the number of edges from src to dst
            }
            q.pop();
            visited[v -> value] = true; //once we check a node, make it's value in the visited array true
            
            neighbor = g -> arr[v -> value] -> next; //move on to the next neighbor
            
                while(neighbor != nullptr){ //queue all neighbors of current node
                    if (visited[neighbor -> value] == false){
                        q.push(neighbor);
                        visited[neighbor -> value]  = true;
                        parents[neighbor -> value] = v;
                    }
                    neighbor =  neighbor -> next;
                }
        }
    }
    return -1;
}

int graph::backTrack(graph *g, node *parents[graphLength], node *src, node *dst){ //backtrack gives us the number of edges
    node *temp = dst;                                                             //in the path we took from src to dst
    int distance = 0;
    
    while(temp -> value != src -> value){
        distance++;
        temp = parents[temp -> value];
    }
    return distance;
}




void graph::printGraph(graph *g){ //function to print our generated graph
    for(int i = 0; i < graphLength; i++){
        node* printNode = g -> arr[i];
        while(printNode != nullptr){
            cout << printNode -> value << ", ";
            printNode = printNode -> next;
        }
        cout << endl;
    }
}

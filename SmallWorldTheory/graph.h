#include "node.h"
#define graphLength 100000
using namespace std;

class graph{
public:
    node* arr[graphLength];
    int degree[graphLength];
    int avgDegree;
    
    graph();
    int initializeGraph(graph *G, int m);                                      //function to create a randomly connected graph given a graph name and an average degree m
    void printGraph(graph *G);                                                 //function to print the contents of a graph
    int BFS(graph *G, node *src, node *dst);                                   //function to find and print the number of edges between any two ndoes in the graph
    bool isFull(graph *G, node *target);                                       //function to check if a node has the proper number of neighbors
    bool inList(graph *G, node *target, node *node);                           //function to check if a node is already a neighbor with another node
    void addConnection(graph *G, node* node1, node* node2);                    //function to connect two nodes
    int numNeighbors(graph *G, node *src);                                     //function to find the number of neighbors a node currently has
    int backTrack(graph *g, node *parents[graphLength], node *src, node *dst); //function used in BFS search to help determine number of edges between two nodes
    int diameter(graph *g);                                                    //function to estimate the diameter of a graph based on 1000 iterations of BFS
};

#include <iostream>
#include <stdlib.h>
#include <time.h> //for random number seeding
#include "graph.h"
using namespace std;

int main(void){
    
    int missedNodes; //Occasonally, a node will not be assigned the proper number of neighbors
                     //This is due to random number generation limitations
                     //This event only happens a few times in a graph of 100,000, making it negligible
    int avgDeg = 0;
    int diameter = 0;
    
    graph *G = new graph;

    cout << "Enter the average degree of the graph: ";
    cin >> avgDeg;
    
    missedNodes = G -> initializeGraph(G, avgDeg); //choose a graph name and an average degree
                                                   //the graph will be populated with a population of 100,000

    
    //G -> printGraph(G);   /****** Uncomment to print graph ******/
    
    cout << "The number of nodes with missed connections is: " << missedNodes << endl;
    
    cout << "BFS between two nodes: " << G -> BFS(G, G -> arr[0], G -> arr[99999]) << endl; //find the distanc between two nodes
    
    cout << "Calculating diameter..." << endl;
    diameter = G -> diameter(G);
    cout << "Average Diameter: " << diameter << endl; //find the longest, shortest path in the graph. This takes a large amount of computation
    
    return 0;
}

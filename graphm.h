// a GraphM object holds one directed graph
// Jenny Harston

#ifndef GRAPHM_H
#define GRAPHM_M
#include "nodedata.h"
#include <iostream>
#include <fstream>
#include <iomanip>
using namespace std;

//----------------------------------------------------------------------------
// GraphM class: stores and displays a directed graph with edge weight
//    -- builds and stores a graph from a text file
//    -- finds the lowest cost paths
//    -- displays the cost and path from every node to every other node
//
// Implementation and assumptions:
//    -- implements Dijkstra's shortest path algorithm to find lowest cost
//       paths and recover the path data.
//    -- implemented using a cost array, the adjacency matrix, a TableType
//       matrix to store Dijkstra information, and a NodeData object that 
//       stores a text description of a node.
//    -- a TableType object stores the currently known shortest distance
//       and associated path info, and keeps track of whether a node
//       has been visited.
//    -- NodeData is responsible for its own operations.
//    -- constructor initializes an empty graph.
//    -- holds at most 100 nodes, begins at number 1.
//    -- assumes input data file has correctly formatted data.
//
//    -- Text file format: first line tells number of nodes (assume
//       nonnegative ints). Then a text description of each of the 1 through
//       n nodes, one description per line (assume 50 chars max length).
//       Then each line consists of 3 ints representing an edge (assume
//       correctly formatted int data). If there is an edge from node 1 to 
//       node 2 with a label of 10, the data is: 1 2 10. A zero for the first
//       integer signifies the end of the data for that one graph. There are 
//       several graphs, each having at most 100 nodes.
//----------------------------------------------------------------------------

const int MAXNODES = 100; // max number of nodes allowed in graph

class GraphM {
public:
   GraphM();   //constructor

   void buildGraph(ifstream& infile); // build the graph from text file
   bool insertEdge(int, int, int); //insert edge into graph
   bool removeEdge(int, int); //remove edge from graph
   void findShortestPath(); // find the shortest path from node to node
   void displayAll() const; // display all graph data and path info
   void display(const int, const int) const; // display data for one path

private:
   struct TableType {
      bool visited; // whether node has been visited
      int dist; // currently known shortest distance from source
      int path; // previous node in path of min dist
   };
   NodeData data[MAXNODES]; // data for graph nodes information
   int C[MAXNODES][MAXNODES]; // Cost array, the adjacency matrix
   int size; // number of nodes in the graph
   TableType T[MAXNODES][MAXNODES]; // stores Dijkstra information
   
   // recursively displays lowest cost path
   void printPath(const int, const int) const; 
};

#endif
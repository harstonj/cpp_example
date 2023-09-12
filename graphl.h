// a GraphL object holds one directed graph
// Jenny Harston

#ifndef GRAPHL_H
#define GRAPHL_H
#include "nodedata.h"
#include <iostream>
#include <fstream>
#include <list>
using namespace std;

//----------------------------------------------------------------------------
// GraphL class: stores and displays a directed graph
//    -- builds and stores a graph from a text file
//    -- displays a list of graph nodes, a text description and edge data for
//       each node, and depth-first ordering
//
// Implementation and assumptions:
//    -- implemented using an adjacency list, an array of GraphNode objects
//    -- struct GraphNode stores graph node information. It holds a list of 
//       edges, a NodeData object that stores a text description of a node,
//       and keepstrack of whether a node has been visited
//    -- NodeData is responsible for its own operations
//    -- constructor initializes an empty graph
//    -- holds at most 100 nodes, begins at number 1
//    -- assumes input data file has correctly formatted data
//
//    -- Text file format: First line tells the number of nodes, followed by
//       a text description of each of the 1 through n nodes, one description
//       per line (max length of 50 chars). Each line after that consists of
//       2 ints representing an edge (assume int data). A zero for the first
//       integer signifies the end of the data for that one graph. There are 
//       several graphs, each having at most 100 nodes.
//----------------------------------------------------------------------------

const int MAX = 100; // max number of nodes allowed in graph

struct GraphNode {
   list<int> edges; // list of edges (edge nodes), the adjacent graph node
   NodeData data; // information on the graph node
   bool visited; // whether node has been visited
};

class GraphL {
public:
   GraphL();   // constructor
   ~GraphL();  // destructor

   void buildGraph(istream& infile); // build the graph from text file
   void displayGraph() const; // displays graph data
   void depthFirstSearch();   // displays depth-first ordering

private:
   GraphNode adjList[MAX]; // array of GraphNodes, assume at most 100 nodes
   int size; // number of nodes in the graph 
   void dfs(int v);  // recursive helper to depthFirstSearch; 
};

#endif
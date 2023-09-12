// a GraphL object holds one directed graph
// Jenny Harston

#include "graphl.h"

//----------------------------------------------------------------------------
// constructor
// Initializes an empty graph, sets size to 0, sets all visited to false
GraphL::GraphL()
{
   size = 0;
   for (int v = 0; v < MAX; v++)
   {
      adjList[v].visited = false;
   }
}

//----------------------------------------------------------------------------
// destructor
GraphL::~GraphL() { }

//----------------------------------------------------------------------------
// buildGraph
// Constructs a directed graph from a properly formatted text file. Does not
// sort the data. Ignores invalid data. If the number of nodes read in is
// less than 1 or greater than the max amount of nodes allowed, the size is
// reset to zero and the rest of the data for that graph is ignored.
void GraphL::buildGraph(istream& infile) {
   int fromNode, toNode;          // from and to node ends of edge

   infile >> size;                // read the number of nodes
   if (size <= 0 || size >= MAX)  // invalid number of nodes
   {
      size = 0;   // reset size to 0
      return;
   }

   if (infile.eof()) return;      // stop reading if no more data

   string s;                      // used to read to end of line holding size
   getline(infile, s);

   // read graph node information
   for (int i = 1; i <= size; i++) {
      // read using setData of the NodeData class, where adjList is the
      // array of GraphNodes and data is the NodeData object of GraphNode
      adjList[i].data.setData(infile);
   }

   // read the edge data and add to the adjacency list
   for (;;) {
      infile >> fromNode >> toNode;
      if (fromNode == 0 && toNode == 0) return;     // end of edge data

      // insert a valid edge into the adjacency list for fromNode
      if (fromNode <= size && fromNode > 0 && toNode <= size && toNode > 0)
      {
         adjList[fromNode].edges.push_front(toNode);
      }
   }
}

//----------------------------------------------------------------------------
// displayGraph
// Displays graph data - nodes, text descriptions and edge data
void GraphL::displayGraph() const
{
   if (size == 0) // if graph is empty then return
      return;

   cout << "Graph:" << endl;
   
   for (int v = 1; v <= size; v++)
   {
      cout << "Node " << v << "        " << adjList[v].data << endl;
      for (int w : adjList[v].edges)
      {
         cout << "  edge " << v << " " << w << endl;
      }
   }
   cout << endl;
}

//----------------------------------------------------------------------------
// depthFirstSearch
// Performs depth-first search and displays depth-first ordering of graph 
// nodes using the order as given by the data, starting at vertex 1. Marks
// all vertices as not visited then performs depth-first ordering. For each
// vertex v in the graph, check if it has been visited. If not, then call dfs
// to mark v as visited, display v, then check each vertex adjacent to v.
void GraphL::depthFirstSearch()
{
   if (size == 0) // if graph is empty then return
      return;

   // mark all the vertices as not visited
   for (int v = 1; v <= size; v++)
   {
      adjList[v].visited = false;
   }

   cout << "Depth-first ordering: ";

   // for each vertex in the graph
   for (int v = 1; v <= size; v++)
   {
      if (!adjList[v].visited)
         dfs(v);
   }
   cout << endl << endl;
}

//----------------------------------------------------------------------------
// dfs
void GraphL::dfs(int v)
{
   // mark v as visited
   adjList[v].visited = true;

   // output v, display gives depth-first order
   cout << v << ' ';

   //for each vertex w adjacent to v
   for (int w : adjList[v].edges)
   {
      // if w is not visited
      if (!adjList[w].visited) {
         dfs(w);
      }
   }
}
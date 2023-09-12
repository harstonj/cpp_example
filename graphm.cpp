// a GraphM Object holds one directed graph
// Jenny Harston

#include "graphm.h"

//----------------------------------------------------------------------------
// constructor
// Initializes an empty graph.
// Data member T: sets all dist for the source node (source row)
// to infinity (int max limit), sets all visited to false, sets all path to 0
GraphM::GraphM()
{
   size = 0; // initalize size

   // initialize T and C
   for (int v = 0; v < MAXNODES; v++)
   {
      for (int w = 0; w < MAXNODES; w++)
      {
         T[v][w].dist = numeric_limits<int>::max();
         T[v][w].visited = false;
         T[v][w].path = 0;

         C[v][w] = numeric_limits<int>::max();
      }
   }
}

//----------------------------------------------------------------------------
// buildGraph
// Constructs a directed graph with edge weight from a properly formatted
// text file. Ignores invalid data. If the number of nodes read in is
// less than 1 or greater than the max amount of nodes allowed, the size is
// reset to zero and the rest of the data for that graph is ignored.
void GraphM::buildGraph(ifstream& infile)
{
   int fromNode, toNode, cost;          // from and to node ends of edge, cost

   infile >> size;                // read the number of nodes
   if (size <= 0 || size >= MAXNODES)  // invalid number of nodes
   {
      size = 0;   // reset size to 0
      return;
   }
   
   if (infile.eof()) return;      // stop reading if no more data

   // purge the rest of the int line to read a string
   string s;                      // used to read to end of line holding size
   getline(infile, s);

   // read graph node information and set data
   for (int i = 1; i <= size; i++) {
      data[i].setData(infile);
   }

   // read the edge data and add to the adjacency matrix
   for (;;) {
      infile >> fromNode >> toNode >> cost;
      if (fromNode == 0 && toNode == 0) return;     // end of edge data

      // insert a valid edge into the adjacency matrix for fromNode
      if (cost > 0 && fromNode <= size && fromNode > 0
            && toNode <= size && toNode > 0) {
         
         C[fromNode][toNode] = cost;
      }
   }
}

//----------------------------------------------------------------------------
// insertEdge
// Insert an edge into the graph.
// If cost is greater than 0, and fromNode and toNode are current nodes in
// the graph, insert edge into the cost array. New edge replaces any previous
// edge. If successful, resets path data and runs findShortestPath to update
// graph changes. Returns true if the graph was changed. 
// Ignores data not in current graph.
bool GraphM::insertEdge(int fromNode, int toNode, int cost)
{
   if (cost > 0 && fromNode > 0 && fromNode <= size && toNode > 0 &&
      toNode <= size)
   {
      C[fromNode][toNode] = cost;

      // reset path data
      for (int v = 1; v <= size; v++)
      {
         for (int w = 1; w <= size; w++)
         {
            T[v][w].dist = numeric_limits<int>::max();
            T[v][w].visited = false;
            T[v][w].path = 0;
         }
      }
      
      findShortestPath();  //update graph changes
      return true;
   }
   
   return false;
}

//----------------------------------------------------------------------------
// removeEdge
// Remove an edge from the graph
// If there is a current edge from fromNode to toNode, set cost to infinity.
// If successful, resets path data and runs findShortestPath to update graph
// changes. Returns true if the graph was changed. 
// Ignores data not in current graph.
bool GraphM::removeEdge(int fromNode, int toNode)
{
   if (fromNode > 0 && fromNode <= size && toNode > 0 && toNode <= size)
   {
      if (C[fromNode][toNode] != numeric_limits<int>::max())
      {
         C[fromNode][toNode] = numeric_limits<int>::max();
         
         // reset path data
         for (int v = 1; v <= size; v++)
         {
            for (int w = 1; w <= size; w++)
            {
               T[v][w].dist = numeric_limits<int>::max();
               T[v][w].visited = false;
               T[v][w].path = 0;
            }
         }
         
         findShortestPath();  //update graph changes
         return true;
      }
   }

   return false;
}

//----------------------------------------------------------------------------
// findShortestPath
// Finds the lowest cost paths using Dijkstra's shortest path algorithm.
void GraphM::findShortestPath()
{
   if (size == 0) // if there is no graph information then return
      return;

   // from each starting source
   for (int source = 1; source <= size; source++)
   {
      T[source][source].dist = 0;


      //for i = 1 to(#vertices - 1)
      for (int i = 1; i < size; i++) // find v
      {
         int v = 0;
         // Find the not yet visited node with the minimum distance 
         // This is a node, the v node, that hasn't been gone thru yet 
         for (int j = 1; j <= size; j++)
         {
            if (!T[source][j].visited)
            {
               if (T[source][j].dist < T[source][v].dist)
               {
                  v = j;
               }
            }
         }
         T[source][v].visited = true;  // mark v as visited

         // for each w adjacent to v
         for (int w = 1; w <= size; w++)
         {
            // if w is not visited
            if (!T[source][w].visited && C[v][w] != numeric_limits<int>::max())
            {
               // Adjust the shortest distance from source to w
               // If going through v is shorter, set .path to v
               if ((T[source][v].dist + C[v][w]) < T[source][w].dist)
               {
                  T[source][w].dist = T[source][v].dist + C[v][w];
                  T[source][w].path = v;
               }
               
            }
         }
      }
   }
}

//----------------------------------------------------------------------------
// displayAll
// Displays the data of each node, from node, to node, Dijkstra's lowest
// cost, and the path details from every node to every other node.
void GraphM::displayAll() const
{
   if (size == 0) // if graph is empty then return
      return;

   cout << "Description               From node  To node  Dijkstra's  Path"
      << endl;
   for (int w = 1; w <= size; w++)
   {
      cout << data[w] << endl;
      for (int v = 1; v <= size; v++)
      {
         if (w != v)
         {
            //cout << "                               ";
            //cout << w << "       " << v << "       ";
            cout << setfill(' ') << setw(25) << ' ';
            cout << setw(7) << w << setw(9) << v << setw(7) << ' ';
            if (T[w][v].dist != numeric_limits<int>::max())
            {
               cout << setw(3) << T[w][v].dist << "        ";
               printPath(w, v);
               cout << endl;
            }
            else
               cout << "---" << endl;
         }
      }
   }
   cout << endl;
}

//----------------------------------------------------------------------------
// printPath
// Recursively prints the path by using .path subscript.
void GraphM::printPath(const int source, const int w) const
{
   if (w == source)
   {
      cout << w << " ";
      return;
   }

   printPath(source, T[source][w].path);
   cout << w << " ";
}

//----------------------------------------------------------------------------
// display
// Displays data for one path with lowest cost and path detail.
void GraphM::display(const int w, const int v) const
{
   if (size == 0) // if graph is empty then return
      return;

   if (w <= size && w > 0 && v <= size && v > 0)
   {
      cout << setw(4) << w << setw(7) << v << setw(5) << ' ';
      if (T[w][v].dist != numeric_limits<int>::max())
      {
         cout << setw(3) << T[w][v].dist << "        ";
         printPath(w, v);
         cout << endl;
      }

      else
         cout << "---" << endl;
   }
   cout << endl;
}
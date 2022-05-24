 #ifndef __DIGRAPH_MATRIX_H
#define __DIGRAPH_MATRIX_H

#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <unordered_map>
#include <stack>
using namespace std;

enum mark_t { UNDISCOVERED, DISCOVERED, EXPLORED };



class DigraphMatrix
{

private:
  //number of vertices
  int n;
  //number of edges
  int m;
  bool** matrix;
  int ctr = 0;
  vector <int> components;

public:
  //Reads in digraph from given file
  //Stores graph as an adjacency matrix
  DigraphMatrix(const string&);

  //Returns number of vertices
  int getOrder() const { return n; }

  //Returns vector containing component ID for each vertex
  vector<int> stronglyConnectedComponents();

  void addEdge (int, int);

  vector<int> getNeighbors(int) const;

  void DFS_Recursive(unordered_map<int, mark_t>&, int, stack<int>&);

  void reverseEdges();
};

#endif
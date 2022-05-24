#include "digraphMatrix.h"
#include <stdexcept>

// Navigator: Malek Zaben
// Driver: Daniel Concepcion
DigraphMatrix :: DigraphMatrix (const string& file)
{
    ifstream in(file);
    if(!in.is_open())
        throw runtime_error ("Couldn't open file!");
    in >> n >> m;
    int x,y;

    matrix = new bool*[n];
    for (int i = 0; i < n; i++)
    {
        matrix[i] = new bool[n];
        for(int j = 0; j < n; j++)
            matrix[i][j] = 0;
    }

    for (int i = 0; i < m; i++)
    {
        in >> x >> y;
        addEdge(x,y);
    }
}

// Navigator: Malek Zaben
// Driver: Daniel Concepcion
void DigraphMatrix :: addEdge(int v1, int v2)
{
    matrix[v1][v2] = 1;
}

// Navigator: Malek Zaben
// Driver: Daniel Concepcion
vector<int> DigraphMatrix :: getNeighbors(int id) const
{
    vector <int> N;

    for (int j = 0; j < n; j++)
    {
        if(matrix[id][j] == 1)
            N.push_back(j);
    }

    return N;
}

// Navigator: Malek Zaben
// Driver: Daniel Concepcion
void DigraphMatrix :: reverseEdges()
{
    bool temp;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < i; j++) 
        {
            temp = matrix[i][j];
            matrix[i][j] = matrix[j][i];
            matrix[j][i] = temp;
            
        }
}

// Navigator: Daniel Concepcion
// Driver: Malek Zaben
void DigraphMatrix :: DFS_Recursive(unordered_map<int, mark_t>& marks, int v, stack<int>& s)
{
  marks[v] = DISCOVERED;

  components.at(v) = ctr;

  for (int i = 0; i < n; i++)
    if (matrix[v][i] == 1 && marks.at(i) == UNDISCOVERED)
    {
      DFS_Recursive(marks, i, s);
    }

  marks[v] = EXPLORED;
  s.push(v);
}

// Navigator: Daniel Concepcion
// Driver: Malek Zaben
vector<int> DigraphMatrix :: stronglyConnectedComponents() 
{
    stack <int> s1,s2;
    unordered_map <int, mark_t> marks;
    for (int i = 0; i < n; i++)
        marks[i] = UNDISCOVERED;

    components.resize(n);
    for (int i = 0; i < n; i++)
    {
        if (marks[i] == UNDISCOVERED)
        {
            DFS_Recursive(marks, i, s1);
        }
    }

    reverseEdges();

    for (int i = 0; i < n; i++)
        marks[i] = UNDISCOVERED;

    while (!s1.empty())
    {
        if (marks[s1.top()] == UNDISCOVERED)
        {
            DFS_Recursive(marks, s1.top(), s2);
            ctr++;
        }
        
        s1.pop();
    }
    return components;
}
#define DEBUG
#include <iostream>
#include "stdio.h"

// C++ program to print DFS_path traversal from
// a given vertex in a given graph
#include <map>
#include <list>
#define SIZE 1000005
using namespace std;

int n, m;

// Graph class represents a directed graph
// using adjacency list representation
class Graph
{
public:
  bool onpath[SIZE];
  list<int> adj[SIZE];
  bool visited[SIZE];
  long long count;

  // function to add an edge to graph
  void addEdge(int v, int w);

  // DFS_path traversal of the vertices
  // reachable from v
  int DFS(int v, int w);
  int DFS_path(int v);
};

int Graph::DFS(int v, int w)
{
  // Mark the current node as visited and
  // print it
  if (v == w)
    return 1;
  visited[v] = true;
  // cout << v << " ";

  // Recur for all the vertices adjacent
  // to this vertex
  for (auto i = adj[v].begin(); i != adj[v].end(); ++i)
    if (!visited[*i])
      return DFS(*i, w);
  return 0;
}

void Graph::addEdge(int v, int w)
{
  adj[v].push_back(w); // Add w to v’s list.
}

int Graph::DFS_path(int v)
{
  onpath[v] = 1;
  if (v == n)
    count++;
  // Recur for all the vertices adjacent
  // to this vertex
  auto ite = adj[v].begin();
  for (; ite != adj[v].end(); ite++)
  {
    int w = *ite;
    if (onpath[w])
    {
      // for (int i = 1; i <= n; i++)
      //   visited[i] = 0;
      if (DFS(w, n) == 0)
        continue;
      else
        return 1;
    }
    else if (DFS_path(w))
      return 1;
  }
  onpath[v] = 0;
  return false;
}

int main()
{
  // dot edge
  cin >> n >> m;
  Graph g;
  g.count = 0;

  for (int i = 0; i < m; i++)
  {
    int u, v;
    scanf("%d %d", &u, &v);
    g.adj[u].push_back(v); // Add w to v’s list.
  }
  // for (auto ite = g.adj.begin(); ite != g.adj.end(); ite++)
  // {
  //   ite->second.sort();
  //   ite->second.unique();
  // }

  int ret = g.DFS_path(1);
  if (ret == 1)
    cout << -1;
  else
    cout << g.count % 998244353;

  system("pause");
  return 0;
}

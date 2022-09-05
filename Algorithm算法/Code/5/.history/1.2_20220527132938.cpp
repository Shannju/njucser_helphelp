#define DEBUG
/*
 */
#include <iostream>
#include "stdio.h"
#include <list>

using namespace std;

#define V 500
#define INT_MAX 2147483647
int n, m, k;

struct node
{
  int num;
  int w;
};

class Graph
{
public:
  bool onpath[V];
  list<node> adj[V];
  bool visited[V];
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

int main()
{
  int ans0, ans1;
  bool *ans = new bool[k + 1];
  int count = 0;
  cin >> n >> m >> k;
  for (int i = 0; i < m; i++)
  {
    int u, v, w;
    cin >> u >> v >> w;
    g[u][v] = g[v][u] = w;
  }
  ans0 = primMST(g);
  // ans1 = ans0;
  for (int i = 0; i < k; i++)
  {
    int u, v, w;
    cin >> u >> v >> w;
    ans[i] = update(g0, u, v, w);
  }
  ans1 = primMST(g0);
  cout << ans0 << endl;
  for (int i = 0; i < k; i++)
  {
    if (ans[i])
      cout << 'Y' << endl;
    else
      cout << 'N' << endl;
  }
  cout << ans1 << endl;

  return 0;
}

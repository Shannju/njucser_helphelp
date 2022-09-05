#include <iostream>
#include "stdio.h"
#include <vector>
#include <list>
#include <algorithm>
#include <map>
using namespace std;
// DSU data structure
// path compression + rank by union

#define SIZE 500
#define INT_MAX 2147483647
int n, m, k;
int ans1;

class DSU
{
  int *parent;
  int *rank;

public:
  DSU(int n)
  {
    parent = new int[n];
    rank = new int[n];

    for (int i = 0; i < n; i++)
    {
      parent[i] = -1;
      rank[i] = 1;
    }
  }

  // Find function
  int find(int i)
  {
    if (parent[i] == -1)
      return i;

    return parent[i] = find(parent[i]);
  }
  // union function
  void unite(int x, int y)
  {
    int s1 = find(x);
    int s2 = find(y);

    if (s1 != s2)
    {
      if (rank[s1] < rank[s2])
      {
        parent[s1] = s2;
        rank[s2] += rank[s1];
      }
      else
      {
        parent[s2] = s1;
        rank[s1] += rank[s2];
      }
    }
  }
};

class Graph
{
  vector<vector<int>> edgelist;
  int adj[SIZE][SIZE];
  int V;

public:
  Graph(int V) { this->V = V; }
  int DFS_path(int u, int v, int onapth[]);
  bool update(int u, int v, int w, int &ans1);
  void addEdge(int x, int y, int w)
  {
    edgelist.push_back({w, x, y});
  }

  void makeEdge(int u, int v, int w)
  {
    adj[u][v] = w;
    adj[v][u] = w; // Add w to v’s list.
  }

  int kruskals_mst()
  {
    // 1. Sort all edges
    sort(edgelist.begin(), edgelist.end());

    // Initialize the DSUD
    DSU s(n);
    int ans = 0;
    for (int i = 0; i < edgelist.size(); i++)
    {
      int w = edgelist[i][0];
      int x = edgelist[i][1];
      int y = edgelist[i][2];

      // take that edge in MST if it does form a cycle
      if (s.find(x) != s.find(y))
      {
        s.unite(x, y);
        ans += w;
        makeEdge(x, y, w);

      }
    }
    // cout << "Minimum Cost Spanning Tree: " << ans;
    return ans;
  }
};

bool Graph::update(int u, int v, int w, int &ans1)
{
  
  int u0 = u, v0 = v;
  int *onpath = new int[n + 1];
  for (int i = 0; i < n + 1; i++)
    onpath[i] = -1;

  DFS_path(u, v, onpath);

  int max_weight = 0;
  int s0 = v, s1 = u;
  while (v != u)
  {
    if (adj[v][onpath[v]] > max_weight)
    {
      s0 = v;
      s1 = onpath[v];
      max_weight = adj[v][onpath[v]];
    }
    v = onpath[v];
  }
  if (max_weight > w)
  {
    adj[s0][s1] = adj[s1][s0] = 0;
    adj[u0][v0] = adj[v0][u0] = w;
    addEdge(u0, v0, w);
    ans1 -= max_weight - w;
    return 1;
  }
  else
    return 0;
}

int Graph::DFS_path(int u, int v, int onpath[])
{
  if (u == v)
    return 1;
  for (int i = 0; i < n; i++)
  {
    if (onpath[i] == -1 && adj[u][i])
    {
      onpath[i] = u; // visted i : its parent
      if (DFS_path(i, v, onpath))
        return 1;
    }
  }
  onpath[u] = -1;
  return 0;
}

int main()
{
  int ans0, ans1;
  bool *ans = new bool[k + 1];
  int count = 0;
  cin >> n >> m >> k;
  Graph g(n);
  for (int i = 0; i < m; i++)
  {
    int u, v, w;
    cin >> u >> v >> w;
    g.addEdge(u, v, w);
  }

  ans0 = g.kruskals_mst();
  ans1 = ans0;

  for (int i = 0; i < k; i++)
  {
    int u, v, w;
    cin >> u >> v >> w;
    ans[i] = g.update(u, v, w, ans1);
  }

  cout << ans0 << endl;
  for (int i = 0; i < k; i++)
  {
    if (ans[i])
      cout << 'Y' << endl;
    else
      cout << 'N' << endl;
  }
  cout << ans1 << endl;
  system("pause");
  return 0;
}

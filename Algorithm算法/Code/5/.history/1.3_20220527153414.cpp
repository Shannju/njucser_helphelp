#include <iostream>
#include "stdio.h"
#include <vector>
#include <list>
#include <algorithm>
using namespace std;
// DSU data structure
// path compression + rank by union

#define SIZE 500
#define INT_MAX 2147483647
int n, m, k;

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
  vector<pair<int, int>> adj[SIZE];
  int V;

public:
  Graph(int V) { this->V = V; }
  int DFS_path(int u, int v, int onapth[]);
  bool update(int u, int v, int w);
  void addEdge(int x, int y, int w)
  {
    edgelist.push_back({w, x, y});
  }

  void makeEdge(int u, int v, int w)
  {
    pair<int, int> p(u, v);
    adj[u].push_back(p); // Add w to v’s list.
  }

  int kruskals_mst()
  {
    // 1. Sort all edges
    sort(edgelist.begin(), edgelist.end());

    // Initialize the DSU
    DSU s(V);
    int ans = 0;
    // cout << "Following are the edges in the "
    //         "constructed MST"
    //      << endl;
    for (auto edge : edgelist)
    {
      int w = edge[0];
      int x = edge[1];
      int y = edge[2];

      // take that edge in MST if it does form a cycle
      if (s.find(x) != s.find(y))
      {
        s.unite(x, y);
        ans += w;
        makeEdge(x, y, w);
        makeEdge(y, x, w);
      }
    }
    // cout << "Minimum Cost Spanning Tree: " << ans;
    return ans;
  }
};

bool Graph::update(int u, int v, int w)
{
  int u0 = u, v0 = v;
  int *visited = new int[n];
  for (int i = 0; i < n; i++)
    visited[i] = -1;

  DFS_path(u, v, visited);

  int max_weight = 0;
  int s0 = v, s1 = u;
  while (v != u)
  {
    if (> max_weight)
    {
      s0 = v;
      s1 = visited[v];
      max_weight = g[v][visited[v]];
    }
    v = visited[v];
  }

  if (max_weight > w)
  {
    addEdge(u0, v0, w);
    return 1;
  }
  else
    return 0;
}

int Graph::DFS_path(int u, int v, int onpath[])
{
  onpath[v] = adj[u][v].second();
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
      for (auto ite = visited.begin(); ite != visited.end(); ite++)
        ite->second = 0;
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

  // for (int i = 0; i < k; i++)
  // {
  //   int u, v, w;
  //   cin >> u >> v >> w;
  //   ans[i] = update(g0, u, v, w);
  // }
  // ans1 = g.kruskals_mst();

  cout << ans0 << endl;
  // for (int i = 0; i < k; i++)
  // {
  //   if (ans[i])
  //     cout << 'Y' << endl;
  //   else
  //     cout << 'N' << endl;
  // }
  // cout << ans1 << endl;
  system("pause");
  return 0;
}

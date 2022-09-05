#include <iostream>
#include "stdio.h"
#include <vector>
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
  int V;

public:
  Graph(int V) { this->V = V; }

  void addEdge(int x, int y, int w)
  {
    edgelist.push_back({w, x, y});
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
      }
    }
    // cout << "Minimum Cost Spanning Tree: " << ans;
    return ans;
  }
};

int main()
{
  int ans0, ans1;
  bool *ans = new bool[k + 1];
  int count = 0;
  cin >> n >> m >> k;
  Graph g;
  for (int i = 0; i < m; i++)
  {
    int u, v, w;
    cin >> u >> v >> w;
    g.addEdge(u, v, w);
  }

  ans0 = g.kruskals_mst();

  for (int i = 0; i < k; i++)
  {
    int u, v, w;
    cin >> u >> v >> w;
    ans[i] = update(g0, u, v, w);
  }
  ans1 = g.kruskals_mst();

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

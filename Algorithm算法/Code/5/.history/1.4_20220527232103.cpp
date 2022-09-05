#include <iostream>
#include "stdio.h"
#include <vector>
#include <list>
#include <algorithm>
using namespace std;

#define SIZE 500
#define INT_MAX 2147483647
int n, m, k;

class DSU //使用秩的并查集
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
      parent[i] = i;
      rank[i] = 1;
    }
  }

  // Find function
  int find(int i)
  {
    if (parent[i] == i)
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

class Graph //图结构
{
  vector<vector<int>> edgelist; //一个m*3的数组 每个三表示了一个边 可以按照weight排序以便dijkstra
  int adj[SIZE][SIZE];          //邻接矩阵 之后打算存放MST
  int V;                        //节点数目

public:
  Graph(int V) { this->V = V; }
  int find_loop(int u, int p, int onpath[]);
  bool update(int u, int v, int w, int &ans1);
  void addEdge(int x, int y, int w)
  {
    if (x == y)
      return;
    edgelist.push_back({w, x, y});
  }

  void makeEdge(int u, int v, int w)
  {
    adj[u][v] = w;
    adj[v][u] = w; // Add w to v’s list.
  }

  void delEdge(int u, int v)
  {
    adj[u][v] = 0;
    adj[v][u] = 0;
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
      if (adj[x][y])
        continue;

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
  if (u == v)
    return 0;
  if (adj[u][v] > 0)
  {
    if (adj[u][v] > w)
    {
      ans1 -= (adj[u][v] - w);
      makeEdge(u, v, w);
      // addEdge(u, v, w);
      return 1;
    }
    else
      return 0;
  }
  int save = adj[u][v];
  makeEdge(u, v, w);
  int u0 = u, v0 = v;
  int x = u, y = v;
  int *onpath = new int[n];
  for (int i = 0; i < n; i++)
    onpath[i] = -1;

  find_loop(u, -2, onpath);

  int maxw = 0;

  while (v != u)
  {
    if (adj[v][onpath[v]] > maxw)
    {
      maxw = adj[v][onpath[v]];
      x = v;
      y = onpath[v];
    }
    v = onpath[v];
  }

  if (adj[x][y] > w)
  {
    ans1 -= (adj[x][y] - w);
    addEdge(u0, v0, w);
    delEdge(x, y);
    return 1;
  }
  else
  {
    makeEdge(u0, v0, save);
    return 0;
  }
}

int Graph::find_loop(int u, int p, int onpath[])
{
  onpath[u] = p;
  for (int i = 0; i < n; i++)
  {
    if (i == u)
      continue;
    if (adj[u][i])
    {
      if (onpath[i] == -1) // not visited
      {
        onpath[i] = u; // visted i : its parent
        if (find_loop(i, u, onpath))
          return 1;
      }
      else if (i != p)
      {
        onpath[i] = u;
        return 1;
      }
    }
  }
  return 0;
}

int main()
{
  int ans0, ans1;
  bool *ans = new bool[k + 1];
  int count = 0;
  cin >> n >> m >> k;
  Graph g(n+1);
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

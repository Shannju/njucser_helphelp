#define DEBUG
/*
 */
#include <iostream>
#include "stdio.h"
#include <list>
#include <vector>
#include <algorithm>

using namespace std;

#define V 500
#define INT_MAX 2147483647
int n, m, k;
bool flag[V] = {0};

struct edge
{
  int u, v, w;
  bool operator>(const edge &x) //重载操作符 为了小至大排序
  {
    if (x.w < this->w)
      return true;
    return false;
  }
  bool operator<(const edge &x) //重载操作符 为了小至大排序
  {
    if (x.w > this->w)
      return true;
    return false;
  }
  edge(int a, int b, int c)
  {
    u = a, v = b, w = c;
  }
  edge() {}
};

class Graph
{
public:
  bool onpath[V];
  list<pair<int, int>> adj[V];
  bool visited[V];

  void addEdge(int u, int v, int w);

  int dijkstra();
};

void Graph::addEdge(int u, int v, int w)
{
  pair<int, int> tmp(u, v);
  adj[u].push_back(tmp); // Add w to v’s list.
}

int Graph::dijkstra()
{
}

int main()
{
  int ans0, ans1;
  bool *ans = new bool[k + 1];
  int count = 0;
  cin >> n >> m >> k;
  Graph g;
  vector<edge> arr;
  for (int i = 0; i < m; i++)
  {
    int u, v, w;
    cin >> u >> v >> w;
    edge tmp = edge(u, v, w);
    arr.push_back(tmp);
    g.addEdge(u, v, w);
  }

  ans0 = g.dijkstra();

  for (int i = 0; i < k; i++)
  {
    int u, v, w;
    cin >> u >> v >> w;
    ans[i] = update(g0, u, v, w);
  }
  ans1 = g.dijkstra();
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

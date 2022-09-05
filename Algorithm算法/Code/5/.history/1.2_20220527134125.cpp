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
bool flag[V] = {0};
struct edge
{
  int u, v, w;
};

struct node
{
  int num;
  int w;
  bool operator>(const p &x) //重载操作符 为了小至大排序
  {
    if (x.val < this->val)
      return true;
    return false;
  }
  bool operator<(const p &x) //重载操作符 为了小至大排序
  {
    if (x.val > this->val)
      return true;
    return false;
  }
};

class Graph
{
public:
  bool onpath[V];
  list<node> adj[V];
  bool visited[V];

  void addEdge(int u, int v, int w);

  int DFS_path(int v);
};

void Graph::addEdge(int u, int v, int w)
{
  node tmp = {v, w};
  adj[u].push_back(tmp); // Add w to v’s list.
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

#define DEBUG
/*

题目：营救路线

题目描述：

阿尼亚又双叒叕因为偷偷用了福杰的电报机发送摩斯电码暴露位置被抓起来了！
福杰为了救回阿尼亚，需要知道有多少种营救路线。
为了简化，每个地方都可以看作一个结点，两个地方之间的道路可以看作一条有向边，福杰在结点1，而阿尼亚在结点n。
福杰想知道结点1到达结点n到底有多少条不同的路线？（若两条路线中边不完全相同则认为这两条路线不同）
营救阿尼亚迫在眉睫，快来帮帮福杰救出可爱的阿尼亚吧！



阿尼亚：哇库哇库

输入格式
第一行两个整数n，m，分别表示点数和边数。
接下来m行，每行两个整数u，v，表示结点u和结点v中有一条有向边（u指向v）。

输出格式
一个整数，表示营救路线的种数，对998244353取模。
如果有无限多条，则输出-1。

样例输入1
7 7
1 3
1 4
3 7
4 7
5 6
6 5
3 4

样例输出1
3

样例输入2
7 8
1 3
1 4
3 7
4 7
5 6
6 5
3 4
4 3

样例输出2
-1

数据范围
1 <= n, m <= 10^6
1 <= u, v <= n

提示
可能有重边
仔细思考结果为无限多条的条件
*/
#include <iostream>
#include "stdio.h"

// C++ program to print DFS_path traversal from
// a given vertex in a given graph
#include <map>
#include <list>
using namespace std;

int n, m;

// Graph class represents a directed graph
// using adjacency list representation
class Graph
{
public:
  map<int, bool> onpath;
  map<int, list<int>> adj;
  map<int, bool> visited;
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
      for (auto ite = visited.begin(); ite != visited.end(); ite++)
        ite->second= 0;
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

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
  int find_loop(int u, int p, int onpath[]);   //遍历寻找环
  bool update(int u, int v, int w, int &ans1); //判断一个边是否值得加入
  void addEdge(int x, int y, int w)            //加边 加入边表
  {
    if (x == y) //再次避免自环
      return;
    edgelist.push_back({w, x, y});
  }

  void makeEdge(int u, int v, int w) //加边 加入邻接矩阵
  {
    adj[u][v] = w;
    adj[v][u] = w; // Add w to v’s list.
  }

  void delEdge(int u, int v) //删边 实际上使用makeedge参数为0即可
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
      if (adj[x][y]) //重边 后面的必然更大 直接扔了
        continue;

      // take that edge in MST if it does form a cycle
      if (s.find(x) != s.find(y))
      {
        s.unite(x, y);
        ans += w;
        makeEdge(x, y, w);
      }
    }
    return ans; // mst大小
  }
};

bool Graph::update(int u, int v, int w, int &ans1)
{
  if (u == v) //自环 直接N
    return 0;
  if (adj[u][v] > 0) //加的边已经在树里 如果更小 就更新
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
  //新边不在树里 一定产生环
  int save = adj[u][v]; //保存原先边
  makeEdge(u, v, w);    //加入新边
  int u0 = u, v0 = v;   //原先节点
  int x = u, y = v;     //未来最大边的两端

  int *onpath = new int[n]; //数组 倒着存parent 就是保存环的路径
  for (int i = 0; i < n; i++)
    onpath[i] = -1; //初始化 -1

  find_loop(u, -2, onpath); //从u开始寻找环 u的parent设为-2

  int maxw = 0; //未来最大边的weight

  while (v != u) //在环的路径数组里面遍历找最大边
  {
    if (adj[v][onpath[v]] > maxw) //更大
    {
      maxw = adj[v][onpath[v]];
      x = v;
      y = onpath[v];
    }
    v = onpath[v]; //更新
  }

  if (maxw > w) //最大边大于weight
  {
    ans1 -= (adj[x][y] - w); // mst大小降低
    addEdge(u0, v0, w);      //加入边集

    delEdge(x, y);//删去最大边
    return 1;
  }
  else
  {
    makeEdge(u0, v0, save);//不值得加这个边 恢复成原状
    return 0;
  }
}

int Graph::find_loop(int u, int p, int onpath[])
{
  onpath[u] = p;//将他路径上的parent存入数组
  for (int i = 0; i < n; i++)//遍历列
  {
    if (i == u)//跳过自己
      continue;
    if (adj[u][i])//若有边
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
  Graph g(n + 1);
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

#define DEBUG
/*
题目：链路广播

题目描述：

假设南大的局域网中有N个主机节点，有M条已经搭建好的链路，每条链路直接连接两台主机；

为了更好实现这些主机节点的数据共享，校领导希望从任意一个节点发送的数据帧都能以最小的总链路代价W0广播到所有其他节点；

同时校庆将至，校领导决定逐个更换或新建共K条链路，以进一步降低广播代价。但是他们并不知道第i+1条待更换或新修的链路是否能够真的降低目前的最小总链路代价Wi，如果是，则开始更换或搭建，更新好后再考虑第i+2条链路，否则就放弃该条，直接考虑第i+2条链路；

现在校领导求助算法学的很好的你，你能帮助他们解答上述问题吗？

提示0：

N个节点的节点标号依次为0~N-1；

每条链路用一个三元组(u,v,w)表示，其含义为节点u和节点v之间有一条代价为w的直接链路；

提示1：

输入格式：

第1行依次为N,M,K，三者以一个空格间隔，末尾无空格

第2~M+1行逐行给出M条已经搭建好的链路三元组，每行分量之间以一个空格间隔，末尾无空格

第M+2~M+K+1行逐行给出K条待更换或新建的链路三元组，每行分量之间以一个空格间隔，末尾无空格

输出格式：

第1行输出原局域网中广播的最小链路代价W0

第2~K+1行逐行输出第i+1条待更换或新修的链路是否真的能够降低Wi，是则输出大写字母'Y'，否则输出大写字母'N'

第K+2行输出考虑完所有待更换或新修的链路之后的Wk

提示2：

输入样例1：

5 5 4

0 1 4

0 2 3

0 3 4

0 4 5

2 4 6

2 3 2

2 4 7

0 4 4

1 3 4

输出样例1：

16

Y

N

Y

N

13

样例1解释：

原始的W0 = 16 → 节点2和3之间新修代价为2的链路后W1 = 14，因此搭建该链路，返回'Y' → 节点2和4之间的原链路若从6更新为7，W2 = W1 = 14，因此放弃该链路，返回'N' → 节点0和4之间原链路若从5更新为4，W3 = 13，因此搭建该链路，返回'Y' → 节点1和3之间新修代价为4的链路后W4 = W3 = 13，因此放弃该链路，返回'N' → 最终的W4 = 13

提示3：

2 ≤ N ≤ 103

M ≥ N, K ≥ 1, 4(M+K) ≤ N2

所有链路代价w均为正整数，且任意链路代价w满足：1 ≤ w ≤ 100

提示4：

要求：算法的时间复杂度不超过O(MlogN+KN)

语言：


*/
#include <iostream>
#include <list>
#include "stdio.h"
using namespace std;
int n, m, k;

#define SIZE 1000005
class Graph
{
public:
  list<node> adj[SIZE];
  bool visited[SIZE];

  // function to add an edge to graph
  void addEdge(int v, int w, int weight);

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
  cin >> n >> m >> k;

  system("pause");
  return 0;
}

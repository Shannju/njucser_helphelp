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
using namespace std;

#define V 500
#define INT_MAX 2147483647
int n, m, k;
int graph[V][V] = {0};
int parent[V];

int minKey(int key[], bool mstSet[]) // get the min node
{
  // Initialize min value
  int min = INT_MAX, min_index;

  for (int v = 0; v < n; v++)
    if (mstSet[v] == false && key[v] < min) // not in mst yet and has a shorter edge
      min = key[v], min_index = v;

  return min_index;
}

bool update(int u, int v, int w, int &ans)
{
  int max_weight = 0;
  while (u != 0)
  {
    max_weight = max(max_weight, graph[u][parent[u]]);
    u = parent[u];
  }
  while (v != 0)
  {
    max_weight = max(max_weight, graph[v][parent[v]]);
    v = parent[v];
  }
  if (max_weight > w)
  {
    ans -= max_weight - w;
    return 1;
  }
  else
    return 0;
}

int primMST()
{
  int ans = 0; // Array to store constructed MST

  // Key values used to pick minimum weight edge in cut
  int key[V];

  // To represent set of vertices included in MST
  bool mstSet[V];

  // Initialize all keys as INFINITE
  for (int i = 0; i < V; i++)
    key[i] = INT_MAX, mstSet[i] = false;

  // Always include first 1st vertex in MST.
  // Make key 0 so that this vertex is picked as first vertex.
  key[0] = 0;
  parent[0] = -1; // First node is always root of MST

  // The MST will have V vertices
  for (int count = 0; count < n; count++)
  {
    // Pick the minimum key vertex from the
    // set of vertices not yet included in MST
    int u = minKey(key, mstSet);

    ans += key[u];
    // Add the picked vertex to the MST Set
    mstSet[u] = true;

    // Update key value and parent index of
    // the adjacent vertices of the picked vertex.
    // Consider only those vertices which are not
    // yet included in MST
    for (int v = 0; v < n; v++)
    {
      // graph[u][v] is non zero only for adjacent vertices of m
      // mstSet[v] is false for vertices not yet included in MST
      // Update the key only if graph[u][v] is smaller than key[v]
      if (graph[u][v] && mstSet[v] == false && graph[u][v] < key[v])
        parent[v] = u, key[v] = graph[u][v];
    }
  }
  // printMST(parent, graph);
  return ans;
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
    graph[u][v] = graph[v][u] = w;
  }
  ans0 = primMST();
  ans1 = ans0;
  for (int i = 0; i < k; i++)
  {
    int u, v, w;
    cin >> u >> v >> w;
    if (update(u, v, w, ans1))
    {
      graph[u][v] = graph[v][u] = w;
      ans[count] = 1;
      count++;
    }
    else
    {
      ans[count] = 0;
      count++;
    }
  }
  // ans1 = primMST();

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

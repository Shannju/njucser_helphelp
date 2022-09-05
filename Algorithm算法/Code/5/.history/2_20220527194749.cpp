#define DEBUG
/*
 */
#include <iostream>
#include "stdio.h"
#include <list>
#include <vector>
#include <queue>

using namespace std;
#define INF 0x3f3f3f3f

int n, m;
typedef pair<int, int> iPair;

class Graph
{
  int V;
  list<pair<int, int>> *adj;
  list<pair<int, int>> *radj;
  vector<int> dist;
  vector<int> visited;
  vector<int> path_count;

public:
  Graph(int V);
  void addEdge(int u, int v, int w);
  int shortestPath(int s);
  void DFS_path(int v, int &count);
};

// Allocates memory for adjacency list
Graph::Graph(int V)
{
  this->V = V;
  adj = new list<iPair>[V + 1];
  radj = new list<iPair>[V + 1];
  dist = vector<int>(V + 1, INF);
  visited = vector<int>(V + 1, -1);
}

void Graph::addEdge(int u, int v, int w)
{
  adj[u].push_back(make_pair(v, w));
  radj[v].push_back(make_pair(u, w));
}

// Prints shortest paths from src to all other vertices
int Graph::shortestPath(int src)
{
  priority_queue<iPair, vector<iPair>, greater<iPair>> pq;

  // vector<int> dist(V, INF);

  // Insert source itself in priority queue and initialize
  // its distance as 0.
  pq.push(make_pair(0, src));
  dist[src] = 0;

  /* Looping till priority queue becomes empty (or all
  distances are not finalized) */
  while (!pq.empty())
  {
    // The first vertex in pair is the minimum distance
    // vertex, extract it from priority queue.
    // vertex label is stored in second of pair (it
    // has to be done this way to keep the vertices
    // sorted distance (distance must be first item
    // in pair)
    int u = pq.top().second;
    pq.pop();

    // 'i' is used to get all adjacent vertices of a vertex
    list<pair<int, int>>::iterator i;
    for (i = adj[u].begin(); i != adj[u].end(); ++i)
    {
      // Get vertex label and weight of current adjacent
      // of u.
      int v = (*i).first;
      int weight = (*i).second;

      // If there is shorted path to v through u.
      if (dist[v] > dist[u] + weight)
      {
        // Updating distance of v
        dist[v] = dist[u] + weight;
        pq.push(make_pair(dist[v], v));
      }
    }
  }
  return dist[V - 1];
  // Print shortest distances stored in dist[]
  // printf("Vertex Distance from Source\n");
  // for (int i = 0; i < V; ++i)
  //   printf("%d \t\t %d\n", i, dist[i]);
}

void Graph::DFS_path(int v, int &count)
{
  if (visited[v] != -1)
    return;
  visited[v] = 1;
  if (v == 1)
  {
    return;
  }

  auto ite = radj[v].begin();
  for (; ite != radj[v].end(); ite++)
  {
    int u = ite->first;

    if (dist[v] == dist[u] + ite->second)
    {
      DFS_path(u, count);
      count = (count + path_count[u]) % 998244353;
    }
  }
  path_count[v] = count;
  return;
}

int main()
{

  cin >> n >> m;
  Graph g(n + 1);
  for (int i = 0; i < m; i++)
  {
    int u, v, w;
    scanf("%d %d %d", &u, &v, &w);
    g.addEdge(u, v, w);
  }
  int cost = g.shortestPath(1);
  cout << cost << endl;
  int count = 0;
  g.DFS_path(n, count);
  cout << count % 998244353;

  system("pause");
  return 0;
}
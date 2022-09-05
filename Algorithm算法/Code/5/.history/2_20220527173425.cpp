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
  vector<int> dist, dist0;

public:
  Graph(int V);
  void addEdge(int u, int v, int w);
  int shortestPath(int s);
  // int count_shortestPath(int src);
  void DFS_path(int v, int val, int &cost, int &count);
};

// Allocates memory for adjacency list
Graph::Graph(int V)
{
  this->V = V;
  adj = new list<iPair>[V];
  dist = vector<int>(V, INF);
  dist0 = vector<int>(V, INF);
}

void Graph::addEdge(int u, int v, int w)
{
  adj[u].push_back(make_pair(v, w));
  adj[v].push_back(make_pair(u, w));
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

void Graph::DFS_path(int v, int val, int &cost, int &count)
{
  if (v == n)
  {
    if (val == cost)
      count++;
    return;
  }

  auto ite = adj[v].begin();
  for (; ite != adj[v].end(); ite++)
  {
    int w = ite->first;
    val += ite->second;
    DFS_path(w, val, cost, count);
  }

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
  cout << cost;
  int count = 0;
  g.DFS_path(1, 0, cost, count);
  cout << count;

  system("pause");
  return 0;
}
#define SIZE 1000005
class Graph
{
public:
  bool onpath[SIZE];
  list<int> adj[SIZE];
  bool visited[SIZE];
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

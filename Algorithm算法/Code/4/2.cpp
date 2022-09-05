#include <vector>
#include <string>
#include <list>
#include <cmath>
#include <iostream>
using namespace std;
char i2c(int c)
{
  // side = 'F' | 'B' | 'L' | 'R' | 'U' | 'D' |
  switch (c)
  {
  case 0:
    return 'F';
    break;
  case 1:
    return 'B';
    break;
  case 2:
    return 'L';
    break;
  case 3:
    return 'R';
    break;
  case 4:
    return 'U';
    break;
  case 5:
    return 'D';
    break;
  default:
    return ' ';
    break;
  }
}
int c2i(char c)
{
  // side = 'F' | 'B' | 'L' | 'R' | 'U' | 'D' |
  switch (c)
  {
  case 'F':
    return 0;
    break;
  case 'B':
    return 1;
    break;
  case 'L':
    return 2;
    break;
  case 'R':
    return 3;
    break;
  case 'U':
    return 4;
    break;
  case 'D':
    return 5;
    break;
  default:
    return -1;
    break;
  }
}
class Cube
{
  /* cube[0]:F | cube[1]:B | cube[2]:L | cube[3]:R | cube[4]:U | cube[5]:D */
private:
  vector<vector<vector<char>>> cube;
  int n;

public:
  // constructor
  int count;
  Cube(vector<string> &sideStr)
  {
    count = 0;
    n = (int)sqrt(sideStr[0].size()); // length of one side str is n^2
    cube = vector<vector<vector<char>>>(
        6, vector<vector<char>>(n, vector<char>(n, 'w')));
    for (int l = 0; l < 6; l++)
      for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
          cube[l][i][j] = sideStr[l][i * n + j];
  }
  // copy constructor
  Cube(const Cube &other)
  {
    this->cube = other.cube;
    this->n = other.n;
    this->count = other.count;
  }
  // getter and setter
  char getChar(int l, int i, int j) const
  {
    return cube[l][i][j];
  }
  int getN() const
  {
    return n;
  }
  void setChar(int l, int i, int j, char c)
  {
    cube[l][i][j] = c;
  }
  // key methods
  bool isResolved()
  { /* TODO:
to tell if the cube is resolved
*/
    for (int l = 0; l < 6; l++)
    {
      char c = cube[l][0][0];
      for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
          if (cube[l][i][j] != c)
            return 0;
    }

    return true;
  }
  void move(char side, bool cw)
  {
    /* TODO:
    move one key step:
    let one side rotate clockwise or counterclockwise by 90°
    params:
    side = 'F' | 'B' | 'L' | 'R' | 'U' | 'D' |
    cw = true => clockwise | false => counterclockwise
    */
    count++;
    int s = c2i(side);

    vector<vector<char>> cube_copy = cube[s];
    vector<vector<char>> f = cube[0];
    vector<vector<char>> b = cube[1];
    vector<vector<char>> l = cube[2];
    vector<vector<char>> r = cube[3];
    vector<vector<char>> u = cube[4];
    vector<vector<char>> d = cube[5];
    if (cw) // clockwise
    {
      for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
          cube[s][i][j] = cube_copy[n - 1 - j][i];
    }
    else
    {
      for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
          cube[s][i][j] = cube_copy[j][n - 1 - i];
    }

    switch (side)
    {
    case 'F':
      if (cw)
      {
        vector<char> tmp = u[n - 1];
        for (int i = 0; i != n; ++i)
          u[n - 1][n - i - 1] = l[i][n - 1];
        for (int i = 0; i != n; ++i)
          l[i][n - 1] = d[0][i];
        for (int i = 0; i != n; ++i)
          d[0][n - i - 1] = r[i][0];
        for (int i = 0; i != n; ++i)
          r[i][0] = tmp[i];
      }
      else
      {
        vector<char> tmp = u[n - 1];
        for (int i = 0; i != n; ++i)
          u[n - 1][i] = r[i][0];
        for (int i = 0; i != n; ++i)
          r[n - i - 1][0] = d[0][i];
        for (int i = 0; i != n; ++i)
          d[0][i] = l[i][n - 1];
        for (int i = 0; i != n; ++i)
          l[n - i - 1][n - 1] = tmp[i];
      }
      cube[1] = b;
      cube[2] = l;
      cube[3] = r;
      cube[4] = u;
      cube[5] = d;
      break;
    case 'B':
      if (cw)
      {
        vector<char> tmp = u[0];
        for (int i = 0; i != n; ++i)
          u[0][i] = r[i][n - 1];
        for (int i = 0; i != n; ++i)
          r[n - i - 1][n - 1] = d[n - 1][i];
        for (int i = 0; i != n; ++i)
          d[n - 1][i] = l[i][0];
        for (int i = 0; i != n; ++i)
          l[n - i - 1][0] = tmp[i];
      }
      else
      {
        vector<char> tmp = u[0];
        for (int i = 0; i != n; ++i)
          u[0][n - i - 1] = l[i][0];
        for (int i = 0; i != n; ++i)
          l[i][0] = d[n - 1][i];
        for (int i = 0; i != n; ++i)
          d[n - 1][n - i - 1] = r[i][n - 1];
        for (int i = 0; i != n; ++i)
          r[i][n - 1] = tmp[i];
      }
      cube[0] = f;
      // cube[1] = b;
      cube[2] = l;
      cube[3] = r;
      cube[4] = u;
      cube[5] = d;
      break;
    case 'L':
      if (cw)
      {
        vector<char> tmp(n, ' ');
        for (int i = 0; i != n; ++i)
          tmp[i] = u[i][0];
        for (int i = 0; i != n; ++i)
          u[n - i - 1][0] = b[i][n - 1];
        for (int i = 0; i != n; ++i)
          b[n - i - 1][n - 1] = d[i][0];
        for (int i = 0; i != n; ++i)
          d[i][0] = f[i][0];
        for (int i = 0; i != n; ++i)
          f[i][0] = tmp[i];
      }
      else
      {
        vector<char> tmp(n, ' ');
        for (int i = 0; i != n; ++i)
          tmp[i] = u[i][0];
        for (int i = 0; i != n; ++i)
          u[i][0] = f[i][0];
        for (int i = 0; i != n; ++i)
          f[i][0] = d[i][0];
        for (int i = 0; i != n; ++i)
          d[n - i - 1][0] = b[i][n - 1];
        for (int i = 0; i != n; ++i)
          b[n - i - 1][n - 1] = tmp[i];
      }
      cube[0] = f;
      cube[1] = b;
      // cube[2] = l;
      cube[3] = r;
      cube[4] = u;
      cube[5] = d;
      break;
    case 'R':
      if (cw)
      {
        vector<char> tmp(n, ' ');
        for (int i = 0; i != n; ++i)
          tmp[i] = u[i][n - 1];
        for (int i = 0; i != n; ++i)
          u[i][n - 1] = f[i][n - 1];
        for (int i = 0; i != n; ++i)
          f[i][n - 1] = d[i][n - 1];
        for (int i = 0; i != n; ++i)
          d[n - i - 1][n - 1] = b[i][0];
        for (int i = 0; i != n; ++i)
          b[n - i - 1][0] = tmp[i];
      }
      else
      {
        vector<char> tmp(n, ' ');
        for (int i = 0; i != n; ++i)
          tmp[i] = u[i][n - 1];
        for (int i = 0; i != n; ++i)
          u[n - i - 1][n - 1] = b[i][0];
        for (int i = 0; i != n; ++i)
          b[n - i - 1][0] = d[i][n - 1];
        for (int i = 0; i != n; ++i)
          d[i][n - 1] = f[i][n - 1];
        for (int i = 0; i != n; ++i)
          f[i][n - 1] = tmp[i];
      }
      cube[0] = f;
      cube[1] = b;
      cube[2] = l;
      // cube[3] = r;
      cube[4] = u;
      cube[5] = d;
      break;
    case 'U':
      if (cw)
      {
        vector<char> tmp = f[0];
        for (int i = 0; i != n; ++i)
          f[0][i] = r[0][i];
        for (int i = 0; i != n; ++i)
          r[0][i] = b[0][i];
        for (int i = 0; i != n; ++i)
          b[0][i] = l[0][i];
        for (int i = 0; i != n; ++i)
          l[0][i] = tmp[i];
      }
      else
      {
        vector<char> tmp = f[0];
        for (int i = 0; i != n; ++i)
          f[0][i] = l[0][i];
        for (int i = 0; i != n; ++i)
          l[0][i] = b[0][i];
        for (int i = 0; i != n; ++i)
          b[0][i] = r[0][i];
        for (int i = 0; i != n; ++i)
          r[0][i] = tmp[i];
      }
      cube[0] = f;
      cube[1] = b;
      cube[2] = l;
      cube[3] = r;
      // cube[4] = u;
      cube[5] = d;
      break;
    case 'D':
      if (cw)
      {
        vector<char> tmp = f[n - 1];
        for (int i = 0; i != n; ++i)
          f[n - 1][i] = l[n - 1][i];
        for (int i = 0; i != n; ++i)
          l[n - 1][i] = b[n - 1][i];
        for (int i = 0; i != n; ++i)
          b[n - 1][i] = r[n - 1][i];
        for (int i = 0; i != n; ++i)
          r[n - 1][i] = tmp[i];
      }
      else
      {
        vector<char> tmp = f[n - 1];
        for (int i = 0; i != n; ++i)
          f[n - 1][i] = r[n - 1][i];
        for (int i = 0; i != n; ++i)
          r[n - 1][i] = b[n - 1][i];
        for (int i = 0; i != n; ++i)
          b[n - 1][i] = l[n - 1][i];
        for (int i = 0; i != n; ++i)
          l[n - 1][i] = tmp[i];
      }
      cube[0] = f;
      cube[1] = b;
      cube[2] = l;
      cube[3] = r;
      cube[4] = u;
      // cube[5] = d;
      break;
    default:

      break;
    }
  }
};

int solve_cube(Cube &cube)
{
  /* TODO:
  to find the min steps k_min to resolve the cube
  */
  // return 0;
  list<Cube> queue;
  queue.push_back(cube);
  while (!queue.empty())
  {
    // Dequeue a vertex from queue and print it
    Cube s = queue.front();
    queue.pop_front();
    if (s.isResolved())
      return s.count;

    for (int i = 0; i < 6; i++)
    {
      char side = i2c(i);
      Cube adj0 = s;
      adj0.move(side, 0);
      queue.push_back(adj0);
      Cube adj1 = s;
      adj1.move(side, 1);
      queue.push_back(adj1);
    }
  }
}

int main()
{
  // input n
  int n;
  cin >> n;
  // input side string
  vector<string> sideStr(6, "");
  for (int l = 0; l < 6; l++)
  {
    cin >> sideStr[l];
  }
  // init cube
  Cube cube(sideStr);
  // TODO: solve cube
  int k = solve_cube(cube);
  // output k
  cout << k;

  // cube.move('U', 1);
  // cube.move('R', 0);
  // cout << cube.isResolved();

  system("pause");
  return 0;
}
#include <iostream>
#include "stdio.h"
#include <vector>
using namespace std;
int nx, kx, ny, ky;
#define INT_MAX 2147483647
int dp(int k, int n)
{
  vector<vector<int>> c(k, vector<int>(n + 1, INT_MAX)); // k egg n+1 floor

  for (int i = 0; i < k; i++) // zero floor
    c[i][0] = 0;
  for (int j = 1; j <= n; j++) // one egg
    c[0][j] = j;
  for (int i = 1; i < k; i++)    // egg
    for (int j = 1; j <= n; j++) // floor
    {
    int low = 1, high = j;
    int tmp = 0; //操作次数
    while (low <= high)
    {
      int mid = low + (high - low) / 2;
      int t1 = c[i - 1][mid - 1]; // broke, go down
      int t2 = c[i][j - mid];     // survive, floor higher
      tmp = 1 + max(t1, t2);
      c[i][j] = min(c[i][j], tmp);
      if (t1 > t2)
      {
        high = mid - 1;
      }
      else if (t1 < t2)
      {
        low = mid + 1;
      }
      else
      {
        break;
      }
    }
    }
  return c[k][n];
}

int main()
{
  cin >> nx >> kx >> ny >> ky;
  int fx = dp(ky, nx);
  int fy = dp(kx, ny);
  cout << min(fx, fy);

  system("pause");
  return 0;
}

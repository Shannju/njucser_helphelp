#define DEBUG
/*
叫什么高楼抛鸡蛋
输入样例1：

5 2

7 1

输出样例1：

4
*/
#include <iostream>
#include "stdio.h"
#include <vector>
using namespace std;
int nx, kx, ny, ky;
vector<vector<int>> c;
int superEggDrop(int k, int n)
{
  int dp[n + 1];
  for (int i = 0; i <= n; ++i)
  {
    dp[i] = i;
  }

  for (int j = 2; j <= k; ++j)
  {
    int dp2[n + 1];
    int x = 1;
    dp2[0] = 0;
    for (int m = 1; m <= n; ++m)
    {
      while (x < m && max(dp[x - 1], dp2[m - x]) >= max(dp[x], dp2[m - x - 1]))
      {
        x++;
      }
      dp2[m] = 1 + max(dp[x - 1], dp2[m - x]);
    }
    for (int m = 1; m <= n; ++m)
    {
      dp[m] = dp2[m];
    }
  }
  return dp[n];
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

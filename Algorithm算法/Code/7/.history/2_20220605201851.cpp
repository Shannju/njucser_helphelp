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
using namespace std;
int nx, kx, ny, ky;
#define SIZE 32
int c[SIZE][SIZE] = {0};
int dp(int k, int n)
{
  int ans;
  if (n == 0)
  {
    c[k][n] = 0;
    return 0;
  }

  else if (k == 1)
  {
    c[k][n] = n;
    return n;
  }

  else
  {
    int low = 1, high = n;
    while (low + 1 < high)
    {
      int x = (low + high) / 2;
      int t1 = dp(k - 1, x - 1);
      int t2 = dp(k, n - x);

      if (t1 < t2)
        low = x;
      else if (t1 > t2)
        high = x;
      else
        low = high = x;
    }

    ans = min(max(dp(k - 1, low - 1), dp(k, n - low)),
              max(dp(k - 1, high - 1), dp(k, n - high))) +
          1;
  }
  return ans;
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

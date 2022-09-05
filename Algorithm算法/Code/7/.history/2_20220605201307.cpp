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
int dp(int k, int n)
{
  int ans;
  if (n == 0)
    return 0;
  else if (k == 1)
    return n;
  else
  {
    int lo = 1, hi = n;
    while (lo + 1 < hi)
    {
      int x = (lo + hi) / 2;
      int t1 = dp(k - 1, x - 1);
      int t2 = dp(k, n - x);

      if (t1 < t2)
      {
        lo = x;
      }
      else if (t1 > t2)
      {
        hi = x;
      }
      else
      {
        lo = hi = x;
      }
    }

    ans = 1 + min(max(dp(k - 1, lo - 1), dp(k, n - lo)),
                  max(dp(k - 1, hi - 1), dp(k, n - hi)));
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

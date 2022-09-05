#include <iostream>
#include "stdio.h"
#include <vector>
using namespace std;
int nx, kx, ny, ky;
int dp(int k, int n)
{

  vector<vector<int>> c(k, vector<int>(n + 1, INT_MAX));//k egg n+1 floor

  for (int i = 0; i < k; i++)//zero floor
    c[i][0] = 0;
  for (int j = 1; j <= n; j++)// one egg
    c[0][j] = j;
  for (int i = 1; i < k; ++i)    //循环鸡蛋 1个蛋已经考虑过了 从2个鸡蛋(k==1)开始循环
    for (int j = 1; j <= n; ++j) // n层楼(总楼层)
    {
      int left = 1, right = j;
      int tmp = 0; //操作次数
      while (left <= right)
      {
        int mid = left + (right - left) / 2;
        int t1 = c[i - 1][mid - 1]; //鸡蛋碎了 随着mid递增
        int t2 = c[i][j - mid];     //鸡蛋没碎 随着mid递减
        // j-mid一定小于j所以 查找的t2一定已经计算过
        tmp = 1 + max(t1, t2);
        c[i][j] = min(c[i][j], tmp);
        if (t1 > t2)
        {
          //这里取大的保证最糟糕情况
          right = mid - 1;
        }
        else if (t1 < t2)
        {
          left = mid + 1;
        }
        else
        {
          break;
        }
      }
    }
  return c.back().back();
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

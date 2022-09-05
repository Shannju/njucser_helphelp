#define DEBUG
/*
题目：柴郡的天雷计划

题目描述：

柴郡为了庆祝周年庆，要帮指挥官偷别人的天雷图纸！
一共有n个地方的天雷图纸可以偷，第i个地方需要t[i]单位的石油，能偷到x[i]张天雷图纸，每个地方只能偷一次。
由于石油有限，只有m单位的石油，柴郡想知道用这些石油最多能偷到多少张天雷图纸？



输入格式
第一行两个整数，n和m，如题目所述。
接下来n行，每行两个整数t[i]和x[i]，如题目所述。

输出格式
一个整数，表示最多能偷取的天雷图纸。

样例输入
3 70
71 100
69 1
1 2

样例输出
3

数据范围
1 <= n，m <= 2000
1 <= t[i] <= m
1 <= x[i] <= 100


f[v]=max{f[v],f[v-w[i]]+v[i]}

*/
#include <iostream>
#include "stdio.h"
using namespace std;
int w[2048];
int val[2048];
int c[2048][2048];
int knapSack(int n, int m) // i 物品数目 j 容量
{
  for (int i = 1; i < n; i++)
  {
    for (int j = 0; j < m; j++)
    {
      if (j == 0)
        c[i][j] = 0;
      else
      {
        if (j >= w[i-1])
          c[i][j] = max(c[i - 1][j], c[i - 1][j - w[i-1]] + val[i-1]);
        else
          c[i][j] = c[i - 1][j];
      }
    }
  }
}

// Driver code
int main()
{
  int n, m;
  cin >> n >> m;
  for (int i = 0; i < n; i++)
  {
    cin >> w[i] >> val[i];
  }

  knapSack(n+1, m+1);
  cout << c[n][m];

  system("pause");
  return 0;
}

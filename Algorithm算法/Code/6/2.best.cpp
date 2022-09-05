#define DEBUG
/*
题目：悸动战士的DD

题目描述：

又一届SIF开始了，悸动战士高咲侑终于摆脱了严防死守的步女士，又可以开始DD了！
在SIF中，一共有n个位置可以观赏学园偶像的表演，有m场演出可供观看。
第i场演出演出时间为t[i]，演出位置为a[i]，获取最大的悸动值为b[i]，
如果在位置x观看演出，则会获得b[i]-|a[i]-x|的悸动值（可以为负）。
侑每个单位时间能移动不大于d单位的距离，同时不能走到这n个位置以外，初始可以在任意位置。
她想知道能获取最大的悸动值是多少，你能帮帮她吗？



输入格式
第一行三个整数n，m，d，如题目所述。
接下来m行，每行三个整数a[i]，b[i]，t[i]，如题目所述。

输出格式
一个整数，表示获取的最大悸动值。

样例输入1
50 3 1
49 1 1
26 1 4
6 1 10

样例输出1
-31

样例输入2
10 2 1
1 1000 4
9 1000 4

样例输出2
1992

数据范围
90%的数据，1 <= n，m <= 100，0<= d <= n，1 <= a[i] <= n，1 <= b[i]，t[i] <= 10^9
剩下10%的数据，n=m=2000，0 <= d <= n，1 <= a[i] <= n，1 <= b[i]，t[i] <= 10^9
保证t[i]单调不减

提示
你能先想出一个O(n^2m)的dp方程吗？
试着化简它，把求解max的无关项放到max之外。
你能试着用数据结构来优化求解这个化简后的dp方程吗，让它降到O(nm)？
注意max的求解区间有一定范围。
*/
#include <iostream>
#include "stdio.h"
using namespace std;
#define SIZE 2048
#define INT_MIN -2147483648
int a[SIZE];
int b[SIZE];
int t[SIZE];
int c[SIZE][SIZE];
int d;
void f(int n, int m)
{
  for (int i = 0; i < m; i++) // dance
  {
    int save = INT_MIN;
    for (int j = 1; j < n + 1; j++) // location
    {
      if (i == 0)
      {
        c[0][j] = b[0] - abs(a[0] - j);
        continue;
      }
      else
      {
        int delt = t[i] - t[i - 1];
        if (delt == 0)
        {
          c[i][j] = c[i - 1][j] + b[i] - abs(a[i] - j);
          continue;
        }
        else
        {
          int tmp;
          tmp = c[i - 1][j];
          int begin = max(1, j - d * delt );
          int end = min(n + 1, j + d * delt );
          if (begin == 1 && end == n + 1 && save != INT_MIN)
          {
            c[i][j] = save + b[i] - abs(a[i] - j);
            continue;
          }

          for (int k = begin; k < end; k++)
          {
            tmp = max(tmp, c[i - 1][k]);
          }

          if (begin == 1 && end == n + 1)
            save = max(tmp, save);

          c[i][j] = tmp + b[i] - abs(a[i] - j);
        }
      }
    }
  }
}

int main()
{
  int n, m;
  cin >> n >> m >> d;
  for (int i = 0; i < m; i++)
    cin >> a[i] >> b[i] >> t[i];
  f(n, m);
  int ans = INT_MIN;
  for (int i = 1; i < n + 1; i++)
  {
    ans = max(ans, c[m - 1][i]);
  }
  cout << ans;
  system("pause");
  return 0;
}

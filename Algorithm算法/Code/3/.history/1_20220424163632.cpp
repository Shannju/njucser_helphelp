#define DEBUG
/*
题目：并查集

题目描述：

如题，现在有一个并查集，你需要完成合并和查询操作。

输入格式
第一行包含两个整数N，M，表示共有N个元素和M个操作。
接下来M行，每行三个整数Zi，Xi，Yi。
当Zi=1时，将Xi与Yi所在的集合合并。
当Zi=2时，输出Xi与Yi是否在同一集合内，是的输出Y；否则输出N。

输出格式
对于每个Zi=2的操作，都有一行输出，每行包含一个大写字母，为Y或者N。

样例输入
4 7
2 1 2
1 1 2
2 1 2
1 3 4
2 1 4
1 2 3
2 1 4

样例输出
N
Y
N
Y

数据范围
1 <= N <= 10^6
1 <= M <= 10^6
1 <= Xi, Yi <= N
Zi = 1 or 2

语言：
*/
#include <iostream>
#include "stdio.h"
using namespace std;
int find(int x, int f[])
{
  if (f[x] != x)
    f[x] = find(f[x], f);
  return f[x];
}

void merge(int x, int y, int f[])
{
  int fx = find(f[x], f);
  int fy = find(f[y], f);
  f[fx] = fy;
}

int main()
{
  int n, m;
  cin >> n >> m;
  int *f = new int[n + 1];
  char *ans = new int[m];
  for (int i = 0; i <= n; i++)
    f[i] = i;
  int count = 0;
  for (int i = 0; i < m; i++)
  {
    int x, y, z;
    cin >> z >> x >> y;
    if (z == 1)
      merge(x, y, f);
    else
    {
      int tmp = (find(x, f) == find(y, f));
      if (tmp)
        ans[count] = 'Y';
      else
        ans[count] = 'N';
    }
  }

  system("pause");
  return 0;
}

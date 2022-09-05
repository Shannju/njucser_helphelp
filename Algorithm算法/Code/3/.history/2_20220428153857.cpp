#define DEBUG
/*
题目：做作业

题目描述：

假设算法课开学就布置好了一学期的作业，共N章课后习题，第i章的习题量为homework[i] (1 ≤ i ≤ N)，要求在一学期之内（共W周）做完

现在你准备制定一个做作业的计划，规定自己每周做K道题，但是有些限制条件需要考虑：

① 由于老师1周只讲1章新的内容，因此第i周结束时最多能做完前i章的题；

② 由于期中考试周（第⌊W/2⌋周）和期末考试周（第W周）需要复习已做过的题，因此这两周不做新题；

为了每周末能按时赶去跳广场舞，你想尽量减小每周的题量K，但是又得保证在ddl前做完所有作业，请设计一个算法，帮助自己找到满足以上所有条件的K的最小值

提示1：

输入格式：

第一行依次为数组homework的大小N、一学期的周数W，二者以一个空格间隔，末尾无空格

第二行为数组homework，相邻元素之间以一个空格间隔，末尾无空格

输出格式：

一个正整数，即K的最小值

提示2：

输入样例1：

6 8

3 4 5 6 2 1

输出样例1：

4

样例1解释：

① 若K=4：前2周显然全部做完 => 第3周5题做了4道，还剩1道 => 第4周期中考试，复习不做题，累计1+6=7道题没做 => 第5周做题前累计可做7+2=9道，做了4道，还剩5道 => 第6周做题前累计可做5+1=6道，做了4道，还剩2道 => 第7周做题前所有作业还剩2道，可全部做完 => 第8周期末考试，复习不做题 => 学期结束后做完所有作业，满足条件

② 若K=3：第一周刚好做完 => 第2周4题做了3道，还剩1道 => 第3周做题前累计可做1+5=6道，做了3道，还剩3道 => 第4周期中考试，复习不做题，累计3+6=9道题没做 => 第5周做题前累计可做9+2=11道，做了3道，还剩8道 => 第6周做题前累计可做8+1=9道，做了3道，还剩6道 => 第7周做题前所有作业还剩6道，做了3道，还剩3道 => 第8周期末考试，复习不做题 => 学期结束后还有3道题没做，不满足条件

综合①②：K ≥ 4 => Kmin = 4

提示3：

1 ≤ N < W < 2N ≤ 10^6

数组homework中任意元素hi满足：1 ≤ hi ≤ N

提示4：

要求：算法的时间复杂度应该不超过O(NlogN)

语言：
*/
#include <iostream>
#include "stdio.h"
using namespace std;
bool ddl(int k);
int n, w;
int *hw;
int binarySearch(int l, int r)
{
  if (r >= l)
  {
    int mid = l + (r - l) / 2;
    if (ddl(mid))
    {
      if (!ddl(mid - 1))
        return mid;
      else
        return binarySearch(l, mid - 1);
    }
    else
      return binarySearch(mid + 1, r);
  }
  return -1;
}

bool ddl(int k)
{
  int left = 0;
  int i = 0;
  for (; i < n; i++)
  {
    left += hw[i];
    if (i == w / 2 - 1 || i == w - 1)
      continue;
    else
      left -= k;
    left = max(left, 0);
  }
  for (; i < w; i++)
  {
    if (i == w / 2 - 1 || i == w - 1)
      continue;
    else
      left -= k;
    left = max(left, 0);
  }
  return left == 0;
}

int main()
{
  cin >> n >> w;
  hw = new int[w];
  for (int i = 0; i < n; i++)
    cin >> hw[i];
  cout << binarySearch(1, 2 * n);
  // ddl(4);

  system("pause");
  return 0;
}

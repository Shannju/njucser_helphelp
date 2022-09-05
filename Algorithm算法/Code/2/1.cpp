#define DEBUG
/*
题目描述：

东海帝王当上特雷森学园学生会长后，打算做一套成绩管理系统，便于赛马娘们管理自己的比赛用时以提升自我。
但是特雷森学园并没有程序员，于是只好拜托各位小蓝鲸们！
这个系统其实很简单，要求是这样的：
赛马娘们每次可以录入自己的比赛用时，然后系统能够反馈出来自己这次的用时比之前多少次快。
你能帮帮无敌⭐可爱的帝宝吗？

输入格式
第一行，一个整数n，表示有n个成绩待录入。
接下来n行，每行一个整数a[i]，表示第i次成绩。

输出格式
共n行，第i行表示第i次成绩比之前多少次快。

样例输入
6
5
4
2
6
3
1

样例输出
0
1
2
0
3
5

10
2
3
5
7
11
32
9
8
1
6
样例说明
以第3次录入成绩为例，第3次成绩为2，比第1次和第2次都快，所以输出2。

数据范围
1 <= n <= 10^5
1 <= a[i] <= 10^5

提示
归并排序是一种离线算法，但是这道题是一道在线问题，你能将这个问题转化成离线问题吗？

语言：


C
源码:
*/
#include <iostream>
#include "stdio.h"
#include <vector>

using namespace std;

int n;
vector<int> arr;
int ans[100005];

int BinInsertSort(int n)
{
  int i = n - 1, j, low, mid, high, temp;
  temp = arr[i]; // 辅助变量temp用来保存待排序的元素
  low = 0;
  high = i - 1;       // 有序区间为[0,i-1]
  while (low <= high) // 在有序区间内采用折半查找，找到插入位置
  {
    mid = (low + high) / 2;
    if (arr[mid] > temp)
      high = mid - 1;
    else
      low = mid + 1;
  }
  for (j = i - 1; j >= high + 1; j--) // 移动元素，腾出空间
    arr[j + 1] = arr[j];
  arr[high + 1] = temp; // 将待排序的元素插入
  return high + 1;
}

int Insert(int x)
{
  if (arr.size() == 0)
  {
    arr.push_back(x);
    return 0;
  }
  arr.push_back(x);
  int index = BinInsertSort(arr.size());
  return arr.size()-index-1;
}

int main()
{
  cin >> n;
  int tmp;
  for (int i = 0; i < n; i++)
  {
    cin >> tmp;
    ans[i] = Insert(tmp);
  }
  for (int i = 0; i < n; i++)
    cout << ans[i] << endl;

  system("pause");
  return 0;
}

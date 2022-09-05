#define DEBUG
/*
题目：多选问题

题目描述：

给定一个大小为n的整数数组A={a1,a2,..,an}，和一个由m个不同的正整数组成的升序数组K={k1,k2,..,km}，请设计算法依次返回数组A中第k1,k2,..,km小的数

提示1：

输入格式：

第一行依次为数组A、K的大小n、m，二者以一个空格间隔，末尾无空格

第二行为数组A，相邻元素之间以一个空格间隔，末尾无空格

第三行为数组K，相邻元素之间以一个空格间隔，末尾无空格

输出格式：

一行，依次为数组A中第k1,k2,..,km小的数，相邻元素之间以一个空格间隔，末尾无空格

提示2：

输入样例1：

5 3
1 3 2 5 4
2 3 5

10 3
1 3 5 7 9 2 4 8 6 8
2 3 5 

输出样例1：

2 3 5

提示3：

要求：算法的时间复杂度应低于O(nm)，且选择算法不能直接调用任何库函数

提示4：

1 < m < n < 107

数组A中任意元素ai满足：-231 <= ai <= 231-1

数组K中任意元素kj满足：1 <= kj <= n

语言：

*/
#include <iostream>
#include "stdio.h"
#include <vector>
#include <algorithm>

using namespace std;
int BFPRT(vector<int> &array, int left, int right, int k);

int InsertSort(vector<int> &array,  int left, int right)
{
  int temp;
  int j;

  for (int i = left + 1; i <= right; i++)
  {
    temp = array[i];
    j = i - 1;

    while (j >= left && array[j] > temp)
    {
      array[j + 1] = array[j];
      j--;
    }

    array[j + 1] = temp;
  }

  return ((right - left) >> 1) + left;
}

int GetPivotIndex(vector<int> &array,  int left, int right)
{
  if (right - left < 5)
    return InsertSort(array, left, right);

  int sub_right = left - 1;

  // 每五个作为一组，求出中位数，并把这些中位数全部依次移动到数组左边
  for (int i = left; i + 4 <= right; i += 5)
  {
    int index = InsertSort(array, i, i + 4);
    swap(array[++sub_right], array[index]);
  }

  // 利用 BFPRT 得到这些中位数的中位数下标（即主元下标）
  return BFPRT(array, left, sub_right, ((sub_right - left + 1) >> 1) + 1);
}

int Partition(vector<int> &array,  int left, int right, int pivot_index)
{
  swap(array[pivot_index], array[right]); // 把主元放置于末尾

  int partition_index = left; // 跟踪划分的分界线
  for (int i = left; i < right; i++)
  {
    if (array[i] < array[right])
    {
      swap(array[partition_index++], array[i]); // 比主元小的都放在左侧
    }
  }
  swap(array[partition_index], array[right]); // 最后把主元换回来

  return partition_index;
}

int BFPRT(vector<int> &array, int left, int right, int k)
{
  if ()
  int pivot_index = GetPivotIndex(array, left, right);              // 得到中位数的中位数下标（即主元下标）
  int partition_index = Partition(array, left, right, pivot_index); // 进行划分，返回划分边界
  int num = partition_index - left + 1;

  if (num == k)
    return partition_index;
  else if (num > k)
    return BFPRT(array, left, partition_index - 1, k);
  else
    return BFPRT(array, partition_index + 1, right, k - num);
}

int main()
{
  int n, k;
  cin >> n >> k;
  vector<int> arr;
  for (int i = 0; i < n; i++)
  {
    int tmp;
    cin >> tmp;
    arr.push_back(tmp);
  }
  auto b = arr.begin();
  auto end = arr.end();
  unique(b, end);
  n = arr.size();
  int *ans = new int[k];
  for (int i = 0; i < k; i++)
  {
    int tmp;
    cin >> tmp;
    ans[i] = BFPRT(arr, 0, n - 1, tmp + 1);
  }
  for (int i = 0; i < k; i++)
    cout << ans[i] << " ";
  system("pause");
  return 0;
}

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

using namespace std;

int InsertSort(int array[], int left, int right)
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

int partition(int array[], int left, int right, int pivot_index)
{
  swap(array[pivot_index], array[right]); // 把主元放置于末尾
  int partition_index = left;             // 跟踪划分的分界线
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

void QuickSort(int a[], int l, int r)
{
  if (r - l + 1 < 10)
  {
    InsertSort(a, l, r);
    return;
  }
  if (l < r)
  {
    int k = partition(a, l, r, (l + r) >> 1);
    QuickSort(a, l, k - 1);
    QuickSort(a, k + 1, r);
  }
}

int kthSmallest(int arr[], int l, int r, int k)
{
  if (k > 0 && k <= r - l + 1)
  {
    int index = partition(arr, l, r,(l+r)>>1);
    if (index - l == k - 1)
      return arr[index];
    if (index - l > k - 1)
      return kthSmallest(arr, l, index - 1, k);
    return kthSmallest(arr, index + 1, r, k - index + l - 1);
  }
}

int main()
{
  int n, k;
  cin >> n >> k;
  int *arr = new int[n];
  for (int i = 0; i < n; i++)
  {
    int tmp;
    cin >> tmp;
    arr[i] = tmp;
  }
  int *ans = new int[k];
  if (k > n / 16)
  {
    QuickSort(arr, 0, n - 1);//k不大
    for (int i = 0; i < k; i++)
    {
      int tmp;
      cin >> tmp;
      ans[i] = arr[tmp - 1];
    }
  }
  else
  {
    for (int i = 0; i < k; i++)//k很大
    {
      int tmp;
      cin >> tmp;
      ans[i] = kthSmallest(arr, 0, n - 1, tmp);
    }
  }

  for (int i = 0; i < k; i++)
    cout << ans[i] << " ";
  system("pause");
  return 0;
}

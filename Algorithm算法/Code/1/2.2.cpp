#define DEBUG
/*
题目：回形排序

题目描述：

给定一个自然数数组，请你原地对其进行“回形排序”，并输出排序后的数组

提示1：

所谓“回形排序”，即排好序的数组A满足大小关系：A[0]≤A[2]≤A[4]≤...≤A[2k]≤(A[2k+1])≤A[2k-1]≤A[2k-3]≤...≤A[3]≤A[1]，其中数组长度n = 2k+1(此时A[2k+1]不存在) 或 2k+2(此时A[2k+1]存在)

例如：数组"1 3 5 2 6 4"回形排序后为：“1 6 2 5 3 4”；数组“2 4 7 1 5 3 6”回形排序后为：“1 7 2 6 3 5 4”

提示2：

输入数据的格式为：第一行为表示数组长度的正整数，第二行为待排序数组

输入/输出数组的格式为：任意相邻数组元素之间用一个空格隔开，末尾元素后无空格

提示3：

要求：算法的最坏时间复杂度为：O(nlogn)，空间复杂度不超过：O(logn)（递归栈深度）

值得注意的是：快速排序的最坏时间复杂度为O(n2)，这本身是无法改变的，但是可以通过改进partition的pivot选取方案来尽量避免极不平衡的划分，否则可能无法通过所有测试用例

常用的改进方案包括“三元取中法”、“随机选取法”等，请自行设计或查阅资料

提示4：

数组长度n满足：1 ≤ n ≤ 104

任意数组元素t(i,a)满足：0 ≤ t(i,a) ≤ 104
*/

#include <iostream>
#include "stdio.h"
using namespace std;
int improve(int a[], int l, int r);
int n = 0;

int &t(int x, int a[])
{
  if (x <= (n - 1) / 2)
  {
    int &ans = a[2 * x];
    return ans;
  }
  else
  {
    int &ans = a[n + 1 - 2 * (x - (n - 1) / 2)];
    return ans;
  }
}

int partition(int a[], int l, int r) // basic partition
{
  int i = l;
  int j = r;
  int pivot = t(l, a);
  while (i < j)
  {
    while (t(j, a) >= pivot && i < j)
      j--;
    t(i, a) = t(j, a);
    while (t(i, a) <= pivot && i < j)
      i++;
    t(j, a) = t(i, a);
  }
  t(i, a) = pivot;
  return i;
}

void QuickSort(int a[], int l, int r)
{
  if (l < r)
  {
    int k = improve(a, l, r);
    QuickSort(a, l, k - 1);
    QuickSort(a, k + 1, r);
  }
}

int kth_smallest(int arr[], int l, int r, int k)
{
  if (k < 0 || k > r - l + 1)
  {
    return -1;
  }
  // partition the array (similar to quicksort)
  int index = partition(arr, l, r);

  // if position same as k return rank-k element
  if (index - l == k - 1)
    return t(index,arr);

  // if rank-k element is less, look in left sub-array
  if (index - l > k - 1)
    return kth_smallest(arr, l, index - 1, k);
  else // look in right sub-array
    return kth_smallest(arr, index + 1, r, k - index + l - 1);
}

int improve(int a[], int l, int r)
{
  int mid = kth_smallest(a, l, r, (r + l) / 2);
  int i = l;
  for (; i <= r; i++)
    if (mid == t(i, a))
      break;
  swap(t(l,a), t(i, a));
  return partition(a, l, r);
}

int main()
{
  int i = 0;
  int a[10] = {0};
  int tmp;
  while (1)
  {
    cin >> tmp;
    n++;
    a[i] = tmp;
    i++;
    if (cin.get() == '\n') //如果是回车符则跳出循环
      break;
  }

  QuickSort(a, 0, n - 1);
  for (int j = 0; j < n; j++)
    cout << a[j] << " ";

  system("pause");
  return 0;
}

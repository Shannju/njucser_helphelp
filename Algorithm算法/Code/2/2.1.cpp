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

void merge(int arr[], int left, int mid, int right)
{
  int s1 = mid - left + 1;
  int s2 = right - mid;
  int *arr1 = new int[s1],
      *arr2 = new int[s2];
  for (int i = 0; i < s1; i++)
    arr1[i] = arr[left + i];
  for (int j = 0; j < s2; j++)
    arr2[j] = arr[mid + 1 + j];

  int idxl = 0,    // Initial index of first sub-arr
      idxr = 0;    // Initial index of second sub-arr
  int idxm = left; // Initial index of merged arr
  while (idxl < s1 && idxr < s2)
  {
    if (arr1[idxl] <= arr2[idxr]) //选中左边
    {
      arr[idxm] = arr1[idxl];
      idxl++;
    }
    else //选中右边
    {
      arr[idxm] = arr2[idxr];
      idxr++;
    }
    idxm++;
  }
  while (idxl < s1) //右边好了 左边还剩
  {
    arr[idxm] = arr1[idxl];
    idxl++;
    idxm++;
  }
  while (idxr < s2) //左边好
  {
    arr[idxm] = arr2[idxr];

    idxr++;
    idxm++;
  }
}

void mergeSort(int arr[], int begin, int end)
{
  if (begin >= end)
    return; // Returns recursively
  int mid = (begin + end) >> 1;
  mergeSort(arr, begin, mid);
  mergeSort(arr, mid + 1, end);
  merge(arr, begin, mid, end);
}

int find(int *arr, int x)
{
  int p = 0;
  while (x)
  {
    if (arr[p] == arr[p + 1])
    {
      p++;
      continue;
    }
    else
      x--;
    p++;
  }
  return arr[p-1];
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
  mergeSort(arr, 0, n - 1);
  int *ans = new int[k];
  for (int i = 0; i < k; i++)
  {
    int tmp;
    cin >> tmp;
    ans[i] = find(arr, tmp);
  }
  for (int i = 0; i < k; i++)
    cout << ans[i] << " ";
  system("pause");
  return 0;
}

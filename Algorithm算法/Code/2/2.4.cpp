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
int select(int A[], int p, int r, int k);

int insert_sort(int A[], int len)
{
  for (int j = 1; j < len; ++j)
  {
    int key = A[j];
    // insert A[j] into the sorted sequence A[0..j-1]
    int i = j - 1;
    // 注意是 i >= 0 而不是 i > 0
    while (i >= 0 && A[i] > key)
    {
      A[i + 1] = A[i];
      --i;
    }

    A[i + 1] = key;
  }
  return A[len / 2];
}

int find_median(int A[], int p, int r)
{
  int len = r - p + 1;

  int *temp = new int[len / 5 + 1];

  int start = p;
  int end = p;
  int j = 0;

  for (int i = 0; i < len; ++i)
  {
    if (i % 5 == 0)
      start = start + i;

    if ((i + 1) % 5 == 0 || i == len - 1)
    {
      end = end + i;
      int small_median = insert_sort(A, end - start + 1);
      temp[j] = small_median;
      ++j;
    }
  }
  int total_median = select(temp, 0, j - 1, (j - 1) / 2);

  delete[] temp;

  return total_median;
}

int partition(int A[], int p, int r, int num)
{
  for (int i = p; i <= r; i++)
  {
    if (A[i] == num)
    {
      swap(A[i], A[r]);
      break;
    }
  }

  int x = A[r];
  int i = p - 1;

  for (int j = p; j < r; ++j)
  {
    if (A[j] <= x)
    {
      ++i;
      swap(A[i], A[j]);
    }
  }

  swap(A[i + 1], A[r]);

  return i + 1;
}

int select(int A[], int p, int r, int k)
{
  if (p == r)
    return A[p];

  int num = find_median(A, p, r);
  int mid = partition(A, p, r, num);

  int count = mid - p + 1;
  if (k == count)
    return A[mid];
  else if (k < count)
    return select(A, p, mid - 1, k);
  else
    return select(A, mid + 1, r, k - count);
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
  for (int i = 0; i < k; i++)
  {
    int tmp;
    cin >> tmp;
    ans[i] = select(arr, 0, n - 1, tmp);
  }
  for (int i = 0; i < k; i++)
    cout << ans[i] << " ";
  system("pause");
  return 0;
}

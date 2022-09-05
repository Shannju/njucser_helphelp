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
1 3 5 7 9 2 4 6 8 10
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
void swap_arr(int a[], int i, int j)
{
  int temp = a[i];
  a[i] = a[j];
  a[j] = temp;
}

void insertSort(int a[], int law, int high)
{ //插入排序
  for (int i = law + 1; i <= high; i++)
  {
    int key = a[i];
    int j = i - 1;
    while (j >= law && a[j] > key)
    {
      a[j + 1] = a[j];
      j--;
    }
    a[j + 1] = key;
  }
}

int median_five(int arr[], int begin, int num)
{
  if (num == 5)
  {
    int a = arr[begin], b = arr[begin + 1], c = arr[begin + 2], d = arr[begin + 3], e = arr[begin + 4];
    if (a < b)
      swap(a, b);
    if (c < d)
      swap(c, d);
    if (a < c)
    {
      swap(a, c);
      swap(b, d);
    }
    if (b < e)
      swap(b, e);
    if (b < c)
    {
      swap(b, c);
      swap(d, e);
    }
    if (e < c)
      return c;
    else
      return e;
  }
  else
  {
    insertSort(arr, begin, begin + num - 1);
    return arr[begin + num >> 1 - 1];
  }
}

int partition(int arr[], int l, int r, int b)
{
  int index;
  for (int i = l; i <= r; i++)
  {
    if (arr[i] == b)
    {
      index = i;
      break;
    }
  }
  swap_arr(arr, r, index);

  int x = arr[r], i = l;
  for (int j = l; j <= r - 1; j++)
  {
    if (arr[j] <= x)
    {
      swap(arr[i], arr[j]);
      i++;
    }
  }
  swap(arr[i], arr[r]);
  return i;
}
int partition(int arr[], int l, int r)
{
  int x = arr[r], i = l;
  for (int j = l; j <= r - 1; j++)
  {
    if (arr[j] <= x)
    {
      swap(arr[i], arr[j]);
      i++;
    }
  }
  swap(arr[i], arr[r]);
  return i;
}

int kthSmallest(int arr[], int l, int r, int k)
{
  if (k > 0 && k <= r - l + 1)
  {
    int index = partition(arr, l, r);
    if (index - l == k - 1)
      return arr[index];
    if (index - l > k - 1)
      return kthSmallest(arr, l, index - 1, k);
    return kthSmallest(arr, index + 1, r, k - index + l - 1);
  }
}

int wlinear_selection(int *A, int l, int r, int k)
{
  if (l == r)
    return A[l];
  int n = r - l + 1; // number of elements in A[1..r]
  if (n < 5)
  {
    insertSort(A, l, r);
    return A[l + k - 1];
  }
  // divide A in groups of size 5, and find median for each group
  int i;
  int *M = new int[(n + 4) / 5]; // ceil (n/ 5)- floor ( (n+4)/ 5)
  for (i = 0; i < n / 5; i++)
  {
    M[i] = median_five(A, l + i * 5, 5);
  }
  if (i * 5 < n)
  { // last group maybe vith less than 5 elema
    M[i] = median_five(A, l + i * 5, n % 5);
    i++;
  }
  // recurse to find median of M
  int m = wlinear_selection(M, 0, i - 1, i / 2);
  delete[] M; // free temporary M
  // partition A with m
  int q = partition(A, l, r, m);
  // recurse in left or right half part
  if (q == k - 1) // found
    return A[q];
  else if (q < k - 1) // recurse in right part
    return wlinear_selection(A, q + 1, r, k - q - 1);
  else // recurse in left part
    return wlinear_selection(A, l, q - 1, k);
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
    ans[i] = wlinear_selection(arr, 0, n - 1, tmp);
  }
  for (int i = 0; i < k; i++)
    cout << ans[i] << " ";
  system("pause");
  return 0;
}

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
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;

void maxHeapify(vector<int> &a, int i, int heapSize)
{
  int l = i * 2 + 1, r = i * 2 + 2, largest = i;
  if (l < heapSize && a[l] > a[largest])
  {
    largest = l;
  }
  if (r < heapSize && a[r] > a[largest])
  {
    largest = r;
  }
  if (largest != i)
  {
    swap(a[i], a[largest]);
    maxHeapify(a, largest, heapSize);
  }
}

void buildMaxHeap(vector<int> &a, int heapSize)
{
  for (int i = heapSize / 2; i >= 0; --i)
  {
    maxHeapify(a, i, heapSize);
  }
}

int findKthLargest(vector<int> &nums, int k)
{
  int heapSize = nums.size();
  buildMaxHeap(nums, heapSize);
  for (int i = nums.size() - 1; i >= nums.size() - k + 1; --i)
  {
    swap(nums[0], nums[i]);
    --heapSize;
    maxHeapify(nums, 0, heapSize);
  }
  return nums[0];
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
    arr.push_back(-tmp);
  }
  auto b = arr.begin();
  auto end = arr.end();
  unique(b, end);
  buildMaxHeap(arr, n);
  int *ans = new int[k];
  for (int i = 0; i < k; i++)
  {
    int tmp;
    cin >> tmp;
    auto begin = arr.begin();
    vector<int> arrk(begin, begin + pow(2, k));
    ans[i] = -findKthLargest(arrk, tmp);
  }
  for (int i = 0; i < k; i++)
    cout << ans[i] << " ";
  system("pause");
  return 0;
}

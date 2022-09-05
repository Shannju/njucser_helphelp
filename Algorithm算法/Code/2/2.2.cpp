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

// int partition(int arr[], int l, int r)
// {
//   int x = arr[r], i = l;
//   for (int j = l; j <= r - 1; j++)
//   {
//     if (arr[j] <= x)
//     {
//       swap(arr[i], arr[j]);
//       i++;
//     }
//   }
//   swap(arr[i], arr[r]);
//   return i;
// }

// int kthSmallest(int arr[], int l, int r, int k)
// {
//   if (k > 0 && k <= r - l + 1)
//   {
//     int index = partition(arr, l, r);
//     if (index - l == k - 1)
//       return arr[index];
//     if (index - l > k - 1)
//       return kthSmallest(arr, l, index - 1, k);
//     return kthSmallest(arr, index + 1, r, k - index + l - 1);
//   }
// }
// void mergeSort(int a[], int law, int high);
int partition(int a[], int l, int r, int pivot);
void swap(int a[], int i, int j);

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
      // ans[arr[idxm].id] += s1 - idxl;
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

int select(int a[], int l, int r, int k)
{
  if (r - l < 75)
  {
    mergeSort(a, l, r); //用快速排序进行排序
    return a[l + k - 1];
  }
  int group = (r - l + 5) / 5;
  for (int i = 0; i < group; i++)
  {
    int left = l + 5 * i;
    int right = (l + i * 5 + 4) > r ? r : l + i * 5 + 4; //如果超出右边界就用右边界赋值
    int mid = (left + right) / 2;
    mergeSort(a, left, right);
    swap(a, l + i, mid); // 将各组中位数与前i个
  }
  int pivot = select(a, l, l + group - 1, (group + 1) / 2); //找出中位数的中位数
  int p = partition(a, l, r, pivot);                        //用中位数的中位数作为基准的位置
  int leftNum = p - l;                                      // leftNum用来记录基准位置的前边的元素个数
  if (k == leftNum + 1)
    return a[p];
  else if (k <= leftNum)
    return select(a, l, p - 1, k);
  else //若k在基准位子的后边，则要从基准位置的后边数起，即第（k - leftNum - 1）个
    return select(a, p + 1, r, k - leftNum - 1);
}

int partition(int a[], int l, int r, int pivot)
{ //适用于线性时间选择的partition方法
  int i = l;
  int j = r;
  while (true)
  {
    while (a[i] <= pivot && i < r)
      ++i; // i一直向后移动，直到出现a[i]>pivot
    while (a[j] > pivot)
      --j; // j一直向前移动，直到出现a[j]<pivot
    if (i >= j)
      break;
    swap(a, i, j);
  }
  a[l] = a[j];
  a[j] = pivot;
  return j;
}
void mergeSort(int a[], int law, int high)
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
void swap(int a[], int i, int j)
{
  int temp = a[i];
  a[i] = a[j];
  a[j] = temp;
}

// int find(int *arr, int x)
// {
//   int p = 0;
//   while (x)
//   {
//     if (arr[p] != arr[p + 1])
//       x--;
//     else
//       p++;
//   }
//   return arr[p];
// }

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
  // mergeSort(arr, 0, n);
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

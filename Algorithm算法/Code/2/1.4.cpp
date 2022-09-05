#define DEBUG
/*
 */
#include <iostream>
#include "stdio.h"
using namespace std;

int ans[100001] = {0};

struct p
{
  int val;
  int id;
  bool operator>(const p &d)
  {
    if (val > d.val)
    {
      return true;
    }
    return false;
  }
  bool operator<=(const p &d)
  {
    if (val <= d.val)
    {
      return true;
    }
    return false;
  }
};

void merge(p arr[], int left, int mid, int right)
{
  int s1 = mid - left + 1;
  int s2 = right - mid;
  p *arr1 = new p[s1],
    *arr2 = new p[s2];
  for (int i = 0; i < s1; i++)
    arr1[i] = arr[left + i];
  for (int j = 0; j < s2; j++)
    arr2[j] = arr[mid + 1 + j];

  int idxl = 0,    // Initial index of first sub-arr
      idxr = 0;    // Initial index of second sub-arr
  int idxm = left; // Initial index of merged arr
  while (idxl < s1 && idxr < s2)
  {
    if (arr1[idxl] <= arr2[idxr])//选中左边
    {
      arr[idxm] = arr1[idxl];
      idxl++;
    }
    else//选中右边
    {
      arr[idxm] = arr2[idxr];
      ans[arr[idxm].id] += s1-idxl;
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

void mergeSort(p arr[], int begin, int end)
{
  if (begin >= end)
    return; // Returns recursively
  int mid = (begin + end) >> 1;
  mergeSort(arr, begin, mid);
  mergeSort(arr, mid + 1, end);
  merge(arr, begin, mid, end);
}

int main()
{
  int n;
  cin >> n;
  int tmp;
  p *arr = new p[n];
  for (int i = 0; i < n; i++)
  {
    cin >> tmp;
    arr[i] = p{tmp, i};
  }
  mergeSort(arr, 0, n - 1);
  for (int i = 0; i < n; i++)
    cout << ans[i] << endl;

  system("pause");
  return 0;
}

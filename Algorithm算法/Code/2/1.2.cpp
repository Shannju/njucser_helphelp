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
int arr[10];
int ans[10];

void merge(int array[], int const left, int const mid, int const right)
{
  auto const subArrayOne = mid - left + 1;
  auto const subArrayTwo = right - mid;
  auto *leftArray = new int[subArrayOne],
       *rightArray = new int[subArrayTwo];
  for (auto i = 0; i < subArrayOne; i++)
    leftArray[i] = array[left + i];
  for (auto j = 0; j < subArrayTwo; j++)
    rightArray[j] = array[mid + 1 + j];

  auto indexOfSubArrayOne = 0,   // Initial index of first sub-array
      indexOfSubArrayTwo = 0;    // Initial index of second sub-array
  int indexOfMergedArray = left; // Initial index of merged array
  while (indexOfSubArrayOne < subArrayOne && indexOfSubArrayTwo < subArrayTwo)
  {
    if (leftArray[indexOfSubArrayOne] <= rightArray[indexOfSubArrayTwo])
    {
      array[indexOfMergedArray] = leftArray[indexOfSubArrayOne];
      indexOfSubArrayOne++;
    }
    else
    {
      array[indexOfMergedArray] = rightArray[indexOfSubArrayTwo];
      indexOfSubArrayTwo++;
    }
    indexOfMergedArray++;
  }
  while (indexOfSubArrayOne < subArrayOne)
  {
    array[indexOfMergedArray] = leftArray[indexOfSubArrayOne];
    indexOfSubArrayOne++;
    indexOfMergedArray++;
  }
  while (indexOfSubArrayTwo < subArrayTwo)
  {
    array[indexOfMergedArray] = rightArray[indexOfSubArrayTwo];
    indexOfSubArrayTwo++;
    indexOfMergedArray++;
  }
}

void mergeSort(int array[], int const begin, int const end)
{
  if (begin >= end)
    return; // Returns recursively

  auto mid = begin + (end - begin) / 2;
  mergeSort(array, begin, mid);
  mergeSort(array, mid + 1, end);
  merge(array, begin, mid, end);
}

void printArray(int A[], int size)
{
  for (auto i = 0; i < size; i++)
    cout << A[i] << " ";
}

int binarySearch(int arr[], int l, int r, int x)
{
    if (r >= l) {
        int mid = l + (r - l) / 2;
        if (arr[mid] == x)
            return mid;
        if (arr[mid] > x)
            return binarySearch(arr, l, mid - 1, x);
        return binarySearch(arr, mid + 1, r, x);
    }
}
 

int Insert(int arr[],int x,int len)
{
  arr[len]=x;
  if (len== 0)
    
    return 0;
  mergeSort(arr,0,len);
  return len-binarySearch(arr,0,len,x);
}

int main()
{
  cin >> n;
  int tmp;
  for (int i = 0; i < n; i++)
  {
    cin >> tmp;
    ans[i] = Insert(arr,tmp,i);
  }
  for (int i = 0; i < n; i++)
    cout << ans[i] << endl;

  system("pause");
  return 0;
}

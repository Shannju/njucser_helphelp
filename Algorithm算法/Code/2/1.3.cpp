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

class BST
{
  int data;

  BST *left, *right, *p;

public:
  // Default constructor.
  BST();
  int weight;
  int lweight;
  // Parameterized constructor.
  BST(int);

  // Insert function.
  BST *Insert(BST *, int);

  // Inorder traversal.
  int larger(BST *root);
  BST *Search(BST *, int);
};

BST ::BST()
    : data(0), left(NULL), right(NULL),weight(0),lweight(0)
{
}

BST ::BST(int value)
{
  data = value;
  left = right = NULL;
  weight = 0;
  lweight = 0;
}

BST *BST ::Insert(BST *root, int value)
{
  if (!root)
  {
    return new BST(value);
  }
  if (value > root->data)
  {

    root->right = Insert(root->right, value);
    root->right += 1 + root->lweight;
  }
  else
  {
    root->lweight++;
    root->left = Insert(root->left, value);
  }
  return root;
}

BST *BST ::Search(BST *root, int x)
{
  if (!root)
  {
    return root;
  }
  if (root->data == x)
    return root;
  if (x > root->data)
    return Search(root->right, x);
  else
    return Search(root->left, x);
}

int n;
int ans[10];
BST *r = NULL;
int main()
{
  cin >> n;
  int tmp;

  for (int i = 0; i < n; i++)
  {
    cin >> tmp;
    BST *t;
    r = r->Insert(r, tmp);
    t = r->Search(r, tmp);
    ans[i] = i - t->weight;
  }
  for (int i = 0; i < n; i++)
    cout << ans[i] << endl;

  system("pause");
  return 0;
}

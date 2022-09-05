#define DEBUG

#include <iostream>
#include "stdio.h"
#include <cstring>
using namespace std;
#define SIZE 10002
int n;
int a[SIZE] = {0};
int s[SIZE] = {0};
int l[SIZE][SIZE] = {0};
int r[SIZE][SIZE] = {0};
// bool sign[SIZE];

// 2）对于3~10，牌所得分的绝对值等于其牌面的大小

// 3）对于JQKA2，牌所得分的绝对值依次为11~15
void a_str(string s)
{
  for (int i = 1; i <= n; i++)
  {
    char c = s[i - 1];
    if (c >= '3' && c <= '9')
      a[i] = c - '0';
    else if (c == '0')
      a[i] = 10;
    else if (c == 'J')
      a[i] = 11;
    else if (c == 'Q')
      a[i] = 12;
    else if (c == 'K')
      a[i] = 13;
    else if (c == 'A')
      a[i] = 14;
    else if (c == '2')
      a[i] = 15;
  }
}

// 1）红桃(记作'r')和方块牌(记作’s‘)得分为正，
// 黑桃(记作'b')和梅花牌(记作'p')得分为负
void sign_str(string s)
{
  for (int i = 1; i <= n; i++)
  {
    char c = s[i - 1];
    int sign = (c == 'r' || c == 's');
    if (!sign)
      a[i] = -a[i];
  }
}

void f()
{
  s[0] = 0;
  for (int i = 1; i <= n; i++)
  {
    s[i] = s[i - 1] + a[i];
    l[i][i] = r[i][i] = a[i];
  }
  for (int i = n; i >= 1; i--)
    for (int j = i + 1; j <= n; j++)
    {
      l[i][j] = a[i] + max(l[i + 1][j], s[j] - s[i] - max(l[i + 1][j], r[i + 1][j]));
      r[i][j] = a[j] + max(r[i][j - 1], s[j - 1] - s[i - 1] - max(l[i][j - 1], r[i][j - 1]));
    }
}

int main()
{
  cin >> n;
  string nstr, cstr;
  cin >> nstr >> cstr;
  a_str(nstr);
  sign_str(cstr);
  f();
  int x = max(l[1][n], r[1][n]);
  cout << 2 * x - s[n];
  system("pause");
  return 0;
}

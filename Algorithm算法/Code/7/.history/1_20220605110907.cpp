#define DEBUG
/*
题目：扑克游戏I

题目描述：

一个月黑风高的夜，有两个高智商犯罪集团，分别称X党和Y党，合伙抢劫了一家赌场，但是在分赃时却出现了分歧，X党老大提议利用赌场里随处可见的扑克牌，和Y党老大玩一局游戏，以决定分赃的比例。

提示0：

游戏规则如下：

① 将赌场里的除了大小王的扑克牌收集起来，随机打乱，明牌摊开在桌子上，排成一行牌组

② X党老大先手，每轮两党老大轮流从牌组的左端或右端连续抽取任意非零数量的牌，直到牌全部抽完为止

③ 最后计算X党老大和Y党老大所抽牌的总分之差D，若D大于0，则X党多拿|D|万元；若D小于0，则Y党多拿|D|万元；若D等于0，则两党各分一半

④ 具体的计分规则如下：

1）红桃(记作'r')和方块牌(记作’s‘)得分为正，黑桃(记作'b')和梅花牌(记作'p')得分为负

2）对于3~10，牌所得分的绝对值等于其牌面的大小

3）对于JQKA2，牌所得分的绝对值依次为11~15

⑤ 假设两党老大都足够聪明

提示1：

输入格式：

第一行为牌组的大小N

第二行为牌面字符串nstr，其中nstr[i]表示从左往右数的第i+1张牌的牌面字符，10用'0'表示 (0 ≤ i ≤ N-1)

第三行为花色字符串cstr，其中cstr[i]表示从左往右数的第i+1张牌的花色字符 (0 ≤ i ≤ N-1)

输出格式：

一个整数，即X、Y党老大所抽牌的总分之差D

提示2：

输入样例1：

4

JQ3A

rbsp

输出样例1：

16

样例1解释：

每张牌的得分依次为11 -12 3 -14，X党老大先手会从左端选3张，得分11-12+3 = 2，Y党老大后手只能选最后1张，得分-14，D = 2 - (-14) = 16；

如果X党老大只从左端选1张，得分虽然为11更高，但是Y党老大会选择2、3张，将-14留给X党老大；故最终X党老大得分11-14 = -3，Y党老大得分-12+3 = -9，D = -3 - (-9) = 6，虽然X党也能赢但并非最优方案；

提示3：

1 ≤ N ≤ 104

|D| ≤ 106

提示4：

要求：算法时间复杂度不超过O(N2)
*/
#include <iostream>
#include "stdio.h"
using namespace std;
int n;
int val[1024];
bool sign[1024];

// 1）红桃(记作'r')和方块牌(记作’s‘)得分为正，黑桃(记作'b')和梅花牌(记作'p')得分为负

// 2）对于3~10，牌所得分的绝对值等于其牌面的大小

// 3）对于JQKA2，牌所得分的绝对值依次为11~15
void val_str(string s)
{
  for (int i = 0; i < n; i++)
  {
    char c = str[i];
    if (c >= '3' && c < '9')
      val[i] = c - '0';
    else if (c=='0')
    val[i]=10;
        else if(c=='2')
    val[i]=15;
    else if(c=='2')
    val[i]=15;
  }
}
int main()
{
  cin >> n;
  string nstr, cstr;
  cin >> nstr >> cstr;
  val_str(nstr);

  system("pause");
  return 0;
}

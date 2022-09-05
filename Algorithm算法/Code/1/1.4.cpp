#include <iostream>
#include "stdio.h"
using namespace std;

long long d[100005] = {0}; // the sum of dis if we build the station here
int n, k;
long long a[100005] = {0}; // the map
long long sum_all = 0;
int len;
int mid;

void dis()
{
  d[1] = sum_all;
  d[0] = (sum_all + n + a[0]);
  long long suml = 0, numl = 0;
  int i = 1;
  for (; i < max(0, mid - k - 2); i++)
  {
    suml += a[i - 1] * (i - 1);
    numl += a[i - 1];
  }
  for (; i < min(mid + k + 1, len + 1); i++)
  {
    suml += a[i - 1] * (i - 1);
    numl += a[i - 1];
    d[i + 1] = ((2 * numl + a[i] - n) * i + sum_all - a[i] * i - 2 * suml);
  }
  return;
}

int main()
{
  cin >> n >> k;
  int maxx = -1;
  for (int i = 0; i < n; i++) // count the stages
  {
    int tmp;
    scanf("%d", &tmp);
    sum_all += tmp;
    a[tmp]++;
    maxx = max(maxx, tmp);
  }
  len = maxx;
  mid = len / 2 + 1;

  dis();
  long long ans = d[mid];
  int pl = mid - 1, pr = mid + 1, count = 1;
  while (count < k)
  {
    if (d[pl] < d[pr] && pl > 0)
    {
      ans += d[pl];
      pl--;
    }
    else if (d[pl] < d[pr] && pl > 0)
    {
      ans += d[pr];
      pr++;
    }
    else if ((d[pl] >= d[pr] && pr < len))
    {
      ans += d[pr];
      pr++;
    }
    else if (d[pl] >= d[pr] && pr >= len)
    {
      ans += d[pl];
      pl--;
    }
    count++;
  }

  // for (int i = max(0, mid - k - 1); i < k + max(0, mid - k - 1); i++)
  //   ans += d[i];
  cout << ans << endl;

  system("pause");
  return 0;
}

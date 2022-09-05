int find(int x, int f[])
{
  if (f[x] != x)
    f[x] = find(f[x], f);
  return f[x];
}

void merge(int x, int y, int f[])
{
  int fx = find(f[x], f);
  int fy = find(f[y], f);
  f[fx] = fy;
}
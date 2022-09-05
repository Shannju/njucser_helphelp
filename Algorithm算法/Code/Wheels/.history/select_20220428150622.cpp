int partition(int a[], int l, int r) // basic partition
{
  int i = l;
  int j = r;
  int pivot = a[l];
  while (i < j)
  {
    while (a[j] >= pivot && i < j)
      j--;
    a[i] = a[j];
    while (a[i] <= pivot && i < j)
      i++;
    a[j] = a[i];
  }
  a[i] = pivot;
  return i;
}
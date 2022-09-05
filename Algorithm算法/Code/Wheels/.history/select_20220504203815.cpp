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
int kth_smallest(int arr[], int l, int r, int k)
{
  if (k < 0 || k > r - l + 1)
  {
    return -1;
  }
  // partition the array (similar to quicksort)
  int index = partition(arr, l, r);

  // if position same as k return rank-k element
  if (index - l == k - 1)
    return arr[index];

  // if rank-k element is less, look in left sub-array
  if (index - l > k - 1)
    return kth_smallest(arr, l, index - 1, k);
  else // look in right sub-array
    return kth_smallest(arr, index + 1, r, k - index + l - 1);
}
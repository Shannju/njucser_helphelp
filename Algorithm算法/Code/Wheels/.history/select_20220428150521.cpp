
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
    return t(index,arr);

  // if rank-k element is less, look in left sub-array
  if (index - l > k - 1)
    return kth_smallest(arr, l, index - 1, k);
  else // look in right sub-array
    return kth_smallest(arr, index + 1, r, k - index + l - 1);
}
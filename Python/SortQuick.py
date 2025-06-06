# 215. Kth Largest Element in an Array
# Find the kth largest element in an unsorted array. Note that it is the kth largest element in the sorted order, not the kth distinct element.
def kSort(self, a, l, r, k):
  """
    Finds the kth largest element in the array 'a' within the sub-array a[l...r].

    This function implements a variation of the quickselect algorithm. It partitions
    the array around a pivot element and recursively searches in the appropriate
    subarray.

    Args:
      a: The input list of numbers.
      l: The left index of the current sub-array.
      r: The right index of the current sub-array.
      k: The desired rank (kth largest) to find. Note that 'k' is 1-indexed
         in the problem description, but typically converted to 0-indexed for array access.
         Here, it seems 'k' is treated as a 0-indexed target index after sorting.

    Returns:
      None. The function modifies the array 'a' in-place such that the kth
      largest element will eventually be at its sorted position, though not
      guaranteed to be returned directly by this recursive helper.

    Time Complexity:
      Average Case: O(N) - On average, each partition step reduces the problem
                      size significantly.
      Worst Case: O(N^2) - If the pivot selection consistently leads to highly
                     unbalanced partitions (e.g., always picking the smallest or largest element).

    Space Complexity:
      O(log N) on average due to recursion stack depth.
      O(N) in worst case due to recursion stack depth.
  """
  # Initialize left pointer, right pointer, and pivot.
  # Pivot is chosen as the middle element.
  i, j, p = l, r, a[(l + r) >> 1]

  # Partitioning phase
  while i < j:
    # Increment i while a[i] is less than the pivot.
    while a[i] < p:
      i += 1
    # Decrement j while a[j] is greater than the pivot.
    while a[j] > p:
      j -= 1
    # If i <= j, swap elements at i and j, then move pointers.
    if i <= j:
      a[i], a[j] = a[j], a[i]
      i += 1
      j -= 1

  # Recursive calls based on the position of k relative to the partitioned segments
  # If the target k is in the left partition
  if l < j and k <= j:
    self.kSort(a, l, j, k)
  # If the target k is in the right partition
  if i < r and k >= i:
    self.kSort(a, i, r, k)


def findKthLargest(self, nums, k):
  """
    :type nums: List[int]
    :type k: int
    :rtype: int
    """
  self.kSort(nums, 0, len(nums) - 1, len(nums) - k)
  return nums[len(nums) - k]

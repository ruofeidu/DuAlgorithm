import math


def merge_sort(arr: list[int], left: int, right: int) -> None:
  """
    Sorts a sub-array of 'arr' from index 'left' to 'right' (inclusive)
    using the Merge Sort algorithm.

    Time Complexity: O(N log N)
    Space Complexity: O(N) due to the temporary array used in merging.

    Args:
        arr: The list of integers to be sorted.
        left: The starting index of the sub-array (inclusive).
        right: The ending index of the sub-array (inclusive).
    """
  # Basic validation for the range.
  if not isinstance(arr, list) or not all(isinstance(x, int) for x in arr):
    raise TypeError("Input 'arr' must be a list of integers.")
  if not isinstance(left, int) or not isinstance(right, int):
    raise TypeError("'left' and 'right' must be integers.")

  # Base case: If the sub-array has one or zero elements, it's already sorted.
  if left >= right:
    return

  # Calculate the middle point of the sub-array.
  # Using 'left + (right - left) // 2' prevents potential integer overflow
  # that could occur with '(left + right) // 2' for very large indices
  # (though less common in Python due to arbitrary precision integers).
  mid = left + (right - left) // 2

  # Recursively sort the left half.
  merge_sort(arr, left, mid)
  # Recursively sort the right half.
  merge_sort(arr, mid + 1, right)

  # Merge the two sorted halves: [left, mid] and [mid + 1, right].
  left_idx = left
  right_idx = mid + 1
  merged_size = right - left + 1  # Total number of elements in the current merged segment.

  # Create a temporary list to store the merged elements.
  temp_array = [0] * merged_size

  # Iterate through the temporary array, filling it with sorted elements.
  for k in range(merged_size):
    # Case 1: The right sub-array is exhausted or the current element
    # from the left sub-array is smaller.
    if right_idx > right or (left_idx <= mid and
                             arr[left_idx] < arr[right_idx]):
      temp_array[k] = arr[left_idx]
      left_idx += 1
    # Case 2: The left sub-array is exhausted or the current element
    # from the right sub-array is smaller (or equal, for stable sort).
    else:
      temp_array[k] = arr[right_idx]
      right_idx += 1

  # Copy the sorted elements from the temporary array back to the original list.
  # Pythonic way to copy a slice back.
  for k in range(merged_size):
    arr[left + k] = temp_array[k]

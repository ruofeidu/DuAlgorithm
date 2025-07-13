import math


def bubble_sort(arr: list[int], left: int, right: int) -> None:
  """
    Sorts a sub-array of 'arr' from index 'left' to 'right' (inclusive)
    using the Bubble Sort algorithm.

    Args:
        arr: The list of integers to be sorted.
        left: The starting index of the sub-array (inclusive).
        right: The ending index of the sub-array (inclusive).
    """
  # Basic validation for the range to avoid out-of-bounds access
  # and handle cases where sorting is not needed (e.g., empty or single-element range).
  if not isinstance(arr, list) or not all(isinstance(x, int) for x in arr):
    raise TypeError("Input 'arr' must be a list of integers.")
  if not isinstance(left, int) or not isinstance(right, int):
    raise TypeError("'left' and 'right' must be integers.")

  if left < 0 or right >= len(arr) or left >= right:
    return

  # Using 'swapped_in_pass' as a flag for optimization.
  swapped_in_pass: bool

  # Outer loop: iterates through the passes. After each pass 'k',
  # the (k+1)-th largest element from the unsorted part is in its final place.
  # We effectively reduce the sorting range from the 'right' side.
  for i in range(left, right + 1):
    swapped_in_pass = False  # Reset flag for each pass.
    # Inner loop: compares adjacent elements and swaps them if they are in
    # the wrong order. The upper bound 'right - (i - left)' decreases
    # with each pass, as elements from the right end become sorted.
    # The `+ 1` in range ensures the last element for comparison is included.
    for j in range(left, right - (i - left)):
      if arr[j] > arr[j + 1]:
        arr[j], arr[j + 1] = arr[j + 1], arr[j]
        swapped_in_pass = True  # Indicate that a swap occurred in this pass.
    # Optimization: If no swaps occurred in an entire pass,
    # the sub-array is already sorted, so we can break early.
    if not swapped_in_pass:
      break

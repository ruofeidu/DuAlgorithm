from typing import List
import math


# Scanning from left to right.
# Time complexity: O(M)
# Space complexity: O(M)
def getMaxAdditionalDinersCount(N: int, K: int, M: int, S: list[int]) -> int:
  """
  Calculates the maximum number of additional diners that can be seated.

  This function determines how many more diners can be seated on a long bench
  of 'N' seats, given 'M' existing diners at specific seat positions 'S',
  and a minimum 'K' empty seats required between any two diners.

  Args:
    N: The total number of seats on the bench.
    K: The minimum number of empty seats required between any two diners.
    M: The number of existing diners.
    S: A list of integers representing the seat positions of the existing diners.

  Returns:
    The maximum number of additional diners that can be seated.

  Time Complexity:
    O(M log M) due to the sorting of the 'S' list.
    The iteration through 'S' is O(M).
    The `countNewDinerInInterval` function takes O(1) time.

  Space Complexity:
    O(1) if sorting is in-place and no extra space is used for the list `S`.
    O(M) if a copy of `S` is made for sorting (language-dependent).
  """
  if not S:
    # If there are no existing diners, all seats can be filled as long as
    # they respect the K-seat separation.
    # The first diner can be at seat 1. The next at 1 + K + 1, and so on.
    # Total available slots = N / (K + 1)
    # The ceiling is used because even a partial (K+1) segment can fit one diner.
    return math.ceil(N / (K + 1))

  S.sort()  # Sort the existing diner positions to easily calculate intervals.

  res = 0  # Initialize the count of additional diners.

  def countNewDinerInInterval(l, r, k):
    """
    Calculates the number of new diners that can be seated in a given interval [l, r].

    Args:
      l: The left boundary of the interval (inclusive).
      r: The right boundary of the interval (exclusive).
      k: The minimum number of empty seats required between diners.

    Returns:
      The number of new diners that can be seated in the interval.
    """

    if r - l - 2 * (k + 1) >= 0:
      return 1 + (r - l - 2 * (k + 1)) // (k + 1)
    else:
      return 0

  res += countNewDinerInInterval(-K, S[0], K)
  print(res)

  for i in range(M - 1):
    res += countNewDinerInInterval(S[i], S[i + 1], K)
    print(res)

  res += countNewDinerInInterval(S[M - 1], N + K + 1, K)
  print(res)

  return res


getMaxAdditionalDinersCount(10, 1, 2, [2, 6])
getMaxAdditionalDinersCount(15, 2, 3, [11, 6, 14])

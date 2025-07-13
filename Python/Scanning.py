# 238. Product of Array Except Self [M]
# Given an array nums of n integers where n > 1,  return an array output such that output[i] is equal to the product of all the elements of nums except nums[i].
def productExceptSelf(self, nums):
  """
	:type nums: List[int]
	:rtype: List[int]
	"""
  if not nums:
    return []
  n = len(nums)
  left, right = [1] * n, 1
  for i in range(1, n):
    left[i] = left[i - 1] * nums[i - 1]
  for i in range(n - 2, -1, -1):
    right *= nums[i + 1]
    left[i] *= right
  return left


def getArtisticPhotographCount(N, C, X, Y):
  """
  For every A, find how many Ps are there in front, how mnay Bs are there in back.
  Find Ps, sumP[r] - sumP[l] etc.
  Time complexity: O(N)
  Space complexity: O(N)
  """
  sumP = [0 for i in range(N + 1)]
  sumB = [0 for i in range(N + 1)]

  for i, c in enumerate(C):
    sumP[i + 1] = sumP[i] + int(c == 'P')
    sumB[i + 1] = sumB[i] + int(c == 'B')

  def getP(l, r):
    left = 0 if l < 0 else (sumP[l] if l <= N else sumP[N])
    right = (sumP[r + 1] if
             (r + 1 >= 0) else sumP[0]) if r + 1 <= N else sumP[N]
    return right - left

  def getB(l, r):
    left = 0 if l < 0 else (sumB[l] if l <= N else sumB[N])
    right = (sumB[r + 1] if
             (r + 1 >= 0) else sumB[0]) if r + 1 <= N else sumB[N]
    return right - left

  res = 0
  for i, c in enumerate(C):
    if c == 'A':
      numP = getP(i - Y, i - X)
      numB = getB(i + X, i + Y)
      res += numP * numB

      numB = getB(i - Y, i - X)
      numP = getP(i + X, i + Y)
      res += numP * numB

  return res


getArtisticPhotographCount(5, 'APABA', 1, 2)
getArtisticPhotographCount(5, 'APABA', 2, 3)
getArtisticPhotographCount(8, '.PBAAP.B', 1, 3)


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

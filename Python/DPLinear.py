import heapq
import math
from typing import List, Set


class DP1D:
  """
    A collection of 1D dynamic programming solutions.
    """

  def trap(self, height: List[int]) -> int:
    """
    42. Trapping Rain Water
    Given n non-negative integers representing an elevation map where the width
    of each bar is 1, compute how much water it can trap after raining.
    """
    n = len(height)
    if n < 3:
      return 0

    lmax = [0] * n
    rmax = [0] * n

    lmax[0] = height[0]
    rmax[n - 1] = height[n - 1]

    for i in range(n - 1):
      lmax[i + 1] = max(lmax[i], height[i + 1])
      rmax[n - 2 - i] = max(rmax[n - 1 - i], height[n - 2 - i])

    ans = 0
    for i in range(1, n - 1):
      ans += min(lmax[i], rmax[i]) - height[i]

    return ans

  def minCost(self, costs: List[List[int]]) -> int:
    """
    256. Paint House
    There is a row of n houses, each house can be painted with one of the 3
    colors. The cost of painting each house with a certain color is different.
    You have to paint all the houses such that no two adjacent houses have the
    same color. Find the minimum cost to paint all houses.
    """
    if not costs or not costs[0]:
      return 0

    dp = costs
    for i in range(1, len(dp)):
      # Cost of painting house i with color 0
      dp[i][0] += min(dp[i - 1][1], dp[i - 1][2])
      # Cost of painting house i with color 1
      dp[i][1] += min(dp[i - 1][0], dp[i - 1][2])
      # Cost of painting house i with color 2
      dp[i][2] += min(dp[i - 1][0], dp[i - 1][1])

    return min(dp[-1])

  def candy(self, ratings: List[int]) -> int:
    """
    135. Candy
    There are N children standing in a line. Each child is assigned a rating
    value. You are giving candies to these children subjected to the following
    requirements:
    - Each child must have at least one candy.
    - Children with a higher rating get more candies than their neighbors.
    What is the minimum number of candies you must give?
    """
    n = len(ratings)
    if n == 0:
      return 0

    f = [1] * n  # Longest increasing from left
    g = [1] * n  # Longest increasing from right

    for i in range(1, n):
      if ratings[i] > ratings[i - 1]:
        f[i] = f[i - 1] + 1

    for i in range(n - 2, -1, -1):
      if ratings[i] > ratings[i + 1]:
        g[i] = g[i + 1] + 1

    ans = 0
    for i in range(n):
      ans += max(f[i], g[i])

    return ans

  def wordBreak(self, s: str, wordDict: Set[str]) -> bool:
    """
    139. Word Break
    Given a non-empty string s and a dictionary wordDict containing a list of
    non-empty words, determine if s can be segmented into a space-separated
    sequence of one or more dictionary words.
    """
    n = len(s)
    if n == 0:
      return False

    # dp[i] is True if s[:i] can be segmented
    dp = [False] * (n + 1)
    dp[0] = True

    for i in range(1, n + 1):
      for j in range(i):
        if dp[j] and s[j:i] in wordDict:
          dp[i] = True
          break
    return dp[n]

  def wordBreak2(self, s: str, wordDict: Set[str]) -> List[str]:
    """
    140. Word Break II
    Given a non-empty string s and a dictionary wordDict, add spaces in s
    to construct a sentence where each word is a valid dictionary word.
    Return all such possible sentences.
    """
    n = len(s)
    if not n:
      return []

    # dp[i] stores list of valid sentences for s[:i]
    dp = [[] for _ in range(n + 1)]
    dp[0] = [""]

    for i in range(1, n + 1):
      for j in range(i):
        word = s[j:i]
        if word in wordDict:
          for sentence in dp[j]:
            dp[i].append((sentence + " " + word).lstrip())

    return dp[n]

  def maxProduct(self, nums: List[int]) -> int:
    """
    152. Maximum Product Subarray
    Given an integer array nums, find a contiguous non-empty subarray within
    the array that has the largest product, and return the product.
    """
    if not nums:
      return 0

    res = nums[0]
    mx = nums[0]
    mn = nums[0]

    for i in range(1, len(nums)):
      num = nums[i]
      # When we multiply by a negative number, max becomes min and vice-versa
      if num < 0:
        mx, mn = mn, mx

      mx = max(num, mx * num)
      mn = min(num, mn * num)

      res = max(res, mx)

    return res

  def rob(self, nums: List[int]) -> int:
    """
    198. House Robber
    You are a professional robber planning to rob houses along a street.
    You cannot rob two adjacent houses. Find the maximum amount of money
    you can rob.
    """
    # A more Pythonic way to handle the space-optimized DP
    prev1 = 0  # Represents dp[i-1]
    prev2 = 0  # Represents dp[i-2]

    for num in nums:
      current = max(prev1, prev2 + num)
      prev2 = prev1
      prev1 = current

    return prev1

  def rob2(self, nums: List[int]) -> int:
    """
    213. House Robber II
    All houses at this place are arranged in a circle. You cannot rob
    adjacent houses. Find the maximum amount of money you can rob.
    """
    n = len(nums)
    if n == 0:
      return 0
    if n == 1:
      return nums[0]

    # The problem can be broken down into two subproblems:
    # 1. Rob houses from 0 to n-2 (excluding the last house).
    # 2. Rob houses from 1 to n-1 (excluding the first house).
    # The final answer is the maximum of these two scenarios.
    return max(self._rob_linear(nums[:-1]), self._rob_linear(nums[1:]))

  def _rob_linear(self, nums: List[int]) -> int:
    """Helper for rob2: performs standard house robber on a linear array."""
    prev1, prev2 = 0, 0
    for num in nums:
      current = max(prev1, prev2 + num)
      prev2 = prev1
      prev1 = current
    return prev1

  def maxCoins(self, nums: List[int]) -> int:
    """
    312. Burst Balloons
    Given n balloons, indexed from 0 to n-1. You are asked to burst all
    the balloons. If you burst balloon i you will get
    nums[left] * nums[i] * nums[right] coins. Find the maximum coins you
    can collect.
    """
    # Add virtual balloons with value 1 at both ends
    a = [1] + nums + [1]
    n = len(a)

    # dp[i][j] = max coins from bursting balloons in range (i, j)
    dp = [[0] * n for _ in range(n)]

    # length of the subarray of balloons to burst
    for length in range(2, n):
      for left in range(n - length):
        right = left + length
        # k is the last balloon to be burst in (left, right)
        for k in range(left + 1, right):
          dp[left][right] = max(
              dp[left][right],
              a[left] * a[k] * a[right] + dp[left][k] + dp[k][right])

    return dp[0][n - 1]


def getDualRotatingLockMinSteps(N: int, M: int, C: List[int]) -> int:
  if M == 0:
    return 0

  C.insert(0, 1)

  def cost(i, j):
    diff = abs(C[i] - C[j])
    return min(diff, N - diff)

  # The state dp[i][j] represents the minimum time to input the first i codes,
  # with one wheel at C[i] and the other at C[j].
  prev_dp = [float('inf')] * M
  prev_dp[0] = cost(0, 1)

  # print(prev_dp)

  for i in range(2, M + 1):
    # This state (wheels at C[i], C[i-1]) is reached by moving the 'other' one.
    curr_dp = [float('inf')] * M

    res = float('inf')
    for k in range(i - 1):
      c = prev_dp[k] + cost(k, i)
      res = min(res, c)
    curr_dp[i - 1] = res

    for j in range(i - 1):
      curr_dp[j] = prev_dp[j] + cost(i - 1, i)

    prev_dp = curr_dp
    # print(prev_dp)

  return min(prev_dp)


print(getDualRotatingLockMinSteps(3, 3, [1, 2, 3]))
print(getDualRotatingLockMinSteps(10, 4, [9, 4, 4, 8]))

# 216. Combination Sum III
# Find all possible combinations of k numbers that add up to a number n, given that only numbers from 1 to 9 can be used and each combination should be a unique set of numbers.


def dfs(self, prev, low, k, n):
  if k == 1 and low <= n <= 9:
    prev.append(n)
    # print(prev)
    self.ans.append(prev)
    return
  for i in range(low, min(n + 1, 10)):
    cur = prev[:]
    cur.append(i)
    self.dfs(cur, i + 1, k - 1, n - i)


def combinationSum3(self, k, n):
  """
  :type k: int
  :type n: int
  :rtype: List[List[int]]
  """
  self.ans = []
  prev = []
  self.dfs(prev, 1, k, n)
  # print(self.ans)
  return self.ans

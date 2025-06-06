# 167. Two Sum II - Input array is sorted
# Linear scanning O(n)
def twoSum(self, numbers, target):
  """
	:type numbers: List[int]
	:type target: int
	:rtype: List[int]
	"""
  l, r = 0, len(numbers) - 1
  while l < r:
    s = numbers[l] + numbers[r]
    if s > target:
      r -= 1
    elif s < target:
      l += 1
    else:
      return [l + 1, r + 1]
  return None


# 205. Isomorphic Strings
# Given two strings s and t, determine if they are isomorphic.
def isIsomorphic(self, s, t):
  """
  :type s: str
  :type t: str
  :rtype: bool
  """
  if len(s) != len(t):
    return False
  f, g = {}, {}
  for i in range(len(s)):
    if (s[i] in f and f[s[i]] != t[i]) or \
       (t[i] in g and g[t[i]] != s[i]):
      return False
    f[s[i]] = t[i]
    g[t[i]] = s[i]
  return True

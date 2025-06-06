# 202. Happy Number
# Write an algorithm to determine if a number is "happy".
# Starting with any positive integer, replace the number by the sum of the
# squares of its digits, and repeat the process until the number equals 1
# (where it will stay), or it loops endlessly in a cycle which does not
# include 1. Those numbers for which this process ends in 1 are happy numbers.
def isHappy(self, n):
  """
    :type n: int
    :rtype: bool
    """
  h = set()
  while n != 1 and n not in h:
    h.add(n)
    m = 0
    while n > 0:
      m += (n % 10)**2
      n = n // 10
    n = m
  return n == 1

# 165. Compare Version Numbers
# version1 = "7.5.2.4", version2 = "7.5.3"
# -1
def v2n(self, v, p):
  if not v:
    return 0
  return int(v[:p]) if p >= 0 else int(v)


def compareVersion(self, version1, version2):
  """
	:type version1: str
	:type version2: str
	:rtype: int
	"""
  while version1 or version2:
    p1 = version1.find('.')
    p2 = version2.find('.')
    v1 = self.v2n(version1, p1)
    v2 = self.v2n(version2, p2)
    if v1 > v2:
      return 1
    elif v1 < v2:
      return -1
    version1 = version1[p1 + 1:] if p1 >= 0 else ''
    version2 = version2[p2 + 1:] if p2 >= 0 else ''
  return 0


# 168. Excel Sheet Column Title
# Given a positive integer, return its corresponding column title as appear in an Excel sheet.
def convertToTitle(self, n):
  """
	:type n: int
	:rtype: str
	"""
  ans = ''
  while n > 0:
    d = n % 26 - 1
    n = int(math.floor(n / 26))
    if d < 0:
      d = 25
      n -= 1
    ans = chr(ord('A') + d) + ans
  return ans


# 179. Largest Number
# Given a list of non negative integers, arrange them such that they form the largest number.
class Key(str):

  def __lt__(a, b):
    return a + b < b + a


def largestNumber(self, nums):
  """
	:type nums: List[int]
	:rtype: str
	"""
  ans = ''.join(sorted([str(x) for x in nums], key=self.Key,
                       reverse=True)).lstrip('0')
  return ans if ans else '0'

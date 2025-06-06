import math


class Palindrome:
  # O(log N), find the next palindrome
  @staticmethod
  def next(x):
    """
      :type x: int
      :rtype: int
      """

    # 192 -> 200
    # 1991 -> 2000
    # 11199111 -> 11200000
    # round up the palindrome by the middle digit
    def round_up(x):
      """
      :type x: int
      :rtype: int
      """
      n = len(str(x))
      inc = 10**((n >> 1) + 1)
      return (x // inc + 1) * inc

    s = str(x)
    n = len(s)
    is_odd = n & 1
    left_half = s[:(n >> 1)]
    middle = s[(n - 1) >> 1]
    if is_odd:
      inc = 10**(n >> 1)
      y = int(left_half + middle + left_half[::-1])
    else:
      inc = int(1.1 * (10**(n >> 1)))
      y = int(left_half + left_half[::-1])
    if y > x:
      return y
    if middle != '9':
      return y + inc
    else:
      return Palindrome.next(round_up(x))

  @staticmethod
  # O(log N), find the previous palindrome
  def prev(x):
    # 291 -> 282
    # 1001 -> 999
    # 10001 -> 9999
    # 1088 -> 999
    # 2881 -> 2772
    # 1188 -> 1111
    # 1000 -> 999
    # 10 -> 9
    # 100 -> 99
    # round up the palindrome by the middle digit
    if x is 1:
      return 0
    s = str(x)
    n = len(s)
    is_odd = n & 1
    left_half = s[:(n >> 1)]
    middle = s[(n - 1) >> 1]
    if is_odd:
      dec = 10**(n >> 1)
      y = int(left_half + middle + left_half[::-1])
    else:
      dec = int(1.1 * (10**(n >> 1)))
      y = int(left_half + left_half[::-1])
    if y < x:
      return y
    if middle is '0' or (n is 2 and middle is '1'):
      return int('9' * (n - 1))
    else:
      return y - dec

  @staticmethod
  def closest(x):
    a, b = Palindrome.next(x), Palindrome.prev(x)
    return b if x - b <= a - x else a

  # is_palindrome: test if a string is palindrome
  @staticmethod
  def is_valid(s):
    n = len(s)
    for i in range(n >> 1):
      if s[i] != s[n - 1 - i]:
        return False
    return True

  @staticmethod
  def is_valid_with_space(self, s):
    """
      :type s: str
      :rtype: bool
      """
    s = s.lower()
    l, r = 0, len(s) - 1
    while l < r:
      if not s[l].isalpha() and not s[l].isdigit():
        l += 1
        continue
      if not s[r].isalpha() and not s[r].isdigit():
        r -= 1
        continue
      if s[l] != s[r]:
        return False
      l += 1
      r -= 1
    return True

  # prime_palindrome: calc the next palindrome
  @staticmethod
  def next_prime(x):
    """
      :type x: int
      :rtype: int
      """

    def is_prime(x):
      for i in range(2, int(math.sqrt(x)) + 1):
        if x % i == 0:
          return False
      return True

    if x is 1 or x is 2:
      return 2

    if Palindrome.is_valid(str(x)) and is_prime(x):
      return x

    while True:
      if x & 1 == 0:
        x += 1
      s = str(x)
      if int(s[0]) & 1 == 0:
        R = 10**(len(s) - 1)
        x = (x + R) - (x % R)
        continue
      if Palindrome.is_valid(s) and is_prime(x):
        return x
      x = Palindrome.next(x)

  @staticmethod
  def is_valid_without1(s):
    """
      :type s: str
      :rtype: bool
      """
    # 0123454321
    # 100
    n = len(s)
    l, r = 0, n - 1
    d, flag = 0, True
    while l < r:
      if s[l + d] != s[r]:
        if d is 0:
          d = 1
          continue
        else:
          flag = False
          break
      l += 1
      r -= 1
    if flag:
      return True

    d, flag = 0, True
    while l < r:
      if s[l] != s[r - d]:
        if d is 0:
          d = 1
          continue
        else:
          flag = False
          break
      l += 1
      r -= 1
    return flag

  @staticmethod
  # Find the largest palindrome made from the product of two n-digit numbers.
  def largest_palindrome(n):
    """
      :type n: int
      :rtype: int
      """
    if n == 1:
      return 9

    l, r = 10**(n - 1), 10**n - 1
    for i in range(r, l - 1, -1):
      x = int(str(i) + str(i)[::-1])
      j = r
      while j * j >= x:
        if x % j == 0:
          return x % 1337
        j -= 1
    return -1


# 234. Palindrome Linked List
# Given a singly linked list, determine if it is a palindrome.
def isPalindrome(self, head):
  """
  :type head: ListNode
  :rtype: bool
  """
  if head is None or head.next is None:
    return True
  root = ListNode(0)
  root.next = head
  n, v = 0, head
  while v is not None:
    v = v.next
    n += 1
  h = n >> 1
  c, v, p, vn = 0, head, root, head.next
  # x->1->2<-2<-1
  # 0: p, v, vn = x, 1, 2
  # 1: p, v, vn = 1, 2, 2
  # 2: p, v, vn = 2, 2, -1
  # 3: p, v, vn = 2, -1, x

  tail = vn
  while vn is not None:
    p = v
    v = vn
    if v is not None:
      tail = v
    vn = vn.next
    c += 1
    if c > h:
      v.next = p

  # I am too lazy to restore the list
  for _ in range(h):
    if head.val != tail.val:
      return False
    head = head.next
    tail = tail.next
  return True


p = Palindrome()
assert (p.next_prime(234522398) == 300020003)
assert (p.closest(234522398) == 234525432)
assert (p.is_valid_without1("cbbcc"))
# for x in range(1, 9):
#     print(p.largest_palindrome(x))
print('Success.')

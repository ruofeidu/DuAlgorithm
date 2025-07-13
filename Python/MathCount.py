import math


# calc n!/(start-1)!
def factor(n: int, start: int = 1) -> int:
  """
  Calculates the factorial of n starting from a given number.
  Equivalent to n! / (start - 1)!
  """
  res = 1
  for i in range(start, n + 1):
    res *= i
  return res


# calc C_n^k
def combination(n: int, k: int) -> int:
  """
  Calculates the binomial coefficient "n choose k".
  """
  if k < 0 or k > n:
    return 0
  if k == 0 or k == n:
    return 1
  if k > n // 2:
    k = n - k

  # Using the formula: C(n, k) = n * (n-1) * ... * (n-k+1) / k!
  # This is more efficient than calculating three full factorials.
  numerator = 1
  for i in range(k):
    numerator *= (n - i)

  denominator = 1
  for i in range(1, k + 1):
    denominator *= i

  return numerator // denominator


class Counts:
  """
  A collection of counting and mathematical functions.
  """

  @staticmethod
  def unique_paths(m: int, n: int) -> int:
    """
    Calculates the number of unique paths on an m x n grid.
    Problem: LeetCode 62. Unique Paths [M]
    In total, there are m+n-2 steps, of which m-1 are downwards steps.
    The formula is C(m+n-2, m-1).
    """
    if m <= 0 or n <= 0:
      return 0
    return combination(m + n - 2, max(m - 1, n - 1))

  @staticmethod
  def count_numbers_with_unique_digits(n: int) -> int:
    """
    Counts the numbers with unique digits up to n digits.
    Problem: LeetCode 357. Count Numbers with Unique Digits
    f[n] = 9 * 9 * 8 * ... * (9 - k + 2)
    """
    if n == 0:
      return 1
    res = 10
    cnt = 9
    for i in range(2, n + 1):
      cnt *= (11 - i)
      res += cnt
    return res

  @staticmethod
  def max_regions_by_a_line(n: int) -> int:
    """
    Calculates the maximum number of regions a plane can be divided into by n lines.
    Formula: f(n) = f(n-1) + n
    """
    return n * (n + 1) // 2 + 1

  @staticmethod
  def max_regions_by_a_poly_line(n: int) -> int:
    """
    Calculates the maximum regions formed by a polyline with n segments.
    """
    return (n - 1) * (2 * n - 1) + 2 * n

  @staticmethod
  def max_regions_by_a_closed_curve(n: int) -> int:
    """
    Calculates the maximum number of regions formed by n intersecting closed curves.
    Formula: f(n) = f(n-1) + 2 * (n-1)
    """
    return n * n - n + 2

  @staticmethod
  def count_triangles_of_polygon(n: int) -> int:
    """
    Calculates the number of non-intersecting triangles that can be formed in a polygon.
    This is related to Catalan numbers.
    """
    if n < 3:
      return 0
    return combination(2 * n - 2, n - 1) // n

  @staticmethod
  def count_klygon_of_polygon(n: int, k: int) -> int:
    """
    A generalization for counting k-gons in a polygon.
    Note: The original C++ code seems to not use the 'n' parameter.
    The formula provided corresponds to a known combinatorial identity, but its direct
    application to "k-gons of an n-gon" might need clarification.
    """
    if k < 3:
      return -1
    # This formula calculates the number of ways to triangulate a k-gon (Catalan number C_{k-2}).
    # It does not depend on 'n'.
    return combination(2 * k - 4, k - 2) // (k - 1)

  @staticmethod
  def trailing_zeroes(n: int) -> int:
    """
    Given an integer n, returns the number of trailing zeroes in n!.
    Problem: LeetCode 172. Factorial Trailing Zeroes
    """
    res = 0
    while n > 0:
      n //= 5
      res += n
    return res

  @staticmethod
  def count_digit_one(n: int) -> int:
    """
    Given an integer n, count the total number of digit 1 appearing in all
    non-negative integers less than or equal to n.
    Problem: LeetCode 233. Number of Digit One [H]
    """
    if n < 1:
      return 0

    count = 0
    multiplier = 1

    while n // multiplier > 0:
      left_part = n // (multiplier * 10)
      current_digit = (n // multiplier) % 10
      right_part = n % multiplier

      # Count of '1's in positions represented by the multiplier
      count += left_part * multiplier

      if current_digit == 1:
        count += right_part + 1
      elif current_digit > 1:
        count += multiplier

      # Avoid overflow in very large numbers, though less of a concern in Python
      if multiplier > n:
        break

      multiplier *= 10

    return count

  @staticmethod
  def josephus(n: int, m: int, k: int) -> int:
    """
    Solves the Josephus problem.
    N people, remove the M first, kick every Kth: who is the winner?
    """
    if n <= 0:
      return -1  # Invalid input

    # Standard Josephus problem (f(n,k)=(f(n-1,k)+k)%n) solved iteratively
    s = 0
    for i in range(2, n + 1):
      s = (s + k) % i

    # Adjust for the starting position 'm'
    # The winner's position in a 0-indexed circle is 's'.
    # We need to map this back to the 1-indexed problem starting at 'm'.
    # The original position of the winner (0-indexed) is (s - (m-1)) % n
    # In 1-based indexing, this is ((s - (m-1)) % n + n) % n + 1
    winner = (s - (m - 1)) % n
    return (winner + n) % n + 1

  @staticmethod
  def josephus_simulation(n: int, m: int, k: int) -> int:
    """
    A simulation-based solution to the Josephus problem.
    """
    if n <= 0:
      return -1

    people = list(range(1, n + 1))

    # Start index is m-1 (0-indexed)
    current_idx = (m - 1) % n

    # Remove the first person at start position m
    people.pop(current_idx)
    n -= 1

    while n > 1:
      # Move k-1 steps to find the next person to remove
      current_idx = (current_idx + k - 1) % n
      people.pop(current_idx)
      n -= 1

    return people[0]


def CountUniform(A: int, B: int) -> int:
  """
  Calculates the number of uniform integers between A and B, inclusive.
  A uniform integer is a positive integer where all of its digits are equal.
  """

  def getCountToTarget(target):
    """
    Calculates the number of uniform integers between 1 and target, inclusive.
    """
    if target < 1:
      return 0

    s_target = str(target)
    num_digits = len(s_target)

    count = 9 * (num_digits - 1)
    first_digit_char = s_target[0]

    uniform_num_str = first_digit_char * num_digits
    count += int(first_digit_char)

    if target < int(uniform_num_str):
      count -= 1

    return count

  return getCountToTarget(B) - getCountToTarget(A - 1)


print(CountUniform(75, 300))

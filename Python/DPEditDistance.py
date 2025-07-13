import math


class DPEditDistance:
  """
    This class contains implementations for various dynamic programming problems
    related to string manipulation, including Edit Distance, One Edit Distance,
    Scramble String, and Interleaving String.
    """

  def min_distance(self, word1: str, word2: str) -> int:
    """
        72. Edit Distance
        Given two words word1 and word2, find the minimum number of operations
        required to convert word1 to word2.
        Operations allowed: insert, delete, and replace.

        This uses a classic dynamic programming approach.
        dp[i][j] represents the minimum edit distance between
        word1[:i] (first i characters of word1) and word2[:j] (first j characters of word2).

        Time Complexity: O(n * m), where n is len(word1) and m is len(word2).
        Space Complexity: O(n * m) for the DP table.

        Args:
            word1: The first string.
            word2: The second string.

        Returns:
            The minimum number of operations.
        """
    n = len(word1)
    m = len(word2)

    # Base case: If both words are empty, no operations are needed.
    if n == 0 and m == 0:
      return 0
    # If one word is empty, the distance is the length of the other word
    # (all characters need to be inserted or deleted).
    if n == 0:
      return m
    if m == 0:
      return n

    # Initialize DP table `dp` of size (n+1) x (m+1) with zeros.
    # `dp[i][j]` will store the min distance for word1[:i] and word2[:j].
    dp = [[0] * (m + 1) for _ in range(n + 1)]

    # Initialize base cases for the DP table:
    # dp[i][0] means transforming word1[:i] to an empty string (m=0).
    # This requires `i` deletions.
    for i in range(n + 1):
      dp[i][0] = i
    # dp[0][j] means transforming an empty string (n=0) to word2[:j].
    # This requires `j` insertions.
    for j in range(m + 1):
      dp[0][j] = j

    # Fill the DP table using the recurrence relation.
    for i in range(1, n + 1):
      for j in range(1, m + 1):
        # If the current characters match, no operation is needed for them.
        # The distance is the same as the distance for the preceding substrings.
        if word1[i - 1] == word2[j - 1]:
          dp[i][j] = dp[i - 1][j - 1]
        else:
          # If characters don't match, we consider three operations:
          # 1. Insertion: dp[i][j-1] + 1 (insert word2[j-1] into word1[:i])
          # 2. Deletion: dp[i-1][j] + 1 (delete word1[i-1] from word1[:i])
          # 3. Replacement: dp[i-1][j-1] + 1 (replace word1[i-1] with word2[j-1])
          # We take the minimum of these three options.
          dp[i][j] = min(dp[i - 1][j], dp[i][j - 1], dp[i - 1][j - 1]) + 1

    # The minimum distance to convert word1 to word2 is at dp[n][m].
    return dp[n][m]

  def is_one_edit_distance(self, s: str, t: str) -> bool:
    """
        161. One Edit Distance
        Given two strings S and T, determine if they are both one edit distance apart.
        One edit distance means you can transform one string into the other by:
        - Inserting one character
        - Deleting one character
        - Replacing one character

        Time Complexity: O(min(len(s), len(t)))
        Space Complexity: O(min(len(s), len(t))) due to string slicing in worst case, or O(1) if optimized.

        Args:
            s: The first string.
            t: The second string.

        Returns:
            True if they are one edit distance apart, False otherwise.
        """
    n = len(s)
    m = len(t)

    # Ensure that `s` is the shorter or equal length string for simpler logic.
    # This swaps s and t if s is longer than t.
    if n > m:
      return self.is_one_edit_distance(t, s)

    # If the length difference is greater than 1, they cannot be one edit distance apart.
    if m - n > 1:
      return False

    # Iterate through the strings from the beginning up to the length of the shorter string.
    for i in range(n):
      # If a character mismatch is found:
      if s[i] != t[i]:
        # Case 1: Lengths are equal (replacement operation).
        # Check if the rest of the strings are identical.
        if n == m:
          return s[i + 1:] == t[i + 1:]
        # Case 2: `t` is longer than `s` (insertion operation in `s` or deletion in `t`).
        # Check if `s` from `i` onwards matches `t` from `i + 1` onwards.
        elif n < m:
          return s[i:] == t[i + 1:]

    # If the loop completes without finding any mismatches, it means
    # the common prefix of length `min(n, m)` is identical.
    # This implies that the only possible difference is an extra character
    # at the end of the longer string, making the difference exactly 1.
    # Example: s = "abc", t = "abcd" (difference is 1)
    # Example: s = "abc", t = "abc" (difference is 0)
    return abs(n - m) == 1

  def is_scramble(self, s1: str, s2: str) -> bool:
    """
        87. Scramble String [Hard][Very Hard]
        Given two strings s1 and s2 of the same length, determine if s2 is a scrambled string of s1.
        A string s1 can be represented as a binary tree by partitioning it into
        two non-empty substrings recursively. To scramble the string, we may
        choose any non-leaf node and swap its two children.

        This uses a 3D dynamic programming approach.
        dp[length][i][j] is true if s1[i:i+length] is a scramble of s2[j:j+length].

        Time Complexity: O(N^4), where N is the length of the strings.
                         (N for length, N for i, N for j, N for k (split point)).
        Space Complexity: O(N^3) for the DP table.

        Args:
            s1: The first string.
            s2: The second string.

        Returns:
            True if s2 is a scrambled string of s1, False otherwise.
        """
    n = len(s1)
    if len(s2) != n:
      return False

    # dp[length][i][j] indicates whether s1[i...i+length-1] is a scramble of s2[j...j+length-1].
    # Initialize a 3D DP table with False.
    dp = [[[False] * n for _ in range(n)] for _ in range(n + 1)]

    # Base case: For length 1 strings, they are scrambled if their characters match.
    for i in range(n):
      for j in range(n):
        dp[1][i][j] = (s1[i] == s2[j])

    # Iterate over possible lengths of substrings (from 2 up to N).
    for length in range(2, n + 1):
      # Iterate over possible starting indices for s1.
      for i in range(n - length + 1):
        # Iterate over possible starting indices for s2.
        for j in range(n - length + 1):
          # Iterate over possible split points `k` for the current length.
          # `k` represents the length of the left part.
          for k in range(1, length):
            # Option 1: No swap at the current node.
            # s1[i...i+k-1] is scramble of s2[j...j+k-1] AND
            # s1[i+k...i+length-1] is scramble of s2[j+k...j+length-1]
            if dp[k][i][j] and dp[length - k][i + k][j + k]:
              dp[length][i][j] = True
              break  # Found a valid scramble, no need to check other splits

            # Option 2: Swap at the current node.
            # s1[i...i+k-1] is scramble of s2[j+length-k...j+length-1] AND
            # s1[i+k...i+length-1] is scramble of s2[j...j+length-k-1]
            # (Effectively, s2's parts are swapped: right part of s2 aligns with left of s1,
            #  and left part of s2 aligns with right of s1).
            if dp[k][i][j + length - k] and dp[length - k][i + k][j]:
              dp[length][i][j] = True
              break  # Found a valid scramble, no need to check other splits

    # The result is whether the entire s1 (length N, starting at 0)
    # is a scramble of the entire s2 (length N, starting at 0).
    return dp[n][0][0]

  def is_interleave(self, s1: str, s2: str, s3: str) -> bool:
    """
        97. Interleaving String [Hard][Very Hard]
        Given three strings s1, s2, and s3, find whether s3 is formed by the
        interleaving of s1 and s2.

        An interleaving means s3 is formed by taking characters from s1 and s2
        in their original relative order.

        This uses a 2D dynamic programming approach.
        dp[i][j] is true if s3[:i+j] is formed by interleaving s1[:i] and s2[:j].

        Time Complexity: O(len(s1) * len(s2))
        Space Complexity: O(len(s1) * len(s2)) for the DP table.

        Args:
            s1: The first string.
            s2: The second string.
            s3: The string to check if it's an interleaving of s1 and s2.

        Returns:
            True if s3 is an interleaving of s1 and s2, False otherwise.
        """
    len_s1 = len(s1)
    len_s2 = len(s2)
    len_s3 = len(s3)

    # If the combined length of s1 and s2 is not equal to s3,
    # it's impossible for s3 to be an interleaving.
    if len_s1 + len_s2 != len_s3:
      return False

    # dp[i][j] means whether s3 (up to index i+j-1) is an interleaving of
    # s1 (up to index i-1) and s2 (up to index j-1).
    # The DP table size is (len_s1 + 1) x (len_s2 + 1).
    dp = [[False] * (len_s2 + 1) for _ in range(len_s1 + 1)]

    # Base case: An empty s3 is an interleaving of empty s1 and empty s2.
    dp[0][0] = True

    # Initialize the first row (s2 is empty, s3 must match s1).
    for i in range(1, len_s1 + 1):
      # If dp[i-1][0] is true AND the i-th character of s1 matches the i-th character of s3,
      # then s3[:i] can be formed by s1[:i] and an empty s2.
      dp[i][0] = dp[i - 1][0] and s1[i - 1] == s3[i - 1]

    # Initialize the first column (s1 is empty, s3 must match s2).
    for j in range(1, len_s2 + 1):
      # If dp[0][j-1] is true AND the j-th character of s2 matches the j-th character of s3,
      # then s3[:j] can be formed by an empty s1 and s2[:j].
      dp[0][j] = dp[0][j - 1] and s2[j - 1] == s3[j - 1]

    # Fill the rest of the DP table.
    for i in range(1, len_s1 + 1):
      for j in range(1, len_s2 + 1):
        # Check if s3[i+j-1] (current character of s3) comes from s1[i-1].
        # This is possible if s3[:i+j-2] was an interleaving of s1[:i-1] and s2[:j],
        # AND s1[i-1] matches s3[i+j-1].
        from_s1 = dp[i - 1][j] and s1[i - 1] == s3[i + j - 1]

        # Check if s3[i+j-1] (current character of s3) comes from s2[j-1].
        # This is possible if s3[:i+j-2] was an interleaving of s1[:i] and s2[:j-1],
        # AND s2[j-1] matches s3[i+j-1].
        from_s2 = dp[i][j - 1] and s2[j - 1] == s3[i + j - 1]

        # dp[i][j] is true if it can be formed by either path.
        dp[i][j] = from_s1 or from_s2

    # The final result is whether the entire s3 is an interleaving of s1 and s2.
    return dp[len_s1][len_s2]


# Example Usage:
if __name__ == "__main__":
  solver = Solution()

  print("--- 72. Edit Distance ---")
  print(f"minDistance('horse', 'ros'): {solver.min_distance('horse', 'ros')}"
       )  # Output: 3
  print(
      f"minDistance('intention', 'execution'): {solver.min_distance('intention', 'execution')}"
  )  # Output: 5
  print(f"minDistance('', ''): {solver.min_distance('', '')}")  # Output: 0
  print(f"minDistance('a', 'b'): {solver.min_distance('a', 'b')}")  # Output: 1
  print(f"minDistance('a', ''): {solver.min_distance('a', '')}")  # Output: 1

  print("\n--- 161. One Edit Distance ---")
  print(
      f"isOneEditDistance('ab', 'acb'): {solver.is_one_edit_distance('ab', 'acb')}"
  )  # Output: True (insert 'c')
  print(
      f"isOneEditDistance('ab', 'cab'): {solver.is_one_edit_distance('ab', 'cab')}"
  )  # Output: True (insert 'c')
  print(
      f"isOneEditDistance('a', 'ba'): {solver.is_one_edit_distance('a', 'ba')}"
  )  # Output: True (insert 'b')
  print(
      f"isOneEditDistance('ab', 'ac'): {solver.is_one_edit_distance('ab', 'ac')}"
  )  # Output: True (replace 'b' with 'c')
  print(
      f"isOneEditDistance('ab', 'a'): {solver.is_one_edit_distance('ab', 'a')}"
  )  # Output: True (delete 'b')
  print(
      f"isOneEditDistance('ab', 'cd'): {solver.is_one_edit_distance('ab', 'cd')}"
  )  # Output: False (2 replacements)
  print(f"isOneEditDistance('a', ''): {solver.is_one_edit_distance('a', '')}"
       )  # Output: True (delete 'a')
  print(f"isOneEditDistance('', 'a'): {solver.is_one_edit_distance('', 'a')}"
       )  # Output: True (insert 'a')
  print(
      f"isOneEditDistance('apple', 'aple'): {solver.is_one_edit_distance('apple', 'aple')}"
  )  # Output: True (delete 'p')
  print(
      f"isOneEditDistance('ab', 'bd'): {solver.is_one_edit_distance('ab', 'bd')}"
  )  # Output: False

  print("\n--- 87. Scramble String ---")
  print(f"isScramble('great', 'rgeat'): {solver.is_scramble('great', 'rgeat')}"
       )  # Output: True
  print(f"isScramble('abcde', 'caebd'): {solver.is_scramble('abcde', 'caebd')}"
       )  # Output: False
  print(f"isScramble('a', 'a'): {solver.is_scramble('a', 'a')}")  # Output: True
  print(f"isScramble('ab', 'ba'): {solver.is_scramble('ab', 'ba')}"
       )  # Output: True

  print("\n--- 97. Interleaving String ---")
  s1_ex1, s2_ex1, s3_ex1 = "aabcc", "dbbca", "aadbbcbcac"
  print(
      f"isInterleave('{s1_ex1}', '{s2_ex1}', '{s3_ex1}'): {solver.is_interleave(s1_ex1, s2_ex1, s3_ex1)}"
  )  # Output: True
  s1_ex2, s2_ex2, s3_ex2 = "aabcc", "dbbca", "aadbbbaccc"
  print(
      f"isInterleave('{s1_ex2}', '{s2_ex2}', '{s3_ex2}'): {solver.is_interleave(s1_ex2, s2_ex2, s3_ex2)}"
  )  # Output: False
  s1_ex3, s2_ex3, s3_ex3 = "", "", ""
  print(
      f"isInterleave('{s1_ex3}', '{s2_ex3}', '{s3_ex3}'): {solver.is_interleave(s1_ex3, s2_ex3, s3_ex3)}"
  )  # Output: True
  s1_ex4, s2_ex4, s3_ex4 = "a", "b", "ab"
  print(
      f"isInterleave('{s1_ex4}', '{s2_ex4}', '{s3_ex4}'): {solver.is_interleave(s1_ex4, s2_ex4, s3_ex4)}"
  )  # Output: True
  s1_ex5, s2_ex5, s3_ex5 = "aa", "ab", "aaba"
  print(
      f"isInterleave('{s1_ex5}', '{s2_ex5}', '{s3_ex5}'): {solver.is_interleave(s1_ex5, s2_ex5, s3_ex5)}"
  )  # Output: True
  s1_ex6, s2_ex6, s3_ex6 = "a", "b", "ba"
  print(
      f"isInterleave('{s1_ex6}', '{s2_ex6}', '{s3_ex6}'): {solver.is_interleave(s1_ex6, s2_ex6, s3_ex6)}"
  )  # Output: True
  s1_ex7, s2_ex7, s3_ex7 = "ab", "bc", "babc"
  print(
      f"isInterleave('{s1_ex7}', '{s2_ex7}', '{s3_ex7}'): {solver.is_interleave(s1_ex7, s2_ex7, s3_ex7)}"
  )  # Output: True

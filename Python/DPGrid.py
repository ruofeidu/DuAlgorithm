import math
from collections import deque


class DPGrid:
  """
    This class provides implementations for various dynamic programming problems
    that typically involve grids or 2D arrays.
    """

  def min_path_sum(self, grid: list[list[int]]) -> int:
    """
    64. Minimum Path Sum
    Given a m x n grid filled with non-negative numbers, find a path from
    top left to bottom right which minimizes the sum of all numbers along
    its path. You can only move either down or right at any point in time.

    This uses dynamic programming with space optimization (O(N) space).
    `f[j]` represents the minimum path sum to reach `grid[current_row][j]`.

    Time Complexity: O(m * n)
    Space Complexity: O(n) (where n is the number of columns)

    Args:
        grid: A 2D list of integers representing the grid.

    Returns:
        The minimum path sum.
    """
    m = len(grid)
    if m == 0:
      return 0
    n = len(grid[0])
    if n == 0:
      return 0

    # `f` will store the minimum path sum to reach each cell in the current row.
    # It's initialized with the path sums for the first row.
    f = [0] * n

    # Initialize the first row of `f`.
    # The path sum to grid[0][j] can only come from grid[0][j-1].
    f[0] = grid[0][0]
    for j in range(1, n):
      f[j] = f[j - 1] + grid[0][j]

    # Iterate through the rest of the rows, starting from the second row.
    for i in range(1, m):
      # Update the first element of `f` for the current row.
      # `f[0]` for the current row can only come from `f[0]` of the previous row
      # plus the current cell's value.
      f[0] += grid[i][0]
      # Iterate through the remaining columns for the current row.
      for j in range(1, n):
        # The minimum path sum to `grid[i][j]` comes from either
        # `grid[i-1][j]` (path from above, stored in `f[j]`)
        # or `grid[i][j-1]` (path from left, stored in `f[j-1]`).
        f[j] = min(f[j], f[j - 1]) + grid[i][j]

    # The result is the minimum path sum to the bottom-right corner.
    return f[n - 1]

  def minimum_total(self, triangle: list[list[int]]) -> int:
    """
    120. Triangle
    Given a triangle, find the minimum path sum from top to bottom. Each step
    you may move to adjacent numbers on the row below.

    This uses dynamic programming with space optimization (O(N) space, where N is
    the number of rows/max width). It iterates from bottom-up.

    Time Complexity: O(N^2), where N is the number of rows.
    Space Complexity: O(N) (using two rows for DP table).

    Args:
        triangle: A list of lists of integers representing the triangle.

    Returns:
        The minimum path sum from top to bottom.
    """
    n = len(triangle)
    if n == 0:
      return 0

    # `dp` table uses two rows for space optimization: `current_row % 2` and `(current_row + 1) % 2`.
    # `f[0]` and `f[1]` will represent the two rows.
    # The size `n + 1` is used to avoid index out of bounds for `j+1` in the last row.
    dp = [[0] * (n + 1) for _ in range(2)]

    # Initialize the `dp` table with the values from the last row of the triangle.
    # The last row's sums are just its own values.
    # `(n - 1) % 2` determines which of the two `dp` rows corresponds to the last row.
    for j in range(n):
      dp[(n - 1) % 2][j] = triangle[n - 1][j]

    # Iterate from the second-to-last row up to the top row (row 0).
    for i in range(n - 2, -1, -1):
      # Iterate through elements in the current row `i`.
      # A row `i` has `i + 1` elements.
      for j in range(i + 1):
        # Calculate the minimum path sum for `triangle[i][j]`.
        # It's `triangle[i][j]` plus the minimum of its two adjacent children
        # in the row below.
        # `(i + 1) % 2` gives the index for the row below in our `dp` table.
        dp[i % 2][j] = triangle[i][j] + min(dp[(i + 1) % 2][j],
                                            dp[(i + 1) % 2][j + 1])

    # The result is the minimum path sum starting from the top element (0,0).
    return dp[0][0]

  def pacific_atlantic_another(
      self, matrix: list[list[int]]) -> list[tuple[int, int]]:
    """
        This is an alternative (and somewhat complex) DP approach to the
        "Pacific Atlantic Water Flow" problem.
        The standard approach uses BFS/DFS starting from the ocean boundaries.

        This C++ implementation attempts to precompute reachability from each of
        the four "sides" (top/left for Pacific, bottom/right for Atlantic)
        using incremental DP passes.

        `Grid` in C++ is assumed to be `list[list[int]]` or `list[list[bool]]` here.

        Time Complexity: O(m * n) due to multiple passes over the grid.
        Space Complexity: O(m * n) for the multiple DP grids.

        Args:
            matrix: A 2D list of integers representing the heights of the land.

        Returns:
            A list of (row, col) tuples where water can flow to both Pacific and Atlantic oceans.
        """
    n = len(matrix)
    if n == 0:
      return []
    m = len(matrix[0])
    if m == 0:
      return []

    # Directions for neighbors: (dy, dx)
    # (1, 0) = down, (0, 1) = right, (-1, 0) = up, (0, -1) = left
    dy = [1, 0, -1, 0]
    dx = [0, 1, 0, -1]

    # `ir`: Can reach Pacific from current cell by only moving right (increasing row)
    # `ic`: Can reach Pacific from current cell by only moving down (increasing col)
    # `irc`: Can reach Pacific (combined row/col increasing paths, or any path)
    pacific_reachable = [[False] * m for _ in range(n)]

    # `dr`: Can reach Atlantic from current cell by only moving left (decreasing row)
    # `dc`: Can reach Atlantic from current cell by only moving up (decreasing col)
    # `drc`: Can reach Atlantic (combined row/col decreasing paths, or any path)
    atlantic_reachable = [[False] * m for _ in range(n)]

    # --- Initialize cells directly adjacent to Pacific and Atlantic ---

    # Initialize cells on the top row and left column as reachable by Pacific.
    for i in range(n):
      pacific_reachable[i][0] = True  # Leftmost column
    for j in range(m):
      pacific_reachable[0][j] = True  # Topmost row

    # Initialize cells on the bottom row and right column as reachable by Atlantic.
    for i in range(n):
      atlantic_reachable[i][m - 1] = True  # Rightmost column
    for j in range(m):
      atlantic_reachable[n - 1][j] = True  # Bottommost row

    # --- First pass: Propagate reachability from Pacific (top/left) ---
    # This is essentially a BFS/DFS from the Pacific border, but implemented
    # as iterative DP.
    # Water flows from higher to lower or equal altitude.
    # If we are checking reachability *from* the ocean *to* the cell,
    # then the cell must be >= its neighbor towards the ocean.
    # So, if matrix[i][j] >= matrix[prev_i][prev_j] and prev_i/prev_j is reachable,
    # then i,j is reachable.

    # Propagate from top-left (Pacific)
    # Iterate over rows, then columns (left to right, top to bottom)
    for i in range(n):
      for j in range(m):
        # Check from left neighbor
        if j > 0 and pacific_reachable[i][
            j - 1] and matrix[i][j] >= matrix[i][j - 1]:
          pacific_reachable[i][j] = True
        # Check from top neighbor
        if i > 0 and pacific_reachable[
            i - 1][j] and matrix[i][j] >= matrix[i - 1][j]:
          pacific_reachable[i][j] = True

    # --- Second pass: Propagate reachability from Atlantic (bottom/right) ---
    # Iterate over rows (bottom to top), then columns (right to left)
    for i in range(n - 1, -1, -1):
      for j in range(m - 1, -1, -1):
        # Check from right neighbor
        if j < m - 1 and atlantic_reachable[i][
            j + 1] and matrix[i][j] >= matrix[i][j + 1]:
          atlantic_reachable[i][j] = True
        # Check from bottom neighbor
        if i < n - 1 and atlantic_reachable[
            i + 1][j] and matrix[i][j] >= matrix[i + 1][j]:
          atlantic_reachable[i][j] = True

    # --- Collect results ---
    ans = []
    for i in range(n):
      for j in range(m):
        # If a cell can reach both Pacific and Atlantic oceans, add it to the result.
        if pacific_reachable[i][j] and atlantic_reachable[i][j]:
          ans.append((i, j))
    return ans

  def maximal_rectangle(self, matrix: list[list[str]]) -> int:
    """
        85. Maximal Rectangle
        Given a 2D binary matrix filled with '0's and '1's, find the largest
        rectangle containing only '1's and return its area.

        This approach converts the problem into finding the largest rectangle
        in a histogram for each row.
        `H[j]` stores the height of consecutive '1's ending at current row `i` and column `j`.
        `L[j]` stores the leftmost boundary for a rectangle of height `H[j]` ending at `j`.
        `R[j]` stores the rightmost boundary for a rectangle of height `H[j]` starting at `j`.

        Time Complexity: O(m * n), where m is rows and n is columns.
                         Each row is processed in O(n) time.
        Space Complexity: O(n) for the auxiliary arrays H, L, R.

        Args:
            matrix: A 2D list of characters ('0' or '1').

        Returns:
            The area of the largest rectangle containing only '1's.
        """
    if not matrix or not matrix[0]:
      return 0

    num_rows = len(matrix)
    num_cols = len(matrix[0])

    # H: height of consecutive '1's ending at current row for each column.
    # L: left boundary for current height H[j].
    # R: right boundary for current height H[j].
    # Initialize L with 0s (can extend to the very left).
    # Initialize R with num_cols (can extend to the very right).
    H = [0] * num_cols
    L = [0] * num_cols
    R = [num_cols] * num_cols  # Corrected initialization to use num_cols

    max_area = 0

    for i in range(num_rows):
      current_left_boundary = 0  # Tracks the leftmost '0' encountered in the current row
      current_right_boundary = num_cols  # Tracks the rightmost '0' encountered in the current row

      # Calculate H and L for the current row (left to right pass)
      for j in range(num_cols):  # Corrected loop limit from n to num_cols
        if matrix[i][j] == '1':
          H[j] += 1  # Increment height if '1'
          # The left boundary for H[j] is the maximum of:
          # 1. Its previous left boundary (from row above, L[j])
          # 2. The current_left_boundary (due to a '0' in the current row)
          L[j] = max(L[j], current_left_boundary)
        else:
          # If '0', reset height, and reset L, R for this column.
          # Update current_left_boundary for subsequent columns.
          H[j] = 0
          L[j] = 0
          R[j] = num_cols  # Reset R to full width
          current_left_boundary = j + 1

      # Calculate R for the current row (right to left pass)
      for j in range(num_cols - 1, -1,
                     -1):  # Corrected loop limit from n to num_cols
        if matrix[i][j] == '1':
          # The right boundary for H[j] is the minimum of:
          # 1. Its previous right boundary (from row above, R[j])
          # 2. The current_right_boundary (due to a '0' in the current row)
          R[j] = min(R[j], current_right_boundary)
          # Calculate area for the rectangle ending at (i,j) with height H[j]
          # and width (R[j] - L[j]). Update max_area.
          max_area = max(max_area, H[j] * (R[j] - L[j]))
        else:
          # If '0', update current_right_boundary for subsequent columns.
          current_right_boundary = j

    return max_area

  def maximal_square(self, a: list[list[str]]) -> int:
    """
        221. Maximal Square
        Given a 2D binary matrix filled with '0's and '1's, find the largest square
        containing only '1's and return its area.

        This uses dynamic programming with space optimization (O(N) space, where N is
        the number of columns).
        `dp[j]` stores the side length of the largest square ending at `(current_row, j)`.

        Time Complexity: O(m * n)
        Space Complexity: O(n) (where n is the number of columns)

        Args:
            a: A 2D list of characters ('0' or '1').

        Returns:
            The area of the largest square.
        """
    if not a or not a[0]:
      return 0

    num_rows = len(a)
    num_cols = len(a[0])

    # `dp` will store the side length of the largest square ending at the current cell.
    # We use two rows for space optimization: `curr_row_idx` and `prev_row_idx`.
    dp = [[0] * num_cols for _ in range(2)]
    max_side = 0  # Stores the maximum side length found so far

    # Initialize the first row of the DP table.
    # The side length of a square ending at (0, j) is 1 if a[0][j] is '1', else 0.
    for j in range(num_cols):
      dp[0][j] = int(a[0][j])
      max_side = max(max_side, dp[0][j])

    # Iterate through the rest of the rows, starting from the second row.
    for i in range(1, num_rows):
      curr_row_idx = i % 2
      prev_row_idx = (i - 1) % 2

      # Initialize the first element of the current row's DP.
      dp[curr_row_idx][0] = int(a[i][0])
      max_side = max(max_side, dp[curr_row_idx][0])

      # Iterate through the remaining columns for the current row.
      for j in range(1, num_cols):
        if a[i][j] == '1':
          # If the current cell is '1', the side length of the square ending here
          # is 1 plus the minimum of the side lengths of squares ending at:
          # - cell to its left (dp[curr_row_idx][j-1])
          # - cell above it (dp[prev_row_idx][j])
          # - cell diagonally top-left (dp[prev_row_idx][j-1])
          dp[curr_row_idx][j] = min(dp[curr_row_idx][j - 1],
                                    dp[prev_row_idx][j],
                                    dp[prev_row_idx][j - 1]) + 1
          max_side = max(max_side, dp[curr_row_idx][j])
        else:
          # If the current cell is '0', no square can end here.
          dp[curr_row_idx][j] = 0

    # The area of the largest square is max_side * max_side.
    return max_side * max_side

  def calculate_minimum_hp(self, dungeon: list[list[int]]) -> int:
    """
        174. Dungeon Game
        Calculates the knight's minimum initial health to rescue the princess.
        The knight starts at top-left and moves to bottom-right.
        Health must always be at least 1.

        This problem is solved using dynamic programming, working backward from
        the princess's location (bottom-right) to the knight's starting location (top-left).
        `dp[i][j]` represents the minimum health required *at the start of cell (i,j)*
        to reach the princess.

        Time Complexity: O(m * n)
        Space Complexity: O(m * n)

        Args:
            dungeon: A 2D list of integers representing the health changes in each cell.
                     Positive values mean health gain, negative mean health loss.

        Returns:
            The minimum initial health required.
        """
    m = len(dungeon)
    if m == 0:
      return 1  # Or handle error, but 1 is min health
    n = len(dungeon[0])
    if n == 0:
      return 1

    # `dp[i][j]` stores the minimum health needed when *entering* cell (i,j).
    dp = [[0] * n for _ in range(m)]

    # Base case: The princess's cell (bottom-right).
    # The health needed to survive this cell and have at least 1 HP remaining
    # is `max(1, 1 - dungeon[m-1][n-1])`.
    dp[m - 1][n - 1] = max(1, 1 - dungeon[m - 1][n - 1])

    # Fill the last column (moving upwards).
    # To reach (i, n-1) from (i+1, n-1), the health needed at (i, n-1)
    # is `dp[i+1][n-1] - dungeon[i][n-1]`, ensuring it's at least 1.
    for i in range(m - 2, -1, -1):
      dp[i][n - 1] = max(1, dp[i + 1][n - 1] - dungeon[i][n - 1])

    # Fill the last row (moving leftwards).
    # Similar logic, coming from (m-1, j+1).
    for j in range(n - 2, -1, -1):
      dp[m - 1][j] = max(1, dp[m - 1][j + 1] - dungeon[m - 1][j])

    # Fill the rest of the DP table (moving from bottom-right to top-left).
    for i in range(m - 2, -1, -1):
      for j in range(n - 2, -1, -1):
        # To reach (i,j), the knight can come from (i+1, j) or (i, j+1).
        # Choose the path that requires less health from the next step.
        min_health_from_next_step = min(dp[i + 1][j], dp[i][j + 1])
        # The health needed at (i,j) is `min_health_from_next_step - dungeon[i][j]`,
        # ensuring it's at least 1.
        dp[i][j] = max(1, min_health_from_next_step - dungeon[i][j])

    # The result is the minimum health needed at the starting cell (0,0).
    return dp[0][0]

  def unique_paths(self, m: int, n: int) -> int:
    """
        62. Unique Paths
        A robot is located at the top-left corner of a m x n grid.
        The robot can only move either down or right at any point in time.
        How many possible unique paths are there to reach the bottom-right corner?

        This uses dynamic programming with space optimization (O(N) space).
        `dp[j]` represents the number of unique paths to reach `(current_row, j)`.

        Time Complexity: O(m * n)
        Space Complexity: O(n) (where n is the number of columns)

        Args:
            m: Number of rows in the grid.
            n: Number of columns in the grid.

        Returns:
            The number of unique paths.
        """
    if m <= 0 or n <= 0:
      return 0

    # `dp` array stores the number of paths to reach each cell in the current row.
    # Initialize with 0s.
    dp = [0] * n
    # There's 1 way to reach the first cell (0,0).
    dp[0] = 1

    # Iterate through each row.
    for i in range(m):
      # Iterate through each column.
      for j in range(n):
        # For any cell (i, j), the number of paths to reach it is the sum of
        # paths from the cell directly above (i-1, j) and the cell directly
        # to its left (i, j-1).
        # `dp[j]` currently holds paths from `(i-1, j)`.
        # `dp[j-1]` holds paths from `(i, j-1)`.
        # Special handling for the first column (j=0): it can only come from above.
        if j > 0:
          dp[j] = dp[j] + dp[j - 1]
        # If j == 0, dp[0] already holds the correct value (1 for first row,
        # or previous row's dp[0] for subsequent rows, as it only comes from above).
        # No change needed for dp[0] if it's 1. If it was 0 (e.g., due to obstacle),
        # it stays 0.

    # The result is the number of unique paths to the bottom-right corner.
    return dp[n - 1]

  def unique_paths_with_obstacles(self, obstacle_grid: list[list[int]]) -> int:
    """
        63. Unique Paths II
        A robot is located at the top-left corner of a m x n grid.
        There are obstacles in the grid. How many unique paths are there?
        An obstacle is marked as 1, an empty space as 0.

        This uses dynamic programming with space optimization (O(N) space).
        `dp[j]` represents the number of unique paths to reach `(current_row, j)`.

        Time Complexity: O(m * n)
        Space Complexity: O(n) (where n is the number of columns)

        Args:
            obstacle_grid: A 2D list of integers where 1 represents an obstacle.

        Returns:
            The number of unique paths, considering obstacles.
        """
    m = len(obstacle_grid)
    if m == 0:
      return 0
    n = len(obstacle_grid[0])
    if n == 0:
      return 0

    # If the start or end cell is an obstacle, there are no paths.
    if obstacle_grid[0][0] == 1 or obstacle_grid[m - 1][n - 1] == 1:
      return 0

    # `dp` array to store paths to current row's cells.
    dp = [0] * n

    # Initialize the first cell's paths. If it's not an obstacle, 1 path.
    dp[0] = 1 if obstacle_grid[0][0] == 0 else 0

    # Iterate through each row.
    for i in range(m):
      # Update the first column's path count for the current row.
      # If the current cell (i, 0) is an obstacle, or if the cell above it
      # was unreachable (dp[0] from previous row was 0), then dp[0] becomes 0.
      # Otherwise, it remains 1 (from the cell above).
      if obstacle_grid[i][0] == 1:
        dp[0] = 0
      # Note: The original C++ `f[0] = f[0] == 0 ? 0 : (!obstacleGrid[i][0]);`
      # is equivalent to `dp[0] = 0` if `obstacleGrid[i][0]` is 1,
      # or `dp[0]` (from previous row) if `obstacleGrid[i][0]` is 0.
      # This is simpler: if current cell is obstacle, it's 0. Else, it keeps path from above.

      # Iterate through the rest of the columns for the current row.
      for j in range(1, n):
        if obstacle_grid[i][j] == 0:  # If current cell is not an obstacle
          # Paths come from left (dp[j-1]) and from above (dp[j]).
          dp[j] = dp[j] + dp[j - 1]
        else:  # If current cell is an obstacle
          dp[j] = 0  # No paths can go through an obstacle

    # The result is the number of unique paths to the bottom-right corner.
    return dp[n - 1]


# --- Example Usage ---
if __name__ == "__main__":
  solver = DPGrid()

  print("--- 64. Minimum Path Sum ---")
  grid1 = [[1, 3, 1], [1, 5, 1], [4, 2, 1]]
  print(f"minPathSum({grid1}): {solver.min_path_sum(grid1)}"
       )  # Expected: 7 (1->1->2->1)
  grid2 = [[1, 2, 3], [4, 5, 6]]
  print(f"minPathSum({grid2}): {solver.min_path_sum(grid2)}"
       )  # Expected: 12 (1->2->3->6)

  print("\n--- 120. Triangle ---")
  triangle1 = [[2], [3, 4], [6, 5, 7], [4, 1, 8, 3]]
  print(f"minimumTotal({triangle1}): {solver.minimum_total(triangle1)}"
       )  # Expected: 11 (2+3+5+1)
  triangle2 = [[-10]]
  print(f"minimumTotal({triangle2}): {solver.minimum_total(triangle2)}"
       )  # Expected: -10

  print("\n--- Pacific Atlantic Water Flow (Alternative DP) ---")
  matrix1 = [[1, 2, 2, 3, 5], [3, 2, 3, 4, 4], [2, 4, 5, 3, 1], [6, 7, 1, 4, 5],
             [5, 1, 1, 2, 4]]
  # Expected output: [(0, 4), (1, 3), (1, 4), (2, 2), (3, 0), (3, 1), (4, 0)]
  # (Order might vary, but content should be the same)
  result_pa = solver.pacific_atlantic_another(matrix1)
  print(f"pacificAtlanticAnother({matrix1}): {sorted(result_pa)}")

  matrix2 = [[1, 2], [3, 4]]
  result_pa2 = solver.pacific_atlantic_another(matrix2)
  print(f"pacificAtlanticAnother({matrix2}): {sorted(result_pa2)}"
       )  # Expected: [(0,1), (1,0), (1,1)]

  print("\n--- 85. Maximal Rectangle ---")
  matrix_rect1 = [["1", "0", "1", "0", "0"], ["1", "0", "1", "1", "1"],
                  ["1", "1", "1", "1", "1"], ["1", "0", "0", "1", "0"]]
  print(
      f"maximalRectangle({matrix_rect1}): {solver.maximal_rectangle(matrix_rect1)}"
  )  # Expected: 6

  matrix_rect2 = [["0"]]
  print(
      f"maximalRectangle({matrix_rect2}): {solver.maximal_rectangle(matrix_rect2)}"
  )  # Expected: 0

  matrix_rect3 = [["1"]]
  print(
      f"maximalRectangle({matrix_rect3}): {solver.maximal_rectangle(matrix_rect3)}"
  )  # Expected: 1

  print("\n--- 221. Maximal Square ---")
  matrix_sq1 = [["1", "0", "1", "0", "0"], ["1", "0", "1", "1", "1"],
                ["1", "1", "1", "1", "1"], ["1", "0", "0", "1", "0"]]
  print(f"maximalSquare({matrix_sq1}): {solver.maximal_square(matrix_sq1)}"
       )  # Expected: 4 (2x2 square)

  matrix_sq2 = [["0"]]
  print(f"maximalSquare({matrix_sq2}): {solver.maximal_square(matrix_sq2)}"
       )  # Expected: 0

  matrix_sq3 = [["1"]]
  print(f"maximalSquare({matrix_sq3}): {solver.maximal_square(matrix_sq3)}"
       )  # Expected: 1

  print("\n--- 174. Dungeon Game ---")
  dungeon1 = [[-2, -3, 3], [-5, -10, 1], [10, 30, -5]]
  print(
      f"calculateMinimumHP({dungeon1}): {solver.calculate_minimum_hp(dungeon1)}"
  )  # Expected: 7

  dungeon2 = [[0]]
  print(
      f"calculateMinimumHP({dungeon2}): {solver.calculate_minimum_hp(dungeon2)}"
  )  # Expected: 1

  dungeon3 = [[100]]
  print(
      f"calculateMinimumHP({dungeon3}): {solver.calculate_minimum_hp(dungeon3)}"
  )  # Expected: 1

  print("\n--- 62. Unique Paths ---")
  print(f"uniquePaths(3, 7): {solver.unique_paths(3, 7)}")  # Expected: 28
  print(f"uniquePaths(3, 2): {solver.unique_paths(3, 2)}")  # Expected: 3

  print("\n--- 63. Unique Paths II ---")
  obstacle_grid1 = [[0, 0, 0], [0, 1, 0], [0, 0, 0]]
  print(
      f"uniquePathsWithObstacles({obstacle_grid1}): {solver.unique_paths_with_obstacles(obstacle_grid1)}"
  )  # Expected: 2

  obstacle_grid2 = [[0, 1], [0, 0]]
  print(
      f"uniquePathsWithObstacles({obstacle_grid2}): {solver.unique_paths_with_obstacles(obstacle_grid2)}"
  )  # Expected: 1

  obstacle_grid3 = [[1]]
  print(
      f"uniquePathsWithObstacles({obstacle_grid3}): {solver.unique_paths_with_obstacles(obstacle_grid3)}"
  )  # Expected: 0

  obstacle_grid4 = [[0]]
  print(
      f"uniquePathsWithObstacles({obstacle_grid4}): {solver.unique_paths_with_obstacles(obstacle_grid4)}"
  )  # Expected: 1

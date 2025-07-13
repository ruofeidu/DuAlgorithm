import collections
import string
from typing import List


def ladderLength(self, beginWord, endWord, wordList):
  """
	:type beginWord: str
	:type endWord: str
	:type wordList: List[str]
	:rtype: int
	"""
  wordList = set(wordList)
  q = collections.deque([[beginWord, 1]])

  while q:
    word, length = q.popleft()
    if word == endWord:
      return length
    for i in range(len(word)):
      for c in 'abcdefghijklmnopqrstuvwxyz':
        next_word = word[:i] + c + word[i + 1:]
        if next_word in wordList:
          wordList.remove(next_word)
          q.append([next_word, length + 1])

  return 0


def bfsGraphWithPortal(R: int, C: int, G: List[List[str]]) -> int:
  """
  Calculates the minimum time to get from 'S' to an 'E' in a grid with walls and portals.
  This is a classic shortest path problem on an unweighted graph, best solved with Breadth-First Search (BFS).

  Time Complexity: O(R * C) because each cell is visited at most once.
  Space Complexity: O(R * C) for the queue and visited trackers.
  """
  # Use a defaultdict to map each portal letter to a list of its (row, col) coordinates.
  # This is more efficient and handles any number of portals per letter.
  portal_locations = collections.defaultdict(list)
  start_pos = None

  # A single pass over the grid to find the start position and catalog all portal locations.
  for r in range(R):
    for c in range(C):
      cell = G[r][c]
      if cell == 'S':
        start_pos = (r, c)
      elif 'a' <= cell <= 'z':
        portal_locations[cell].append((r, c))

  # The BFS queue will store tuples of (row, col, current_steps).
  queue = collections.deque([(start_pos[0], start_pos[1], 0)])

  # 'visited_cells' tracks visited (r, c) coordinates to prevent cycles and redundant work.
  visited_cells = [[False for _ in range(C)] for _ in range(R)]
  visited_cells[start_pos[0]][start_pos[1]] = True

  # 'visited_portals' tracks which portal networks (by letter) have been used.
  # This is a key optimization to prevent re-exploring the same portal system.
  visited_portals = set()

  DIRECTIONS = [(0, 1), (0, -1), (1, 0), (-1, 0)]  # Right, Left, Down, Up

  while queue:
    # Use popleft() for FIFO behavior, which is essential for BFS.
    r, c, steps = queue.popleft()

    # Action 1: Walk to all valid adjacent cells.
    for dr, dc in DIRECTIONS:
      nr, nc = r + dr, c + dc

      # Check if the new position is within grid boundaries.
      if not (0 <= nr < R and 0 <= nc < C):
        continue

      # Check for walls or if the cell has already been visited.
      if G[nr][nc] == '#' or visited_cells[nr][nc]:
        continue

      # If we find an exit, we're done! The first time we reach it is the shortest path.
      if G[nr][nc] == 'E':
        return steps + 1

      visited_cells[nr][nc] = True
      queue.append((nr, nc, steps + 1))

    # Action 2: Teleport if the current cell is a portal.
    current_cell = G[r][c]
    if 'a' <= current_cell <= 'z' and current_cell not in visited_portals:
      # Explore all destinations for this portal letter.
      for pr, pc in portal_locations[current_cell]:
        if not visited_cells[pr][pc]:
          visited_cells[pr][pc] = True
          queue.append((pr, pc, steps + 1))

      # Mark this entire portal network as used so we don't teleport through it again.
      visited_portals.add(current_cell)

  # If the queue is exhausted and no exit was found, the exit is unreachable.
  return -1


graph = ['.E.', '.#E', '.S#']
print(bfsGraphWithPortal(3, 3, graph))

graph = ['aS.b', '####', 'Eb.a']
print(bfsGraphWithPortal(3, 4, graph))

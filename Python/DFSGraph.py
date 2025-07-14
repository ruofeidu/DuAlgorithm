import sys
from typing import List


def getLargestStronglyConnectedComponents(N: int, M: int, A: List[int],
                                          B: List[int]) -> int:
  """
  Calculates the maximum number of different pages that can be visited in a single session.

  This function models the problem as finding the longest path in a directed graph.
  It handles cycles by identifying Strongly Connected Components (SCCs) and then
  computes the longest path on the resulting Directed Acyclic Graph (DAG) of components.

  Args:
      N: The total number of web pages.
      M: The number of links.
      A: A list of pages where links originate.
      B: A list of pages where links point to.

  Returns:
      The maximum number of unique pages that can be visited.
  """
  # Adjusting the recursion limit is no longer necessary for Tarjan's algorithm
  # but might still be needed for find_longest_path if the condensation graph is very deep.
  # new_recursion_limit = N + M + 50
  # if sys.getrecursionlimit() < new_recursion_limit:
  #   sys.setrecursionlimit(new_recursion_limit)

  # 1. Build the graph using an adjacency list (with 0-based indexing).
  adj = [[] for _ in range(N)]
  for i in range(M):
    u, v = A[i] - 1, B[i] - 1
    adj[u].append(v)

  # 2. Find Strongly Connected Components (SCCs) using an iterative Tarjan's Algorithm.
  ids = [-1] * N
  low = [-1] * N
  onStack = [False] * N
  stack = []
  timer = 0
  scc_count = 0
  scc_map = [-1] * N  # Maps each node to its SCC identifier.

  for i in range(N):
    if ids[i] == -1:
      # The call_stack simulates the recursion stack.
      # Each element is a tuple: (node, neighbor_index)
      call_stack = [(i, 0)]

      while call_stack:
        at_node, neighbor_idx = call_stack[-1]

        if neighbor_idx == 0:
          # First time visiting the node (equivalent to the start of the recursive call)
          stack.append(at_node)
          onStack[at_node] = True
          ids[at_node] = low[at_node] = timer
          timer += 1

        if neighbor_idx < len(adj[at_node]):
          # Process next neighbor
          to_node = adj[at_node][neighbor_idx]

          # Move to the next neighbor for the current node in the next iteration
          call_stack[-1] = (at_node, neighbor_idx + 1)

          if ids[to_node] == -1:
            # If neighbor is unvisited, push it to the stack to visit next
            call_stack.append((to_node, 0))
          elif onStack[to_node]:
            # If neighbor is a visited ancestor on the stack
            low[at_node] = min(low[at_node], ids[to_node])

        else:
          # Finished visiting all neighbors (equivalent to returning from the recursive call)
          call_stack.pop()

          if len(call_stack) > 0:
            parent_node = call_stack[-1][0]
            low[parent_node] = min(low[parent_node], low[at_node])

          # If 'at_node' is the root of an SCC, pop the SCC from the stack.
          if ids[at_node] == low[at_node]:
            while stack:
              node = stack.pop()
              onStack[node] = False
              scc_map[node] = scc_count
              if node == at_node:
                break
            scc_count += 1

  if scc_count == 0:
    return 0

  # 3. Build the condensation graph.
  scc_sizes = [0] * scc_count
  for node_scc_id in scc_map:
    if node_scc_id != -1:
      scc_sizes[node_scc_id] += 1

  scc_adj_sets = [set() for _ in range(scc_count)]
  for u in range(N):
    for v in adj[u]:
      if scc_map[u] != scc_map[v]:
        scc_adj_sets[scc_map[u]].add(scc_map[v])

  scc_adj = [list(s) for s in scc_adj_sets]

  # 4. Find the longest path in the condensation DAG using Dynamic Programming.
  dp = [-1] * scc_count  # Memoization table for longest path from each SCC.

  def find_longest_path(scc_id):
    if dp[scc_id] != -1:
      return dp[scc_id]

    max_suffix_path = 0
    for neighbor_scc_id in scc_adj[scc_id]:
      max_suffix_path = max(max_suffix_path, find_longest_path(neighbor_scc_id))

    dp[scc_id] = scc_sizes[scc_id] + max_suffix_path
    return dp[scc_id]

  max_visited_pages = 0
  for i in range(scc_count):
    if dp[i] == -1:
      max_visited_pages = max(max_visited_pages, find_longest_path(i))

  return max_visited_pages


def getLargestStronglyConnectedComponentsRecursion(N: int, M: int, A: List[int],
                                                   B: List[int]) -> int:
  """
  Calculates the maximum number of different pages that can be visited in a single session.

  This function models the problem as finding the longest path in a directed graph.
  It handles cycles by identifying Strongly Connected Components (SCCs) and then
  computes the longest path on the resulting Directed Acyclic Graph (DAG) of components.

  Args:
      N: The total number of web pages.
      A: A list of pages where links originate.
      B: A list of pages where links point to.

  Returns:
      The maximum number of unique pages that can be visited.
  """
  # Set a higher recursion limit for deep DFS traversals in large graphs.
  new_recursion_limit = N + M + 50

  if sys.getrecursionlimit() < new_recursion_limit:
    sys.setrecursionlimit(new_recursion_limit)

  # 1. Build the graph using an adjacency list (with 0-based indexing).
  adj = [[] for _ in range(N)]
  for i in range(M):
    # Convert from 1-based page numbers to 0-based indices.
    u, v = A[i] - 1, B[i] - 1
    adj[u].append(v)

  # 2. Find Strongly Connected Components (SCCs) using Tarjan's Algorithm.
  ids = [-1] * N
  low = [-1] * N
  onStack = [False] * N
  stack = []
  timer = 0
  scc_count = 0
  scc_map = [-1] * N  # Maps each node to its SCC identifier.

  def tarjan_dfs(at_node):
    nonlocal timer, scc_count

    stack.append(at_node)
    onStack[at_node] = True
    ids[at_node] = low[at_node] = timer
    timer += 1

    for to_node in adj[at_node]:
      if ids[to_node] == -1:  # If neighbor is unvisited, recurse.
        tarjan_dfs(to_node)
        low[at_node] = min(low[at_node], low[to_node])
      elif onStack[to_node]:  # If neighbor is a visited ancestor on the stack.
        low[at_node] = min(low[at_node], ids[to_node])

    # If 'at_node' is the root of an SCC, pop the SCC from the stack.
    if ids[at_node] == low[at_node]:
      while stack:
        node = stack.pop()
        onStack[node] = False
        scc_map[node] = scc_count
        if node == at_node:
          break
      scc_count += 1

  for i in range(N):
    if ids[i] == -1:
      tarjan_dfs(i)

  if scc_count == 0:
    return 0

  # 3. Build the condensation graph.
  scc_sizes = [0] * scc_count
  for node_scc_id in scc_map:
    if node_scc_id != -1:
      scc_sizes[node_scc_id] += 1

  scc_adj_sets = [set() for _ in range(scc_count)]
  for u in range(N):
    for v in adj[u]:
      scc_u, scc_v = scc_map[u], scc_map[v]
      if scc_u != scc_v:
        scc_adj_sets[scc_u].add(scc_v)

  scc_adj = [list(s) for s in scc_adj_sets]

  # 4. Find the longest path in the condensation DAG using Dynamic Programming.
  dp = [-1] * scc_count  # Memoization table for longest path from each SCC.

  def find_longest_path(scc_id):
    if dp[scc_id] != -1:
      return dp[scc_id]

    max_suffix_path = 0
    for neighbor_scc_id in scc_adj[scc_id]:
      max_suffix_path = max(max_suffix_path, find_longest_path(neighbor_scc_id))

    # The longest path is the size of the current SCC + the longest path from its neighbors.
    dp[scc_id] = scc_sizes[scc_id] + max_suffix_path
    return dp[scc_id]

  max_visited_pages = 0
  # Check all SCCs as potential starting points for a session.
  for i in range(scc_count):
    max_visited_pages = max(max_visited_pages, find_longest_path(i))

  return max_visited_pages


print(getLargestStronglyConnectedComponents(4, 4, [1, 2, 3, 4], [4, 1, 2, 1]))

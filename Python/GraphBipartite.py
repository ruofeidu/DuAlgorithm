class Solution:

  def isBipartite(self, graph: list[list[int]]) -> bool:
    """
        Checks if a given graph is bipartite.

        A graph is bipartite if its nodes can be divided into two disjoint and independent sets,
        U and V, such that every edge connects a node in U to one in V.
        This means there are no edges within the same set.
        This function uses a Breadth-First Search (BFS) or Depth-First Search (DFS)
        approach (implemented with a stack, mimicking DFS implicitly) to color the graph.

        Args:
            graph: An adjacency list representation of the graph. `graph[i]` is a list
                   of neighbors of node `i`. Nodes are 0-indexed.

        Returns:
            True if the graph is bipartite, False otherwise.
        """

    # `col` (colors) dictionary: Stores the color assigned to each node.
    # `col[node] = 0` means node is in set U.
    # `col[node] = 1` means node is in set V.
    # An unvisited node will not be in `col`.
    col = {}
    n = len(graph)  # Number of nodes in the graph

    # Iterate through each node in the graph.
    # This handles disconnected components within the graph.
    for node in range(n):
      # If the current node has already been colored (visited),
      # skip it as it's part of a component already processed.
      if node in col:
        continue

      # Start a traversal (DFS-like using a stack) from the current `node`.
      stack = [node]
      # Assign an initial color (e.g., 0) to the starting node of the component.
      col[node] = 0

      # Process nodes in the stack until it's empty.
      while stack:
        u = stack.pop()  # Get the current node to process

        # Iterate through all neighbors `v` of node `u`.
        for v in graph[u]:
          # If neighbor `v` has not been colored yet:
          if v not in col:
            stack.append(v)  # Add `v` to the stack for future processing.
            # Assign `v` the opposite color of `u`.
            # `col[u] ^ 1` is a bitwise XOR that flips 0 to 1 and 1 to 0.
            col[v] = col[u] ^ 1
          # If neighbor `v` has already been colored:
          elif col[v] == col[u]:
            # If `v` has the same color as `u`, it means there's an edge
            # connecting two nodes of the same color. This violates the
            # definition of a bipartite graph.
            return False
    # If the entire graph (all its connected components) has been traversed
    # without finding any conflicts (i.e., no adjacent nodes with the same color),
    # then the graph is bipartite.
    return True

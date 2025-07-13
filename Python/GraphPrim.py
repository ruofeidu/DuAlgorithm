import sys
import heapq


def prim(graph: list[list[int]]) -> int:
  """
    Implements Prim's algorithm to find the Minimum Spanning Tree (MST) weight.
    Prim's algorithm builds the MST by adding one node at a time.

    Time Complexity: O(V^2), where V is the number of vertices.
                     This version is suitable for dense graphs or when V is small.
                     For sparse graphs, a Min-Priority Queue (e.g., using heapq)
                     optimization can reduce time to O(E log V) or O(E + V log V).
    Space Complexity: O(V) for 'low' and 'visited' arrays.

    Args:
        graph: An adjacency matrix representing the graph.
               graph[i][j] is the weight of the edge between vertex i and j.
               Assumes graph[i][i] is 0 or infinity (no self-loops)
               and graph[i][j] == graph[j][i] (undirected).
               Use float('inf') for non-existent edges.

    Returns:
        The total weight of the Minimum Spanning Tree.
        Returns -1 if the graph is not connected.
    """
  num_vertices = len(graph)

  if num_vertices == 0:
    return 0  # An empty graph has an MST weight of 0

  # low[v] stores the minimum weight of an edge connecting vertex v
  # to the set of vertices already included in the MST.
  # Initialize with a very large value (infinity) for all nodes except the start.
  low = [sys.maxsize] * num_vertices  # Or float('inf')

  # visited[v] is True if vertex v is already included in the MST.
  visited = [False] * num_vertices

  mst_weight = 0  # Accumulator for the total weight of the MST

  # Start Prim's algorithm from vertex 0.
  # The 'low' value for the starting node is effectively 0,
  # as it's the first node added to the MST.
  low[0] = 0

  # The outer loop runs 'num_vertices' times. In each iteration,
  # one vertex is added to the MST.
  for _ in range(num_vertices):
    current_min_edge_weight = sys.maxsize  # Initialize with infinity
    vertex_to_add = -1  # Stores the index of the vertex with the minimum edge

    # Inner loop: Find the unvisited vertex with the minimum 'low' value.
    # This vertex has the minimum edge connecting it to the current MST.
    for j in range(num_vertices):
      if not visited[j] and low[j] < current_min_edge_weight:
        current_min_edge_weight = low[j]
        vertex_to_add = j

    # If no unvisited vertex can be reached (current_min_edge_weight is still infinity),
    # it means the graph is not connected.
    if vertex_to_add == -1 or current_min_edge_weight == sys.maxsize:
      # If this happens before all vertices are added, the graph is disconnected.
      # For a connected graph, current_min_edge_weight should always find a finite value
      # until all vertices are added.
      if _ < num_vertices:  # If we haven't processed all vertices yet
        return -1  # Not a connected graph
      else:
        break  # All vertices processed, even if last current_min_edge_weight was 0 (for a single node left)

    # Add the found vertex to the MST.
    mst_weight += current_min_edge_weight
    visited[vertex_to_add] = True

    # Update 'low' values for all unvisited neighbors of the newly added vertex.
    # If an edge from the newly added vertex 'vertex_to_add' to an unvisited
    # vertex 'j' is shorter than the current 'low[j]', update 'low[j]'.
    for j in range(num_vertices):
      # The bug in C++ `++i` was fixed here to `++j` (Python `for j in range(...)` handles it).
      if not visited[j] and graph[vertex_to_add][j] < low[j]:
        low[j] = graph[vertex_to_add][j]

  return mst_weight


def prim_priority_queue(graph: list[list[int]]) -> int:
  """
    Implements Prim's algorithm to find the Minimum Spanning Tree (MST) weight
    using a Min-Priority Queue (heapq). This optimization is efficient for sparse graphs.

    Args:
        graph: An adjacency matrix representing the graph.
               `graph[i][j]` is the weight of the edge between vertex `i` and `j`.
               Use `float('inf')` for non-existent edges.
               Assumes `graph[i][i]` is 0 or infinity (no self-loops)
               and `graph[i][j] == graph[j][i]` (undirected).

    Returns:
        The total weight of the Minimum Spanning Tree.
        Returns -1 if the graph is not connected.
    """
  num_vertices = len(graph)

  if num_vertices == 0:
    return 0  # An empty graph has an MST weight of 0

  # min_heap stores tuples of (weight, vertex_id).
  # The 'weight' is the minimum cost to connect 'vertex_id' to the current MST.
  # We start by pushing the starting vertex (e.g., vertex 0) with a weight of 0.
  min_heap = [(0, 0)]  # (current_min_edge_weight, vertex_id)

  # visited[v] is True if vertex v is already included in the MST.
  visited = [False] * num_vertices

  mst_weight = 0  # Accumulator for the total weight of the MST
  nodes_in_mst_count = 0  # To count how many unique nodes have been added to the MST.
  # For a connected graph, this should reach num_vertices.

  while min_heap and nodes_in_mst_count < num_vertices:
    # Extract the vertex with the minimum edge weight from the priority queue.
    current_weight, u = heapq.heappop(min_heap)

    # If 'u' has already been visited (i.e., already added to the MST),
    # this is an old entry in the heap (due to lazy updates), so skip it.
    if visited[u]:
      continue

    # Add vertex 'u' to the MST.
    visited[u] = True
    mst_weight += current_weight
    nodes_in_mst_count += 1

    # Explore all neighbors 'v' of the newly added vertex 'u'.
    for v in range(num_vertices):
      edge_weight = graph[u][v]
      # If there's a valid edge (u, v) and 'v' is not yet in the MST,
      # push this edge to the priority queue.
      # We use `float('inf')` as the sentinel for non-existent edges.
      if edge_weight != float('inf') and not visited[v]:
        heapq.heappush(min_heap, (edge_weight, v))

  # After the loop, check if all vertices were included in the MST.
  # If `nodes_in_mst_count` is less than `num_vertices`, it means the graph
  # is disconnected (or at least the component containing the starting node
  # does not include all other nodes).
  if nodes_in_mst_count != num_vertices:
    return -1  # Graph is not connected

  return mst_weight


# --- Example Usage ---
if __name__ == "__main__":

  # Example Graph (Adjacency Matrix):
  # Representing non-existent edges with float('inf')
  graph1 = [
      #   A       B       C       D       E
      [0, 2, math.inf, 6, math.inf],  # A
      [2, 0, 3, 8, 5],  # B
      [math.inf, 3, 0, math.inf, 7],  # C
      [6, 8, math.inf, 0, 9],  # D
      [math.inf, 5, 7, 9, 0]  # E
  ]
  # Expected MST weight: 2 + 3 + 5 + 6 = 16 (Edges: AB, BC, BE, AD)

  print(f"Graph 1 MST weight: {prim(graph1)}")  # Expected: 16

  # Disconnected Graph Example:
  graph2 = [[0, 1, math.inf, math.inf], [1, 0, math.inf, math.inf],
            [math.inf, math.inf, 0, 1], [math.inf, math.inf, 1, 0]]
  print(f"Graph 2 MST weight (disconnected): {prim(graph2)}")  # Expected: -1

  # Single Node Graph
  graph3 = [[0]]
  print(f"Graph 3 MST weight (single node): {prim(graph3)}")  # Expected: 0

  # Empty Graph
  graph4 = []
  print(f"Graph 4 MST weight (empty graph): {prim(graph4)}")  # Expected: 0

  # Graph where some nodes might be unreachable initially but connect later
  graph5 = [[0, 10, math.inf], [10, 0, 1], [math.inf, 1, 0]]
  print(f"Graph 5 MST weight: {prim(graph5)}")  # Expected: 11 (Edges: AB, BC)

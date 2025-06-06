# DuAlgorithm

My personal collection of algorithms, data structures, and design patterns in C++, Python, and more.

## Algorithm

### Dynamic Programming

#### Knapsack problem

- f[j] = f[j] || f[j-v[i]]
- f[i][j] = max(f[i-1]j-v[i]] + w[i], f[i-1][j])
- f[i,j] = f[i-1,j-a[i]] or f[i-1,j+a[i]]

##### Knapsack on a Tree

- f[i,j] = max(f[i,j], f[l,j-v[i]-v[fb[i]]-v[fa[i]]]+v[i]*p[i]+v[fb[i]]*p[fb[i]]+v[fa[i]]\*p[fa[i]])

#### LIS: Longest Increasing Subsequence

- f[i] = max{ f[j] } + 1, a[j] < a[i], f[i] ascending, lower_bound

#### LCS: Longest Common Subsequence

- f[i] = max{f[j] + 1}
- f[i] = min{{f(i-k)} (not stone[i]) {f(i-k)} + 1} (stone[i]);

#### Edit Distance

- f[i][j] = min(min(f[i-1][j], f[i][j-1]), f[i-1][j - 1]) + 1;

#### Stock problem

- buy[i] = max(rest[i-1] - price, buy[i-1])
- sell[i] = max(buy[i-1] + price, sell[i-1])
- rest[i] = max(sell[i-1], buy[i-1], rest[i-1])

### Math

#### Counting Problems

- uniquePath: C(m+n-2, max(m-1, n-1))
- maxRegionsByALine: n \* (n + 1) / 2 + 1
- maxRegionsByAPolyLine: (n - 1)_(2_ n - 1) + 2 \* n
- countTrianglesOfPolygon: C(2 \* n - 2, n - 1)

#### Mods Theory

- GCD: Greatest Common Divisor; Extended: gcd(a, b) = a _x + b_ y
- LCM: Lowest Common Multiple
- Modular exponentiation: (a ^ b) % n
- Modular multiplication (x \* y) % n
- mod equation solver: a \* x = b % n
- Chinese remainder theorem

#### Number Theory

#### Primes

- Miller¨CRabin primality test
- Euler's totient function
- Count primes

#### Permutations

#### Random

- Shuffle: scan and swap a[i] with a[random(i, n - 1)].

#### Probability

##### Shuffle

- Time: O(N), scan and swap a[i] with a[random(i,n-1)].

##### Basic

- Random variables, union, joint distribution, conditional probabilities, chain rule, marginalization, Baye's Rule
- P(A|B) = P(B|A) \* P(A) / P(B)
- P(AB) = P(A|B)P(B)
- P(ABC) = P(A,B | C) P(C) = P(A|BC)P(BC) = P(A|BC) P(B|C) P(C)
- rand(0,1): unifiorm
- Y~ uniform (0,1)
- X = Y_1 .. Y_n i.i.d. ~ Gaussian(0,1)
- X = rand(0,1) + rand(0,1) + rand(0,1) + rand(0,1) + rand(0,1)......(100000 times)

#### Sampling

- Compute the CDF of the 1D distribution
- Derive the inverse of the CDF
- Map a random variable through the inverse from the previous step.

### Graph Theory

#### Shortest Path

- Dijkstra: O(E + V log V), heap for pending vertices.
- Bellman Ford: O(VE)
- Kruskal: O(E log V)
- Prim: O(E + V log V) Fibonacci heap and adjacency list

#### Network Flow

- Graham, BFS for sparse biparate graph
  \*\* O(VE)
- Hopcroft-Carp
  \*\* O(V^0.5 E)
- Kuhn Munkras
  \*\* O(VE^2)
- Max Flow = Min Cut = minimum set to remove for cutting the graph
  \*\* O(N^3)
- Dinic
  \*\* O(V^2 E)
- HLPP
  \*\* O(V^3)
- MinCostMaxFlow
  \*\* SPFA << O(VEf)

##### SPFA

### Greedy

- Heap

### Linear

#### RMQ: Range Minimum/Maximum Query

#### LCA(T, u, V) = E[RMQ(d, r[u], r[v])], (r[u] < r[v])

#### RSQ: Range Sum Query

### String

#### KMP

- O(n + m)

#### RabinKarp

- Avereage: O(N), Worst: O(MN)

### Sorts

#### QuickSort

- When N < 16, use insersion sort, since the data is mostly sorted
- When depth > T, use heap sort
- Time: O(N log N)

#### MergeSort

- Time: O(N log N)

#### BubbleSort

#### BucketSort

### Search

#### BFS

- Queue

#### DFS

- Stack

#### Binary Search

- lower_bound, greater or equal to

## Data Structure

### Linear

#### Interval

- Sort and merge

##### Sweeping line

#### Linked List

- Reverse (between): Use a dummy pointer
- Deep copy: Copy one after one

#### Queue

##### Dequeue

- Sliding window
- Moving average

#### Stacks

- Calculator

### Cluster

#### Union Set

- Time: O(alpha), typically alpha < 4

## Design Patterns

### Sinleton

- multithreading safe singleton
- a static instance member pointing to its self
- all other members are ensured singleton
- garbage collection when destroyed

### Factory

- create and recycle objects

### Abstract Factory

- virtual factories for creating products

1. Use a Heap for K Elements

- When finding the top K largest or smallest elements, heaps are your best tool.
- They efficiently handle priority-based problems with O(log K) operations.
- Example: Find the 3 largest numbers in an array.

2. Binary Search or Two Pointers for Sorted Inputs

- Sorted arrays often point to Binary Search or Two Pointer techniques.
- These methods drastically reduce time complexity to O(log n) or O(n).
- Example: Find two numbers in a sorted array that add up to a target.

3. Backtracking or BFS for Combinations

- Use Backtracking or BFS to explore all combinations or permutations.
- They’re great for generating subsets or solving puzzles.
- Example: Generate all possible subsets of a given set.

4. BFS or DFS for Trees and Graphs

- Trees and graphs are often solved using BFS for shortest paths or DFS for traversals.
- BFS is best for level-order traversal, while DFS is useful for exploring paths.
- Example: Find the shortest path in a graph.

5. Convert Recursion to Iteration with a Stack

- Recursive algorithms can be converted to iterative ones using a stack.
- This approach provides more control over memory and avoids stack overflow.
- Example: Iterative in-order traversal of a binary tree.

6. Optimize Arrays with HashMaps or Sorting

- Replace nested loops with HashMaps for O(n) solutions or sorting for O(n log n).
- HashMaps are perfect for lookups, while sorting simplifies comparisons.
- Example: Find duplicates in an array.

7. Use Dynamic Programming for Optimization Problems

- DP breaks problems into smaller overlapping sub-problems for optimization.
- It's often used for maximization, minimization, or counting paths.
- Example: Solve the 0/1 knapsack problem.

8. HashMap or Trie for Common Substrings

- Use HashMaps or Tries for substring searches and prefix matching.
- They efficiently handle string patterns and reduce redundant checks.
- Example: Find the longest common prefix among multiple strings.

9. Trie for String Search and Manipulation

- Tries store strings in a tree-like structure, enabling fast lookups.
- They’re ideal for autocomplete or spell-check features.
- Example: Implement an autocomplete system.

10. Fast and Slow Pointers for Linked Lists

- Use two pointers moving at different speeds to detect cycles or find midpoints.
- This approach avoids extra memory usage and works in O(n) time.
- Example: Detect if a linked list has a loop.

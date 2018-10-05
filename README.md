# DuAlgorithm
My collection of algorithms, data structures, and design patterns in C++, Python, and more.

## Algorithm
### Dynamic Programming
#### Knapsack problem
* f[j] = f[j] || f[j-v[i]]
* f[i][j] = max(f[i-1][j-v[i]] + w[i], f[i-1][j])
* f[i,j] = f[i-1,j-a[i]] or f[i-1,j+a[i]]
##### Knapsack on a tree
* f[i,j] = max(f[i,j], f[l,j-v[i]-v[fb[i]]-v[fa[i]]]+v[i]*p[i]+v[fb[i]]*p[fb[i]]+v[fa[i]]*p[fa[i]])
#### LIS: Longest Increasing Subsequence
* f[i] = max{ f[j] } + 1, a[j] < a[i], f[i] ascending, lower_bound
#### LCS: Longest Common Subsequence
* f[i] = max{f[j] + 1}
* f[i] = min{{f(i-k)} (not stone[i]) {f(i-k)} + 1} (stone[i]);  
#### Edit Distance
* f[i][j] = min(min(f[i-1][j], f[i][j-1]), f[i-1][j - 1]) + 1;
#### Stock problem
* buy[i]  = max(rest[i-1] - price, buy[i-1])
* sell[i] = max(buy[i-1] + price, sell[i-1])
* rest[i] = max(sell[i-1], buy[i-1], rest[i-1])
### Math
#### Counting Problems
* uniquePath: C(m+n-2, max(m-1, n-1))
* maxRegionsByALine: n * (n + 1) / 2 + 1
* maxRegionsByAPolyLine: (n - 1)*(2 * n - 1) + 2 * n
* countTrianglesOfPolygon: C(2 * n - 2, n - 1)
#### Mods Theory
* GCD: Greatest Common Divisor; Extended: gcd(a, b) = a * x + b * y
* LCM: Lowest Common Multiple
* Modular exponentiation: (a ^ b) % n
* Modular multiplication (x * y) % n
* mod equation solver: a * x = b % n
* Chinese remainder theorem
#### Number Theory
#### Primes
* Miller¨CRabin primality test
* Euler's totient function
* Count primes
#### Permutations
#### Random
* Shuffle: scan and swap a[i] with a[random(i, n - 1)].
#### Probability
##### Shuffle
* Time: O(N), scan and swap a[i] with a[random(i,n-1)].
#### Sampling
* Compute the CDF of the 1D distribution
* Derive the inverse of the CDF
* Map a random variable through the inverse from the previous step.
### Graph Theory
#### Shortest Path
* Dijkstra: O(E + V log V), heap for pending vertices.
* Bellman Ford: O(VE)
* Kruskal: O(E log V)
* Prim: O(E + V log V) Fibonacci heap and adjacency list
#### Network Flow
* Graham
* Hopcroft-Carp
* Kuhn Munkras
* Max Flow = Min Cut
* Dinic
* HLPP
* MinCostMaxFlow
##### SPFA
### Greedy
* Heap
### Linear
#### RMQ: Range Minimum/Maximum Query
#### LCA(T, u, V) = E[RMQ(d, r[u], r[v])], (r[u] < r[v])
#### RSQ: Range Sum Query
### String
#### KMP
* O(n + m)
#### RabinKarp
* Avereage: O(N), Worst: O(MN)
### Sorts
#### QuickSort
* When N < 16, use insersion sort, since the data is mostly sorted
* When depth > T, use heap sort
* Time: O(N log N)
#### MergeSort
* Time: O(N log N)
#### BubbleSort
#### BucketSort
### Search
#### BFS
* Queue
#### DFS
* Stack
#### Binary Search
* lower_bound, greater or equal to
## Data Structure
### Linear
#### Interval
* Sort and merge
##### Sweeping line
#### Linked List
* Reverse (between): Use a dummy pointer
* Deep copy: Copy one after one

#### Queue
##### Dequeue
* Sliding window
* Moving average

#### Stacks
* Calculator

### Cluster
#### Union Set
* Time: O(alpha), typically alpha < 4

## Design Patterns
### Sinleton
* multithreading safe singleton
* a static instance member pointing to its self
* all other members are ensured singleton
* garbage collection when destroyed

### Factory
* create and recycle objects

### Abstract Factory
* virtual factories for creating products
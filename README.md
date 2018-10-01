# DuAlgorithm
My collection of algorithms, data structures, and design patterns in C++ and Python.

## Algorithm
### Dynamic Programming
#### Knapsack problem
* f[j] = f[j] || f[j-v[i]]
* f[i][j] = max(f[i-1][j-v[i]] + w[i], f[i-1][j])
* f[i,j] = f[i-1,j-a[i]] or f[i-1,j+a[i]]
##### Knapsack on a tree
* f[i,j] = max(f[i,j], f[l,j-v[i]-v[fb[i]]-v[fa[i]]]+v[i]*p[i]+v[fb[i]]*p[fb[i]]+v[fa[i]]*p[fa[i]])
#### LCS
* f[i] = max{f[j] + 1}
* f[i] = min{{f(i-k)} (not stone[i]) {f(i-k)} + 1} (stone[i]);  
#### Stock problem

### Math
#### Counting Problems
#### Mods Theory
#### Number Theory
#### Primes
#### Permutations
#### Random
#### Probability
##### Shuffle
* Time: O(N), scan and swap a[i] with a[random(i,n-1)].

### Graph Theory
#### Shortest Path
* Dijkstra: O(E + V log V), heap for pending vertices.
* Bellman Ford: O(VE)
* Kruskal: O(E log V)
* Prim: O(E + V log V) Fibonacci heap and adjacency list
#### Network Flow
##### SPFA
### Greedy


### Linear

### String
#### KMP
#### RabinKarp

### Sorts
#### QuickSort
* When N < 16, use insersion sort, since the data is mostly sorted
* When depth > T, use heap sort
* Time: O(N log N)

#### MergeSort
* Time: O(N log N)

#### BubbleSort

#### 

### Search
#### BFS

#### DFS

#### Binary Search


## Data Structure

### Linear

#### Interval
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
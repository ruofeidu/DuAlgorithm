# DuAlgorithm
My collection of algorithms and data structure in C++ and Python.

## Data Structure
### Linear
#### Interval
##### Sweeping line
#### Linked List
* Reverse (between) with a dummy pointer
* Deep copy, one after one

#### Queue
##### Dequeue
* Sliding window
* Moving average

#### Stacks
* Calculator

### Cluster
#### Union Set
* Time: O(alpha), typically alpha < 4

## Algorithm
### Dynamic Programming
#### Bag problem
##### Infinite goods
#### LCS
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

#### Network Flow

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
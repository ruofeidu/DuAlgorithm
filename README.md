# DuAlgorithm
My collection of algorithms and data structure in C++ and Python.

## Data Structure
### Linear
#### Interval

#### Linked List


#### Queue


#### Stacks


### Cluster
#### Union Set
* Time: O(alpha), typically alpha < 4

## Algorithm
### Dynamic Programming

### Math

#### Random
##### Shuffle
* Time: O(N), scan and swap a[i] with a[random(i,n-1)].

### Graph Theory
#### Shortest Path

### Greedy


### Linear


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
#pragma once
#pragma warning(disable : 4996)
#include <algorithm>
#include <bitset>
#include <cmath>
#include <cstdio>
#include <ctime>
#include <fstream>
#include <functional>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <map>
#include <numeric>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>
using namespace std;

// common data structued are defined below

// Hasing for pairs
template <class T>
inline void hash_combine(std::size_t &seed, const T &v) {
  std::hash<T> hasher;
  seed ^= hasher(v) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
};

namespace std {
template <typename S, typename T>
struct hash<pair<S, T>> {
  inline size_t operator()(const pair<S, T> &v) const {
    size_t seed = 0;
    ::hash_combine(seed, v.first);
    ::hash_combine(seed, v.second);
    return seed;
  }
};
}  // namespace std

// Linear

struct ListNode {
  int val;
  ListNode *next;
  ListNode(int x) : val(x), next(nullptr) {}
};

struct RandomListNode {
  int label;
  RandomListNode *next, *random;
  RandomListNode(int x) : label(x), next(nullptr), random(nullptr) {}
};

struct Interval {
  int start;
  int end;
  Interval() : start(0), end(0) {}
  Interval(int s, int e) : start(s), end(e) {}
};

// Graph

struct UndirectedGraphNode {
  int label;
  vector<UndirectedGraphNode *> neighbors;
  UndirectedGraphNode(int x) : label(x){};
};

// Tree

class TreeNode {
 public:
  int val;
  TreeNode *left, *right;
  TreeNode(int _val) : val(_val), left(nullptr), right(nullptr) {}
};
using GraphMap =
    unordered_map<const UndirectedGraphNode *, UndirectedGraphNode *>;

struct TreeLinkNode {
  int val;
  TreeLinkNode *left, *right, *next;
  TreeLinkNode(int x) : val(x), left(NULL), right(NULL), next(NULL) {}
};

// Spatial

struct Point {
  int x;
  int y;
  Point() : x(0), y(0) {}
  Point(int a, int b) : x(a), y(b) {}
};

// Notations

using Vector = vector<int>;
using Vector2 = vector<pair<int, int>>;
using Grid = vector<Vector>;
using BVector = vector<bool>;
using BGrid = vector<BVector>;
using Matrix = Grid;

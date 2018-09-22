#pragma once
#pragma warning(disable:4996)
#include <cstdio>
#include <cmath>
#include <ctime>

#include <iostream>
#include <sstream>
#include <vector>
#include <queue>
#include <stack>
#include <iterator>
#include <string>
#include <set>
#include <unordered_set>
#include <unordered_map>

#include <functional>
#include <algorithm>

using namespace std;

// hasing for pairs
template <class T>
inline void hash_combine(std::size_t & seed, const T & v)
{
	std::hash<T> hasher;
	seed ^= hasher(v) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
};

namespace std
{
	template<typename S, typename T> struct hash<pair<S, T>>
	{
		inline size_t operator()(const pair<S, T> & v) const
		{
			size_t seed = 0;
			::hash_combine(seed, v.first);
			::hash_combine(seed, v.second);
			return seed;
		}
	};
}

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

struct UndirectedGraphNode {
	int label;
	vector<UndirectedGraphNode *> neighbors;
	UndirectedGraphNode(int x) : label(x) {};
};

class TreeNode {
public:
	int val;
	TreeNode *left, *right;
	TreeNode(int _val) : val(_val), left(nullptr), right(nullptr) {}
};

struct Point {
	int x;
	int y;
	Point() : x(0), y(0) {}
	Point(int a, int b) : x(a), y(b) {}
};

using GraphMap = unordered_map<const UndirectedGraphNode*, UndirectedGraphNode*>;

#pragma once
#include "common.h"

class UnionSets {
public:

	// Union Find Set with Compressed Path in O(alpha)
	int getParent(vector<int>& union_set, int i) {
		while (i != union_set[i]) {
			union_set[i] = union_set[union_set[i]];
			i = union_set[i];
		}
		return i;
	}

	// Test if a graph is a valid tree
	// A tree is n-1 edges and no circle
	bool validTree(int n, vector<pair<int, int>>& edges) {
		vector<int> roots(n);
		for (int i = 0; i < n; ++i) roots[i] = i;

		for (auto e : edges) {
			int x = getParent(roots, e.first);
			int y = getParent(roots, e.second);
			if (x == y) return false;
			roots[x] = y;
		}
		return edges.size() == n - 1;
	}

	// test if number of Connected Components in an Undirected Graph
	int countComponents(int n, vector<pair<int, int>>& edges) {
		vector<int> union_set(n);
		for (int i = 0; i < n; ++i) union_set[i] = i;
		int ans = n;

		for (auto& e : edges) {
			int x = getParent(union_set, e.first);
			int y = getParent(union_set, e.second);
			if (x != y) --ans;
			union_set[x] = y;
		}

		return ans;
	}

	vector<int> numIslands2(int m, int n, vector<pair<int, int>>& positions) {
		vector<int> res;
		if (m <= 0 || n <= 0) return res;
		vector<int> roots(m * n, -1);
		int cnt = 0;
		vector<vector<int> > dirs{ { 0, -1 },{ -1, 0 },{ 0, 1 },{ 1, 0 } };
		for (auto a : positions) {
			int id = n * a.first + a.second;
			roots[id] = id;
			++cnt;
			for (auto d : dirs) {
				int x = a.first + d[0], y = a.second + d[1];
				int cur_id = n * x + y;
				if (x < 0 || x >= m || y < 0 || y >= n || roots[cur_id] == -1) continue;
				int new_id = findRoots(roots, cur_id);
				if (id != new_id) {
					roots[id] = new_id;
					id = new_id;
					--cnt;
				}
			}
			res.push_back(cnt);
		}
		return res;
	}

	int findRoots(vector<int> &roots, int id) {
		while (id != roots[id]) {
			roots[id] = roots[roots[id]];
			id = roots[id];
		}
		return id;
	}
};
#pragma once
#include "common.h"

// RMQ: Range Minimum/Maximum Query
// Init: O(n log n)
// Query: O(1)
// LCA = RMQ
// LCA Offline: O(E) + O(1)
// Init: id[] <- -1, g[] adj matrix
// Call:
// DFS the tree, each time we visit a node i,
// put the depth into the end of e[], record the first time i appears in the array, as r[i]
// d[i] is the depth of e[i]
// LCA(T, u, V) = E[RMQ(d, r[u], r[v])], (r[u] < r[v])

// for (int i = 0; i < n; ++i)
//   if (st[i] == -1)
//      dfs(i, n);
class RMQ {
public:

	int N, M;
	vector<int> nums;
	vector<vector<int>> st;
	vector<int> pow2, log2;

	RMQ(vector<int> _nums) {
		nums = _nums;
		N = (int)nums.size();
		M = int(log(double(N)) / log(2)) + 1;
		st = vector<vector<int>>(N, vector<int>(M, 0));
		pow2 = vector<int>(M, 1);
		log2 = vector<int>(M, 0);
		for (int i = 1; i < M; ++i)
			pow2[i] = 2 * pow2[i - 1];
		for (int j = (M >> 1) + 1; j <= M; ++j)
			log2[j] = log2[j >> 1] + 1;
	}

	// POJ 3264. Balanced Lineup
	// http://poj.org/problem?id=3264
	// st[i][j] indicates the peak value from i to i+2^j
	// st[i][j] = max(st[i][j - 1], st[i + (1 << (j - 1))][j - 1]);
	void InitRMQ() {
		for (int i = 0; i < N; ++i)
			st[i][0] = nums[i];

		// [1, 7] = [1, 2] + [4, 2]
		for (int j = 1; j < M; ++j)
			for (int i = 0; i < M; ++i) {
				if (i + pow2[j - 1] - 1 < N)
					st[i][j] = max(st[i][j - 1], st[i + pow2[j - 1]][j - 1]);
				else
					break; // st[i][j] = st[i][j-1];
			}
	}

	// max of { nums[x] ... nums[y] }
	int query(int x, int y)
	{
		int bl = log2[y - x + 1];
		return min(st[bl][x], st[bl][y - (1 << bl) + 1]);
	}
};
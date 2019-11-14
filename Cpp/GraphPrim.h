#pragma once
#include "common.h"

namespace GraphPrim {
	// Prim adds one node at a time for MST
	// Time: O(V^2)
	int Prim(Grid &g) {
		const int n = (int)g.size();
		// current minimal edge
		vector<int> low(n, 0);
		// visited
		vector<bool> vd(n, false);
		int res = 0;

		// starting from node 0
		vd[0] = true;
		for (int i = 1; i < n; ++i)
			low[i] = g[0][i];

		for (int i = 1; i < n; ++i) {
			int cur = INT_MAX;
			int p = -1;
			for (int j = 0; j < n; ++j) {
				if (!vd[j] && low[j] < cur) {
					cur = low[j];
					p = j;
				}
			}
			// not a connected graph
			if (cur == INT_MAX)
				return -1;
			res += cur;
			vd[p] = true;

			for (int j = 0; j < n; ++i)
				if (!vd[j] && low[j] > g[p][j])
					low[j] = g[p][j];
		}
		return res;
	}

	// second MST
	//
}

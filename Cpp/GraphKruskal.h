#pragma once
#include "common.h"

namespace Kruskal {
	// Kruskal solves MST by sorting the edges and merging them with union sets
	// Time: O(E log E)
	struct Edge {
		int w, x, y;
	};
	bool operator < (const Edge& a, const Edge& b) {
		return a.w < b.w;
	}

	int getP(vector<int> &p, int i) {
		while (p[i] != i) {
			p[i] = p[p[i]];
			i = p[i];
		}
		return i;
	}

	int Kruskal(vector<Edge> &edges, int n) {
		sort(edges.begin(), edges.end());
		vector<int> p(n);
		for (int i = 0; i < n; ++i)
			p[i] = i;
		int total = 0, res = 0;
		for (const auto &e : edges) {
			int x = e.x, y = e.y;
			if (getP(p, x) != getP(p, y)) {
				p[getP(p, x)] = getP(p, y);
				res += e.w;
				++total;
				if (total == n - 1)
					break;
			}
		}
		return res;
	}
}

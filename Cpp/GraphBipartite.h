#pragma once
#include "common.h"

namespace GraphBiparite {
	bool isBipartite(vector<vector<int>>& graph) {
		unordered_map<int, int> col;
		int n = graph.size();
		for (int i = 0; i < n; ++i) {
			if (col.count(i)) {
				continue;
			}
			stack<int> s;
			s.push(i);
			col[i] = 0;
			while (!s.empty()) {
				int u = s.top();
				s.pop();
				for (auto v : graph[u]) {
					if (!col.count(v)) {
						s.push(v);
						col[v] = col[u] ^ 1;
					}
					else if (col[v] == col[u])
						return false;
				}
			}
		}
		return true;
	}
}
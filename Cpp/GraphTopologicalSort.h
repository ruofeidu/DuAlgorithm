#pragma once
#include "common.h"

namespace TopologicalSort {
	// 207. Course Schedule [E]
	// Given the total number of courses and a list of prerequisite pairs, is it possible for you to finish all courses?
	// Solution: Topological Sort - Verify DAG (Directed Acyclic Graph)
	// Time: O(N), Space: O(M)
	bool canFinish(int n, vector<pair<int, int>>& prerequisites) {
		// directed graph
		Grid g(n);
		// vd
		Vector vd(n, 0);
		for (const auto &p : prerequisites) {
			g[p.first].emplace_back(p.second);
		}
		for (int i = 0; i < n; ++i) {
			if (!topologicalDFS(i, g, vd))
				return false;
		}
		return true;
	}


	bool topologicalDFS(int i, Grid &g, Vector &vd) {
		if (vd[i] == -1)
			return false;
		if (vd[i] == 1)
			return true;
		vd[i] = -1;
		for (const auto &j : g[i]) {
			if (!topologicalDFS(j, g, vd)) return false;
		}
		vd[i] = 1;
		return true;
	}

	// 210. Course Schedule II [M]
	// Given the total number of courses and a list of prerequisite pairs, return the ordering of courses you should take to finish all courses.
	vector<int> findOrder(int n, vector<pair<int, int>>& prerequisites) {
		// g: i <- j, in degree; 
		// f: i -> j, out degree;
		Grid f(n), g(n);

		// Time and Space: O(m)
		for (const auto &p : prerequisites) {
			g[p.first].emplace_back(p.second);
			f[p.second].emplace_back(p.first);
		}

		// BFS, Time: O(N)
		// q contains nodes with zero degree
		Vector res;
		queue<int> q;
		for (int i = 0; i < n; ++i) {
			if (g[i].empty())
				q.emplace(i);
		}

		while (!q.empty()) {
			auto i = q.front();
			q.pop();
			res.emplace_back(i);
			for (const auto &j : f[i]) {
				auto it = std::find(g[j].begin(), g[j].end(), i);
				if (it != g[j].end()) {
					std::swap(*it, g[j].back());
					g[j].pop_back();
				}
				if (g[j].empty())
					q.emplace(j);
			}
		}
		return res.size() == n ? res : Vector();
	}

	// Refer to 630. Course Schedule III [H], in Greedy.h
}

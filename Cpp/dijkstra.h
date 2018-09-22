#pragma once
#include "common.h"

struct GraphNode {
	unordered_map<GraphNode*, int> adjs;
};

using DisNode = pair<int, GraphNode*>;

struct greater_DisNode {
	bool operator()(DisNode const& lhs, DisNode const& rhs) {
		return lhs.first < rhs.first;
	}
};

// Dijkstra
// Time: O(E + V log V)
// Create a priority queue to store vertices that are being preprocessed.
vector<GraphNode*> dijkstra(int n, GraphNode* s, GraphNode* t) {
	unordered_map<GraphNode*, int> dist;
	unordered_map<GraphNode*, GraphNode*> from;
	priority_queue<DisNode, vector<DisNode>, greater_DisNode> pq;

	pq.push(make_pair(0, s));
	dist[s] = 0;
	from[s] = nullptr;

	while (!pq.empty()) {
		auto p = pq.top().second;
		pq.pop();

		for (const auto kvp : p->adjs) {
			auto q = kvp.first;
			auto w = kvp.second;

			if (dist.find(q) == dist.end() || dist[q] > dist[p] + w) {
				dist[q] = dist[p] + w;
				from[q] = p;
				pq.push(make_pair(dist[q], q));
			}
		}
	}

	vector<GraphNode*> res;
	if (from.find(t) == from.end())
		return res;
	while (t) {
		res.emplace_back(t);
		t = from[t];
	}
	reverse(res.begin(), res.end());
	return res;
}

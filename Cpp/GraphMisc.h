#pragma once
#include "common.h"

class Graphs {
	// Visual Graph Traversal
	// http://chengyichao.info/visual-graph-traversal/

	// 133. Clone Graph
	// Given the head of a graph, return a deep copy (clone) of the graph. Each node in the graph contains a label (int) and a list (List[UndirectedGraphNode]) of its neighbors. There is an edge between the given node and each of the nodes in its neighbors.
public:
	typedef unordered_map<const UndirectedGraphNode*, UndirectedGraphNode*> GraphMap;
	// 133
	UndirectedGraphNode *cloneGraph(UndirectedGraphNode *node) {
		if (node == nullptr) return nullptr;
		GraphMap result;
		cloneGraph(node, result);
		return result[node];
	}

private:
	static UndirectedGraphNode* cloneGraph(const UndirectedGraphNode *node, GraphMap &copied) {
		if (copied.find(node) != copied.end()) return copied[node];
		UndirectedGraphNode *newNode = new UndirectedGraphNode(node->label);
		copied[node] = newNode;
		for (auto neighborNode : node->neighbors) {
			newNode->neighbors.push_back(cloneGraph(neighborNode, copied));
		}
		return newNode;
	}
};

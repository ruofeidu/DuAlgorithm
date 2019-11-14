#pragma once
#include "common.h"

class Graphs {
  // Visual Graph Traversal
  // http://chengyichao.info/visual-graph-traversal/

  // 133. Clone Graph
  // Given the head of a graph, return a deep copy (clone) of the graph. Each
  // node in the graph contains a label (int) and a list
  // (List[UndirectedGraphNode]) of its neighbors. There is an edge between the
  // given node and each of the nodes in its neighbors.
 public:
  typedef unordered_map<const UndirectedGraphNode *, UndirectedGraphNode *>
      GraphMap;
  // 133
  UndirectedGraphNode *cloneGraph(UndirectedGraphNode *node) {
    if (node == nullptr) return nullptr;
    GraphMap result;
    cloneGraph(node, result);
    return result[node];
  }

 private:
  static UndirectedGraphNode *cloneGraph(const UndirectedGraphNode *node,
                                         GraphMap &copied) {
    if (copied.find(node) != copied.end()) return copied[node];
    UndirectedGraphNode *newNode = new UndirectedGraphNode(node->label);
    copied[node] = newNode;
    for (auto neighborNode : node->neighbors) {
      newNode->neighbors.push_back(cloneGraph(neighborNode, copied));
    }
    return newNode;
  }

  // 310. Minimum Height Trees
  // For a undirected graph with tree characteristics, we can choose any node as
  // the root. The result graph is then a rooted tree. Among all possible rooted
  // trees, those with minimum height are called minimum height trees (MHTs).
  // Given such a graph, write a function to find all the MHTs and return a list
  // of their root labels.
  // Time:  O(n)
  // Space: O(m)
  vector<int> findMinHeightTrees(int n, vector<pair<int, int>> &edges) {
    vector<int> ans;
    if (n == 1) return {0};
    if (n == 2) return {0, 1};

    // build adjacent lists: adj
    // degree per vertex: deg
    unordered_map<int, unordered_set<int>> adj(n);
    vector<int> deg(n, 0);
    for (auto e : edges) {
      int u, v;
      tie(u, v) = e;
      adj[u].emplace(v);
      adj[v].emplace(u);
      ++deg[u];
      ++deg[v];
    }

    vector<int> pre_level, cur_level;
    unordered_set<int> unvd;
    for (int i = 0; i < n; ++i) {
      if (adj[i].size() == 1) pre_level.emplace_back(i);
      unvd.emplace(i);
    }

    while (unvd.size() > 2) {
      cur_level.clear();
      for (const auto &u : pre_level) {
        unvd.erase(u);
        for (const auto &v : adj[u]) {
          if (unvd.count(v)) {
            adj[v].erase(u);
            if (adj[v].size() == 1) {
              cur_level.emplace_back(v);
            }
          }
        }
      }
      swap(pre_level, cur_level);
    }

    vector<int> res(unvd.begin(), unvd.end());
    return res;
  }

  // 332. Reconstruct Itinerary [M]
  // Given a list of airline tickets represented by pairs of departure and
  // arrival airports [from, to], reconstruct the itinerary in order. All of the
  // tickets belong to a man who departs from JFK. Thus, the itinerary must
  // begin with JFK.
  using ItineraryGraph = unordered_map<string, multiset<string>>;

  vector<string> findItinerary(vector<pair<string, string>> tickets) {
    vector<string> ans;
    ItineraryGraph graph;
    for (auto &t : tickets) graph[t.first].insert(t.second);
    DFS(graph, "JFK", ans);
    return vector<string>(ans.rbegin(), ans.rend());
  }

  void DFS(ItineraryGraph &g, string s, vector<string> &ans) {
    while (g[s].size()) {
      string t = *g[s].begin();
      g[s].erase(g[s].begin());
      DFS(g, t, ans);
    }
    ans.emplace_back(s);
  }
};

#pragma once
#include "common.h"

namespace DFSTree {
	bool leafSimilar(TreeNode* root1, TreeNode* root2) {
		vector<TreeNode*> s1{ root1 }, s2{ root2 };
		while (!s1.empty() && !s2.empty()) {
			if (dfs(s1) != dfs(s2)) {
				return false;
			}
		}
		return s1.empty() && s2.empty();
	}

	int dfsLeafSimilar(vector<TreeNode*>& s) {
		while (true) {
			const auto node = s.back();
			s.pop_back();
			if (node->right) {
				s.emplace_back(node->right);
			}
			if (node->left) {
				s.emplace_back(node->left);
			}
			if (!node->left && !node->right) {
				return node->val;
			}
		}
	}
}
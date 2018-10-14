#pragma once
#include "common.h"

class LCA {
	// 235. Lowest Common Ancestor of a Binary Search Tree
	// 236. Lowest Common Ancestor of a Binary Tree
	// Given a binary search tree (BST), find the lowest common ancestor (LCA) of two given nodes in the BST.
	TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
		if (root == nullptr || root == p || root == q)
			return root;
		auto l = lowestCommonAncestor(root->left, p, q);
		auto r = lowestCommonAncestor(root->right, p, q);
		return l ? (r ? root : l) : r;
	}

	// Deepest Common Ancestor
	// Given a binary tree, write a function that takes in the root of the tree, two nodes, and returns the deepest common ancestor of two nodes.
	// Space: O(N), Time: O(N)
	using TreeDict = unordered_map<TreeNode*, pair<bool, bool>>;

	TreeNode* getDCA(TreeNode *root, TreeNode *a, TreeNode *b) {
		if (root == nullptr || root == a || root == b)
			return root;
		TreeDict dict;
		// build a hash map if a node contains a and b
		DFS(dict, root, a, b);


		// after having a dict, we can tell if both nodes in left or right or (one left, one right)
		if (root->left) {
			auto l = root->left;
			if (dict[l].first && dict[l].second)
				return getDCA(l, a, b);

			if (root->right) {
				auto r = root->right;
				if ((dict[l].first && dict[r].second) || (dict[l].second && dict[l].first)) {
					return root;
				}
			}
		}
		if (root->right) {
			auto r = root->right;
			if (dict[r].first && dict[r].second)
				return getDCA(r, a, b);
		}
		return nullptr;
	}

	pair<bool, bool> DFS(TreeDict &dict, TreeNode *root, TreeNode *a, TreeNode *b) {
		if (!root)
			return{ false, false };

		pair<bool, bool> res = { (root == a), (root == b) };

		auto r = DFS(dict, root->left, a, b);
		res.first |= r.first;
		res.second |= r.second;

		r = DFS(dict, root->right, a, b);
		res.first |= r.second;
		res.second |= r.second;

		dict[root] = res;
		return res;
	}
}
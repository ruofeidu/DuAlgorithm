#pragma once
#include "common.h"

namespace LCA {
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
}
#pragma once
#include "common.h"

class DPTree {
	// 124. Binary Tree Maximum Path Sum
	// Given a non-empty binary tree, find the maximum path sum.
	int maxPathSum(TreeNode* root) {
		int res = root->val;
		maxPathSumDP(root, res);
		return res;
	}

	int maxPathSumDP(TreeNode* root, int &res) {
		if (root == NULL) return 0;
		int l = max(0, maxPathSumDP(root->left, res));
		int r = max(0, maxPathSumDP(root->right, res));
		res = max(res, l + r + root->val);
		return root->val + max(l, r);
	}

	// 112. Path Sum
	// Given a binary tree and a sum, determine if the tree has a root-to-leaf path such that adding up all the values along the path equals the given sum.
	bool hasPathSum(TreeNode* root, int sum) {
		typedef pair<TreeNode*, int> NodeSum;
		stack<NodeSum> s;
		if (root == nullptr) return false;
		s.push(NodeSum(root, root->val));
		while (!s.empty()) {
			NodeSum t = s.top();
			s.pop();
			TreeNode* node = t.first;
			int cur_sum = t.second;
			if (!node->left && !node->right && cur_sum == sum) return true;
			if (node->left) s.push(NodeSum(node->left, cur_sum + node->left->val));
			if (node->right) s.push(NodeSum(node->right, cur_sum + node->right->val));
		}
		return false;
	}

	// 113. Path Sum II
	// Given a binary tree and a sum, find all root-to-leaf paths where each path's sum equals the given sum.
	// Non-recursive solution!
	vector<vector<int>> pathSum(TreeNode* root, int sum) {
		using NodeSum = pair<TreeNode*, int>;

		vector<vector<int>> res;
		if (root == nullptr) return res;
		stack<NodeSum> s;
		stack<bool> rightmost;

		s.push(NodeSum(root, root->val));
		rightmost.push(false);
		vector<int> path;
		stack<bool> flags;

		while (!s.empty()) {
			NodeSum t = s.top(); 			s.pop();
			bool r = rightmost.top();		rightmost.pop();

			TreeNode* node = t.first;
			int cur_sum = t.second;

			path.push_back(node->val);
			flags.push(r);


			if (!node->left && !node->right) {
				if (cur_sum == sum) {
					vector<int> new_path(path);
					res.push_back(new_path);
				}
				path.pop_back();
				flags.pop();
				if (r && !flags.empty()) {
					r = flags.top();
					flags.pop();
					path.pop_back();
					while (r && !flags.empty()) {
						r = flags.top();
						flags.pop();
						path.pop_back();
					}
				}
				continue;
			}
			if (node->right) {
				s.push(NodeSum(node->right, cur_sum + node->right->val));
				rightmost.push(true);
			}
			if (node->left) {
				s.push(NodeSum(node->left, cur_sum + node->left->val));
				rightmost.push(node->right == nullptr);
			}
		}
		return res;
	}

	// 337. House Robber III [M]
	// It will automatically contact the police if two directly-linked houses were broken into on the same night. Determine the maximum amount of money the thief can rob tonight without alerting the police.
	// Tree DP
	int rob(TreeNode* root) {
		auto res = robDP(root);
		return max(res.first, res.second);
	}

	pair<int, int> robDP(TreeNode* root) {
		if (!root)
			return{ 0, 0 };

		auto l = robDP(root->left);
		auto r = robDP(root->right);
		return{ root->val + l.second + r.second,
			max(l.first, l.second) + max(r.first, r.second) };
	}
};

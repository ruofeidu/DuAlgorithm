#pragma once
#include "common.h"

namespace BinaryTrees {
	// 94. Binary Tree Inorder Traversal
	vector<int> inorderTraversal(TreeNode* root) {
		stack<TreeNode*> s;
		typedef unsigned char byte;
		stack<byte> d;

		s.push(root);
		d.push(0);

		vector<int> ans;
		if (root == NULL) return ans;

		while (!s.empty()) {
			TreeNode* node = s.top();
			byte depth = d.top();

			if (depth == 0) {
				// first step, deal with left
				d.top() = 1;
				if (node->left != NULL) {
					s.push(node->left);
					d.push(0);
				}
			}
			else
				if (depth == 1) {
					// left done, deal itself
					ans.push_back(node->val);
					d.top() = 2;
				}
				else {
					d.pop();
					s.pop();
					if (node->right != NULL) {
						s.push(node->right);
						d.push(0);
					}
				}
		}
		return ans;
	}

	vector<int> preorderTraversal(TreeNode* root) {
		vector<int> ans;
		if (root == nullptr)
			return ans;
		stack<TreeNode*> s;
		s.emplace(root);
		while (!s.empty()) {
			TreeNode* node = s.top();
			s.pop();
			ans.emplace_back(node->val);
			if (node->right) s.emplace(node->right);
			if (node->left) s.emplace(node->left);
		}
		return ans;
	}

	vector<int> postorderTraversal(TreeNode* root) {
		vector<int> ans;
		if (root == nullptr)
			return ans;

		using DFSNode = pair<TreeNode*, bool>;
		stack<DFSNode> s;
		s.emplace(DFSNode(root, false));

		while (!s.empty()) {
			DFSNode t = s.top();
			s.pop();
			TreeNode* node = t.first;
			bool output = t.second;
			if (output) {
				ans.emplace_back(node->val);
			}
			else {
				s.push(DFSNode(node, true));
				if (node->right) s.emplace(DFSNode(node->right, false));
				if (node->left) s.emplace(DFSNode(node->left, false));
			}
		}
		return ans;
	}

	bool isSymmetric(TreeNode* root) {
		if (root == nullptr) return true;
		stack<TreeNode*> s;
		s.push(root->left);
		s.push(root->right);


		while (!s.empty()) {
			TreeNode* p = s.top(); s.pop();
			TreeNode* q = s.top(); s.pop();
			if (p == nullptr && q != nullptr) return false;
			if (q == nullptr && p != nullptr) return false;
			if (p == nullptr && q == nullptr) continue;
			if (p->val != q->val) return false;
			s.push(p->left);
			s.push(q->right);


			s.push(p->right);
			s.push(q->left);
		}
		return true;
	}

	vector<vector<int>> levelOrder(TreeNode* root) {
		vector<vector<int>> res;
		if (root == nullptr) return res;
		using Level = pair<TreeNode*, int>;


		queue<Level> q;
		q.push(Level(root, 0));
		int curLevel = -1;

		while (!q.empty()) {
			Level node = q.front();
			q.pop();
			if (node.second > curLevel) {
				++curLevel;
				vector<int> values(1, node.first->val);
				res.emplace_back(values);
			}
			else {
				res[curLevel].emplace_back(node.first->val);
			}
			if (node.first->left != nullptr) q.push(Level(node.first->left, curLevel + 1));
			if (node.first->right != nullptr) q.push(Level(node.first->right, curLevel + 1));
		}
		return res;
	}

	vector<vector<int>> zigzagLevelOrder(TreeNode* root) {
		vector<vector<int>> res;
		if (root == nullptr) return res;
		using Level = pair<TreeNode*, int>;

		queue<Level> q;
		q.push(Level(root, 0));
		int curLevel = -1;

		while (!q.empty()) {
			Level node = q.front();
			q.pop();
			if (node.second > curLevel) {
				++curLevel;
				vector<int> values(1, node.first->val);
				res.emplace_back(values);
			}
			else {
				if (curLevel % 2 == 0) {
					res[curLevel].emplace_back(node.first->val);
				}
				else {
					res[curLevel].insert(res[curLevel].begin(), node.first->val);
				}
			}

			if (node.first->left != nullptr) q.push(Level(node.first->left, curLevel + 1));
			if (node.first->right != nullptr) q.push(Level(node.first->right, curLevel + 1));
		}
		return res;
	}

	int maxDepth(TreeNode* root) {
		typedef pair<TreeNode*, int> Nodep;
		stack<Nodep> s;
		if (root == nullptr) return 0;
		s.push(Nodep(root, 1));
		int ans = 1;
		while (!s.empty()) {
			Nodep t = s.top();
			s.pop();
			TreeNode* node = t.first;
			int depth = t.second;
			if (depth > ans) ans = depth;
			if (node->left != nullptr) s.push(Nodep(node->left, depth + 1));
			if (node->right != nullptr) s.push(Nodep(node->right, depth + 1));
		}
		return ans;
	}


	int minDepth(TreeNode* root) {
		using Level = pair<TreeNode*, int>;
		stack<Level> s;
		if (root == nullptr) return 0;
		s.push(Level(root, 1));
		int ans = INT_MAX;
		while (!s.empty()) {
			Level t = s.top();
			s.pop();
			TreeNode* node = t.first;
			int depth = t.second;
			if (node->left == nullptr && node->right == nullptr) {
				ans = min(ans, depth);
				continue;
			}
			if (node->left != nullptr) s.push(Level(node->left, depth + 1));
			if (node->right != nullptr) s.push(Level(node->right, depth + 1));
		}
		return ans;
	}

	// 100. Same Tree [E]
	// Given two binary trees, write a function to check if they are the same or not.
	bool isSameTree(TreeNode* p, TreeNode* q) {
		if (p == nullptr && q == nullptr) return true;
		if ((p == nullptr && q != nullptr) || (q == nullptr && p != nullptr)) return false;
		if (p->val != q->val) return false;
		return isSameTree(p->left, q->left) && isSameTree(p->right, q->right);
	}
}
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

	// 144. Binary Tree Preorder Traversal
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

	// 145. Binary Tree Postorder Traversal
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

	// 101. Symmetric Tree E]
	// Given a binary tree, check whether it is a mirror of itself (ie, symmetric around its center).
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

	// 102. Binary Tree Level Order Traversal [M]
	// Given a binary tree, return the level order traversal of its nodes' values. (ie, from left to right, level by level).
	vector<vector<int>> levelOrder(TreeNode* root) {
		vector<vector<int>> res;
		if (root == nullptr) return res;
		using Level = pair<TreeNode*, int>;


		queue<Level> q;
		q.emplace(Level(root, 0));
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

	// 107. Binary Tree Level Order Traversal II
	// Given a binary tree, return the bottom-up level order traversal of its nodes' values. (ie, from left to right, level by level from leaf to root).
	vector<vector<int>> levelOrderBottom(TreeNode* root) {
		vector<vector<int>> res;
		if (root == nullptr) return res;
		typedef pair<TreeNode*, int> Level;


		queue<Level> q;
		q.push(Level(root, 0));
		int curLevel = -1;

		while (!q.empty()) {
			Level node = q.front();
			q.pop();
			if (node.second > curLevel) {
				++curLevel;
				vector<int> values(1, node.first->val);
				res.push_back(values);
			}
			else {
				res[curLevel].push_back(node.first->val);
			}
			if (node.first->left != nullptr) q.push(Level(node.first->left, curLevel + 1));
			if (node.first->right != nullptr) q.push(Level(node.first->right, curLevel + 1));
		}

		for (int i = 0; i < res.size() >> 1; ++i) {
			swap(res[i], res[res.size() - i - 1]);
		}
		return res;
	}

	// 103. Binary Tree Zigzag Level Order Traversal
	// Given a binary tree, return the zigzag level order traversal of its nodes' values. (ie, from left to right, then right to left for the next level and alternate between).
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

	// 104. Maximum Depth of Binary Tree
	// Given a binary tree, find its maximum depth.
	// The maximum depth is the number of nodes along the longest path from the root node down to the farthest leaf node.
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

	// 111. Minimum Depth of Binary Tree
	// Given a binary tree, find its minimum depth.
	// The minimum depth is the number of nodes along the shortest path from the root node down to the nearest leaf node.
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

	// 105. Construct Binary Tree from Preorder and Inorder Traversal
	// Given preorder and inorder traversal of a tree, construct the binary tree.
	// MLR LMR
	namespace preorderInorder {
		TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
			return buildTree(preorder, 0, preorder.size() - 1, inorder, 0, inorder.size() - 1);
		}

		TreeNode* buildTree(vector<int>& preorder, int pl, int pr, vector<int>& inorder, int il, int ir) {
			printf("%d %d %d %d\n", pl, pr, il, ir);
			if (pr - pl != ir - il) return nullptr;
			if (pr - pl < 0 || ir - il < 0) return nullptr;
			int val = preorder[pl];
			TreeNode* root = new TreeNode(val);
			if (pl == pr) return root;
			int j = -1;
			for (int i = il; i <= ir; ++i) if (inorder[i] == val) {
				j = i;
				break;
			}
			// check if finds or not, assume we always find it
			root->left = buildTree(preorder, pl + 1, pl + 1 + (j - 1 - il), inorder, il, j - 1);
			root->right = buildTree(preorder, pr - (ir - j - 1), pr, inorder, j + 1, ir);
			return root;
		}
	}

	// 106. Construct Binary Tree from Inorder and Postorder Traversal
	// Given inorder and postorder traversal of a tree, construct the binary tree.
	namespace InorderPostorder {
		TreeNode* buildTree(vector<int>& inorder, vector<int>& postorder) {
			return buildTree(inorder, 0, inorder.size() - 1, postorder, 0, postorder.size() - 1);
		}

		TreeNode* buildTree(vector<int>& inorder, int il, int ir, vector<int>& postorder, int pl, int pr) {
			if (ir - il != pr - pl || pl > pr || il > ir) return nullptr;
			int val = postorder[pr];
			TreeNode* root = new TreeNode(val);

			if (pl == pr) return root;
			int j = -1;
			for (int i = il; i <= ir; ++i) if (inorder[i] == val) {
				j = i;
				break;
			}
			// check if finds or not
			root->left = buildTree(inorder, il, j - 1, postorder, pl, pl + j - 1 - il);
			root->right = buildTree(inorder, j + 1, ir, postorder, pr - 1 - (ir - j - 1), pr - 1);
			return root;
		}
	}

	// 114. Flatten Binary Tree to Linked List
	// Given a binary tree, flatten it to a linked list in-place.
	// O(n) Time, O(log n) Space
	void flatten(TreeNode* root) {
		if (root == nullptr) return;
		stack<TreeNode*> s;
		s.push(root);

		while (!s.empty()) {
			auto p = s.top();
			s.pop();

			if (p->right) s.push(p->right);
			if (p->left) s.push(p->left);

			p->left = nullptr;
			if (!s.empty()) p->right = s.top();
		}
	}

	// 100. Same Tree [E]
	// Given two binary trees, write a function to check if they are the same or not.
	bool isSameTree(TreeNode* p, TreeNode* q) {
		if (p == nullptr && q == nullptr) return true;
		if ((p == nullptr && q != nullptr) || (q == nullptr && p != nullptr)) return false;
		if (p->val != q->val) return false;
		return isSameTree(p->left, q->left) && isSameTree(p->right, q->right);
	}

	// 116. Populating Next Right Pointers in Each Node
	// Populate each next pointer to point to its next right node. If there is no next right node, the next pointer should be set to NULL.
	// Initially, all next pointers are set to NULL.
	// You may only use constant extra space.
	// Recursive approach is fine, implicit stack space does not count as extra space for this problem.
	// You may assume that it is a perfect binary tree (ie, all leaves are at the same level, and every parent has two children).
	void connect(TreeLinkNode *root) {
		if (root == nullptr) return;
		TreeLinkNode level(0);
		for (auto node = root, prev = &level; node; node = node->next) {
			if (node->left) {
				prev->next = node->left;
				prev = prev->next;
			}
			if (node->right) {
				prev->next = node->right;
				prev = prev->next;
			}
		}
		connect(level.next);
	}

	// 117. Populating Next Right Pointers in Each Node II
	// Populate each next pointer to point to its next right node. If there is no next right node, the next pointer should be set to NULL.
	// You may only use constant extra space.
	void connect2(TreeLinkNode *root) {
		if (root == nullptr) return;
		TreeLinkNode level(0);
		for (auto node = root, prev = &level; node; node = node->next) {
			if (node->left) {
				prev->next = node->left;
				prev = prev->next;
			}
			if (node->right) {
				prev->next = node->right;
				prev = prev->next;
			}
		}
		connect(level.next);
	}

	// 226. Invert Binary Tree [E]
	TreeNode* invertTree(TreeNode* root) {
		if (!root)
			return nullptr;
		auto t = invertTree(root->left);
		root->left = invertTree(root->right);
		root->right = t;
		return root;
	}

	// 257. Binary Tree Paths [E]
	vector<string> binaryTreePaths(TreeNode* root) {
		vector<string> res;
		if (root) binaryTreePathsDFS(root, "", res);
		return res;
	}
	void binaryTreePathsDFS(TreeNode *root, string out, vector<string> &res) {
		out += to_string(root->val);
		if (!root->left && !root->right) res.push_back(out);
		else {
			if (root->left) binaryTreePathsDFS(root->left, out + "->", res);
			if (root->right) binaryTreePathsDFS(root->right, out + "->", res);
		}
	}
}


// 297. Serialize and Deserialize Binary Tree
class Codec {
public:
	// Encodes a tree to a single string.
	string serialize(TreeNode* root) {
		ostringstream out;
		serialize(root, out);
		return out.str();
	}

	void serialize(TreeNode *root, ostringstream &out) {
		if (root) {
			out << root->val << ' ';
			serialize(root->left, out);
			serialize(root->right, out);
		}
		else {
			out << "# ";
		}
	}

	TreeNode* deserialize(istringstream &in) {
		string val;
		in >> val;
		if (val == "#") return nullptr;
		TreeNode *root = new TreeNode(stoi(val));
		root->left = deserialize(in);
		root->right = deserialize(in);
		return root;
	}

	// Decodes your encoded data to tree.
	TreeNode* deserialize(string data) {
		istringstream in(data);
		return deserialize(in);
	}
};
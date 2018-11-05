#pragma once
#include "common.h"

class BinarySearchTrees {
	// 98. Validate Binary Search Tree [E]
public:
	bool isValidBST(TreeNode* root) {
		return isValidBST(root, INT_MIN, INT_MAX);
	}

private:
	bool isValidBST(TreeNode* root, int lowerbound, int upperbound) {
		if (root == nullptr)
			return true;
		if (root->val < lowerbound || root->val > upperbound)
			return false;
		if (root->left != nullptr) {
			if (root->left->val >= root->val)
				return false;
			if (!isValidBST(root->left, lowerbound, root->val - 1))
				return false;
		}
		if (root->right != nullptr) {
			if (root->right->val <= root->val)
				return false;
			if (!isValidBST(root->right, root->val + 1, upperbound))
				return false;
		}
		return true;
	}

public:
	// 109. Convert Sorted List to Binary Search Tree
	// Given a singly linked list where elements are sorted in ascending order, convert it to a height balanced BST.
	// For this problem, a height - balanced binary tree is defined as a binary tree in which the depth of the two subtrees of every node never differ by more than 1.
	TreeNode* sortedListToBST(ListNode* head) {
		int len = 0;
		ListNode *node = head;
		while (node != nullptr) {
			++len;
			node = node->next;
		}
		return sortedListToBST(head, 0, len - 1);
	}

public:
	// Time: O(n)
	// Space O(log n)
	TreeNode* sortedListToBST(ListNode* &head, int start, int end) {
		if (start > end)
			return nullptr;
		int mid = (start + end) / 2;
		auto leftChild = sortedListToBST(head, start, mid - 1);
		auto parent = new TreeNode(head->val);
		parent->left = leftChild;
		head = head->next;
		parent->right = sortedListToBST(head, mid + 1, end);
		return parent;
	}

public:
	// 108. Convert Sorted Array to Binary Search Tree
	// Given an array where elements are sorted in ascending order, convert it to a height balanced BST.
	// For this problem, a height-balanced binary tree is defined as a binary tree in which the depth of the two subtrees of every node never differ by more than 1.
	template<typename T>
	TreeNode* sortedArrayToBST(T first, T last) {
		const auto length = distance(first, last);
		if (length <= 0)
			return nullptr;
		auto mid = first + length / 2;
		auto node = new TreeNode(*mid);
		node->left = sortedArrayToBST(first, mid);
		node->right = sortedArrayToBST(mid + 1, last);
		return node;
	}

public:
	int balanceHeight(TreeNode* root) {
		if (root == nullptr)
			return 0;
		int l = balanceHeight(root->left);
		int r = balanceHeight(root->right);
		if (l < 0 || r < 0 || abs(l - r) > 1) return -1;
		return max(l, r) + 1;
	}

	// 110. Balanced Binary Tree
	// Given a binary tree, determine if it is height-balanced.
	// For this problem, a height - balanced binary tree is defined as:
	// a binary tree in which the depth of the two subtrees of every node never differ by more than 1.

	bool isBalanced(TreeNode* root) {
		return balanceHeight(root) >= 0;
	}

	// 450. Delete Node in a BST
	/*
	root = [5,3,6,2,4,null,7]
	key = 3

		5
	   / \
	  3   6
	 / \   \
	2   4   7

	Given key to delete is 3. So we find the node with value 3 and delete it.

	One valid answer is [5,4,6,2,null,null,7], shown in the following BST.

		5
	   / \
	  4   6
	 /     \
	2       7

	Another valid answer is [5,2,6,null,4,null,7].

		5
	   / \
	  2   6
	   \   \
		4   7
	*/
	TreeNode* deleteNode(TreeNode* root, int key) {
		if (!root)
			return nullptr;

		if (root->val > key) {
			root->left = deleteNode(root->left, key);
		}
		else if (root->val < key) {
			root->right = deleteNode(root->right, key);
		}
		else {
			if (!root->left) {
				auto right = root->right;
				delete root;
				return right;
			}
			else if (!root->right) {
				auto left = root->left;
				delete root;
				return left;
			}
			else {
				auto successor = root->right;
				while (successor->left) {
					successor = successor->left;
				}
				root->val = successor->val;
				root->right = deleteNode(root->right, successor->val);
			}
		}
		return root;
	}

	// 783. Minimum Distance Between BST Nodes
	class BSTMinDist {
	public:
		int minDiffInBST(TreeNode* root) {
			int prev = numeric_limits<int>::min();
			int result = numeric_limits<int>::max();
			dfs(root, &prev, &result);
			return result;
		}

	private:
		void dfs(TreeNode* node, int *prev, int *result) {
			if (!node) {
				return;
			}
			dfs(node->left, prev, result);
			if (*prev != numeric_limits<int>::min()) {
				*result = min(*result, node->val - *prev);
			}
			*prev = node->val;
			dfs(node->right, prev, result);
		}
	};

	// 99. Recover Binary Search Tree [H]
	// Two elements of a binary search tree (BST) are swapped by mistake.
	// Recover the tree without changing its structure.
	// A solution using O(n) space is pretty straight forward.
	// Could you devise a constant space solution ?
	void recoverTree(TreeNode* root) {
		// Morris in-order
		pair<TreeNode*, TreeNode*> broken;
		TreeNode* prev = nullptr;
		TreeNode* cur = root;


		while (cur != nullptr) {
			if (cur->left == nullptr) {
				detect(broken, prev, cur);
				prev = cur;
				cur = cur->right;
			}
			else {
				auto node = cur->left;
				while (node->right != nullptr && node->right != cur) node = node->right;
				if (node->right == nullptr) {
					node->right = cur;
					cur = cur->left;
				}
				else {
					detect(broken, prev, cur);
					node->right = nullptr;
					prev = cur;
					cur = cur->right;
				}
			}
		}
		swap(broken.first->val, broken.second->val);
	}

	void detect(pair<TreeNode*, TreeNode*> &broken, TreeNode* prev, TreeNode* current) {
		if (prev != nullptr && prev->val > current->val) {
			if (broken.first == nullptr) {
				broken.first = prev;
			}
			broken.second = current;
		}
	}

	// 230. Kth Smallest Element in a BST [M]
	// Given a binary search tree, write a function kthSmallest to find the kth smallest element in it.
	int kthSmallest(TreeNode* root, int k) {
		return kthSmallestDFS(root, k);
	}
	int kthSmallestDFS(TreeNode* root, int &k) {
		if (!root) return -1;
		int val = kthSmallestDFS(root->left, k);
		if (!k) return val;
		if (!--k) return root->val;
		return kthSmallestDFS(root->right, k);
	}


	int kthSmallestNonRecursive(TreeNode* root, int k) {
		int cnt = 0;
		stack<TreeNode*> s;
		TreeNode *p = root;
		while (p || !s.empty()) {
			while (p) {
				s.push(p);
				p = p->left;
			}
			p = s.top(); s.pop();
			++cnt;
			if (cnt == k)
				return p->val;
			p = p->right;
		}
		return 0;
	}

	// 285. Inorder Successor in BST
	TreeNode* inorderSuccessor(TreeNode* root, TreeNode* p) {
		if (!root)
			return NULL;
		if (root->val <= p->val) {
			return inorderSuccessor(root->right, p);
		}
		else {
			TreeNode *left = inorderSuccessor(root->left, p);
			return left ? left : root;
		}
	}
};

// 173. Binary Search Tree Iterator
// Implement an iterator over a binary search tree (BST). Your iterator will be initialized with the root node of a BST.
class BSTIterator {
public:
	BSTIterator(TreeNode *root) {
		while (root) {
			s.push(root);
			root = root->left;
		}
	}

	/** @return whether we have a next smallest number */
	bool hasNext() {
		return !s.empty();
	}

	/** @return the next smallest number */
	int next() {
		TreeNode *n = s.top();
		s.pop();
		int res = n->val;
		if (n->right) {
			n = n->right;
			while (n) {
				s.push(n);
				n = n->left;
			}
		}
		return res;
	}

private:
	stack<TreeNode*> s;
};

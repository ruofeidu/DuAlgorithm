#pragma once
#include "common.h"

class BinarySearchTrees {
	template<typename T>
	TreeNode* sortedArrayToBST(T first, T last) {
		const auto length = distance(first, last);
		if (length <= 0) return nullptr;
		auto mid = first + length / 2;
		TreeNode* node = new TreeNode(*mid);
		node->left = sortedArrayToBST(first, mid);
		node->right = sortedArrayToBST(mid + 1, last);
		return node;
	}

	TreeNode* sortedListToBST(ListNode* head) {
		int len = 0;
		ListNode *node = head;
		while (node != nullptr) {
			++len;
			node = node->next;
		}
		return sortedListToBST(head, 0, len - 1);
	}

	// Time: O(n); Space O(log n)
	TreeNode* sortedListToBST(ListNode* &head, int start, int end) {
		if (start > end) return nullptr;
		int mid = start + (end - start) / 2;
		TreeNode *leftChild = sortedListToBST(head, start, mid - 1);
		TreeNode *parent = new TreeNode(head->val);
		parent->left = leftChild;
		head = head->next;
		parent->right = sortedListToBST(head, mid + 1, end);
		return parent;
	}

	int balanceHeight(TreeNode* root) {
		if (root == nullptr) return 0;
		int l = balanceHeight(root->left);
		int r = balanceHeight(root->right);
		if (l < 0 || r < 0 || abs(l - r) > 1) return -1;
		return max(l, r) + 1;
	}

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
		if (!root) {
			return nullptr;
		}
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
};

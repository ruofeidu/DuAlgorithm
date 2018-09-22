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
};

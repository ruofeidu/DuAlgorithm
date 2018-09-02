#pragma once
#include "common.h"

// http://blog.ruofeidu.com/quicksort-in-c/
namespace sorts {
	// Quick Sort
	// sort in STL is quick sort + bubble sort + heap sort (when iteration is too deep)
	void qsort(int *a, int n, int l, int r) {
		int i = l, j = r, mid = a[(l + r) >> 1];
		while (i <= j) {
			while (a[i] < mid) ++i;
			while (a[j] > mid) --j;
			if (i <= j) {
				swap(a[i], a[j]);
				++i;
				--j;
			}
		}
		if (l < j) qsort(a, n, l, j);
		if (i < r) qsort(a, n, i, r);
	}

	// kth element
	void Kth(int *a, int l, int r, int k)
	{
		int i = l, j = r, mid = a[(i + j) >> 1];
		while (i <= j) {
			while (a[i] < mid) ++i;
			while (a[j] > mid) --j;
			if (i <= j) {
				swap(a[i], a[j]);
				++i; 
				--j;
			}
		}
		if (k >= i && k <= r) Kth(a, i, r, k);
		if (k >= l && k <= j) Kth(a, l, j, k);
	}

	ListNode* mergeTwoLists(ListNode* left, ListNode* right) {
		ListNode dummy(-1);
		for (ListNode* p = &dummy; left || right; p = p->next) {
			int l = left ? left->val : INT_MAX;
			int r = right ? right->val : INT_MAX;
			if (l <= r) {
				p->next = left;
				left = left->next;
			}
			else {
				p->next = right;
				right = right->next;
			}
		}
		return dummy.next;
	}

	// merge sort of linked list
	ListNode* sortList(ListNode* head) {
		if (!head || !head->next) return head;

		// find mid O(n)
		ListNode *fast = head, *slow = head;
		while (fast->next && fast->next->next) {
			fast = fast->next->next;
			slow = slow->next;
		}

		// break into two
		fast = slow;
		slow = slow->next;
		fast->next = NULL;

		ListNode *left = sortList(head);
		ListNode *right = sortList(slow);

		return mergeTwoLists(left, right);
	}
	// merge sort of vector
	void ms(vector<int> &nums, int l, int r) {
		if (l == r) return;
		int p = (l + r) >> 1;
		ms(nums, l, p);
		ms(nums, p + 1, r);
		int i = l, j = p + 1;
		int n = r - l + 1;

		vector<int> tmp(n);
		for (int k = 0; k < n; ++k) {
			if (j > r || (i <= p && nums[i] < nums[j])) {
				tmp[k] = nums[i];
				++i;
			}
			else {
				tmp[k] = nums[j];
				++j;
			}
		}

		for (int k = 0, i = l; k < n; ++k, ++i) {
			nums[i] = tmp[k];
		}
	}

	// bubble sort
	void bubble_sort(vector<int> &a, int l, int r) {
		bool sorted = false; 
		const auto n = a.size(); 
		for (size_t i = 0; i < n; ++i) {
			if (sorted)
				break; 
			sorted = true; 
			for (size_t j = 0; j < n - 1 - i; ++j) {
				if (a[j] > a[j + 1]) {
					swap(a[j], a[1]);
					sorted = false; 
				}
			}
		}
	}

	// sort four element
	template <class T>
	vector<T> sort(T i, T j, T k, T l) {
		if (i < j) {
			if (j < k) {
				if (k < l) return {i, j, k, l};
				if (j < l) return {i, j, l, k};
				if (i < l) return {i, l, j, k};
				return { l, i, j, k };
			}
			else if (i < k) {
				if (j < l) return {i, k, j, l};
				if (k < l) return {i, k, l, j};
				if (i < l) return {i, l, k, j};
				return{ l, i, k, j };		 
			}								 
			else {							 
				if (j < l) return {k, i, j, l};
				if (i < l) return {k, i, l, j};
				if (k < l) return {k, l, i, j};
				return{ l, k, i, j };
			}								 
		}									 
		else {								 
			if (i < k) {					 
				if (k < l) return {j, i, k, l};
				if (i < l) return {j, i, l, k};
				if (j < l) return {j, l, i, k};
				return { l, j, i, k };
			}								 
			else if (j < k) {				 
				if (i < l) return {j, k, i, l};
				if (k < l) return {j, k, l, i};
				if (j < l) return {j, l, k, i};
				return { l, j, k, i };
			}								 
			else {							 
				if (i < l) return {k, j, i, l};
				if (j < l) return {k, j, l, i};
				if (k < l) return {k, l, j, i};
				return { l, k, j, i };
			}
		}
	}
}
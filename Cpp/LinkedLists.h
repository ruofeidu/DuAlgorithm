#pragma once
#include "common.h"

namespace TestLinkedList {
	// reverse a linked list
	// 0  1->2->3
	//    0->t->1
	//       0->t->2->1
	ListNode* reverseList(ListNode* head) {
		auto dummy = ListNode{0};
		while (head) {
			auto t = head->next;
			head->next = dummy.next;
			dummy.next = head;
			head = t;
		}
		return dummy.next;
	}

	// reverse a linked list between
	ListNode* reverseBetween(ListNode* head, int m, int n) {
		auto dummy = ListNode{ 0 };
		dummy.next = head;
		auto *p = &dummy;
		for (int i = 0; i < m - 1; ++i) {
			p = p->next;
		}

		// head
		//       head2    
		//   0, 1, 2, 3, 4, 5
		//   |        p  cur
		// dummy

		auto *head2 = p;
		p = p->next;
		auto *cur = p->next;

		for (int i = m; i < n; ++i) {
			// remove cur from the list
			p->next = cur->next;
			// add cur to the new head
			cur->next = head2->next;
			head2->next = cur;
			cur = p->next;
		}
		return dummy.next;
	}

	// 25. Reverse Nodes in k-Group [H]
	// Given a linked list, reverse the nodes of a linked list k at a time and return its modified list.
	/*
	Given this linked list: 1->2->3->4->5
	For k = 2, you should return: 2->1->4->3->5
	For k = 3, you should return: 3->2->1->4->5
	*/
	ListNode* reverseKGroup(ListNode* head, int k) {
		if (head == nullptr || head->next == nullptr || k <= 1) return head;
		ListNode *next_group = head;
		for (int i = 0; i < k; ++i) {
			if (next_group)
				next_group = next_group->next;
			else
				return head;
		}
		// next_group is the head of next group
		// new_next_group is the new head of next group after reversion
		ListNode *new_next_group = reverseKGroup(next_group, k);
		ListNode *prev = NULL, *cur = head;
		while (cur != next_group) {
			ListNode *next = cur->next;
			cur->next = prev ? prev : new_next_group;
			prev = cur;
			cur = next;
		}
		return prev; // prev will be the new head of this group
	}

	// 19. Remove Nth Node From End of List
	ListNode* removeNthFromEnd(ListNode* head, int n) {
		ListNode* node = head;
		if (node == NULL) return head;

		int total = 1;
		while (node->next != NULL) {
			node = node->next;
			++total;
		}

		int cur = 0;
		if (total < n) return head;
		if (cur == total - n) return head->next;
		node = head;
		while (node->next != NULL) {
			++cur;
			if (cur == total - n) {
				node->next = node->next->next;
				break;
			}
			node = node->next;
		}
		return head;
	}

	// deep copy of a linked list with an additional pointer
	RandomListNode* copyRandomList(RandomListNode* head) {
		// insert the copied node after the original one.
		for (auto p = head; p; p = p->next->next) {
			auto *node = new RandomListNode(p->label);
			node->next = p->next;
			p->next = node;
		}

		// update random node.
		for (auto p = head; p; p = p->next->next) {
			if (p->random) {
				p->next->random = p->random->next;
			}
		}

		// seperate the copied nodes from the original ones
		RandomListNode dummy{ 0 };
		for (auto p = head, q = &dummy; p; p = p->next, q = q->next) {
			q->next = p->next;
			p->next = p->next->next;
		}
		return dummy.next;
	}

	// Use three pointers to reverse a linked list
	ListNode* reverse(ListNode *head) {
		if (!head || !head->next) return head;
		ListNode *prev = head;
		for (ListNode *curr = head->next, *next = curr->next; curr; prev = curr, curr = next, next = next ? next->next : nullptr) {
			curr->next = prev;
		}
		head->next = nullptr;
		return prev;
	}

	// Given a singly linked list L0 -> L1 -> Ln-1 -> Ln,
	// reorder it to: L0 -> Ln -> L1 -> Ln-1 -> L2 -> Ln-2
	// O(n) time
	// O(1) space
	void reorderList(ListNode* head) {
		if (head == nullptr || head->next == nullptr) return;
		// calc length
		ListNode* node = head;
		int N = 0;
		while (node) {
			++N;
			node = node->next;
		}

		// cut in the middle O(n)
		ListNode *slow = head, *fast = head, *prev = nullptr;
		while (fast && fast->next) {
			prev = slow;
			fast = fast->next->next;
			slow = slow->next;
		}
		prev->next = nullptr;


		slow = reverse(slow);


		// merge two lists
		ListNode *curr = head;
		while (curr->next) {
			ListNode *tmp = curr->next;
			curr->next = slow;
			slow = slow->next;
			curr->next->next = tmp;
			curr = tmp;
		}
		curr->next = slow;
	}

	// 24. Swap Nodes in Pairs [M]
	// Given a linked list, swap every two adjacent nodes and return its head.
	// Given 1->2->3->4, you should return the list as 2->1->4->3.
	ListNode* swapPairs(ListNode* head) {
		if (head == nullptr) return nullptr;
		ListNode* ans = head;
		ListNode* prev = ans;
		bool first = true;
		ListNode *p = head, *q = p->next;
		while (q != nullptr) {
			if (first) {
				ans = q;
			}
			else {
				prev->next = q;
			}
			p->next = q->next;
			q->next = p;
			prev = p;
			p = p->next;
			if (p == nullptr) break;
			q = p->next;
			first = false;
		}
		return ans;
	}
}
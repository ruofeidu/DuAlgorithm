#pragma once
#include "common.h"

namespace HPExercise {
	ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
		ListNode *ans = new ListNode(0);
		ListNode *last = NULL;
		bool first_bit = true;
		int next_carry = 0;
		int v1 = 0, v2 = 0;

		while (l1 != NULL || l2 != NULL) {
			if (l1 != NULL) {
				v1 = l1->val;
				l1 = l1->next;
			}
			else {
				v1 = 0;
			}

			if (l2 != NULL) {
				v2 = l2->val;
				l2 = l2->next;
			}
			else {
				v2 = 0;
			}

			int sum = v1 + v2 + next_carry;
			if (sum >= 10) {
				sum %= 10;
				next_carry = 1;
			}
			else {
				next_carry = 0;
			}

			if (first_bit) {
				ans->val = sum;
				last = ans;
			}
			else {
				last->next = new ListNode(sum);
				last = last->next;
			}
			first_bit = false;
		}

		if (next_carry == 1) {
			last->next = new ListNode(1);
			last = last->next;
		}
		return ans;
	}
}
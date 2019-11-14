#pragma once
#include "common.h"

namespace HPMisc {
// 2. Add Two Numbers
// The digits are stored in reverse order and each of their nodes contain a
// single digit. Add the two numbers and return it as a linked list.
// You may assume the two numbers do not contain any leading zero, except the
// number 0 itself.
ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
  ListNode* ans = new ListNode(0);
  ListNode* last = NULL;
  bool first_bit = true;
  int next_carry = 0;
  int v1 = 0, v2 = 0;

  while (l1 != NULL || l2 != NULL) {
    if (l1 != NULL) {
      v1 = l1->val;
      l1 = l1->next;
    } else {
      v1 = 0;
    }

    if (l2 != NULL) {
      v2 = l2->val;
      l2 = l2->next;
    } else {
      v2 = 0;
    }

    int sum = v1 + v2 + next_carry;
    if (sum >= 10) {
      sum %= 10;
      next_carry = 1;
    } else {
      next_carry = 0;
    }

    if (first_bit) {
      ans->val = sum;
      last = ans;
    } else {
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

// 66. Plus One
void add(vector<int>& digits, int num) {
  int carry = num;
  for (auto it = digits.rbegin(); it != digits.rend(); ++it) {
    *it += carry;
    carry = *it / 10;
    *it %= 10;
  }
  if (carry > 0) digits.insert(digits.begin(), 1);
}

vector<int> plusOne(vector<int>& digits) {
  add(digits, 1);
  return digits;
}

// 67. Add Binary
// Given two binary strings, return their sum (also a binary string).
string addBinary(string a, string b) {
  int n = (int)a.size(), m = (int)b.size();
  std::reverse(a.begin(), a.end());
  std::reverse(b.begin(), b.end());
  if (n < m) {
    swap(n, m);
    swap(a, b);
  }

  int carry = 0;
  string res = "";
  for (int i = 0; i < m; ++i) {
    int c = (a[i] - '0') + (b[i] - '0') + carry;
    carry = c / 2;
    c %= 2;
    res += char('0' + c);
  }

  for (int i = m; i < n; ++i) {
    int c = (a[i] - '0') + carry;
    carry = c / 2;
    c %= 2;
    res += char('0' + c);
  }
  if (carry > 0) res += char('1');
  std::reverse(res.begin(), res.end());
  return res;
}

// 43. Multiply Strings
// Given two non-negative integers num1 and num2 represented as strings, return
// the product of num1 and num2, also represented as a string.
typedef vector<int> bigint;
bigint make_bigint(string const& s) {
  bigint n;
  transform(s.rbegin(), s.rend(), back_inserter(n),
            [](char c) { return c - '0'; });
  return n;
}

string to_string(bigint const& n) {
  string s;
  transform(find_if(n.rbegin(), prev(n.rend()), [](char c) {
              return c > '\0';
            }), n.rend(), back_inserter(s), [](char c) { return c + '0'; });
  return s;
}

bigint operator*(bigint const& x, bigint const& y) {
  bigint z(x.size() + y.size());
  for (size_t i = 0; i < x.size(); ++i) {
    for (size_t j = 0; j < y.size(); ++j) {
      z[i + j] += x[i] * y[j];
      z[i + j + 1] += z[i + j] / 10;
      z[i + j] %= 10;
    }
  }
  return z;
}

class Solution {
 public:
  string multiply(string num1, string num2) {
    return to_string(make_bigint(num1) * make_bigint(num2));
  }
};
};

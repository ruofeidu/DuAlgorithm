#pragma once
#include "common.h"

namespace Stacks {
	class MinStack {
	public:
		/** initialize your data structure here. */
		MinStack() {}

		void push(int x) {
			s1.push(x);
			if (s2.empty() || x <= s2.top()) s2.push(x);
		}

		void pop() {
			if (s1.top() == s2.top()) s2.pop();
			s1.pop();
		}

		int top() {
			return s1.top();
		}

		int getMin() {
			return s2.top();
		}

	private:
		stack<int> s1, s2;
	};

	/* 
	 * 224. Basic Calculator
		"1 + 1" = 2
		" 2-1 + 2 " = 3
		"(1+(4+5+2)-3)+(6+8)" = 23
	 */
	int calculate(string s) {
		int res = 0;
		vector<int> sign(2, 1);
		for (int i = 0; i < s.size(); ++i) {
			char c = s[i];
			if (c >= '0') {
				int num = 0;
				while (i < s.size() && s[i] >= '0') {
					num = 10 * num + s[i++] - '0';
				}
				res += sign.back() * num;
				sign.pop_back();
				--i;
			}
			else if (c == ')') sign.pop_back();
			else if (c != ' ') sign.emplace_back(sign.back() * (c == '-' ? -1 : 1));
		}
		return res;
	}

	/**
	* 402. Remove K Digits
	Input: num = "1432219", k = 3
	Output: "1219"
	Explanation: Remove the three digits 4, 3, and 2 to form the new number 1219 which is the smallest.
	*/
	string removeKdigits(string num, int k) {
		string res = "";
		const auto n = num.size();
		auto keep = n - k;
		for (char c : num) {
			while (k && res.size() && res.back() > c) {
				res.pop_back();
				--k;
			}
			res.push_back(c);
		}
		res.resize(keep);
		while (!res.empty() && res[0] == '0') res.erase(res.begin());
		return res.empty() ? "0" : res;
	}

	// 84. Largest Rectangle in Histogram
	// Given n non-negative integers representing the histogram's bar height where the width of each bar is 1, find the area of largest rectangle in the histogram.
	int largestRectangleArea(vector<int>& heights) {
		int n = (int)heights.size();
		if (n == 0) return 0;
		stack<int> s;
		heights.emplace_back(0);
		++n;
		int ans = 0;
		for (int i = 0; i < n; ) {
			if (s.empty() || heights[i] > heights[s.top()]) {
				s.push(i++);
			}
			else {
				int tmp = s.top();
				s.pop();
				ans = max(ans, heights[tmp] * (s.empty() ? i : i - s.top() - 1));
			}
		}
		return ans;
	}

	// 114 O(n) Time, O(log n) Space
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
}
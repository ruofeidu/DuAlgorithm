#pragma once
#include "common.h"

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

class Stacks {
	// 224. Basic Calculator [H]
	/*
		"3-(2+5) = -4
	 */
	// The expression string may contain open ( and closing parentheses ), the plus + or minus sign -, non-negative integers and empty spaces.
	// Solution: Maintain a stack of - or (
	int calculateI(string s) {
		int res = 0, n = (int)s.size();
		vector<int> sign(2, 1);
		for (int i = 0; i < n; ++i) {
			char c = s[i];
			// read a number
			if (c >= '0') {
				int num = 0;
				while (i < n && s[i] >= '0') {
					num = 10 * num + s[i++] - '0';
				}
				--i;
				res += sign.back() * num;
				sign.pop_back();
			}
			else if (c == ')')
				sign.pop_back();
			// read a '-' or '('
			else if (c != ' ')
				sign.emplace_back(sign.back() * (c == '-' ? -1 : 1));
		}
		return res;
	}

	// 227. Basic Calculator II [M]
	// Support +, -, *, /.
	int calculate(string s) {
		stack<int64_t> operands;
		stack<char> operators;
		string operand;
		for (int i = (int)s.length() - 1; i >= 0; --i) {
			if (isdigit(s[i])) {
				operand.push_back(s[i]);
				if (i == 0 || !isdigit(s[i - 1])) {
					reverse(operand.begin(), operand.end());
					operands.emplace(stol(operand));
					operand.clear();
				}
			}
			else if (s[i] == ')' || s[i] == '*' ||
				s[i] == '/') {
				operators.emplace(s[i]);
			}
			else if (s[i] == '+' || s[i] == '-') {
				while (!operators.empty() && (operators.top() == '*' ||
					operators.top() == '/')) {
					compute(operands, operators);
				}
				operators.emplace(s[i]);
			}
			else if (s[i] == '(') {
				// operators at least one element, i.e. ')'.
				while (operators.top() != ')') {
					compute(operands, operators);
				}
				operators.pop();
			}
		}
		while (!operators.empty()) {
			compute(operands, operators);
		}
		return (int)operands.top();
	}

	void compute(stack<int64_t>& operands, stack<char>& operators) {
		const int64_t left = operands.top();
		operands.pop();
		const int64_t right = operands.top();
		operands.pop();
		const char op = operators.top();
		operators.pop();
		if (op == '+') {
			operands.emplace(left + right);
		}
		else if (op == '-') {
			operands.emplace(left - right);
		}
		else if (op == '*') {
			operands.emplace(left * right);
		}
		else if (op == '/') {
			operands.emplace(left / right);
		}
	}

	// 402. Remove K Digits
	/*
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

	// 20. Valid Parentheses
	// Given a string containing just the characters '(', ')', '{', '}', '[' and ']', determine if the input string is valid.
	bool isValid(string s)
	{
		string stack = "";
		for (auto c : s) {
			if (c == '(') stack += ')';
			else if (c == '[') stack += ']';
			else if (c == '{') stack += '}';
			else {
				if (stack.empty() || c != stack.back()) {
					return false;
				}
				else {
					stack.pop_back();
				}
			}

		}
		return stack.empty();
	}

	// 32. Longest Valid Parentheses
	int longestValidParentheses(string s) {
		int n = (int)s.size();
		int* f = new int[n];
		memset(f, 0, n * sizeof(int));
		int ans = 0;
		for (int i = 1; i < n; ++i) if (s[i] == ')') {
			int prev = i - f[i - 1] - 1;
			if (prev >= 0 && s[prev] == '(') {
				if (prev >= 1)
					f[i] = max(f[i], f[i - 1] + 2 + f[prev - 1]);
				else
					f[i] = max(f[i], f[i - 1] + 2);
			}
			if (s[i - 1] == '(') {
				f[i] = max(f[i], f[i - 2] + 2);
			}
			ans = max(ans, f[i]);
		}
		delete[] f;
		return ans;
	}

	// 150. Evaluate Reverse Polish Notation [M]
	// Evaluate the value of an arithmetic expression in Reverse Polish Notation. Valid operators are + , -, *, / .Each operand may be an integer or another expression.
	int evalRPN(vector<string>& tokens) {
		// reverse Polish Notation
		const int ERROR_CODE = INT_MIN;
		stack<int> stk;
		for (string s : tokens) {
			if (!s.compare("+")) {
				if (stk.size() < 2) return ERROR_CODE;
				int a = stk.top(); stk.pop();
				int b = stk.top(); stk.pop();
				stk.push(b + a);
			}
			else if (!s.compare("-")) {
				if (stk.size() < 2) return ERROR_CODE;
				int a = stk.top(); stk.pop();
				int b = stk.top(); stk.pop();
				stk.push(b - a);
			}
			else if (!s.compare("*")) {
				if (stk.size() < 2) return ERROR_CODE;
				int a = stk.top(); stk.pop();
				int b = stk.top(); stk.pop();
				stk.push(b * a);
			}
			else if (!s.compare("/")) {
				if (stk.size() < 2) return ERROR_CODE;
				int a = stk.top(); stk.pop();
				int b = stk.top(); stk.pop();
				stk.push(b / a);
			}
			else {
				stk.push(stoi(s));
			}
		}

		return (int)round(stk.top());
	}

	// 341. Flatten Nested List Iterator [M]
	// Given a nested list of integers, implement an iterator to flatten it. Each element is either an integer, or a list -- whose elements may also be integers or other lists.
	// Input: [[1,1],2,[1,1]]
	// Output: [1, 1, 2, 1, 1]
	// Explanation : By calling next repeatedly until hasNext returns false, the order of elements returned by next should be : [1, 1, 2, 1, 1].

	class NestedInteger {
	private:
		int m_val = INT_MIN;
		vector<NestedInteger> m_vec;
	public:
		// Return true if this NestedInteger holds a single integer, rather than a nested list.
		bool isInteger() {
			return m_vec.empty() && m_val > INT_MIN;
		}
			
		// Return the single integer that this NestedInteger holds, if it holds a single integer
		// The result is undefined if this NestedInteger holds a nested list
		int getInteger() {
			return m_val;
		}
			
		// Return the nested list that this NestedInteger holds, if it holds a nested list
		// The result is undefined if this NestedInteger holds a single integer
		const vector<NestedInteger> &getList() {
			return m_vec;
		}
	};

	class NestedIterator {
	public:
		NestedIterator(vector<NestedInteger> &nestedList) {
			for (int i = (int)nestedList.size() - 1; i >= 0; --i) {
				s.push(nestedList[i]);
			}
		}

		int next() {
			NestedInteger t = s.top(); s.pop();
			return t.getInteger();
		}

		bool hasNext() {
			while (!s.empty()) {
				NestedInteger t = s.top();
				if (t.isInteger()) return true;
				s.pop();
				for (int i = (int)t.getList().size() - 1; i >= 0; --i) {
					s.push(t.getList()[i]);
				}
			}
			return false;
		}

	private:
		stack<NestedInteger> s;

	};
};

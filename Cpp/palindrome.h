#pragma once
#include "common.h"

namespace Palindrome {
	// 5. Longest Palindromic Subsequence
	// Find the length of the longest palindromic subsequence in a given sequence
	string longestPalindrome(string s)
	{
		const size_t n = s.size();
		if (n == 0) return s;
		bool* g = new bool[n*n];
		memset(g, false, sizeof(g));

		size_t max_len = 1, start = 0;
		for (size_t i = 0; i < n; ++i) {
			g[i*n + i] = true;
			for (size_t j = 0; j < i; ++j) {
				g[i*n + j] = (s[j] == s[i] && (j == i - 1 || g[j + 1 + n*(i - 1)]));
				if (g[j + n*i] && max_len < (i - j + 1)) {
					max_len = i - j + 1;
					start = j;
				}
			}
		}
		delete[] g;
		return s.substr(start, max_len);
	}

	int int_len(int x) {
		int y = 1;
		while (x > 10) {
			x /= 10;
			++y;
		}
		return y;
	}

	int pow10(int n)
	{
		static int pow10[10] = {
			1, 10, 100, 1000, 10000, 100000, 1000000, 10000000, 100000000, 1000000000
		};
		return pow10[n];
	}

	// round up the palindrom by the middle digit
	// 192 -> 200
	// 1991 -> 2000
	// 11199111 -> 11200000
	int round_up(int x) {
		int n = int_len(x);
		int inc = pow10((n >> 1) + 1);
		int y = x / inc;
		return (y + 1) * inc;
	}

	int next(int x) {
		auto s = to_string(x);
		int n = (int)s.size();
		bool is_odd = n & 1;
		auto left_half = s.substr(0, n >> 1);
		auto middle = s[(n - 1) >> 1];
		string right_half = left_half;
		reverse(right_half.begin(), right_half.end());
		int y = 0, inc = 0;
		if (is_odd) {
			inc = pow10(n >> 1);

			auto res = left_half + middle + right_half;
			y = atoi(res.c_str());
		}
		else {
			int inc = (int)(1.1 * pow10(n >> 1));
			auto res = left_half + right_half;
			y = atoi(res.c_str());
		}
		if (y > x)
			return y;
		if (middle != '9')
			return y + inc;
		else
			return next(round_up(x));
	}

	// 9. Palindrome Number
	bool isPalindrome(int x) {
		if (x < 0) return false;
		if (x == INT_MAX) return false;
		int n = (int)ceil(log10(x + 1));
		while (n > 1) {
			int a = x % 10;
			int b = x / (int)pow(10, n - 1);
			if (a != b) return false;
			x %= (int)pow(10, n - 1);
			x /= 10;
			n -= 2;
		}
		return true;
	}

	// 125. Valid Palindrome
	// Given a string, determine if it is a palindrome, considering only alphanumeric characters and ignoring cases.
	bool isPalindrome(string s) {
		const int n = (int)s.size();
		if (n == 0) return true;
		transform(s.begin(), s.end(), s.begin(), ::tolower);
		auto l = s.begin(), r = prev(s.end());

		while (l < r) {
			if (!::isalnum(*l)) ++l;
			else if (!::isalnum(*r)) --r;
			else if (*l != *r) return false;
			else { ++l, --r; }
		}
		return true;
	}

	// 131. Palindrome Partitioning
	// Given a string s, partition s such that every substring of the partition is a palindrome. Return all possible palindrome partitioning of s.
	vector<vector<string>> partition(string s) {
		// Time Complexity: average: O(n^2), worst: O(n^2 * 2^n)
		// Space Complexity: average: O(1), worst: O(2^n)
		const int n = (int)s.size();
		vector<vector<bool>> p(n, vector<bool>(n, 0));

		for (int i = n - 1; i >= 0; --i)
			for (int j = i; j < n; ++j)
				p[i][j] = s[i] == s[j] && ((j - i < 2) || p[i + 1][j - 1]);

		vector<vector<vector<string>>> sub_palins(n, vector<vector<string>>());
		for (int i = n - 1; i >= 0; --i) {
			for (int j = i; j < n; ++j)
				if (p[i][j]) {
					const string palindrome = s.substr(i, j - i + 1);
					if (j + 1 < n) {
						for (auto v : sub_palins[j + 1]) {
							v.insert(v.begin(), palindrome);
							sub_palins[i].push_back(v);
						}
					}
					else {
						sub_palins[i].push_back(vector<string> { palindrome });
					}
				}
		}

		return sub_palins[0];
	}

	// 132. Palindrome Partitioning II [H]
	// Given a string s, partition s such that every substring of the partition is a palindrome. Return the minimum cuts needed for a palindrome partitioning of s.
	/*
		Input: "aab"
		Output: 1
		Explanation: The palindrome partitioning ["aa","b"] could be produced using 1 cut.
	*/
	int minCut(string s) {
		const int len = (int)s.size();
		vector<vector<bool>> P(len, vector<bool>(len, false));
		Vector dp(len + 1, 0);
		for (int i = 0; i <= len; ++i) {
			dp[i] = len - i - 1;
		}
		for (int i = 0; i < len; ++i) {
			for (int j = 0; j < len; ++j) {
				P[i][j] = false;
			}
		}
		for (int i = len - 1; i >= 0; --i) {
			for (int j = i; j < len; ++j) {
				if (s[i] == s[j] && (j - i <= 1 || P[i + 1][j - 1])) {
					P[i][j] = true;
					dp[i] = min(dp[i], dp[j + 1] + 1);
				}
			}
		}
		return dp[0];
	}

	// 214. Shortest Palindrome [H]
	// Given a string s, you are allowed to convert it to a palindrome by adding characters in front of it. Find and return the shortest palindrome you can find by performing this transformation.
	/*
		Input: "aacecaaa"
		Output: "aaacecaaa"
	*/
	string shortestPalindrome(string s) {
		string r = s;
		reverse(r.begin(), r.end());
		string t = s + "#" + r;
		vector<int> p(t.size(), 0);
		for (int i = 1; i < t.size(); ++i) {
			int j = p[i - 1];
			while (j > 0 && t[i] != t[j]) j = p[j - 1];
			p[i] = (j += t[i] == t[j]);
		}
		return r.substr(0, s.size() - p[t.size() - 1]) + s;
	}

	// 234. Palindrome Linked List [E]
	// Given a singly linked list, determine if it is a palindrome.
	// See Python

	// 336. Palindrome Pairs [H]
	// Given a list of unique words, find all pairs of distinct indices (i, j) in the given list, so that the concatenation of the two words, i.e. words[i] + words[j] is a palindrome.
	bool isP(string s) {
		if (s.empty() || s.size() == 1) return true;
		int l = 0, r = (int)s.size() - 1;
		while (l < r) {
			if (s[l++] != s[r--]) return false;
		}
		return true;
	}

	vector<vector<int>> palindromePairs(vector<string>& words) {
		unordered_map<string, int> map;
		vector<vector<int>> ans;
		const int N = (int)words.size();
		if (N == 0) return ans;

		vector<vector<bool>> visited(N, vector<bool>(N));

		for (int i = 0; i < N; ++i)
			map[words[i]] = i;
		for (int i = 0; i < N; ++i) {
			visited[i][i] = true;
			string s = words[i];
			const int n = (int)s.size();

			if (n == 0) {
				for (int j = 0; j < N; ++j)
					if (i != j && isP(words[j])) {
						if (!visited[i][j]) {
							ans.push_back(vector<int>{i, j});
							visited[i][j] = true;
						}
						if (!visited[j][i]) {
							ans.push_back(vector<int>{j, i});
							visited[j][i] = true;
						}
					}
				continue;
			}

			for (int len = 0; len <= n; ++len) {
				if (!isP(s.substr(n - len, len))) continue;
				string r = s.substr(0, n - len);
				reverse(r.begin(), r.end());
				if (map.find(r) != map.end() && !visited[i][map[r]]) {
					ans.push_back(vector<int>{i, map[r]});
					visited[i][map[r]] = true;
				}
			}


			for (int len = 1; len < n; ++len) {

				//			    if (i == 3) cout << s.substr(0, len) << " " << s.substr(len, n-len) << endl;


				if (!isP(s.substr(0, len))) continue;
				string r = s.substr(len, n - len);
				reverse(r.begin(), r.end());
				if (map.find(r) != map.end() && !visited[map[r]][i]) {
					ans.push_back(vector<int>{map[r], i});
					visited[map[r]][i] = true;
				}
			}
		}


		return ans;
	}
}

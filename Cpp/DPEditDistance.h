#pragma once
#include "common.h"

namespace DPEditDistance {
	// 72. Edit Distance
	// Given two words word1 and word2, find the minimum number of operations required to convert word1 to word2.
	// Operations: insert, delete, and replace
	int minDistance(string word1, string word2) {
		int n = word1.size();
		int m = word2.size();
		if (n == 0 && m == 0) return 0;

		vector<vector<int>> f(n + 1, vector<int>(m + 1));

		for (int i = 0; i <= n; ++i) f[i][0] = i;
		for (int j = 0; j <= m; ++j) f[0][j] = j;

		for (int i = 1; i <= n; ++i) {
			for (int j = 1; j <= m; ++j) {
				if (word1[i - 1] == word2[j - 1]) {
					f[i][j] = f[i - 1][j - 1];
				}
				else {
					f[i][j] = min(min(f[i - 1][j], f[i][j - 1]), f[i - 1][j - 1]) + 1;
				}
			}
		}
		return f[n][m];
	}

	// 161. Edit Distance
	// Given two strings S and T, determine if they are both one edit distance apart.
	bool isOneEditDistance(string s, string t) {
		int n = (int)s.size(), m = (int)t.size();
		for (int i = 0; i < min(n, m); ++i) {
			if (s[i] != t[i]) {
				if (n == m) return s.substr(i + 1) == t.substr(i + 1);
				else if (n < m) return s.substr(i) == t.substr(i + 1);
				else return s.substr(i + 1) == t.substr(i);
			}
		}
		return (int)(abs(n - m)) == 1;
	}

	// 87. Scramble String [H][VH]
	// Given a string s1, we may represent it as a binary tree by partitioning it to two non-empty substrings recursively.
	// To scramble the string, we may choose any non-leaf node and swap its two children.
	// Given two strings s1 and s2 of the same length, determine if s2 is a scrambled string of s1.
	// Time: O(N^4)
	bool isScramble(string s1, string s2) {
		const int N = s1.size();
		if (s2.size() != N) return false;
		// length, starting i, starting j
		vector<vector<vector<bool>>> f(N + 1, vector<vector<bool>>(N, vector<bool>(N)));

		for (int i = 0; i < N; ++i)
			for (int j = 0; j < N; ++j)
				f[1][i][j] = (s1[i] == s2[j]);

		for (int n = 1; n <= N; ++n) {
			for (int i = 0; i + n <= N; ++i) {
				for (int j = 0; j + n <= N; ++j) {
					for (int k = 1; k < n; ++k) {
						if ((f[k][i][j] && f[n - k][i + k][j + k]) ||
							(f[k][i][j + n - k] && f[n - k][i + k][j])) {
							f[n][i][j] = true;
							break;
						}
					}
				}
			}
		}
		return f[N][0][0];
	}

	// 97. Interleaving String [H][VH]
	// Given s1, s2, s3, find whether s3 is formed by the interleaving of s1 and s2.
	/*
		Example 1:

		Input: s1 = "aabcc", s2 = "dbbca", s3 = "aadbbcbcac"
		Output: true
		Example 2:

		Input: s1 = "aabcc", s2 = "dbbca", s3 = "aadbbbaccc"
		Output: false
	*/
	bool isInterleave(string s1, string s2, string s3) {
		int N = s3.size();
		int m = s1.size();
		int n = s2.size();
		if (m + n != N) return false;
		vector<vector<bool>> f(N + 1, vector<bool>(m + 1, false));
		f[0][0] = true;

		for (int i = 1; i <= N; ++i) {
			f[i][0] = (f[i - 1][0] && s3[i - 1] == s2[i - 1]);
			if (f[i][0]) printf("f[%d][%d] = T\t", i, 0); else printf("f[%d][%d] = F\t", i, 0);
			for (int j = 1; j <= i; ++j) {
				if (f[i - 1][j] && s3[i - 1] == s2[i - j - 1]) f[i][j] = true;
				if (f[i - 1][j - 1] && s3[i - 1] == s1[j - 1]) f[i][j] = true;
				//if (f[i][j]) printf("f[%d][%d] = T\t", i, j); else printf("f[%d][%d] = F\t", i, j);
			}
			//printf("\n");
		}

		return f[N][m];
	}
}
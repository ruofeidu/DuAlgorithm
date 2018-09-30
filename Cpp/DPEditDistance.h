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
}
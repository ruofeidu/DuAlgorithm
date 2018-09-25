#pragma once
#include "common.h"

// Longest Common Subsequence (LCS)
// Find the length of the longest subsequence of a given sequence 
// such that all elements of the subsequence are sorted in increasing order.
// Time: O(N log N)
// Space: O(N) => O(1)
namespace LCSProblems {
	int LCS(string &a, string &b) {
		int n = (int)a.size(), m = (int)b.size();
		Grid f(n + 1, Vector(m + 1, 0));

		for (int i = 0; i <= n; ++i) {
			for (int j = 0; j <= m; ++j) {
				if (a[i - 1] == b[j - 1])
					f[i][j] = f[i - 1][j - 1] + 1;
				else
					f[i][j] = max(f[i - 1][j], f[i][j - 1]);
			}
		}
		return f[n][m];
	}
}
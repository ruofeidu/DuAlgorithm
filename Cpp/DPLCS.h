#pragma once
#include "common.h"

// Longest Common Subsequence (LCS)
// Find the longest subsequence common to all sequences in a set of sequences (often just two sequences).
// Time: O(M)
// Space: O(M) => O(1)
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
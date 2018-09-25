#pragma once
#include "common.h"

namespace LCSProblems {
	// Longest common subsequence
	// O(MN)
	int LCS(string &a, string &b) {
		int n = (int)a.size();
		int m = (int)b.size();
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
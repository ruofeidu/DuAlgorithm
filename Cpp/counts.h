#pragma once
#include "common.h"

namespace Counts {
	// # of unique paths from top left to bottom right.
	// f[i][j] = f[i-1][j] + f[i][j-1]
	int uniquePathsDP(int m, int n) {
		vector<int> f(n, 0);
		f[0] = 1;
		for (int i = 0; i < m; ++i) {
			for (int j = 1; j < n; ++j) {
				f[j] = f[j] + f[j - 1];
			}
		}
		return f[n - 1];
	}

	// In total, there are m+n-2 steps, in which m-1 downwards steps
	// C_{m+n-2}^{m-1}

	// calc n!/(start-1)!
	static long long factor(int n, int start = 1) {
		long long res = 1;
		for (int i = start; i <= n; ++i)
			res *= i;
		return res;
	}

	// calc C_n^k
	static long long combination(int n, int k) {
		if (k == 0)
			return 1;
		if (k == 1)
			return n;
		return factor(n, k + 1) / factor(n - k);
	}

	long long uniquePathC(int m, int n) {
		return combination(m + n - 2, max(m - 1, n - 1));
	}

	int uniquePathsWithObstacles(Grid& obstacleGrid) {
		int m = (int)obstacleGrid.size();
		int n = (int)obstacleGrid[0].size();

		if (n == 0 || m == 0 || obstacleGrid[0][0] || obstacleGrid[m - 1][n - 1]) return 0;

		vector<int> f(n, 0);
		f[0] = 1;

		for (auto i = 0; i < m; ++i) {
			f[0] = f[0] == 0 ? 0 : (!obstacleGrid[i][0]);
			for (int j = 1; j < n; ++j) 
				if (!obstacleGrid[i][j]) {
					f[j] = f[j] + f[j - 1];
				}
				else {
					f[j] = 0;
				}
		}

		return f[n - 1];
	}

	// 357. Count Numbers with Unique Digits
	int countNumbersWithUniqueDigits(int n) {
		// [0-9]    10
		// [10-99]  90-9=81
		// f[n] = 9 * 9 * 8 * ... * (9 - k + 2)
		if (n == 0) return 1;
		int res = 10, cnt = 9;
		for (int i = 2; i <= n; ++i) {
			cnt *= (11 - i);
			res += cnt;
		}
		return res;
	}

	// 70. Climbing Stairs
	// you are climbing a stair case. It takes n steps to reach to the top.
	// Each time you can either climb 1 or 2 steps.
	// In how many distinct ways can you climb to the top ?
	int climbStairs(int n) {
		if (n <= 0) return 0;
		vector<int> f(3, 1);
		for (int i = 2; i <= n; ++i) {
			f[i % 3] = f[(i - 1) % 3] + f[(i - 2) % 3];
		}
		return f[n % 3];
	}

}
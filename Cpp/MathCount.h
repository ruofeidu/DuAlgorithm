#pragma once
#include "common.h"

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

namespace Counts {
	// 62. Unique Paths [M]
	// See DPGrid.h
	// In total, there are m+n-2 steps, in which m-1 downwards steps
	// C_{m+n-2}^{m-1}

	long long uniquePath(int m, int n) {
		return combination(m + n - 2, max(m - 1, n - 1));
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

	int maxRegionsByALine(int n) {
		// f[n] = f[n-1] + n
		return n * (n + 1) / 2 + 1;
	}

	int maxRegionsByAPolyLine(int n) {
		return (n - 1)*(2 * n - 1) + 2 * n;
	}

	int maxRegionsByAClosedCurve(int n) {
		// f[n] = f[n-1] + 2 * (n-1)
		return n * n - n + 2;
	}

	long long countTrianglesOfPolygon(int n) {
		return combination(2 * n - 2, n - 1) / n;
	}

	long long countKlygonOfPolygon(int n, int k) {
		if (k < 3)
			return -1;
		return combination(2 * k - 4, k - 2) / (k - 1);
	}

	// 172. Factorial Trailing Zeroes
	// Given an integer n, return the number of trailing zeroes in n!.
	int trailingZeroes(int n) {
		int res = 0;
		while (n > 0) {
			res += n / 5;
			n /= 5;
		}
		return res;
	}

	// Josephus problem
	
}
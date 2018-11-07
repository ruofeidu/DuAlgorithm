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
		if (n == 0)
			return 1;
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

	// 233. Number of Digit One [H]
	// Given an integer n, count the total number of digit 1 appearing in all non-negative integers less than or equal to n.
	int countDigitOne(int n) {
		// 1-9:1
		// 10-19: +19
		// 20-99: +8
		const int k = 1;
		int cnt = 0, multiplier = 1, left_part = n;

		while (left_part > 0) {
			// split number into: left_part, curr, right_part
			int curr = left_part % 10;
			int right_part = n % multiplier;

			// count of (c000 ~ oooc000) = (ooo + (k < curr)? 1 : 0) * 1000
			cnt += (left_part / 10 + (k < curr)) * multiplier;

			// if k == 0, oooc000 = (ooo - 1) * 1000
			if (k == 0 && multiplier > 1) {
				cnt -= multiplier;
			}

			// count of (oook000 ~ oookxxx): count += xxx + 1
			if (curr == k) {
				cnt += right_part + 1;
			}

			left_part /= 10;
			multiplier *= 10;
		}

		return cnt;
	}

	// Josephus problem
	// N people, remove the M first, kick every Kth: who is the winner?
	// POJ 3157
	int joseph(int n, int m, int k) {
		int s = 0;
		for (int i = 2; i <= n; ++i)
			s = (s + k) % i;
		k = k % n;
		if (k == 0)
			k = n;
		int d = (s + 1) + (m - k);
		if (d >= 1 && d <= n)
			return d;
		else if (d < 1)
			return n + d;
		else
			return d % n;
	}

	int josephSimulation(int n, int m, int k) {
		vector<int> a(n);
		int i = 0; 
		for (; i < m - 1; ++i)
			a[i] = i;
		for (; i < n; ++i)
			a[i] = i + 1;
		int cur = m - 1; 
		while (--n) {
			cur = (cur + k - 1) & n;
			for (i = cur + 1; i < n; ++i)
				a[i - 1] = a[i];
		}
		return a[0] + 1;
	}
}
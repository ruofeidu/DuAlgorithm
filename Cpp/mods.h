#pragma once
#include "common.h"

namespace Mods{
	// 326. Power of Three
	bool isPowerOfThree(int n) {
		return (n > 0 && 1162261467 % n == 0);
		return (n > 0 && int(log10(n) / log10(3)) - log10(n) / log10(3) == 0);
	}

	// 263. Ugly numbers
	// Ugly numbers are positive numbers whose prime factors only include 2, 3, 5. 
	// For example, 6, 8 are ugly while 14 is not ugly since it includes another prime factor 7.
	bool isUgly(int num) {
		if (num <= 0) return false;
		while (num % 2 == 0) num /= 2;
		while (num % 3 == 0) num /= 3;
		while (num % 5 == 0) num /= 5;
		return num == 1;
	}

	// 264. Ugly Number II
	// Find the nth ugly number
	// For example, 1, 2, 3, 4, 5, 6, 8, 9, 10, 12 is the sequence of the first 10 ugly numbers.
	int nthUglyNumber(int n) {
		vector<int> res(1, 1);
		int i2 = 0, i3 = 0, i5 = 0;
		while (res.size() < n) {
			int m2 = res[i2] * 2, m3 = res[i3] * 3, m5 = res[i5] * 5;
			int mn = min(m2, min(m3, m5));
			if (mn == m2) ++i2;
			if (mn == m3) ++i3;
			if (mn == m5) ++i5;
			res.emplace_back(mn);
		}
		return res.back();
	}

	// 313. Super Ugly Number
	// Super ugly numbers are positive numbers whose all prime factors are in the given prime list primes of size k. 
	int nthSuperUglyNumber(int n, vector<int>& primes) {
		vector<int> dp(n, 1), idx(primes.size(), 0);
		for (int i = 1; i < n; ++i) {
			dp[i] = INT_MAX;
			for (int j = 0; j < primes.size(); ++j) {
				dp[i] = min(dp[i], dp[idx[j]] * primes[j]);
			}
			for (int j = 0; j < primes.size(); ++j) {
				if (dp[i] == dp[idx[j]] * primes[j]) {
					++idx[j];
				}
			}
		}
		return dp.back();
	}
}
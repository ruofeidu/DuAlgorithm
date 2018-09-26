#pragma once
#include "common.h"

class BagProblems {
public:
	// 322. Coin Change
	// infinite goods
	/**
	*	Example 1:
	*	coins = [1, 2, 5], amount = 11
	*	return 3 (11 = 5 + 5 + 1)
	*/
	int coinChange(vector<int>& coins, int amount) {
		size_t n = coins.size();
		int m = amount;
		if (m < 0) return -1;
		vector<int> f(m + 1, m + 1);
		// f[i] indicates the min number of coins to form total amount of i
		f[0] = 0;
		for (int i = 1; i <= m; ++i) {
			for (int j = 0; j < n; ++j) if (coins[j] <= i) {
				f[i] = min(f[i], f[i - coins[j]] + 1);
			}
		}
		return f[m] > m ? -1 : f[m];
	}
};
#pragma once
#include "common.h"

class KnapsackProblems {
public:
	// 322. Coin Change
	// Unbounded knapsack with infinite goods
	// Time: O(MN)
	// Space: O(M)
	/**
	*	Example 1:
	*	coins = [1, 2, 5], amount = 11
	*	return 3 (11 = 5 + 5 + 1)
	*/
	int coinChange(vector<int>& coins, int amount) {
		const int n = (int)coins.size(), m = amount;
		if (m < 0)
			return -1;
		vector<int> f(m + 1, m + 1);
		// f[i] indicates the min number of coins to form total amount of i
		f[0] = 0;
		for (int i = 1; i <= m; ++i)
			for (int j = 0; j < n; ++j)
				if (coins[j] <= i && f[i - coins[j]] + 1 < f[i]) {
					f[i] = f[i - coins[j]] + 1;
				}
		return f[m] > m ? -1 : f[m];
	}

	// 416. Partition Equal Subset Sum [M]
	// Given a non-empty array containing only positive integers, find if the array can be partitioned into two subsets such that the sum of elements in both subsets is equal.
	// 0/1 knapsack Solution, refer to Bits for more details
	// Time: O(NM), M is the sum of nums.
	// Space: O(M)
	bool canPartition(vector<int>& nums) {
		int sum = accumulate(nums.begin(), nums.end(), 0);
		if (sum & 1)
			return false;
		const int n = (int)nums.size(), m = sum >> 1;
		vector<bool> dp(m + 1, false);
		dp[0] = true;
		for (int i = 0; i < n; ++i) {
			for (int j = m; j >= nums[i]; --j) {
				dp[j] = dp[j] || dp[j - nums[i]];
			}
		}
		return dp.back();
	}
};
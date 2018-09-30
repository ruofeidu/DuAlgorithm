#pragma once
#include "common.h"

namespace DP1D {
	// 42. Trapping Rain Water
	// Given n non-negative integers representing an elevation map where the width of each bar is 1, 
	// compute how much water it is able to trap after raining.
	int trap(vector<int>& height) {
		const int n = (int)height.size();
		if (n < 3) return 0;
		vector<int> lmax(n, 0), rmax(n, 0);
		lmax[0] = height[0];
		rmax[n - 1] = height[n - 1];
		for (int i = 0; i < n - 1; ++i) {
			lmax[i + 1] = max(lmax[i], height[i + 1]);
			rmax[n - 2 - i] = max(rmax[n - 1 - i], height[n - 2 - i]);
		}
		int ans = 0;
		for (int i = 1; i < n - 1; ++i) {
			ans += min(lmax[i], rmax[i]) - height[i];
		}
		return ans;
	}

	// 300. Longest Increasing Subsequence
	// O(n^2)
	int lengthOfLISN2(vector<int>& nums) {
		const auto n = nums.size();
		if (n == 0) return 0;
		vector<int> f(n + 1);
		f[0] = 1;
		int ans = 1;
		for (size_t i = 1; i < n; ++i) {
			f[i] = 1;
			for (size_t j = 0; j < i; ++j) if (nums[i] > nums[j]) {
				f[i] = max(f[i], f[j] + 1);
				ans = max(ans, f[i]);
			}
		}
		return ans;
	}

	// O(N log N)
	int lengthOfLIS(vector<int>& nums) {
		vector<int> f;
		const auto n = nums.size();
		for (int x : nums) {
			int l = 0, r = (int)f.size();
			// find the first element in f, that is not greater than x
			// 4, 2, 4, 5, 3, 7 =>
			// 4
			// 2
			// 2, 4
			// 2, 4, 5
			// 2, 3, 5
			// 2, 3, 5, 7
			while (l < r) {
				int mid = (l + r) >> 1;
				if (f[mid] < x) l = mid + 1;
				else r = mid;
			}
			if (r >= f.size()) f.emplace_back(x); else f[r] = x;
		}
		return (int)f.size();
	}

	// 256. Paint House
	// k = 3
	// There are a row of n houses, each house can be painted with one of the k colors. 
	// The cost of painting each house with a certain color is different. 
	// You have to paint all the houses such that no two adjacent houses have the same color.
	int minCost(vector<vector<int>>& costs) {
		if (costs.empty() || costs[0].empty()) return 0;
		vector<vector<int>> dp = costs;
		for (size_t i = 1; i < dp.size(); ++i) {
			for (size_t j = 0; j < 3; ++j) {
				dp[i][j] += min(dp[i - 1][(j + 1) % 3], dp[i - 1][(j + 2) % 3]);
			}
		}
		return min(min(dp.back()[0], dp.back()[1]), dp.back()[2]);
	}

}
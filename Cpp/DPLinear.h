#pragma once
#include "common.h"

class DP1D {
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


	// 135. Candy [H]
	// There are N children standing in a line. Each child is assigned a rating value. You are giving candies to these children subjected to the following requirements : Each child must have at least one candy. Children with a higher rating get more candies than their neighbors. What is the minimum candies you must give ?
	// 1, 2, 3, 4, 5 ==>
	// 3, 2, 1, 2, 3 ==>
	// 1, 2, 1, 2, 1
	int candy(vector<int>& ratings) {
		const int n = (int)ratings.size();
		int ans = 0;
		vector<int> f(n, 1); // longest increasing from left
		vector<int> g(n, 1); // longest increasing from right
		for (int i = 1; i < n; ++i) {
			if (ratings[i] > ratings[i - 1]) f[i] = f[i - 1] + 1;
		}
		for (int i = n - 2; i >= 0; --i) {
			if (ratings[i] > ratings[i + 1]) g[i] = g[i + 1] + 1;
		}
		for (int i = 0; i < n; ++i) {
			// cout << f[i] << "\t" << g[i] << endl; 
			ans += max(f[i], g[i]);
		}
		return ans;
	}

	// 139. Word Break
	// Given a non-empty string s and a dictionary wordDict containing a list of non-empty words, determine if s can be segmented into a space-separated sequence of one or more dictionary words.
	bool wordBreak(string s, unordered_set<string>& wordDict) {
		const int n = (int)s.size(), m = (int)wordDict.size();
		if (n <= 0) return false;
		vector<bool> f(n + 1);
		f[0] = true;
		for (int i = 1; i <= n; ++i) {
			for (int j = 1; j <= i; ++j) if (f[j - 1]) {
				if (wordDict.find(s.substr(j - 1, i - j + 1)) != wordDict.end()) {
					f[i] = true;
					break;
				}
			}
		}
		return f[n];
	}

	// 140. Word Break II
	// Given a non-empty string s and a dictionary wordDict containing a list of non-empty words, add spaces in s to construct a sentence where each word is a valid dictionary word. Return all such possible sentences.
	vector<string> wordBreak2(string s, unordered_set<string>& wordDict) {
		const int n = (int)s.size(), m = (int)wordDict.size();
		vector<string> ans;
		if (n <= 0) return ans;
		vector<bool> f(n + 1);
		vector<vector<int>> p(n + 1);
		f[0] = true;
		for (int i = 1; i <= n; ++i) {
			for (int j = 1; j <= i; ++j) if (f[j - 1]) {
				if (wordDict.find(s.substr(j - 1, i - j + 1)) != wordDict.end()) {
					f[i] = true;
					p[i].push_back(j - 1);
				}
			}
		}
		if (!f[n]) return ans;
		findWordBreak(ans, f, p, s, n, "");
		return ans;
	}


	void findWordBreak(vector<string> &ans, vector<bool> &f, vector<vector<int>> &p, string &s, int n, string path) {
		if (n <= 0) {
			ans.push_back(path);
			return;
		}
		if (!f[n]) return;
		for (int i = 0; i < p[n].size(); ++i) {
			int j = p[n][i];
			string newpath = path;
			if (newpath.empty()) {
				newpath = s.substr(j, n - j);
			}
			else {
				newpath = s.substr(j, n - j) + " " + newpath;
			}
			findWordBreak(ans, f, p, s, j, newpath);
		}
	}

	// 152. Maximum Product Subarray
	// Given an integer array nums, find the contiguous subarray within an array (containing at least one number) which has the largest product.
	int maxProduct(vector<int>& nums) {
		if (nums.empty()) return 0;
		int res = nums[0], mn = nums[0], mx = nums[0];
		for (int i = 1; i < nums.size(); ++i) {
			int tmax = mx, tmin = mn;
			mx = max(max(nums[i], tmax * nums[i]), tmin * nums[i]);
			mn = min(min(nums[i], tmax * nums[i]), tmin * nums[i]);
			res = max(res, mx);
		}
		return res;
	}

	// 198. House Robber [E]
	// You are a professional robber planning to rob houses along a street. Each house has a certain amount of money stashed, the only constraint stopping you from robbing each of them is that adjacent houses have security system connected and it will automatically contact the police if two adjacent houses were broken into on the same night. Max.
	int rob(vector<int>& nums) {
		const int n = (int)nums.size();
		if (n == 0) return 0;
		vector<int> f(3); // f[i] = maximum from 0 .. i - 1
		f[1] = nums[0];

		for (int i = 2; i <= n; ++i) {
			f[i % 3] = max(f[(i - 1) % 3], f[(i - 2) % 3] + nums[i - 1]);
		}

		return f[n % 3];
	}

	// 213. House Robber II [M]
	// All houses at this place are arranged in a circle.
	int rob2(vector<int>& nums) {
		const int n = (int)nums.size();
		if (n <= 1)
			return nums.empty() ? 0 : nums[0];
		return max(rob2(nums, 0, n - 1), rob2(nums, 1, n));
	}

	int rob2(vector<int> &nums, int l, int r) {
		if (r - l <= 1)
			return nums[l];
		vector<int> f(r, 0);
		f[l] = nums[l];
		f[l + 1] = max(nums[l], nums[l + 1]);
		for (int i = l + 2; i < r; ++i) {
			f[i] = max(nums[i] + f[i - 2], f[i - 1]);
		}
		return f.back();
	}
};

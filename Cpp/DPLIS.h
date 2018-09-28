#pragma once
#include "common.h"

// Longest Increasing Subsequence (LCS)
namespace LISProblems {
	// 300. Longest Increasing Subsequence
	// Given an unsorted array of integers, find the length of longest increasing subsequence.
	int lengthOfLIS(vector<int>& nums) {
		vector<int> f;
		int n = nums.size();
		for (int x : nums) {
			int l = 0, r = f.size();
			// find the first element in f, that is not greater than x
			// 4, 2, 4, 5, 3, 7
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
			if (r >= f.size()) f.push_back(x); else f[r] = x;
		}
		return f.size();
	}

	// 675. Longest Continuous Increasing Subsequence
	// Given an unsorted array of integers, find the length of longest continuous increasing subsequence (subarray).
	int findLengthOfLCIS(vector<int>& nums) {
		int res = 0, cnt = 0, n = (int)nums.size();
		for (int i = 0; i < n; ++i) {
			if (i == 0 || nums[i - 1] < nums[i]) {
				cnt += 1;
				res = max(res, cnt);
			}
			else {
				cnt = 1;
			}
		}
		return res;
	}
}
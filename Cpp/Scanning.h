#pragma once
#include "common.h"

namespace Scanning {
	// 849. Maximize Distance to Closest Person
	int maxDistToClosest(vector<int>& seats) {
		int res = 0, cnt = 0;
		bool ends = true;
		for (const auto &seat : seats) {
			if (seat == 0) {
				cnt += 1;
			}
			else {
				if (!ends) {
					cnt = (cnt + 1) >> 1;
				}
				res = max(res, cnt);
				cnt = 0;
				ends = false;
			}
		}
		return max(res, cnt);
	}

	// 11. Container With Most Water [M]
	// Given n non-negative integers a1, a2, ..., an , where each represents a point at coordinate (i, ai). n vertical lines are drawn such that the two endpoints of line i is at (i, ai) and (i, 0). Find two lines, which together with x-axis forms a container, such that the container contains the most water.
	// Input: [1,8,6,2,5,4,8,3,7]
	// Output: 49
	// Time: O(N)
	int maxArea(vector<int>& height) {
		int i = 0, j = (int)height.size() - 1, ans = 0;

		while (i < j) {
			auto hi = height[i], hj = height[j];
			ans = max(ans, min(hi, hj) * (j - i));
			if (hi < hj) {
				++i;
			}
			else if (hi > hj) {
				--j;
			}
			else {
				++i;
				--j;
			}
		}

		return ans;
	}

	// 53. Maximum Subarray
	// Given an integer array nums, find the contiguous subarray (containing at least one number) which has the largest sum and return its sum.
	// Time: O(n)
	int maxSubArray(vector<int>& nums) {
		const int n = (int)nums.size();
		if (n == 0) return 0;
		int ans = nums[0], curmax = ans;
		for (int i = 1; i < n; ++i) {
			curmax = max(curmax + nums[i], nums[i]);
			ans = max(ans, curmax);
		}
		return ans;
	}

	// 55. Jump Game
	// Given an array of non-negative integers, you are initially positioned at the first index of the array.
	// Each element in the array represents your maximum jump length at that position.
	// Determine if you are able to reach the last index.
	bool canJump(vector<int>& nums) {
		size_t n = nums.size();
		int res = 0;
		bool* vd = new bool[n];
		memset(vd, false, n * sizeof(bool));

		for (int i = 0; i < n; ++i) if (nums[i] > 0 && i <= res) {
			res = max(res, nums[i] + i);
		}
		return res >= n - 1;
	}

	int removeDuplicatesTwice(vector<int>& nums) {
		int n = (int)nums.size();
		if (n <= 2) return n;
		int index = 2;

		for (size_t i = index; i < n; ++i) {
			if (nums[i] != nums[index - 2]) nums[index++] = nums[i];
		}
		return index;
	}

	// 169. Majority Element
	// Given an array of size n, find the majority element. The majority element is the element that appears more than n/2 times.
	int majorityElement(vector<int>& nums) {
		// O(n) time, O(1) space;
		//   "5,4,4,2,1,5,5,5,5,2,1"
		//    5 5 4 4 1 1 5 5 5 5 5
		//    1 0 1 0 1 0 1 2 3 2 1

		int majority = 0;
		int count = 0;

		for (int x : nums) {
			if (count == 0) {
				majority = x;
				++count;
			}
			else {
				if (majority == x) {
					++count;
				}
				else {
					--count;
				}
			}
		}
		return majority;
	}

	int threeSumSmaller(vector<int>& nums, int target) {
		if (nums.size() < 3) return 0;
		int res = 0;
		sort(nums.begin(), nums.end());
		for (int i = 0; i < nums.size() - 2; ++i) {
			int left = i + 1, right = (int)nums.size() - 1;
			while (left < right) {
				if (nums[i] + nums[left] + nums[right] < target) {
					res += right - left;
					++left;
				}
				else {
					--right;
				}
			}
		}
		return res;
	}

	// 45. Jump Game II [H?]
	// Given an array of non-negative integers, you are initially positioned at the first index of the array.
	// Each element in the array represents your maximum jump length at that position.
	// Your goal is to reach the last index in the minimum number of jumps.
	/*
	Input: [2,3,1,1,4]
	Output: 2
	Explanation: The minimum number of jumps to reach the last index is 2.
    Jump 1 step from index 0 to 1, then 3 steps to the last index.
	*/
	int jump(vector<int>& nums) {
		const size_t n = nums.size();
		int steps = 0;
		int left = 0, right = 0;
		if (n == 1) return 0;
		while (left <= right) {
			++steps;
			const int prev_right = right;
			for (int i = left; i <= prev_right; ++i) {
				int new_right = i + nums[i];
				if (new_right >= n - 1) return steps;
				if (new_right > right) right = new_right;
			}
			left = prev_right + 1;
		}
		return 0;
	}

	// 76. Minimum Window Substring [H]
	// Given a string S and a string T, find the minimum window in S which will contain all the characters in T in complexity O(n).
	// Input: S = "ADOBECODEBANC", T = "ABC"
	// Output: "BANC"
	string minWindow(string s, string t) {
		int m = (int)s.size(), n = (int)t.size();

		int MAX_CHAR = 256;
		vector<int> t_count(MAX_CHAR);
		vector<int> s_count(MAX_CHAR);
		int total_match = 0;
		int min_match = INT_MAX;
		string ans = "";

		for (int i = 0; i < n; ++i) {
			++t_count[t[i]];
		}

		int l = 0, r = 0;
		bool go_forward = true;

		// ADOBECODEBANC
		while (r < m && l <= r) {
			if (go_forward) {
				++s_count[s[r]];
				if (t_count[s[r]] > 0 && s_count[s[r]] <= t_count[s[r]]) {
					++total_match;
				}
			}

			if (total_match >= n) {
				if (r - l + 1 < min_match) {
					min_match = r - l + 1;
					ans = s.substr(l, r - l + 1);
					//cout << ans << endl; 
				}
				--s_count[s[l]];
				if (t_count[s[l]] > 0 && s_count[s[l]] < t_count[s[l]]) {
					--total_match;
				}
				++l;
				go_forward = false;
			}
			else {
				++r;
				go_forward = true;
			}
		}
		return ans;
	}

	// 904. Fruit Into Baskets [E]
	// You have two baskets, and each basket can carry any quantity of fruit, but you want each basket to only carry one type of fruit each.
	// What is the total amount of fruit you can collect with this procedure?
	int totalFruit(vector<int>& tree) {
		const int n = (int)tree.size();
		if (n <= 2)
			return n;

		int l = 0, r = 0;
		int A = tree[0], a = 1, B = -1, b = 0;
		int res = 1;

		while (r < n - 1) {
			int C = tree[++r];

			if (A == C)
				++a;
			else
			if (B == C)
				++b;
			else
			if (b == 0) {
				B = C;
				++b;
			}
			else
			if (a == 0) {
				A = C;
				++a;
			}
			else {
				while (a > 0 && b > 0) {
					if (tree[l++] == A)
						--a;
					else
						--b;
				}
				--r;
				continue;
			}
			res = max(res, r - l + 1);
		}
		return res;
	}
}

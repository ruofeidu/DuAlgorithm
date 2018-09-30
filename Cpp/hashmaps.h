#pragma once
#include "common.h"

namespace Hashmaps {
	vector<size_t> twoSum(vector<int>& nums, int target) {
		unordered_map<int, size_t> dict;
		vector<size_t> res;
		for (size_t i = 0; i < nums.size(); ++i) {
			int cur = nums[i];
			if (dict.find(cur) == dict.end()) {
				dict[target - cur] = i;
			}
			else {
				res.emplace_back(dict[nums[i]]);
				res.emplace_back(i);
				break;
			}
		}
		return res;
	}

	// 316. Remove Duplicate Letters
	// Given a string which contains only lowercase letters, remove duplicate letters so that every letter appear once and only once. You must make sure your result is the smallest in lexicographical order among all possible results.
	/*
		Given "bcabc"
		Return "abc"

		Given "cbacdcbc"
		Return "acdb"
	*/
	string removeDuplicateLetters(string s) {
		int m[256] = { 0 }, visited[256] = { 0 };
		string res = "0";
		for (auto a : s) ++m[a];
		for (auto a : s) {
			--m[a];
			if (visited[a]) continue;
			while (a < res.back() && m[res.back()]) {
				visited[res.back()] = 0;
				res.pop_back();
			}
			res += a;
			visited[a] = 1;
		}
		return res.substr(1);
	}

	// 217. Contains Duplicate
	// Given an array of integers, find if the array contains any duplicates. 
	// Your function should return true if any value appears at least twice in the array, 
	// and it should return false if every element is distinct.
	bool containsDuplicate(vector<int>& nums) {
		unordered_map<int, bool> m;
		for (int x : nums) {
			if (m.find(x) != m.end()) return true;
			m[x] = true;
		}
		return false;
	}

	// 219. Contains Duplicate II
	// Given an array of integers and an integer k, find out whether there are two distinct indices i and j in the array such that nums[i] = nums[j] and the difference between i and j is at most k.
	bool containsNearbyDuplicate(vector<int>& nums, int k) {
		unordered_map<int, int> m;
		int i = 0;
		for (int x : nums) {
			if (m.find(x) != m.end() && i - m[x] <= k) return true; else m[x] = i;
			++i;
		}
		return false;
	}

	// 325. Maximum Size Subarray Sum Equals k
	// Given an array nums and a target value k, find the maximum length of a subarray that sums to k.
	int maxSubArrayLen(vector<int>& nums, int k) {
		int n = (int)nums.size();
		if (n == 0) return 0;

		unordered_map<int, int> m;
		int sum = 0, res = 0;

		for (int i = 0; i < n; ++i) {
			sum += nums[i];
			if (sum == k) res = max(res, i + 1);
			if (m.find(sum - k) != m.end()) {
				res = max(res, i - m[sum - k]);
			}
			if (m.find(sum) == m.end()) {
				m[sum] = i;
			}
		}
		return res;
	}

	// 349. Intersection of Two Arrays [E]
	// Given two arrays, write a function to compute their intersection.
	// Time:  O(m + n)
	// Space: O(min(m, n))
	// See log time and O(1) space in Binary Search
	vector<int> intersection(vector<int>& nums1, vector<int>& nums2) {
		if (nums1.size() > nums2.size()) {
			return intersection(nums2, nums1);
		}

		unordered_set<int> s{ nums1.cbegin(), nums1.cend() };
		vector<int> res;

		for (const auto x : nums2) {
			if (s.count(x)) {
				res.emplace_back(x);
				s.erase(x);
			}
		}
		return res;
	}

	// 525. Contiguous Array [M]
	// Time: O(N)
	// Space: O(N)
	// nums  0, 1, 1, 1, 0, 0, 0
	// dict 0:2, -1:0, 1:2, 2:3, 
	int findMaxLength(vector<int>& nums) {
		int res = 0, cnt = 0, n = (int)nums.size();
		unordered_map<int, int> dict{ { 0, -1 } };
		for (int i = 0; i < n; ++i) {
			cnt += (nums[i] << 1) - 1;
			if (dict.count(cnt)) {
				res = max(res, i - dict[cnt]);
			}
			else {
				dict[cnt] = i;
			}
		}
		return res;
	}

	// 554. Brick Wall
	// Given a block of walls with bricks of the same height but different width.
	// Draw a vertical line from the top to the bottom and cross the least bricks.
	int leastBricks(vector<vector<int>>& wall) {
		const int n = (int)wall.size();
		unordered_map<int, int> d;
		int res = n;

		for (const auto &w : wall) {
			const int m = (int)w.size();
			int c = 0;
			for (int i = 0; i < m - 1; ++i) {
				c += w[i];
				d[c] += 1;
				res = min(res, n - d[c]);
			}
		}

		return res;
	}

	// 340. Longest Substring with At Most K Distinct Characters
	// Given a string, find the length of the longest substring T that contains at most k distinct characters.
	int lengthOfLongestSubstringKDistinct(string s, int k) {
		int res = 0, left = 0;
		unordered_map<char, int> m;
		for (int i = 0; i < s.size(); ++i) {
			++m[s[i]];
			while (m.size() > k) {
				if (--m[s[left]] == 0) m.erase(s[left]);
				++left;
			}
			res = max(res, i - left + 1);
		}
		return res;
	}


}
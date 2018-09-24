#pragma once
#include "common.h"

namespace Hashmaps {
	vector<int> twoSum(vector<int>& nums, int target) {
		unordered_map<int, size_t> map;
		vector<int> res;
		for (size_t i = 0; i < nums.size(); ++i) {
			int cur = nums[i];
			if (map.find(cur) == map.end()) {
				map[target - cur] = i;
			}
			else {
				res.emplace_back(map[nums[i]]);
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

	// 220. Contains Duplicate III
	// or use multiset
	// Given an array of integers, find out whether there are two distinct indices i and j in the array such that the difference between nums[i] and nums[j] is at most t and the difference between i and j is at most k.
	bool containsNearbyAlmostDuplicate(vector<int>& nums, int k, int t) {
		map<int, int> m;
		int j = 0;
		for (int i = 0; i < nums.size(); ++i) {
			if (i - j > k && m[nums[j]] == j) m.erase(nums[j++]);
			auto a = m.lower_bound(nums[i] - t);
			if (a != m.end() && abs(a->first - nums[i]) <= t) return true;
			m[nums[i]] = i;
		}
		return false;
	}

	/**
	 * 325. Maximum Size Subarray Sum Equals k
	 * Given an array nums and a target value k, find the maximum length of a subarray that sums to k.
	 * If there isn't one, return 0 instead.
	 */
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
}
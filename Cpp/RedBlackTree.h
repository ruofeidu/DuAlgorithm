#pragma once
#include "common.h"

namespace map {
	// 220. Contains Duplicate III
	// Given an array of integers, find out whether there are two distinct indices i and j in the array such that the difference between nums[i] and nums[j] is at most t and the difference between i and j is at most k.
	// or use multiset
	bool containsNearbyAlmostDuplicate(vector<int>& nums, int k, int t) {
		std::map<int, int> m;
		int j = 0;
		for (int i = 0; i < (int)nums.size(); ++i) {
			if (i - j > k && m[nums[j]] == j)
				m.erase(nums[j++]);
			auto a = m.lower_bound(nums[i] - t);
			if (a != m.end() && abs(a->first - nums[i]) <= t)
				return true;
			m[nums[i]] = i;
		}
		return false;
	}
}
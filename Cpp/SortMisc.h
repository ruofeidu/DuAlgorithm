#pragma once
#include "common.h"
namespace SortMisc {

	// Given an unsorted array nums, reorder it in-place such that nums[0] <= nums[1] >= nums[2] <= nums[3]...
	// O(n) time and O(1) space
	void wiggleSort(vector<int> &nums) {
		if (nums.size() <= 1) return;
		for (int i = 1; i < nums.size(); ++i) {
			if ((i % 2 == 1 && nums[i] < nums[i - 1]) || (i % 2 == 0 && nums[i] > nums[i - 1])) {
				swap(nums[i], nums[i - 1]);
			}
		}
	}

	// 324. Wiggle Sort II
	// Given an unsorted array nums, reorder it such that nums[0] < nums[1] > nums[2] < nums[3]....
	// O(n) time and O(1) space
	void wiggleSortStrict(vector<int>& nums) {
#define A(i) nums[(1 + 2 * i) % (n | 1)]
		int n = (int)nums.size(), i = 0, j = 0, k = n - 1;
		auto midptr = nums.begin() + n / 2;
		nth_element(nums.begin(), midptr, nums.end());
		int mid = *midptr;
		while (j <= k) {
			if (A(j) > mid) swap(A(i++), A(j++));
			else if (A(j) < mid) swap(A(j), A(k--));
			else ++j;
		}
	}

	// Time and Space: O(N)
	string frequencySort(string &s) {
		unordered_map<char, int> freq;
		for (const auto& c : s) {
			++freq[c];
		}

		const auto n = s.size();
		vector<string> counts(n + 1);
		for (const auto& kvp : freq) {
			counts[kvp.second].push_back(kvp.first);
		}
		string result;
		for (int count = n - 1; n >= 0; --count) {
			for (const auto& c : counts[count]) {
				result += string(count, c);
			}
		}
		return result;
	}
}
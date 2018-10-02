#pragma once
#include "common.h"

namespace ArrayInPlace {
	// 26. Remove Duplicates from Sorted Array [E]
	// Given a sorted array nums, remove the duplicates in-place such that each element appear only once and return the new length.
	int removeDuplicates(vector<int>& nums) {
		if (nums.empty())
			return 0;
		int index = 0;
		for (int i = 0; i < nums.size(); ++i) {
			if (nums[index] != nums[i])
				nums[++index] = nums[i];
		}
		return index + 1;
	}

	// 80. Remove Duplicates from Sorted Array II
	// Given a sorted array nums, remove the duplicates in-place such that duplicates appeared at most twice and return the new length.
	// Do not allocate extra space for another array, you must do this by modifying the input array in - place with O(1) extra memory.
	int removeDuplicates2(vector<int>& nums) {
		auto n = (int)nums.size();
		if (n <= 2) return n;
		int index = 2;

		for (size_t i = index; i < n; ++i) {
			if (nums[i] != nums[index - 2]) nums[index++] = nums[i];
		}
		return index;
	}

	// 27. Remove Element [E]
	// Given an array nums and a value val, remove all instances of that value in-place and return the new length.
	int removeElement(vector<int>& nums, int val) {
		if (nums.empty())
			return 0;
		int index = 0;
		for (int i = 0; i < nums.size(); ++i) {
			if (nums[i] != val)
				nums[index++] = nums[i];
		}
		return index;
	}

	// 41. First Missing Positive [H]
	// Given an unsorted integer array, find the smallest missing positive integer.
	/*
	Input: [7,8,9,11,12]
	Output: 1

	Input: [1,2,0]
	Output: 3

	Input: [3,4,-1,1]
	Output: 2
	*/
	// Time: O(N)
	int firstMissingPositive(vector<int>& nums) {
		const int n = (int)nums.size();
		for (int i = 0; i < n; ++i) {
			while (nums[i] != i + 1) {
				if (nums[i] <= 0 || nums[i] > n || nums[i] == nums[nums[i] - 1])
					break;
				swap(nums[i], nums[nums[i] - 1]);
			}
		}

		for (int i = 0; i < n; ++i)
			if (nums[i] != (i + 1))
				return i + 1;
		return n + 1;
	}
}
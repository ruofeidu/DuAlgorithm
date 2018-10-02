#pragma once
#include "common.h"

namespace CountSort {
	// 75. Sort Colors [M]
	// Given an array with n objects colored red, white or blue, sort them in-place so that objects of the same color are adjacent, with the colors in the order red, white and blue. (0, 1, 2)
	void sortColors(vector<int>& nums) {
		int red = 0, blue = nums.size() - 1;
		for (int i = 0; i <= blue; ++i) {
			if (nums[i] == 0) {
				swap(nums[i], nums[red++]);
			}
			else
				if (nums[i] == 2) {
					swap(nums[i--], nums[blue--]);
				}
		}
	}
}
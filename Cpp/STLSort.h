#pragma once
#include "common.h"

namespace STLSort {
	/*
		75. Sort Colors
		Given an array with n objects colored red, white or blue, sort them so that objects of the same color are adjacent, with the colors in the order red, white and blue.
		Here, we will use the integers 0, 1, and 2 to represent the color red, white, and blue respectively.
		Note:
		You are not suppose to use the library's sort function for this problem.
	*/
	void sortColorsSTL(vector<int>& nums) {
		partition(
			partition(nums.begin(), nums.end(), bind1st(equal_to<int>(), 0)),
			nums.end(), bind1st(equal_to<int>(), 1)
			);
	}
}
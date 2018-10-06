#pragma once

namespace MathMisc {
	// 258. Add Digits
	// Given a non-negative integer num, repeatedly add all its digits until the result has only one digit.
	// Solution: Digital root https://en.wikipedia.org/wiki/Digital_root
	// The digital root (also repeated digital sum) of a non-negative integer is the (single digit) value obtained by an iterative process of summing digits, on each iteration using the result from the previous iteration to compute a digit sum. The process continues until a single-digit number is reached.
	int addDigits(int num) {
		return num > 0 ? (num - 1) % 9 + 1 : 0;
		// 10 = 19 = 1
		// 110 = 58 = 47 = 38 = 29 = 20 = 11 = 2
		// 99999 = 45 = 9
		// 99999999996 = 96 = 15 = 6
	}

	// 268. Missing Number
	// Given an array containing n distinct numbers taken from 0, 1, 2, ..., n, find the one that is missing from the array.
	int missingNumber(vector<int>& nums) {
		int n = (int)nums.size();
		int s = accumulate(nums.begin(), nums.end(), 0);
		return n * (n + 1) / 2 - s;
	}
}
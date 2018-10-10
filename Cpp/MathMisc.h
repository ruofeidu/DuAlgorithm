#pragma once
#include "common.h"

class MathMisc {
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

	// 319. Bulb Switcher [M]
	// There are n bulbs that are initially off. You first turn on all the bulbs. Then, you turn off every second bulb. On the third round, you toggle every third bulb (turning on if it's off or turning off if it's on). For the i-th round, you toggle every i bulb. For the n-th round, you only toggle the last bulb. Find how many bulbs are on after n rounds.
	// Find out how many bulbs are operated for odd times
	// 
	int bulbSwitch(int n) {
		return (int)(sqrt(n));
	}


	// 321. Create Maximum Number [H]
	// Given two arrays of length m and n with digits 0-9 representing two numbers. Create the maximum number of length k <= m + n from digits of the two. The relative order of the digits from the same array must be preserved. Return an array of the k digits. Note: You should try to optimize your time and space complexity.
	using bigint = vector<int>;
	bigint maxNumber(bigint& nums1, bigint& nums2, int k) {
		int n = (int)nums1.size(), m = (int)nums2.size();
		bigint ans;
		for (int i = max(0, k - m); i <= min(k, n); ++i) {
			ans = max(ans, mergeVector(maxVector(nums1, i), maxVector(nums2, k - i)));
		}
		return ans;
	}

	bigint maxVector(bigint& nums, int reserved) {
		int drop = (int)nums.size() - reserved;
		bigint res;
		// 9 6
		for (int x : nums) {
			while (drop && res.size() && res.back() < x) {
				res.pop_back();
				--drop;
			}
			res.push_back(x);
		}
		res.resize(reserved);
		return res;
	}


	bigint mergeVector(bigint a, bigint b) {
		bigint res;
		while (a.size() + b.size()) {
			bigint& c = a > b ? a : b;
			res.push_back(c[0]);
			c.erase(c.begin());
		}
		return res;
	}
};

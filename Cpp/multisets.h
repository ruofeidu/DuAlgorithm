#pragma once
#include "common.h"

/**
 * Multiset is an ordered ascending Red-Black tree. In contrast to set, it allows duplicated elemented.
 * lower_bound(x) returns the first element that >= x
 **/
namespace Multisets{
	// 327. Count of Range Sum
	// Given an integer array nums, return the number of range sums that lie in [lower, upper] inclusive.
	// a:	1, 2, 3, 4, 5
	// sum:	1, 3, 6, 10, 15
	// range:	7-10
	// result:	2 + 1 = 3
	// Note sum may exceed int
	// Time: O(N log N)
	// See mergesort.h for another solution.
	int countRangeSum(vector<int>& nums, int lower, int upper) {
		int res = 0;
		long long sum = 0; 
		multiset<long long> sums;
		sums.insert(0);
		for (size_t i = 0; i < nums.size(); ++i) {
			sum += nums[i];
			res += (int)distance(sums.lower_bound(sum - upper), sums.upper_bound(sum - lower));
			sums.insert(sum);
		}
		return res;
	}
}
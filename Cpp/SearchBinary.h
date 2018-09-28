#pragma once
#include "common.h"

class BinarySearch {
	// search key, return the first value >= key
	int binarySearch(vector<int>& A, int l, int r, int key) {
		while (l <= r) {
			int p = (l + r) >> 1;
			if (key == A[p])
				return p;
			if (key > A[p]) {
				l = p + 1;
			}
			else {
				r = p - 1;
			}
		}
		return l;
	}

	// Find peak element in an array
	int peakIndexInMountainArray(vector<int>& A) {
		int l = 0, r = (int)A.size();
		while (l < r) {
			int p = (l + r) >> 1;
			if (A[p] > A[p + 1]) {
				r = p;
			}
			else {
				l = p + 1;
			}
		}
		return l;
	}

	// 719. Given an integer array, return the k-th smallest distance among all the pairs. The distance of a pair (A, B) is defined as the absolute difference between A and B.
	// O(N log N)
	// http://blog.ruofeidu.com/719-find-k-th-smallest-pair-distance/
	int smallestDistancePair(vector<int>& nums, int k) {
		sort(nums.begin(), nums.end());
		int l = 0, r = nums[nums.size() - 1] - nums[0];
		while (r > l) {
			int mid = (l + r) >> 1;
			if (count(nums, mid) < k) {
				l = mid + 1;
			}
			else {
				r = mid;
			}
		}
		return r;
	}

	int count(vector<int>& nums, int mid) {
		int ans = 0, j = 0;
		for (int i = 1; i < nums.size(); ++i) {
			while (j < i && nums[i] - nums[j] > mid) ++j;
			ans += i - j;
		}
		return ans;
	}
};

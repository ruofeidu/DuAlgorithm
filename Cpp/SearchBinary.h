#pragma once
#include "common.h"

// lower_bound: returns an iterator pointing to the first element in the range [first, last), which is greater or equal to) val, in log2(last - first)
// upper_bound: returns an iterator pointing to the first element in the range [first,last) which compares greater than val.
class BinarySearch {
	// Search key, return the first value >= key [E]
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

	// 162. Find peak element in an array [E]
	int findPeakElement(vector<int>& nums) {
		int n = (int)nums.size();
		if (n <= 1) return 0;
		int l = 0, r = n - 1;
		while (l < r) {
			int mid = (l + r) >> 1;
			if (nums[mid] < nums[mid + 1]) {
				l = mid + 1;
			}
			else {
				r = mid;
			}
		}
		return r;
	}

	// 852. Peak Index in a Mountain Array [E]
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


	// 719. Find K-th Smallest Pair Distance [H]
	// Given an integer array, return the k-th smallest distance among all the pairs. The distance of a pair (A, B) is defined as the absolute difference between A and B.
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

	// 349. Intersection of Two Arrays
	// Given two arrays, write a function to compute their intersection.
	// Time:  O(max(m, n) * log(max(m, n)))
	// Space: O(1)
	// See hash map for linear time solution 
	vector<int> intersection(vector<int>& nums1, vector<int>& nums2) {
		// Time:  O(max(m, n) * log(max(m, n)))
		// Space: O(1)
		// Binary search solution.

		if (nums1.size() > nums2.size()) {
			return intersection(nums2, nums1);
		}

		sort(nums1.begin(), nums1.end());
		sort(nums2.begin(), nums2.end());

		vector<int> result;
		auto it = nums2.cbegin();
		for (const auto& x : nums1) {
			it = lower_bound(it, nums2.cend(), x);
			if (it != nums2.end() && *it == x) {
				result.emplace_back(*it);
				it = upper_bound(it, nums2.cend(), x);
			}
		}

		return result;
	}
};

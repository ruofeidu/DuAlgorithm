#pragma once
#include "common.h"

/**
 * Multiset is an ordered ascending Red-Black tree. In contrast to set, it allows duplicated elemented.
 * lower_bound(x) returns the first element that >= x
 **/
namespace Multisets{
	// 327. Count of Range Sum [H]
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

	// 218. The Skyline Problem [H]
	// A city's skyline is the outer contour of the silhouette formed by all the buildings in that city when viewed from a distance. Now suppose you are given the locations and height of all the buildings as shown on a cityscape photo, write a program to output the skyline formed by these buildings collectively.
	vector<pair<int, int>> getSkyline(vector<vector<int>>& buildings) {
		vector<pair<int, int>> h, res;
		multiset<int> m;
		int pre = 0, cur = 0;
		for (auto &a : buildings) {
			h.push_back({ a[0], -a[2] });
			h.push_back({ a[1], a[2] });
		}
		sort(h.begin(), h.end());
		m.insert(0);
		for (auto &a : h) {
			if (a.second < 0) m.insert(-a.second);
			else m.erase(m.find(a.second));
			cur = *m.rbegin();
			if (cur != pre) {
				res.push_back({ a.first, cur });
				pre = cur;
			}
		}
		return res;
	}

	// 220. Contains Duplicate III [M]
	// Given an array of integers, find out whether there are two distinct indices i and j in the array such that the difference between nums[i] and nums[j] is at most t and the difference between i and j is at most k.
	// O(n log k), or use hashing
	bool containsNearbyAlmostDuplicate(vector<int>& nums, int k, int t) {
		multiset<long long> BST; // a BST with size k
		const int n = (int)nums.size();
		for (int i = 0; i < n; ++i) {
			if ((int)BST.size() == k + 1) {
				BST.erase(nums[i - k - 1]);
			}
			auto low = BST.lower_bound(nums[i] - t); // the first element that >= nums[i] - t 
			if (low != BST.end() && abs(*low - nums[i]) <= t) return true;
			BST.insert(nums[i]);
		}
		return false;
	}
}
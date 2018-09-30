#pragma once
#include "common.h"

namespace Scanning {
	// 849. Maximize Distance to Closest Person
	int maxDistToClosest(vector<int>& seats) {
		int res = 0, cnt = 0;
		bool ends = true;
		for (const auto &seat : seats) {
			if (seat == 0) {
				cnt += 1;
			}
			else {
				if (!ends) {
					cnt = (cnt + 1) >> 1;
				}
				res = max(res, cnt);
				cnt = 0;
				ends = false;
			}
		}
		return max(res, cnt);
	}

	int maxArea(vector<int>& height)
	{
		int i = 0, j = (int)height.size() - 1, ans = 0;

		while (i < j) {
			auto hi = height[i], hj = height[j];
			ans = max(ans, min(hi, hj) * (j - i));
			if (hi < hj) {
				++i;
			}
			else if (hi > hj) {
				--j;
			}
			else {
				++i;
				--j;
			}
		}

		return ans;
	}

	int removeDuplicatesTwice(vector<int>& nums) {
		int n = (int)nums.size();
		if (n <= 2) return n;
		int index = 2;

		for (size_t i = index; i < n; ++i) {
			if (nums[i] != nums[index - 2]) nums[index++] = nums[i];
		}
		return index;
	}

	// 169. Majority Element
	// Given an array of size n, find the majority element. The majority element is the element that appears more than n/2 times.
	int majorityElement(vector<int>& nums) {
		// O(n) time, O(1) space;
		//   "5,4,4,2,1,5,5,5,5,2,1"
		//    5 5 4 4 1 1 5 5 5 5 5
		//    1 0 1 0 1 0 1 2 3 2 1

		int majority = 0;
		int count = 0;

		for (int x : nums) {
			if (count == 0) {
				majority = x;
				++count;
			}
			else {
				if (majority == x) {
					++count;
				}
				else {
					--count;
				}
			}
		}
		return majority;
	}

	int threeSumSmaller(vector<int>& nums, int target) {
		if (nums.size() < 3) return 0;
		int res = 0;
		sort(nums.begin(), nums.end());
		for (int i = 0; i < nums.size() - 2; ++i) {
			int left = i + 1, right = nums.size() - 1;
			while (left < right) {
				if (nums[i] + nums[left] + nums[right] < target) {
					res += right - left;
					++left;
				}
				else {
					--right;
				}
			}
		}
		return res;
	}
}

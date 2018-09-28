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

	int trap(vector<int>& height)
	{
		const int n = (int)height.size();
		if (n < 3) return 0;
		vector<int> lmax(n, 0);
		vector<int> rmax(n, 0);
		lmax[0] = height[0];
		rmax[n - 1] = height[n - 1];
		for (int i = 1; i < n; ++i) {
			lmax[i] = max(lmax[i - 1], height[i]);
		}

		for (int i = n - 2; i >= 0; --i) {
			rmax[i] = max(rmax[i + 1], height[i]);
		}

		int ans = 0;
		for (int i = 1; i < n - 1; ++i) {
			ans += min(lmax[i], rmax[i]) - height[i];
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
}

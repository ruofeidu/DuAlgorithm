#pragma once
#include "common.h"

namespace Hashmaps {
	vector<int> twoSum(vector<int>& nums, int target) {
		unordered_map<int, size_t> map;
		vector<int> res;
		for (size_t i = 0; i < nums.size(); ++i) {
			int cur = nums[i];
			if (map.find(cur) == map.end()) {
				map[target - cur] = i;
			}
			else {
				res.emplace_back(map[nums[i]]);
				res.emplace_back(i);
				break;
			}
		}
		return res;
	}
}
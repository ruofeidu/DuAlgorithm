#pragma once
#include "common.h"

namespace Scanning {
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
}

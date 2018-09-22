#pragma once
#include "common.h"

namespace BinarySearch {
	int peakIndexInMountainArray(vector<int>& A) {
		int l = 0, r = A.size();
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
}
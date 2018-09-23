#pragma once
#include "common.h"

namespace BinarySearch {
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

	// find peak element in an array
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
}
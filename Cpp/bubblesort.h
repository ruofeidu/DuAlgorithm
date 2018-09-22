#pragma once
#include "common.h"

// Bubble sort 
// While not sorted, scan and float the largest to the end
// Time: O(N^2)
void bubble_sort(vector<int> &a, int l, int r) {
	bool sorted = false;
	const auto n = a.size();
	for (size_t i = 0; i < n; ++i) {
		if (sorted)
			break;
		sorted = true;
		for (size_t j = 0; j < n - 1 - i; ++j) {
			if (a[j] > a[j + 1]) {
				swap(a[j], a[1]);
				sorted = false;
			}
		}
	}
}

#pragma once
#include "common.h"

// sort in C++ uses quicksort for large N
// when N < 16, use insersion sort, since the data is mostly sorted
// when depth > T, use heap sort
namespace QuickSort {
	// http://blog.ruofeidu.com/quicksort-in-c/
	void qsort(int *a, int n, int l, int r) {
		int i = l, j = r, mid = a[(l + r) >> 1];
		while (i <= j) {
			while (a[i] < mid) ++i;
			while (a[j] > mid) --j;
			if (i <= j) {
				swap(a[i], a[j]);
				++i;
				--j;
			}
		}
		if (l < j) qsort(a, n, l, j);
		if (i < r) qsort(a, n, i, r);
	}

	// find the kth element in C
	void Kth(int *a, int l, int r, int k)
	{
		int i = l, j = r, mid = a[(i + j) >> 1];
		while (i <= j) {
			while (a[i] < mid) ++i;
			while (a[j] > mid) --j;
			if (i <= j) {
				swap(a[i], a[j]);
				++i;
				--j;
			}
		}
		if (k >= i && k <= r) Kth(a, i, r, k);
		if (k >= l && k <= j) Kth(a, l, j, k);
	}
}
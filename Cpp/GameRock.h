#pragma once
#include "common.h"

namespace RockGame {
	// POJ 1063
	// n rocks, first picker can pick arbitrary, next picker cannot pick 2 times than previous: the one who pick the last wins
	const int N = 51;
	int a[N];

	bool canFirstWin(int n) {
		a[0] = 2;
		a[1] = 3;
		if (n == 2 || n == 3)
			return false;
		for (int i = 2; i < N; ++i) {
			a[i] = a[i - 1] + a[i - 2];
			if (a[i] == n)
				return false;
		}
		return true;
	}
};

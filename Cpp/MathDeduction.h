#pragma once
#include "common.h"

namespace MathDeduction {
	// 119. Pascal's Triangle II
	// Given a non-negative index k where k <= 33, return the kth index row of the Pascal's triangle.
	// Note that the row index starts from 0.
	vector<int> getRow(int rowIndex) {
		int& N = rowIndex;
		vector<int> ans(N + 1);
		ans[0] = 1;
		for (int i = 0; i < N + 1; ++i) {
			int prev = 1;
			for (int j = 1; j <= i; ++j) {
				const int t = ans[j];
				ans[j] += prev;
				prev = t;
			}
		}
		return ans;
	}


}
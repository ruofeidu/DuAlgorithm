#pragma once
#include "common.h"
namespace Greedy {
	int carFleet(int target, vector<int>& position, vector<int>& speed) {
		using PosTime = pair<int, double>;
		vector<PosTime> cars;
		const auto N = position.size();
		for (int i = 0; i < N; ++i) {
			cars.emplace_back(position[i], (double)(target - position[i]) / speed[i]);
		}
		sort(cars.begin(), cars.end(), [](const PosTime& a, const PosTime &b) {
			return a.first == b.first ? a.second < b.second : a.first < b.first;
		});
		int res = 0;
		double cur = 0;
		for (int i = N - 1; i >= 0; --i) {
			if (cars[i].second > cur) {
				cur = cars[i].second;
				++res;
			}
		}
		return res;
	}
}
#pragma once
#include <random>
#include "common.h"

namespace Randoms {
	std::random_device rd;
	std::mt19937 mt(rd());
	std::uniform_real_distribution<double> uniform_random(0.0, 1.0);

	// Use as sample = uniform_random(mt);
	int getRandom(int low, int high) {
		auto sample = uniform_random(mt);
		return (int)floor(sample * (high - low + 1)) + low;
	}

	// Time: O(N), scan and swap a[i] with a[random(i, n - 1)].
	void shuffle(vector<int> &a) {
		for (int i = 0; i < a.size(); ++i) {
			int id = getRandom(i, (int)a.size() - 1);
			swap(a[i], a[id]);
		}
	}
}

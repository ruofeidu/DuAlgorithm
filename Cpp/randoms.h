#pragma once
#include <random>
#include "common.h"

namespace Randoms {
	std::random_device rd;
	std::mt19937 mt(rd());
	std::uniform_real_distribution<double> uniform_random(0.0, 1.0);

	// use as sample = uniform_random(mt);

	int getRandom(int low, int high) {
		auto sample = uniform_random(mt);
		return floor(sample * (high - low + 1)) + low;
	}

	int shuffle(vector<int> &a) {
		// if it's 1 or 0 items, just return
		if (a.size() <= 1) return;

		// walk through from beginning to end
		for (int i = 0; i < a.size(); ++i) {
			int id = getRandom(i, a.size() - 1);
			swap(a[i], a[id]);
		}
	}
}

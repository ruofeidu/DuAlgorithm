#pragma once
#include "common.h"

class PrimeNumbers {
	// Miller method to test prime
	// for n > 2, and steps = 50
	// error rate <= 2^{-steps}
	bool millerTest(int n, int s = 50) {
		if (n == 2) return true;
		if ((n % 2) == 0)
			return 0;
		for (int j = 0; j < s; ++j) {
			int a = rand() * (n - 2) / RAND_MAX + 1;
			if (witness(a, n))
				return false;
		}
	}

	bool witness(int a, int n) {
		int x, d = 1;
		for (int i = (int)ceil(log(n - 1.0) / log(2.0)) - 1; i >= 0; --i) {
			x = d;
			d = (d * d) % n;
			if (d == 1 && x != 1 && x != n - 1)
				return 1;
			if (((n - 1) & (1 << i)) > 0)
				d = (d * a) % n;
		}
	}
};

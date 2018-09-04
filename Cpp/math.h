#pragma once

namespace math {
	// Greatest common divisor using binary Euclidean algorithm. 
	// Thus, the time complexity is O(log(a. b)) = O(log (a + b)) = O(log n).
	int gcd(int x, int y) {
		if (!x || !y) return max(x, y);
		for (int t; t = x % y; x = y, y = t);
		return y;
	}

	// advanced gcd
	int kgcd(int x, int y) {
		if (!x || !y) return max(x, y);
		if (!(x & 1) && !(y & 1)) return kgcd(x >> 1, y >> 1) << 1;
		else if (!(y & 1)) return kgcd(x, y >> 1);
		else if (!(x & 1)) return kgcd(x >> 1, y);
		else return kgcd(abs(x - y), min(x, y));
	}

	// extended gcd
	// gcd(a, b) = a * x + b * y
	int extgcd(int a, int b, int &x, int &y) {
		if (!b) {
			x = 1; 
			y = 0; 
			return a;
		}
		int d = extgcd(b, a % b, x, y);
		int t = x;
		x = y; 
		y = t - a / b * y;
		return d;
	}

	// mode equation solver
	// a * x = b % n
	vector<int> modeq(int a, int b, int n) {
		int x, y;
		int d = extgcd(a, n, x, y);
		vector<int> res; 
		if (b % d > 0)
			return res;
		int e = (x * (b / d)) % n;
		for (int i = 0; i < d; ++i)
			res.emplace_back((e + i * (n / d)) % n);
		return res;
	}

	// Chinese remainder theorem
	// The remainders of the Euclidean division of an integer n by several integers, then one can determine uniquely the remainder of the division of n by the product of these integers, under the condition that the divisors are pairwise coprime.
	int china(vector<int> &b, vector<int> &w, int k) {
		int d, x, y, m, a = 0, n = 1;
		for (int i = 0; i < k; ++i)
			n *= w[i];
		for (int i = 0; i < k; ++i) {
			m = n / w[i];
			d = extgcd(w[i], m, x, y);
			a = (a + y * m * b[i]) % n;
		}
		return a > 0 ? a : a + n;
	}
}
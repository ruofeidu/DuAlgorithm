#pragma once
#include "common.h"

namespace Mods{
	// GCD: Greatest common divisor using binary Euclidean algorithm. 
	// Thus, the time complexity is O(log(a.b)) = O(log (a + b)) = O(log n).
	int gcd(int x, int y) {
		if (!x || !y) return max(x, y);
		for (int t; t = x % y; x = y, y = t);
		return y;
	}

	// Bit-level GCD
	int kgcd(int x, int y) {
		if (!x || !y) return max(x, y);
		if (!(x & 1) && !(y & 1)) return kgcd(x >> 1, y >> 1) << 1;
		else if (!(y & 1)) return kgcd(x, y >> 1);
		else if (!(x & 1)) return kgcd(x >> 1, y);
		else return kgcd(abs(x - y), min(x, y));
	}

	// Extended GCD
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

	// LCM: Lowest Common Multiple
	int lcm(int x, int y) {
		return x * y == 0 ? 0 : x * y / gcd(x, y);
	}

	// Modular exponentiation: (a ^ b) % n
	// https://en.wikipedia.org/wiki/Modular_exponentiation
	int modExp(int a, int b, int n) {
		int res = 1, y = a;
		while (b != 0) {
			if (b & 1)
				res *= y % n;
			y = y * y % n;
			b >>= 1;
		}
		return res;
	}

	// Modular multiplication (x * y) % n
	long long mod_pro(long long x, long long y, long long n) {
		long long res = 0, tmp = x % n;
		while (y) {
			if (y & 0x1)
				if ((res += tmp) > n)
					res -= n;
			if ((tmp <<= 1) > n)
				tmp -= n;
			y >>= 1;
		}
		return res;
	}

	// Modular exponentiation: (a ^ b) % n
	long long mod_exp(long long a, long long b, long long c) {
		long long res = 1;
		while (b) {
			if (b & 0x1)
				res = mod_pro(res, a, c);
			a = mod_pro(a, a, c);
			b >>= 1;
		}
		return res;
	}

	// Modular equation solver: a * x = b % n
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

	// 326. Power of Three
	bool isPowerOfThree(int n) {
		return (n > 0 && 1162261467 % n == 0);
		return (n > 0 && int(log10(n) / log10(3)) - log10(n) / log10(3) == 0);
	}

	// 263. Ugly numbers
	// Ugly numbers are positive numbers whose prime factors only include 2, 3, 5. 
	// For example, 6, 8 are ugly while 14 is not ugly since it includes another prime factor 7.
	bool isUgly(int num) {
		if (num <= 0) return false;
		while (num % 2 == 0) num /= 2;
		while (num % 3 == 0) num /= 3;
		while (num % 5 == 0) num /= 5;
		return num == 1;
	}

	// 264. Ugly Number II
	// Find the nth ugly number
	// For example, 1, 2, 3, 4, 5, 6, 8, 9, 10, 12 is the sequence of the first 10 ugly numbers.
	int nthUglyNumber(int n) {
		vector<int> res(1, 1);
		int i2 = 0, i3 = 0, i5 = 0;
		while (res.size() < n) {
			int m2 = res[i2] * 2, m3 = res[i3] * 3, m5 = res[i5] * 5;
			int mn = min(m2, min(m3, m5));
			if (mn == m2) ++i2;
			if (mn == m3) ++i3;
			if (mn == m5) ++i5;
			res.emplace_back(mn);
		}
		return res.back();
	}
	// Super Ugly Number see DPLinear
}
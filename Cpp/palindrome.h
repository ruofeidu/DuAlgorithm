#pragma once
#include "common.h"

namespace Palindrome {
	int int_len(int x) {
		int y = 1; 
		while (x > 10) {
			x /= 10;
			++y;
		}
		return y;
	}

	int pow10(int n)
	{
		static int pow10[10] = {
			1, 10, 100, 1000, 10000, 100000, 1000000, 10000000, 100000000, 1000000000
		};
		return pow10[n];
	}

	// round up the palindrom by the middle digit
	// 192 -> 200
	// 1991 -> 2000
	// 11199111 -> 11200000
	int round_up(int x) {
		int n = int_len(x);
		int inc = pow10((n >> 1) + 1);
		int y = x / inc;
		return (y + 1) * inc;
	}

	int next(int x) {
		auto s = to_string(x);
		int n = (int)s.size();
		bool is_odd = n & 1;
		auto left_half = s.substr(0, n >> 1);
		auto middle = s[(n - 1) >> 1];
		string right_half = left_half;
		reverse(right_half.begin(), right_half.end());
		int y = 0, inc = 0; 
		if (is_odd) {
			inc = pow10(n >> 1);
			
			auto res = left_half + middle + right_half;
			y = atoi(res.c_str());
		}
		else {
			int inc = (int)(1.1 * pow10(n >> 1));
			auto res = left_half + right_half;
			y = atoi(res.c_str());
		}
		if (y > x)
			return y;
		if (middle != '9')
			return y + inc;
		else
			return next(round_up(x));
	}
}
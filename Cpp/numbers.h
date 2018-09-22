#pragma once
#include "common.h"

namespace Numbers {
	int reverse(int x)
	{
		bool minus = (x < 0);
		if (minus) x = -x;
		int ans = 0;
		while (x > 0) {
			if (ans > INT_MAX / 10) return 0;
			ans *= 10;
			ans += x % 10;
			x /= 10;
		}
		if (minus) ans = -ans;
		return ans;
	}

	int Solutions::myAtoi(string str)
	{
		int num = 0;
		int sign = 1;
		const int n = (int)str.size();
		int i = 0;
		while (str[i] == ' ' && i < n) ++i;

		if (str[i] == '+') {
			++i;
		}
		else if (str[i] == '-') {
			sign = -1;
			++i;
		}

		for (; i < n; ++i) {
			if (str[i] < '0' || str[i] > '9') break;
			if (num > INT_MAX / 10 ||
				(num == INT_MAX / 10 && (str[i] - '0') > INT_MAX % 10)) {
				return sign == -1 ? INT_MIN : INT_MAX;
			}
			num = num * 10 + str[i] - '0';
		}
		return num * sign;
	}
}
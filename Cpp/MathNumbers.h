#pragma once
#include "common.h"

class MathNumberMisc {
	// 7. Reverse Integer
	// Given a 32-bit signed integer, reverse digits of an integer.
	// #define INT_MAX     ((1 << 31) - 1)
	// #define INT_MIN     (-INT_MAX - 1)
	// Time: O(n)
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

	// 8. String to Integer (atoi)
	int myAtoi(string str)
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

	// 29. Divide Two Integers
	// Given two integers dividend and divisor, divide two integers without using multiplication, division and mod operator.
	// Return the quotient after dividing dividend by divisor.
	// The integer division should truncate toward zero.
	// [-2^31,  2^31 - 1]
	// For the purpose of this problem, assume that your function returns 2^31 - 1 when the division result overflows.
	int divide(int dividend, int divisor) {
		if (divisor == 0) return INT_MAX;
		typedef unsigned int uint;
		bool sign = (dividend < 0) ^ (divisor < 0);
		uint a = dividend >= 0 ? dividend : -dividend;
		uint b = divisor >= 0 ? divisor : -divisor;
		uint result = 0;
		// 9 / 2 = 4; 
		// 9 = 2 + 7,  1
		// 7 = 4 + 3,  2
		// 3 < 8
		// 3 = 2 + 1,  1
		while (a >= b) {
			uint c = b;
			for (uint i = 0; a >= c && a > 0; ++i, c <<= 1) {
				a -= c;
				result += (uint)(1 << i);
			}
		}
		if (!sign && result > INT_MAX) return INT_MAX;
		if (sign && result > 1u + INT_MAX) return INT_MAX;
		return sign ? (-(int)result) : (result);
	}

	// 38. Count and Say [E]
	// The count-and-say sequence is the sequence of integers with the first five terms as following:
public:
	string countAndSay(int n) {
		string s = "1";
		while (--n) s = countAndSayStr(s);
		return s;
	}

private:
	string countAndSayStr(string s) {
		const int n = (int)s.size();
		int i = 0, cnt = 0;
		string ans = "";
		while (i < n) {
			cnt = 1;
			while (i + 1 < n && s[i + 1] == s[i]) {
				++i;
				++cnt;
			}
			ans += to_string(cnt);
			ans += s[i];
			++i;
		}
		return ans;
	}

	// 50. Pow(x, n)
	// Implement pow(x, n), which calculates x raised to the power n(x^n).
	// Input: 2.00000, 10
	// Output: 1024.00000
	double myPow(double x, int n) {
		if (n == INT_MIN) {
			int m = n / 2;
			double v = myPow(x, -m);
			return 1.0 / v / v;
		}
		if (n < 0) return 1.0 / myPow(x, -n);
		if (n == 0) return 1;
		double v = myPow(x, n / 2);
		if (n % 2 == 0) return v * v;
		return v * v * x;
	}
};

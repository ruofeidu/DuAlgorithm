#pragma once
#include "common.h"

namespace Number2Words {
	string twoDigits(const int& num, const unordered_map<int, string>& lookup) {
		if (lookup.find(num) != lookup.end()) {
			return lookup.find(num)->second;
		}
		return lookup.find((num / 10) * 10)->second + " " + lookup.find(num % 10)->second;
	}

	string join(const vector<string>& strings, const string& delim) {
		if (strings.empty()) {
			return "";
		}
		ostringstream imploded;
		copy(strings.begin(), prev(strings.end()), ostream_iterator<string>(imploded, delim.c_str()));
		return imploded.str() + *prev(strings.end());
	}

	string threeDigits(const int& num, const unordered_map<int, string>& lookup, const string& unit) {
		vector<string> res;
		if (num / 100) {
			res.emplace_back(lookup.find(num / 100)->second + " " + "Hundred");
		}
		if (num % 100) {
			res.emplace_back(twoDigits(num % 100, lookup));
		}
		if (!unit.empty()) {
			res.emplace_back(unit);
		}
		return join(res, " ");
	}

	string numberToWords(int num) {
		if (num == 0) {
			return "Zero";
		}
		const unordered_map<int, string> lookup = {
			{ 0, "Zero" },{ 1, "One" },{ 2, "Two" },
			{ 3, "Three" },{ 4, "Four" },{ 5, "Five" },
			{ 6, "Six" },{ 7, "Seven" },{ 8, "Eight" },
			{ 9, "Nine" },{ 10, "Ten" },{ 11, "Eleven" },
			{ 12, "Twelve" },{ 13, "Thirteen" },{ 14, "Fourteen" },
			{ 15, "Fifteen" },{ 16, "Sixteen" },{ 17, "Seventeen" },
			{ 18, "Eighteen" },{ 19, "Nineteen" },{ 20, "Twenty" },
			{ 30, "Thirty" },{ 40, "Forty" },{ 50, "Fifty" },
			{ 60, "Sixty" },{ 70, "Seventy" },{ 80, "Eighty" },
			{ 90, "Ninety" } };
		const vector<string> unit{ "", "Thousand", "Million", "Billion" };

		vector<string> res;
		int i = 0;
		while (num) {
			const int cur = num % 1000;
			if (num % 1000) {
				res.emplace_back(threeDigits(cur, lookup, unit[i]));
			}
			num /= 1000;
			++i;
		}
		reverse(res.begin(), res.end());
		return join(res, " ");
	}

	// 12. Integer to Roman
	// Roman numerals are represented by seven different symbols: I, V, X, L, C, D and M.
	/*
	Symbol       Value
	I             1
	V             5
	X             10
	L             50
	C             100
	D             500
	M             1000
	*/
	string intToRoman(int num)
	{
		const int radix[] = { 1000, 900, 500, 400, 100, 90, 50, 40, 10, 9, 5, 4, 1 };
		const string symbol[] = { "M", "CM", "D", "CD", "C", "XC", "L", "XL", "X", "IX", "V", "IV", "I" };

		string ans;
		for (size_t i = 0; num > 0; ++i) {
			int count = num / radix[i];
			num %= radix[i];
			for (; count > 0; --count) ans += symbol[i];
		}

		return ans;
	}

	inline int rmap(const char c) {
		switch (c) {
		case 'I': return 1;
		case 'V': return 5;
		case 'X': return 10;
		case 'L': return 50;
		case 'C': return 100;
		case 'D': return 500;
		case 'M': return 1000;
		default: return 0;
		}
	}

	// 13. Roman to Integer
	int romanToInt(string s)
	{
		int ans = 0;
		for (size_t i = 0; i < s.size(); ++i) {
			// if RHS > LHS, subtract
			if (i > 0 && rmap(s[i]) > rmap(s[i - 1])) {
				ans += (rmap(s[i]) - 2 * rmap(s[i - 1]));
			}
			else {
				ans += rmap(s[i]);
			}
		}
		return ans;
	}
};
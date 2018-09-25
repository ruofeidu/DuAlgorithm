#pragma once
#include "common.h"

// 43. Multiply Strings HP Mult
typedef vector<int> bigint;
bigint make_bigint(string const& s);
string to_string(bigint const& n);
bigint operator * (bigint const& x, bigint const& y);

#include "bigint.h"

typedef vector<int> bigint;
bigint make_bigint(string const& s) {
	bigint n;
	transform(s.rbegin(), s.rend(), back_inserter(n), [](char c) {return c - '0'; });
	return n;
}

string to_string(bigint const& n) {
	string s;
	transform(
		find_if(n.rbegin(), prev(n.rend()), [](char c) { return c > '\0'; }),
		n.rend(),
		back_inserter(s),
		[](char c) { return c + '0'; });
	return s;
}

bigint operator * (bigint const& x, bigint const& y) {
	bigint z(x.size() + y.size());
	for (size_t i = 0; i < x.size(); ++i) {
		for (size_t j = 0; j < y.size(); ++j) {
			z[i + j] += x[i] * y[j];
			z[i + j + 1] += z[i + j] / 10;
			z[i + j] %= 10;
		}
	}
	return z;
}

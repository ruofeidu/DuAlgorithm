#pragma once
#include "common.h"

// Avereage: O(N), if a sufficiently large prime number is used for the hash function
// Worst Case: O(M N)
// Space: O(1)
namespace RabinKarp {
	void build(vector<int> &T, const string &s, const string &p, int &P)
	{
		int n = (int)s.size(), m = (int)p.size();
		for (int i = 0; i < m; i++)
			P = P * 256 + p[i];
		for (int i = 0; i < m; i++)
			T[0] = T[0] * 256 + s[i];
		for (int i = 1; i < n - m; i++)
			T[i] = T[i - 1] * 256 + s[i + m] - (1 << (8 * m)) * s[i - 1];
	}

	int RabinKarp(const string &s, const string &p)
	{
		int n = (int)s.size(), m = (int)p.size();
		vector<int> T(m, 0);
		int P = 0;
		build(T, s, p, P);
		for (int i = 0; i < n - m; i++)
			if (T[i] == P && s.substr(i, m) == p)
				return i;
		return -1;
	}
}